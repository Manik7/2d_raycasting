#pragma once

#include <vector>
#include <optional>
#include <utility>
#include <Eigen/Dense>
#include "constants.hpp"

namespace rc
{
    using Vertex         = Eigen::Vector3f;
    using Transformation = Eigen::Matrix3f;

    struct Graph // a bag of vertices and lines
    {
        Transformation _transformation{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // initialize to valid homogeneous matrix
        std::vector<Vertex> _vertices{};
        std::vector<std::pair<int, int>> _edges{}; // a pair (a, b) means that there is a line from _vertices[a] to _vertices[b]
        BGR _color{color::black};
        // for 3d, add one more vector, to encode faces between edges
    };

    // TODO: it's nice to multiply the entire graph by a transformation, and get a graph in return. This requires a lot
    //       of copying though. Maybe I can come up with a more efficient solution here.
    Graph operator*(Transformation const& t, Graph const& g);

    Vertex vertex(float x, float y);

    Graph coordinate(Transformation const& origin);
    Graph point(Transformation const& origin, BGR const& color);
    Graph line(Transformation const& origin, Vertex const& other, BGR const& color);
    Graph rectangle(Transformation const& origin, Vertex const& other, BGR const& color);
    Graph right_triangle(Transformation const& origin, Vertex const& other, BGR const& color);
    Graph triangle(Transformation const& origin, Vertex const& a, Vertex const& b, BGR const& color);

    std::optional<std::pair<Vertex, Vertex>> bounding_box(Graph const& graph);

    // TODO: (later on in another ticket) free function to intersect a ray with a bag-of-lines
}
