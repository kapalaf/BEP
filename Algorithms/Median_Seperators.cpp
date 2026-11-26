#include "Median_Seperators.h"
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

    vector<Pt> best, chosen;

    Solver rec = [&](const vector<Pt>& v) { return solve(v, r); };

    enumerate(singletons(sep), 0, chosen, left, right, best, r, rec, rec);

    return best;
}

}

vector<pair<int, int>> Median_Seperators::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;

    return ::solve(points, r);
}