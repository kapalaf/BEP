#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>

namespace Common {

    using Pt = std::pair<int, int>;

    bool conflict(const Pt& a, const Pt& b, int r);

    bool onSeparator(const Pt& p, int s, int r);

}

#endif