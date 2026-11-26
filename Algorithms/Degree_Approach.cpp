
#include "Degree_Approach.h"
#include "Common.h"
#include <bits/stdc++.h>

using namespace Common;
using namespace std;

namespace {

typedef pair<int, int> Pt;

int degreeCounter;
int degreeMaxIndependentSet;

vector<vector<int>> g;
vector<bool> indep;
vector<Pt> points;
vector<Pt> degreeBestSet;

// Recursive search for the maximum independent set
void degreeIndependent(int v, int n) {

    // All vertices have been considered
    if (v == n) {

        if (degreeCounter > degreeMaxIndependentSet) {
            degreeMaxIndependentSet = degreeCounter;

            degreeBestSet.clear();

            for (int i = 0; i < n; i++) {
                if (indep[i]){
                    degreeBestSet.push_back(points[i]);
                }
            }
        }

        return;
    }

    // Try including vertex v
    bool canInclude = true;

    for (int i = 0; i < g[v].size(); i++) {
        int neighbor = g[v][i];
        if (indep[neighbor]) {
            canInclude = false;
            break;
        }
    }

    if (canInclude) {
        indep[v] = true;
        degreeCounter++;

        degreeIndependent(v + 1, n);

        // Backtrack
        indep[v] = false;
        degreeCounter--;
    }

    // Try excluding vertex v
    degreeIndependent(v + 1, n);
}

} 

vector<pair<int, int>> Degree_Approach::solve(
    const vector<pair<int, int>>& pts, int r) {

    points = pts;

    int n = points.size();

    if (n == 0)
        return {};

    // Calculate the degree of each point
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (conflict(points[i], points[j], r)) {
                degree[i]++;
                degree[j]++;
            }
        }
    }

    // Sort points by degree (highest degree first)
    vector<int> order(n);

    for (int i = 0; i < n; i++){
        order[i] = i;
    }

    stable_sort(order.begin(), order.end(), [&](int a, int b) {
            return degree[a] > degree[b];
        }
    );

    vector<Pt> sorted(n);

    for (int i = 0; i < n; i++){
        sorted[i] = points[order[i]];
    }
    points = sorted;

    // Build the conflict graph
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

    // Initialize search variables
    degreeCounter = 0;
    degreeMaxIndependentSet = 0;
    degreeBestSet.clear();

    // Search for the maximum independent set
    degreeIndependent(0, n);

    return degreeBestSet;
}
