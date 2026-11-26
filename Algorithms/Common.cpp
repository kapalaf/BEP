#include "Common.h"

namespace Common {

    bool conflict(const Pt& a, const Pt& b, int r) {
        long long dx = a.first - b.first;
        long long dy = a.second - b.second;

        return dx * dx + dy * dy <= 4LL * r * r;
    }

    bool onSeparator(const Pt& p, int s, int r) {
        return abs(p.first - s) <= r;
    }

}