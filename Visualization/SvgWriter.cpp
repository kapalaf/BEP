
#include "SvgWriter.h"
#include <bits/stdc++.h>

using namespace std;

void SvgWriter::write(
    const vector<pair<int, int>>& points,
    const vector<pair<int, int>>& independentSet,
    const string& filename,
    int r) {

    if (points.empty()) {
        cout << "No points to display!" << endl;
        return;
    }

    if (r <= 0) {
        cout << "Radius must be positive!" << endl;
        return;
    }

    // Find coordinate boundaries
    int minX = points[0].first;
    int maxX = points[0].first;
    int minY = points[0].second;
    int maxY = points[0].second;

    for (const auto& p : points) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
        minY = min(minY, p.second);
        maxY = max(maxY, p.second);
    }

    // Add space around the drawing, including circle radius
    int padding = static_cast<int>(r) + 2;

    minX -= padding;
    maxX += padding;
    minY -= padding;
    maxY += padding;

    // Pixels per coordinate unit
    const double U = 40.0;

    // Convert mathematical radius to SVG pixels
    const double svgRadius = r * U;

    double width = (maxX - minX) * U;
    double height = (maxY - minY) * U;

    // Convert mathematical coordinates to SVG coordinates
    auto X = [&](double x) {
        return (x - minX) * U;
    };

    auto Y = [&](double y) {
        return height - (y - minY) * U;
    };

    // Create SVG file
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Could not create SVG file!" << endl;
        return;
    }

    file << fixed << setprecision(1);

    file << "<svg xmlns='http://www.w3.org/2000/svg' "
         << "width='" << width << "' height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "'>\n";

    // White background
    file << "<rect width='100%' height='100%' fill='white'/>\n";

    // Draw grey vertical grid lines
    for (int x = minX; x <= maxX; x++) {
        file << "<line x1='" << X(x) << "' y1='0' "
             << "x2='" << X(x) << "' y2='" << height
             << "' stroke='#d3d3d3' stroke-width='1'/>\n";
    }

    // Draw grey horizontal grid lines
    for (int y = minY; y <= maxY; y++) {
        file << "<line x1='0' y1='" << Y(y) << "' "
             << "x2='" << width << "' y2='" << Y(y)
             << "' stroke='#d3d3d3' stroke-width='1'/>\n";
    }

    // Draw all points as circles with radius r
    for (const auto& p : points) {

        double x = X(p.first);
        double y = Y(p.second);

        // Check whether point belongs to maximum independent set
        bool selected = find(
            independentSet.begin(),
            independentSet.end(),
            p
        ) != independentSet.end();

        // Green for selected points, grey for other points
        const char* color = selected ? "#1f8a5b" : "#808080";

        // Draw circle with radius r coordinate units
        file << "<circle cx='" << x
             << "' cy='" << y
             << "' r='" << svgRadius
             << "' fill='" << color
             << "' fill-opacity='0.15'"
             << " stroke='" << color
             << "' stroke-width='1.5'/>\n";

        // Draw center of the circle
        file << "<circle cx='" << x
             << "' cy='" << y
             << "' r='3' fill='" << color << "'/>\n";

        // Display point coordinates
        file << "<text x='" << x + 8
             << "' y='" << y - 8
             << "' font-size='12' fill='black'>("
             << p.first << "," << p.second
             << ")</text>\n";
    }

    // Finish SVG
    file << "</svg>\n";

    file.close();

    cout << "Visualization saved to: " << filename << endl;
}
