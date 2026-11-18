#ifndef SVG_WRITER_H
#define SVG_WRITER_H

#include <vector>
#include <utility>
#include <string>
using namespace std;

class SvgWriter {
public:
    void write(const vector<pair<int, int>>& points,
               const vector<pair<int, int>>& independentSet,
               const string& filename,
                int r);
};

#endif