#include "Degree_Seperators.h"
#include "Common.h"
#include <bits/stdc++.h>

using namespace std;
using namespace Common;

namespace {

typedef pair<int, int> Pt;

const double PI = acos(-1.0);
const double EPS = 1e-9;

// Rank of every disk, computed once on the full input 
map<Pt, int> rankOf;

// Signed distance of p from the line through c with the given angle
double signedDist(const Pt& p, const Pt& c, double angle) {
    double dx = p.first - c.first;
    double dy = p.second - c.second;

    return -dx * sin(angle) + dy * cos(angle);
}

// Disk with the best (smallest) rank among the current points
Pt pivot(const vector<Pt>& pts) {
    Pt best = pts[0];

    for (int i = 1; i < pts.size(); i++) {
        if (rankOf[pts[i]] < rankOf[best]) {
            best = pts[i];
        }
    }

    return best;
}

vector<Pt> solve(const vector<Pt>& pts, int r);

void enumerate(const vector<Pt>& sep, int idx,
               vector<Pt>& chosen,
               const vector<Pt>& left,
               const vector<Pt>& right,
               vector<Pt>& best,
               int r) {

    if (idx == sep.size()) {
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

    // Option 1: exclude the current point
    enumerate(sep, idx + 1, chosen, left, right, best, r);

    // Option 2: include the current point
    bool ok = true;

    for (int i = 0; i < chosen.size(); i++) {
        if (conflict(sep[idx], chosen[i], r)) {
            ok = false;
            break;
        }
    }

    if (ok) {
        chosen.push_back(sep[idx]);

        enumerate(sep, idx + 1, chosen, left, right, best, r);

        chosen.pop_back();
    }
}

vector<Pt> solve(const vector<Pt>& pts, int r) {
    if (pts.empty()) return {};

    // The separator goes through the disk with the most neighbours
    Pt c = pivot(pts);

    // Try every angle from 0 to 179 degrees
    int bestDeg = 0;
    int bestSep = INT_MAX;
    int bestDiff = INT_MAX;

    for (int deg = 0; deg < 180; deg++) {
        double angle = deg * PI / 180.0;

        int sepCount = 0, leftCount = 0, rightCount = 0;

        for (int i = 0; i < pts.size(); i++) {
            double d = signedDist(pts[i], c, angle);

            if (fabs(d) <= r + EPS) {
                sepCount++;
            } else if (d < 0) {
                leftCount++;
            } else {
                rightCount++;
            }
        }

        int diff = abs(leftCount - rightCount);

        if (sepCount < bestSep || (sepCount == bestSep && diff < bestDiff)) {
            bestSep = sepCount;
            bestDiff = diff;
            bestDeg = deg;
        }
    }

    double angle = bestDeg * PI / 180.0;

    vector<Pt> sep, left, right;

    for (int i = 0; i < pts.size(); i++) {
        double d = signedDist(pts[i], c, angle);

        if (fabs(d) <= r + EPS) {
            sep.push_back(pts[i]);
        }
        else if (d < 0) {
            left.push_back(pts[i]);
        }
        else {
            right.push_back(pts[i]);
        }
    }

    vector<Pt> best, chosen;

    enumerate(sep, 0, chosen, left, right, best, r);

    return best;
}

}

vector<pair<int, int>> Degree_Seperators::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;

    int n = points.size();

    if (n == 0) {return {};}

    // ---- Preprocessing: rank disks by number of neighbours ----
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (conflict(points[i], points[j], r)) {
                degree[i]++;
                degree[j]++;
            }
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++){
        order[i] = i;
    }

    stable_sort(order.begin(), order.end(), [&](int a, int b) {
        return degree[a] > degree[b];
    });

    rankOf.clear();
    for (int i = 0; i < n; i++) {
        rankOf[points[order[i]]] = i;
    }


    return ::solve(points, r);
}