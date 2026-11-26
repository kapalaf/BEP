#include "Basic_Approach.h"
#include "Common.h"
#include <bits/stdc++.h>

using namespace Common;
using namespace std;

namespace {

typedef pair<int, int> Pt;

int counter;
int maximalIndependentSet;
vector<vector<int>> g;
vector<bool> indep;
vector<Pt> points;
vector<Pt> bestSet;

void independent(int v, int n, int r) {
    indep[v] = true;

    for (int i = 0; i < g[v].size(); i++) {
        if (indep[g[v][i]]) {
            indep[v] = false;
            return;
        }
    }

    counter++;

    if (counter > maximalIndependentSet) {
        maximalIndependentSet = counter;

        // Save the current independent set
        bestSet.clear();
        for (int i = 0; i < n; i++) {
            if (indep[i]) bestSet.push_back(points[i]);
        }
    }

    for (int j = v + 1; j < n; j++) {
        independent(j, n, r);
    }

    indep[v] = false;
    counter--;

    if (v + 1 < n) {
        independent(v + 1, n, r);
    }
}

} 

vector<pair<int, int>> Basic_Approach::solve(
    const vector<pair<int, int>>& pts, int r) {

    points = pts;

    int n = points.size();

    if (n == 0) {return {};}

    g.assign(n, vector<int>());
    indep.assign(n, false);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (conflict(points[i], points[j], r)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    counter = 0;
    maximalIndependentSet = 0;
    bestSet.clear();

    independent(0, n, r);

    return bestSet;
}