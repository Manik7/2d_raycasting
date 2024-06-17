#pragma once

#include "geometry.hpp"
#include "image.hpp"

namespace rc
{
    template <typename T, int Height, int Width, int Padding>
    void draw(Vertex const& vertex, T const& value, GenericImage<T, Height, Width, Padding>& image)
    {
        const int x = vertex[0];
        const int y = vertex[1];
        image(x,y) = value;
    }

    template <typename T, int Height, int Width, int Padding>
    void draw(Vertex const& from, Vertex const& to, T const& value, GenericImage<T, Height, Width, Padding>& image)
    {
        const float x1              = from[0];
        const float y1              = from[1];
        const float x2              = to[0];
        const float y2              = to[1];
        const float dx              = x2 - x1;
        const float dy              = y2 - y1;
        int const length_squared    = dx * dx + dy * dy;
        const float samplesPerPixel = 4.0F;

        // TODO: replace this TERRIBLY INEFFICIENT line drawing algorithm with something proper like Bresenham's or
        //       the Gupta-Sproull line drawing algorithm: https://en.wikipedia.org/wiki/Line_drawing_algorithm
        for(float t = 0; t*t <= length_squared*samplesPerPixel; ++t)
        {
            float x = x1 + (t*t/(length_squared*samplesPerPixel))*dx;
            float y = y1 + (t*t/(length_squared*samplesPerPixel))*dy;
            const int i = static_cast<int>(x);
            const int j = static_cast<int>(y);
            if(image.isPixelInBounds(i, j))
            {
                image(i,j) = value;
            }
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw_vertices(Graph const& graph, GenericImage<T, Height, Width, Padding> & image)
    {
        for (Vertex const& vertex : graph._vertices)
        {
            draw(graph._transformation * vertex, graph._color, image);
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw_lines(Graph const& graph, GenericImage<T, Height, Width, Padding> & image)
    {
        for (std::pair<int, int> const& edge : graph._edges)
        {
            draw(graph._transformation * graph._vertices[edge.first],
                 graph._transformation * graph._vertices[edge.second],
                 graph._color,
                 image);
        }
    }
}
