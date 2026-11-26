#include "Clique_Median_Seperator.h"
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
// Points are sorted by the coordinate along the separator line and grouped greedily.
vector<vector<Pt>> buildCliques(vector<Pt> sep, int r) {
    sort(sep.begin(), sep.end(), [](const Pt& a, const Pt& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    vector<vector<Pt>> cliques;

    for (int i = 0; i < sep.size(); i++) {
        bool placed = false;

        if (!cliques.empty()) {
            vector<Pt>& cur = cliques.back();
            bool ok = true;

            for (int j = 0; j < cur.size(); j++) {
                if (!conflict(sep[i], cur[j], r)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                cur.push_back(sep[i]);
                placed = true;
            }
        }

        if (!placed) {
            cliques.push_back({sep[i]});
        }
    }

    return cliques;
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

    Solver rec = [&](const vector<Pt>& v) { return solve(v, r); };

    enumerate(cliques, 0, chosen, left, right, best, r, rec, rec);

    return best;
}

}

vector<pair<int, int>> Clique_Median_Seperator::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;


    return ::solve(points, r);
}