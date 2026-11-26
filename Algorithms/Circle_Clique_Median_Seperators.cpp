#include "Circle_Clique_Median_Seperators.h"
#include "Common.h"
#include <bits/stdc++.h>

using namespace std;
using namespace Common;

namespace {

typedef pair<int, int> Pt;


int median(const vector<Pt>& pts) {
    return pts[pts.size() / 2].first;
}

vector<Pt> solve(const vector<Pt>& pts, int r);

// Split separator points into cliques (every pair inside a clique conflicts),
// so at most one point per clique can be in an independent set.
// Take the first point not yet in any clique as a center, and put into its clique
// every unused point whose center lies inside the circle of diameter 2r (radius r)
// around it. Two such points are at most 2r apart, so they always conflict.
vector<vector<Pt>> buildCliques1(vector<Pt> sep, int r) {
    sort(sep.begin(), sep.end(), [](const Pt& a, const Pt& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    vector<vector<Pt>> cliques;
    vector<bool> used(sep.size(), false);

    for (int i = 0; i < sep.size(); i++) {
        if (!used[i]){

            vector<Pt> clique;
            clique.push_back(sep[i]);
            used[i] = true;

            for (int j = i + 1; j < sep.size(); j++) {
                if (sep[j].second - sep[i].second >= r) {
                    break;
                }

                if (!used[j]){
                    long long dx = sep[j].first - sep[i].first;
                    long long dy = sep[j].second - sep[i].second;

                    if (dx * dx + dy * dy <= r * r) {
                        clique.push_back(sep[j]);
                        used[j] = true;
                    }
                }
            }
            cliques.push_back(clique);
        }
    }

    return cliques;
}

vector<vector<Pt>> buildCliques(vector<Pt> sep, int r) {
    sort(sep.begin(), sep.end(), [](const Pt& a, const Pt& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    vector<vector<Pt>> cliques;
    vector<bool> used(sep.size(), false);

    for (int i = 0; i < sep.size(); i++) {
        if (used[i]) continue;

        vector<Pt> clique;
        clique.push_back(sep[i]);
        used[i] = true;

        long long cx = sep[i].first;
        long long cy = sep[i].second + 86 * r / 100;

        for (int j = i + 1; j < sep.size(); j++) {
            // sorted by second coordinate, so nothing further can be inside the circle
            if (sep[j].second - cy >= r) break;

            if (used[j]) continue;

            long long dx = sep[j].first - cx;
            long long dy = sep[j].second - cy;

            if (dx * dx + dy * dy < r * r) {
                clique.push_back(sep[j]);
                used[j] = true;
            }
        }

        cliques.push_back(clique);
    }

    return cliques;
}

void enumerate(const vector<vector<Pt>>& cliques, int idx,
               vector<Pt>& chosen,
               const vector<Pt>& left,
               const vector<Pt>& right,
               vector<Pt>& best,
               int r) {

    if (idx == cliques.size()) {
        vector<Pt> L, R;

        for (int i = 0; i < left.size(); i++) {
            bool ok = true;

            for (int j = 0; j < chosen.size(); j++) {
                if (conflict(left[i], chosen[j], r)) {
                    ok = false;
                    break;
                }
            }

            if (ok) L.push_back(left[i]);
        }

        for (int i = 0; i < right.size(); i++) {
            bool ok = true;

            for (int j = 0; j < chosen.size(); j++) {
                if (conflict(right[i], chosen[j], r)) {
                    ok = false;
                    break;
                }
            }

            if (ok) R.push_back(right[i]);
        }

        vector<Pt> resL = solve(L, r);
        vector<Pt> resR = solve(R, r);

        int total = chosen.size() + resL.size() + resR.size();

        if (total > best.size()) {
            best = chosen;
            best.insert(best.end(), resL.begin(), resL.end());
            best.insert(best.end(), resR.begin(), resR.end());
        }

        return;
    }

    // Option 1: take nothing from this clique
    enumerate(cliques, idx + 1, chosen, left, right, best, r);

    // Option 2: take exactly one point from this clique
    const vector<Pt>& clique = cliques[idx];

    for (int k = 0; k < clique.size(); k++) {
        bool ok = true;

        for (int i = 0; i < chosen.size(); i++) {
            if (conflict(clique[k], chosen[i], r)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            chosen.push_back(clique[k]);

            enumerate(cliques, idx + 1, chosen, left, right, best, r);

            chosen.pop_back();
        }
    }
}

vector<Pt> solve(const vector<Pt>& pts, int r) {
    if (pts.empty()) return {};

    int s = median(pts);

    vector<Pt> sep, left, right;

    for (int i = 0; i < pts.size(); i++) {
        if (onSeparator(pts[i], s, r)) {
            sep.push_back(pts[i]);
        }
        else if (pts[i].first < s) {
            left.push_back(pts[i]);
        }
        else {
            right.push_back(pts[i]);
        }
    }

    vector<vector<Pt>> cliques = buildCliques(sep, r);

    vector<Pt> best, chosen;

    enumerate(cliques, 0, chosen, left, right, best, r);

    return best;
}

}

vector<pair<int, int>> Circle_Clique_Median_Seperator::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;


    return ::solve(points, r);
}