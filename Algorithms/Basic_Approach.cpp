#include "Basic_Approach.h"
#include <bits/stdc++.h>

using namespace std;

namespace {

int counter;
int maximalIndependentSet;
vector<vector<int>> g;
vector<bool> indep;

void independent(int v, int n, int r) {
    indep[v] = true;
    
    for(int i=0; i<g[v].size(); i++) {
        if(indep[g[v][i]]) {
            indep[v] = false;
            return;
        }
    }


    counter++;
    maximalIndependentSet = max(maximalIndependentSet, counter);


    for (int j = v + 1; j < n; j++) {
        independent(j, n, r);
    }

    indep[v] = false;
    counter--;


    if (v + 1 < n) {
        independent(v + 1, n, r);
    }
}

} // namespace

int Basic_Approach::solve(const vector<int>& x,
                          const vector<int>& y, int n, int r) {

    g.assign(n, vector<int>());
    indep.assign(n, false);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = x[i] - x[j];
            int dy = y[i] - y[j];

            if (dx * dx + dy * dy <= 4*r*r) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    counter = 0;
    maximalIndependentSet = 0;

    if (n > 0) {
        independent(0, n, r);
    }

    return maximalIndependentSet;
}
