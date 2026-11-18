#include "Basic_Seperators.h"
#include <bits/stdc++.h>

using namespace std;

namespace {

typedef pair<int, int> Pt;

bool conflict(const Pt& a, const Pt& b, int r) {
    long long dx = a.first - b.first;
    long long dy = a.second - b.second;

    return dx * dx + dy * dy <= 4 * r * r;
}

bool onSeparator(const Pt& p, int s, int r) {
    return abs(p.first - s) <= r;
}

vector<Pt> solve(const vector<Pt>& pts, int r, int a, int b);

void enumerate(const vector<Pt>& sep, int idx,
               vector<Pt>& chosen,
               const vector<Pt>& left,
               const vector<Pt>& right,
               vector<Pt>& best,
               int r, int a, int b, int s) {

    if (idx == sep.size()) {
        vector<Pt> L, R;

        for (const Pt& p : left) {
            bool ok = true;

            for (const Pt& c : chosen) {
                if (conflict(p, c, r)) {
                    ok = false;
                    break;
                }
            }

            if (ok) L.push_back(p);
        }

        for (const Pt& p : right) {
            bool ok = true;

            for (const Pt& c : chosen) {
                if (conflict(p, c, r)) {
                    ok = false;
                    break;
                }
            }

            if (ok) R.push_back(p);
        }

        vector<Pt> resL = solve(L, r, a, s - r - 1);
        vector<Pt> resR = solve(R, r, s + r + 1, b);

        int total = chosen.size() + resL.size() + resR.size();

        if (total > best.size()) {
            best = chosen;
            best.insert(best.end(), resL.begin(), resL.end());
            best.insert(best.end(), resR.begin(), resR.end());
        }

        return;
    }

    // Option 1: exclude current separator point
    enumerate(sep, idx + 1, chosen,
              left, right, best, r, a, b, s);

    // Option 2: include current separator point
    bool ok = true;

    for (const Pt& p : chosen) {
        if (conflict(sep[idx], p, r)) {
            ok = false;
            break;
        }
    }

    if (ok) {
        chosen.push_back(sep[idx]);

        enumerate(sep, idx + 1, chosen,
                  left, right, best, r, a, b, s);

        chosen.pop_back();
    }
}

vector<Pt> solve(const vector<Pt>& pts, int r, int a, int b) {
    if (pts.empty() || a > b) return {};

    // Basic separator: midpoint of the current interval
    int s = a + (b - a) / 2;

    vector<Pt> sep, left, right;

    for (const Pt& p : pts) {
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

    enumerate(sep, 0, chosen,
              left, right, best, r, a, b, s);

    return best;
}

}

vector<pair<int, int>> Basic_Seperators::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());

    if (points.empty()) return {};

    int minX = points.front().first;
    int maxX = points.back().first;

    return ::solve(points, r, minX, maxX);
}