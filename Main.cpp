#include <bits/stdc++.h>
#include "Algorithms/Basic_Approach.h"
#include "Algorithms/Median_Seperators.h"
#include "Visualization/SvgWriter.h"
#include "Algorithms/Basic_Seperators.h"
#include "Algorithms/Degree_Approach.h"
#include "Algorithms/Degree_Seperators.h"
#include "Algorithms/Clique_Median_Seperator.h"
#include "Algorithms/Degree_Seperators_2.h"
#include "Algorithms/Circle_Clique_Median_Seperators.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n, r;

    // Open the input file from the Data folder
    ifstream fin("Data/input_6.txt");

    if (!fin.is_open()) {
        cerr << "Error: could not open Data/input.txt" << endl;
        return 1;
    }

    fin >> n >> r;

    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; i++) {
        fin >> points[i].first >> points[i].second;
    }

    fin.close();

    // Remove duplicate points
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());

    SvgWriter writer;

    // ---------------- Basic Approach ----------------

    vector<pair<int, int>> result1;
    double time1 = 0.0;

    if(n<35){
        Basic_Approach basic;

        auto start1 = high_resolution_clock::now();
        result1 = basic.solve(points, r);
        auto end1 = high_resolution_clock::now();

        time1 = duration<double, milli>(end1 - start1).count();

        cout << endl << "Basic Approach:" << endl
             << "Maximum Independent Set size: " << result1.size() << endl
             << "Time: " << time1 << " ms" << endl
             << "Points in the independent set:" << endl;

        for (int i = 0; i < result1.size(); i++) {
            cout << result1[i].first << " "
                 << result1[i].second << endl;
        }

        writer.write(points, result1, "Visualization/output/output_basic_approach.svg", r);
    } else {
        cout<<"Basic Approach skipped due to large input size."<<endl;
    }

    // ---------------- Basic Separators ----------------
    Basic_Seperators basics;

    auto start3 = high_resolution_clock::now();
    vector<pair<int, int>> result3 = basics.solve(points, r);
    auto end3 = high_resolution_clock::now();

    double time3 = duration<double, milli>(end3 - start3).count();

    cout << endl << "Basic Separators:" << endl
         << "Maximum Independent Set size: " << result3.size() << endl
         << "Time: " << time3 << " ms" << endl
         << "Points in the independent set:" << endl;

    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i].first << " "
             << result3[i].second << endl;
    }

    writer.write(points, result3, "Visualization/output/output_basic.svg", r);

    // ---------------- Median Separators ----------------
    Median_Seperators median;

    auto start2 = high_resolution_clock::now();
    vector<pair<int, int>> result2 = median.solve(points, r);
    auto end2 = high_resolution_clock::now();

    double time2 = duration<double, milli>(end2 - start2).count();

    cout << endl << "Median Separators:" << endl
         << "Maximum Independent Set size: " << result2.size() << endl
         << "Time: " << time2 << " ms" << endl
         << "Points in the independent set:" << endl;

    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i].first << " "
             << result2[i].second << endl;
    }

    writer.write(points, result2, "Visualization/output/output_median.svg", r);

    // ---------------- Degree Approach ----------------

    vector<pair<int, int>> result4;
    double time4 = 0.0;

    if(n<40){
        Degree_Approach degree;

        auto start4 = high_resolution_clock::now();
        result4 = degree.solve(points, r);
        auto end4 = high_resolution_clock::now();

        time4 = duration<double, milli>(end4 - start4).count();

        cout << endl << "Degree Approach:" << endl
             << "Maximum Independent Set size: " << result4.size() << endl
             << "Time: " << time4 << " ms" << endl
             << "Points in the independent set:" << endl;

        for (int i = 0; i < result4.size(); i++) {
            cout << result4[i].first << " "
                 << result4[i].second << endl;
        }

        writer.write(points, result4, "Visualization/output/output_degree.svg", r);
    } else {
        cout<<"Degree Approach skipped due to large input size."<<endl;
    }

    // ---------------- Degree Separators ----------------

    vector<pair<int, int>> result5;
    double time5 = 0.0;

    if(n<=60){
        Degree_Seperators degreeSep;

        auto start5 = high_resolution_clock::now();
        result5 = degreeSep.solve(points, r);
        auto end5 = high_resolution_clock::now();

        time5 = duration<double, milli>(end5 - start5).count();

        cout << endl << "Degree Separators:" << endl
             << "Maximum Independent Set size: " << result5.size() << endl
             << "Time: " << time5 << " ms" << endl
             << "Points in the independent set:" << endl;

        for (int i = 0; i < result5.size(); i++) {
            cout << result5[i].first << " "
                 << result5[i].second << endl;
        }

        writer.write(points, result5, "Visualization/output/output_degree_sep.svg", r);
    } else {
        cout<<"Degree Separators skipped due to large input size."<<endl;
    }


     // ---------------- Degree Separators 2 ---------------
    vector<pair<int, int>> result6;
    double time6 = 0.0;

    if(n<=60){
        Degree_Seperators_2 degreeSep;

        auto start6 = high_resolution_clock::now();
        result6 = degreeSep.solve(points, r);
        auto end6 = high_resolution_clock::now();

        time6 = duration<double, milli>(end6 - start6).count();

        cout << endl << "Degree Separators:" << endl
             << "Maximum Independent Set size: " << result6.size() << endl
             << "Time: " << time6 << " ms" << endl
             << "Points in the independent set:" << endl;

        for (int i = 0; i < result6.size(); i++) {
            cout << result6[i].first << " "
                 << result6[i].second << endl;
        }

        writer.write(points, result6, "Visualization/output/output_degree_sep.svg", r);
    } else {
        cout<<"Degree Separators 2 skipped due to large input size."<<endl;
    }

    // ---------------- Clique Median Separators ----------------
    Clique_Median_Seperator cliqueMedian;

    auto start7 = high_resolution_clock::now();
    vector<pair<int, int>> result7 = cliqueMedian.solve(points, r);
    auto end7 = high_resolution_clock::now();

    double time7 = duration<double, milli>(end7 - start7).count();

    cout << endl << "Clique Median Separators:" << endl
         << "Maximum Independent Set size: " << result7.size() << endl
         << "Time: " << time7 << " ms" << endl
         << "Points in the independent set:" << endl;

    for (int i = 0; i < result7.size(); i++) {
        cout << result7[i].first << " "
             << result7[i].second << endl;
    }

    writer.write(points, result7, "Visualization/output/output_clique_median.svg", r);

     // ---------------- Circle Clique Median Separators ----------------

    Circle_Clique_Median_Seperator circleCliqueMedian;

    auto start8 = high_resolution_clock::now();
    vector<pair<int, int>> result8 = circleCliqueMedian.solve(points, r);
    auto end8 = high_resolution_clock::now();

    double time8 = duration<double, milli>(end8 - start8).count();

    cout << endl << "Circle Clique Median Separators:" << endl
         << "Maximum Independent Set size: " << result8.size() << endl
         << "Time: " << time8 << " ms" << endl
         << "Points in the independent set:" << endl;

    for (int i = 0; i < result8.size(); i++) {
        cout << result8[i].first << " "
             << result8[i].second << endl;
    }

    writer.write(points, result8, "Visualization/output/output_circle_clique_median.svg", r);

    // ---------------- Time Comparison ----------------
    cout << endl << "==== Time Comparison ====" << endl;
    cout << left << setw(22) << "Algorithm"
         << setw(12) << "Set size"
         << "Time (ms)" << endl;
    cout << string(46, '-') << endl;

    cout << left << setw(22) << "Basic Approach"
         << setw(12) << result1.size()
         << time1 << endl;

    cout << left << setw(22) << "Basic Separators"
         << setw(12) << result3.size()
         << time3 << endl;

    cout << left << setw(22) << "Median Separators"
         << setw(12) << result2.size()
         << time2 << endl;

    cout << left << setw(22) << "Degree Approach"
         << setw(12) << result4.size()
         << time4 << endl;

    cout << left << setw(22) << "Degree Separators"
         << setw(12) << result5.size()
         << time5 << endl;

     cout << left << setw(22) << "Degree Separators 2"
         << setw(12) << result6.size()
         << time6 << endl;

    cout << left << setw(22) << "Clique Median Sep."
         << setw(12) << result7.size()
         << time7 << endl;

     cout << left << setw(22) << "Cir-Cliq-Med Sep."
         << setw(12) << result8.size()
         << time8 << endl;

    return 0;
}