#include "utility.hpp"

namespace rc
{
    bool is_horizontal(Vertex const& from, Vertex const& to)
    {
        return float_equal(std::round(from[0]), std::round(to[0]));
    }

    bool is_vertical(Vertex const& from, Vertex const& to)
    {
        return float_equal(std::round(from[1]), std::round(to[1]));
    }
}
