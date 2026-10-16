#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> Pt;

// Circles of radius 1 intersect if the distance between centers is < 2.
// Set to true if tangent circles (distance == 2) should also count as intersecting.

bool conflict(const Pt& a, const Pt& b) {
    int dx = a.first - b.first, dy = a.second - b.second;
    if (dx * dx + dy * dy <= 4.0){
        return true;
    } else {
        return false;
    }
}

bool onSeparator(const Pt& p, int s) {
    return abs(p.first - s) <= 1;
}

vector<Pt> solve(const vector<Pt>& pts, int lo, int hi);

void enumerate(const vector<Pt>& sep, int idx, vector<Pt>& chosen, const vector<Pt>& left, const vector<Pt>& right, int lo, int hi, int s, vector<Pt>& best);

void enumerate(const vector<Pt>& sep, int idx, vector<Pt>& chosen, const vector<Pt>& left, const vector<Pt>& right, int lo, int hi, int s, vector<Pt>& best) {
    if (idx == sep.size()) {
        vector<Pt> L, R;
        for (int i = 0; i < left.size(); i++) {
            bool ok = true;
            for (int j = 0; j < chosen.size(); j++) {
                if (conflict(left[i], chosen[j])) {
                    ok = false;
                    break;
                }
            }
            if (ok) L.push_back(left[i]);
        }
        for (int i = 0; i < right.size(); i++) {
            bool ok = true;
            for (int j = 0; j < chosen.size(); j++) {
                if (conflict(right[i], chosen[j])) {
                    ok = false;
                    break;
                }
            }
            if (ok) R.push_back(right[i]);
        }
        vector<Pt> resL = solve(L, lo, s - 2);
        vector<Pt> resR = solve(R, s + 2, hi);

        int total = chosen.size() + resL.size() + resR.size();
        if (total > best.size()) {
            best = chosen;
            best.insert(best.end(), resL.begin(), resL.end());
            best.insert(best.end(), resR.begin(), resR.end());
        }
        return;
    }

    // Option 1: don't include sep[idx]
    enumerate(sep, idx + 1, chosen, left, right, lo, hi, s, best);

    // Option 2: include sep[idx] (only if it doesn't intersect already chosen ones)
    bool ok = true;
    for (int i=0; i<chosen.size(); i++) {
        if (conflict(sep[idx], chosen[i])) {
            ok = false;
            break;
        }
    }

    if (ok) {
        chosen.push_back(sep[idx]);
        enumerate(sep, idx + 1, chosen, left, right, lo, hi, s, best);
        chosen.pop_back();
    }
}


int median(const vector<Pt>& pts) {
    return pts[pts.size() / 2].first;
}

vector<Pt> solve(const vector<Pt>& pts, int lo, int hi) {
    if (pts.empty() || lo > hi) return {};

    int s = median(pts);    
    vector<Pt> sep, left, right;
    for (int i = 0; i < pts.size(); i++) {
        if (onSeparator(pts[i], s)) sep.push_back(pts[i]);
        else if (pts[i].first < s)  left.push_back(pts[i]);
        else                        right.push_back(pts[i]);
    }

    vector<Pt> best, chosen;
    enumerate(sep, 0, chosen, left, right, lo, hi, s, best);
    return best;
}


int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;
    cout << "Enter the coordinates of the points (x y):" << endl;

    vector<Pt> g(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[i] = make_pair(x, y);
    }
    sort(g.begin(), g.end());
    g.erase(unique(g.begin(), g.end()), g.end());   

    vector<Pt> ans = solve(g, 0, 16);

    cout << "Maximum independent set size: " << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for (const Pt& p : ans) cout << p.first << " " << p.second << endl;
    return 0;
}
