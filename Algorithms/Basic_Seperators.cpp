#include "Basic_Seperators.h"
#include "Common.h"
#include <bits/stdc++.h>

using namespace std;
using namespace Common;

namespace {

typedef pair<int, int> Pt;


vector<Pt> solve(const vector<Pt>& pts, int r, int a, int b);

vector<Pt> solve(const vector<Pt>& pts, int r, int a, int b) {
    if (pts.empty() || a > b) {return {};}

    // Basic separator: midpoint of the current interval
    int s = a + (b - a) / 2;

    vector<Pt> sep, left, right;

    for (int i = 0; i < pts.size(); i++) {
        const Pt& p = pts[i];
        if (onSeparator(p, s, r)) {
            sep.push_back(p);
        }
        else if (p.first < s) {
            left.push_back(p);
        }
        else {
            right.push_back(p);
        }
    }

    // Base case: avoid infinite recursion
    if (left.size() == pts.size() || right.size() == pts.size()) {
        return pts;
    }

    vector<Pt> best, chosen;

    Solver recL = [&](const vector<Pt>& v) { return solve(v, r, a, s - r - 1); };
    Solver recR = [&](const vector<Pt>& v) { return solve(v, r, s + r + 1, b); };

    enumerate(singletons(sep), 0, chosen, left, right, best, r, recL, recR);

    return best;
}

}

vector<pair<int, int>> Basic_Seperators::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;


    if (points.empty()) {return {};}

    int minX = points.front().first;
    int maxX = points.back().first;

    return ::solve(points, r, minX, maxX);
}