#include "Common.h"

namespace Common {

    bool conflict(const Pt& a, const Pt& b, int r) {
        long long dx = a.first - b.first;
        long long dy = a.second - b.second;

        return dx * dx + dy * dy <= 4 * r * r;
    }

    bool onSeparator(const Pt& p, int s, int r) {
        return abs(p.first - s) <= r;
    }

    vector<vector<Pt>> singletons(const vector<Pt>& sep) {
        vector<vector<Pt>> cliques;

        for (int i = 0; i < sep.size(); i++) {
            cliques.push_back({sep[i]});
        }

        return cliques;
    }

    void enumerate(const vector<vector<Pt>>& cliques, int idx,
                vector<Pt>& chosen,
                const vector<Pt>& left,
                const vector<Pt>& right,
                vector<Pt>& best,
                int r,
                const Solver& solveLeft,
                const Solver& solveRight) {

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

            vector<Pt> resL = solveLeft(L);
            vector<Pt> resR = solveRight(R);

            int total = chosen.size() + resL.size() + resR.size();

            if (total > best.size()) {
                best = chosen;
                best.insert(best.end(), resL.begin(), resL.end());
                best.insert(best.end(), resR.begin(), resR.end());
            }

            return;
        }

        // Option 1: take nothing from this clique
        enumerate(cliques, idx + 1, chosen, left, right, best, r, solveLeft, solveRight);

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

                enumerate(cliques, idx + 1, chosen, left, right, best, r, solveLeft, solveRight);

                chosen.pop_back();
            }
        }
    }
}