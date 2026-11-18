#include <bits/stdc++.h>
#include "Algorithms/Basic_Approach.h"
#include "Algorithms/Median_Seperators.h"
#include "Visualization/SvgWriter.h"
#include "Algorithms/Basic_Seperators.h"

using namespace std;

int main() {
    int n, r;

    cout << "Enter the number of points: ";
    cin >> n;

    cout << "Enter the radius of the disks: ";
    cin >> r;

    vector<pair<int, int>> points(n);

    cout << "Enter the coordinates of the points (x y):" << endl;

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    // Remove duplicate points
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());

    // Prepare input for Basic Approach
    vector<int> x, y;

    for (int i = 0; i < points.size(); i++) {
        x.push_back(points[i].first);
        y.push_back(points[i].second);
    }

    // Run Basic Approach
    Basic_Approach basic;

    int result1 = basic.solve(x, y, points.size(), r);

    cout << endl << "Basic Approach:" << endl << "Maximum Independent Set size: " << result1 << endl;

    // Run Basic Separators
    Basic_Seperators basics;

    vector<pair<int, int>> result3 = basics.solve(points, r);
    cout << endl << "Basic Separators:" << endl
        << "Maximum Independent Set size: " << result3.size() << endl
        << "Points in the independent set:" << endl;

    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i].first << " "
            << result3[i].second << endl;
    }

    SvgWriter writer;

    writer.write(points, result3, "Visualization/output/output_basic.svg", r);


    // Run Median Separators
    Median_Seperators median;

    vector<pair<int, int>> result2 = median.solve(points, r);

    cout << endl << "Median Separators:" << endl << "Maximum Independent Set size: " << result2.size() << endl << "Points in the independent set:" << endl;

    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i].first << " "
             << result2[i].second << endl;
    }


    writer.write(points, result2, "Visualization/output/output_median.svg", r);

    return 0;
}