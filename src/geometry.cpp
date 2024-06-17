
#include <algorithm>
#include <optional>
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

    // Graphs which are empty, have only a coordinate system, or have only a coordinate system and a single point have
    // no bounding box. In order to have a bounding box, the graph must contain at least two unequal points.
    std::optional<std::pair<Vertex, Vertex>> bounding_box(Graph const& graph)
    {

        if(graph._vertices.size() > 1 && std::any_of(graph._vertices.cbegin()+1,
                                                     graph._vertices.cend(),
                                                     [&graph](Vertex const& v){return v != graph._vertices.front();}))
        {
            auto x = std::minmax_element(graph._vertices.cbegin(),
                                               graph._vertices.cend(),
                                               [](Vertex const& l, Vertex const& r){ return l[0] < r[0]; });
            auto y = std::minmax_element(graph._vertices.cbegin(),
                                               graph._vertices.cend(),
                                               [](Vertex const& l, Vertex const& r){ return l[1] < r[1]; });

            return std::optional<std::pair<Vertex, Vertex>>(std::make_pair(vertex((*x.first)[0], (*y.first)[1]),
                                                                           vertex((*x.second)[0], (*y.second)[1])));
        }
        else
        {
            return std::optional<std::pair<Vertex, Vertex>>(); // empty optional
        }
    }
}
