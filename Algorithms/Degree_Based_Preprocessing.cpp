#include "Degree_Based_Preprocessing.h"
#include "Median_Seperators.h"   
#include "Common.h"
#include <bits/stdc++.h>

using namespace Common;
using namespace std;

using namespace std;

namespace {

typedef pair<int, int> Pt;


// Decides for every high degree disk (high[idx], high[idx + 1], ...)
// whether it is in the set or not. When all of them are decided,
// the rest of the disks is solved by the inner algorithm.
void branch(const vector<Pt>& pts,
            const vector<vector<int> >& adj,
            const vector<int>& high,
            int idx,
            vector<bool> removed,      // copy on purpose, so we do not need to undo changes
            vector<Pt>& chosen,
            vector<Pt>& best,
            int r) {

    if (idx == high.size()) {
        // Collect the disks that are still left
        vector<Pt> rest;

        for (int i = 0; i < pts.size(); i++) {
            if (!removed[i]) rest.push_back(pts[i]);
        }

        // Solve the rest with the inner algorithm
        Median_Seperators inner;                    // change this line to swap the inner solver
        vector<Pt> res = inner.solve(rest, r);      // and this one

        int total = chosen.size() + res.size();

        if (total > best.size()) {
            best = chosen;
            best.insert(best.end(), res.begin(), res.end());
        }

        return;
    }

    int v = high[idx];

    // v was already removed because one of its neighbors was chosen
    if (removed[v]) {
        branch(pts, adj, high, idx + 1, removed, chosen, best, r);
        return;
    }

    // Option 1: exclude v (remove only v)
    {
        vector<bool> removed2 = removed;
        removed2[v] = true;

        branch(pts, adj, high, idx + 1, removed2, chosen, best, r);
    }

    // Option 2: include v (remove v and all of its neighbors)
    {
        vector<bool> removed2 = removed;
        removed2[v] = true;

        for (int i = 0; i < adj[v].size(); i++) {
            removed2[adj[v][i]] = true;
        }

        chosen.push_back(pts[v]);

        branch(pts, adj, high, idx + 1, removed2, chosen, best, r);

        chosen.pop_back();
    }
}

}

vector<pair<int, int>> Degree_Based_Preprocessing::solve(
    const vector<pair<int, int>>& pts, int r) {

    // ---------------- Constants to play with ----------------
    const double DEGREE_FACTOR   = 10.0; // disk is "high degree" if degree > DEGREE_FACTOR * average degree
    const int    MAX_HIGH_DEGREE = 20;   // max number of disks we branch on (cost is 2^this)
    // --------------------------------------------------------

    int n = pts.size();

    if (n == 0) return {};

    // Build the conflict graph (two disks conflict if the centers are closer than 2r)
    vector<vector<int> > adj(n);
    long long edgeCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (conflict(pts[i], pts[j], r)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
                edgeCount++;
            }
        }
    }

    double avgDegree = 2.0 * edgeCount / n;
    double threshold = DEGREE_FACTOR * avgDegree;

    // Find the high degree disks, stored as (degree, index)
    vector<pair<int, int> > candidates;

    for (int i = 0; i < n; i++) {
        if (adj[i].size() > threshold) {
            candidates.push_back(make_pair((int)adj[i].size(), i));
        }
    }

    // Biggest degree first
    sort(candidates.begin(), candidates.end(), greater<pair<int, int> >());

    vector<int> high;

    for (int i = 0; i < candidates.size() && i < MAX_HIGH_DEGREE; i++) {
        high.push_back(candidates[i].second);
    }

    // Nothing to preprocess, just run the inner algorithm
    if (high.empty()) {
        Median_Seperators inner;                    // change this line to swap the inner solver
        return inner.solve(pts, r);                 // and this one
    }

    vector<bool> removed(n, false);
    vector<Pt> chosen, best;

    branch(pts, adj, high, 0, removed, chosen, best, r);

    return best;
}