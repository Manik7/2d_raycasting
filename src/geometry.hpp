#pragma once

#include <vector>
#include <optional>
#include <utility>
#include <Eigen/Dense>
#include "constants.hpp"
#include "transformations.hpp"

namespace rc
{
    template <typename T>
    struct Graph // a bag of vertices and lines
    {
        Transformation _transformation{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // initialize to valid homogeneous matrix
        std::vector<Vertex> _vertices{};
        std::vector<std::pair<int, int>> _edges{}; // a pair (a, b) means that there is a line from _vertices[a] to _vertices[b]
        T _value{};
        // for 3d, add one more vector, to encode faces between edges
    };

    // TODO: it's nice to multiply the entire graph by a transformation, and get a graph in return. This requires a lot
    //       of copying though. Maybe I can come up with a more efficient solution here.
    template <typename T>
    Graph<T> operator*(Transformation const& t, Graph<T> const& g)
    {
        Graph<T> result = g;
        result._transformation = t * result._transformation;
        return result;
    }

    template <typename T>
    Graph<T> coordinate(Transformation const& origin)
    {
        // Technically, default constructing T (which is black) is incorrect, since a coordinate system does not have
        // a value. Since it contains no vertices and no edges which can be rendered, and thus nothing to which the
        // value can be applied, this should not cause any issues. Wrapping the value in a std::optional just for this
        // one special case would complicate the code everywhere, and seems like overkill.
        return Graph<T>{origin, {}, {}, T{}};
    }

    template <typename T>
    Graph<T> point(Transformation const& origin, T const& value)
    {
        return Graph<T>{origin, {vertex(0.0F, 0.0F)}, {}, value};
    }

    template <typename T>
    Graph<T> line(Transformation const& origin, Vertex const& other, T const& value)
    {
        return Graph<T>{origin, {vertex(0.0F, 0.0F), other}, {std::make_pair(0, 1)}, value};
    }

    template <typename T>
    Graph<T> rectangle(Transformation const& origin, Vertex const& other, T const& value)
    {
        return Graph<T>{origin,
                     {vertex(0.0F, 0.0F), vertex(other[0], 0.0F), other, vertex(0.0F, other[1])},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3), std::make_pair(3, 0)},
                     value};
    }

    template <typename T>
    Graph<T> right_triangle(Transformation const& origin, Vertex const& other, T const& value)
    {
        return Graph<T>{origin,
                     {vertex(0.0F, 0.0F), vertex(other[0], 0.0F), other},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 0)},
                     value};
    }

    template <typename T>
    Graph<T> triangle(Transformation const& origin, Vertex const& a, Vertex const& b, T const& value)
    {
        return Graph<T>{origin,
                     {vertex(0.0F, 0.0F), a, b},
                     {std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 0)},
                     value};
    }

    // Graph<T>s which are empty, have only a coordinate system, or have only a coordinate system and a single point have
    // no bounding box. In order to have a bounding box, the graph must contain at least two unequal points.
    template <typename T>
    std::optional<std::pair<Vertex, Vertex>> bounding_box(Graph<T> const& graph)
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

    // TODO: (later on in another ticket) free function to intersect a ray with a bag-of-lines
}
