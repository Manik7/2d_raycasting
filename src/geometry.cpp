
#include <utility>
#include "geometry.hpp"

namespace rc
{
    Vertex vertex(float x, float y)
    {
        return Vertex{x, y, 1.0F};
    }

    Graph coordinate(Transformation const& origin)
    {
        // Technically, default constructing BGR (which is black) is incorrect, since a coordinate system does not have
        // a color. Since it contains no vertices and no edges which can be rendered, and thus nothing to which the
        // color can be applied, this should not cause any issues. Wrapping the color in a std::optional just for this
        // one special case would complicate the code everywhere, and seems like overkill.
        return Graph{origin, {}, {}, BGR{}};
    }

    Graph point(Transformation const& origin, BGR const& color)
    {
        return Graph{origin, {vertex(0.0F, 0.0F)}, {}, color};
    }

    Graph line(Transformation const& origin, Vertex const& other, BGR const& color)
    {
        return Graph{origin, {vertex(0.0F, 0.0F), other}, {std::make_pair(0, 1)}, color};
    }

    Graph rectangle(Transformation const& origin, Vertex const& other, BGR const& color)
    {
        return Graph{origin,
                     {vertex(0.0F, 0.0F), vertex(other[0], 0.0F), other, vertex(0.0F, other[1])},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3), std::make_pair(3, 0)},
                     color};
    }

    Graph right_triangle(Transformation const& origin, Vertex const& other, BGR const& color)
    {
        return Graph{origin,
                     {vertex(0.0F, 0.0F), vertex(other[0], 0.0F), other},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 0)},
                     color};
    }

    Graph triangle(Transformation const& origin, Vertex const& a, Vertex const& b, BGR const& color)
    {
        return Graph{origin,
                     {vertex(0.0F, 0.0F), a, b},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 0)},
                     color};
    }
}
