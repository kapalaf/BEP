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

    enumerate(sep, 0, chosen, left, right, best, r);

    return best;
}

}

vector<pair<int, int>> Median_Seperators::solve(
    const vector<pair<int, int>>& pts, int r) {

    vector<Pt> points = pts;

    return ::solve(points, r);
}