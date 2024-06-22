#pragma once

#include <cmath>
#include "constants.hpp"
#include "geometry.hpp"

namespace rc
{
    constexpr bool float_equal(float l, float r)
    {
        return std::abs(l - r) < constants::epsilon;
    }

    constexpr int round(float f)
    {
        return static_cast<int>(std::round(f));
    }

    bool is_horizontal(Vertex const& from, Vertex const& to);
    bool is_vertical(Vertex const& from, Vertex const& to);
}
