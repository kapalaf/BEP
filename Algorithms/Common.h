#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>

using namespace std;

namespace Common {

    using Pt = std::pair<int, int>;

    bool conflict(const Pt& a, const Pt& b, int r);

    bool onSeparator(const Pt& p, int s, int r);

    typedef function<vector<Pt>(const vector<Pt>&)> Solver;

    vector<vector<Pt>> singletons(const vector<Pt>& sep);

    void enumerate(const vector<vector<Pt>>& cliques, int idx,
                vector<Pt>& chosen,
                const vector<Pt>& left,
                const vector<Pt>& right,
                vector<Pt>& best,
                int r,
                const Solver& solveLeft,
                const Solver& solveRight);

}

#endif