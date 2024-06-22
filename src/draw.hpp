#pragma once

#include <cmath>
#include "constants.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "transformations.hpp"
#include "utility.hpp"

namespace rc
{
    template <typename T, int Height, int Width, int Padding>
    void draw(Vertex const& vertex, T const& value, GenericImage<T, Height, Width, Padding>& image)
    {
        const int row = round(vertex[0]);
        const int col = round(vertex[1]);
        if(image.isPixelInBounds(row, col))
        {
            image(row, col) = value;
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw(Vertex const& from, Vertex const& to, T const& value, GenericImage<T, Height, Width, Padding>& image)
    {
        const float origin_row      = from[0];
        const float origin_col      = from[1];
        const float other_row       = to[0];
        const float other_col       = to[1];
        const float delta_row       = other_row - origin_row;
        const float delta_col       = other_col - origin_col;
        int const length_squared    = delta_row * delta_row + delta_col * delta_col;
        const float samplesPerPixel = 2.0F;

        // TODO: replace this TERRIBLY INEFFICIENT line drawing algorithm with something proper like Bresenham's or
        //       the Gupta-Sproull line drawing algorithm: https://en.wikipedia.org/wiki/Line_drawing_algorithm
        for(float t = 0; t*t <= length_squared*samplesPerPixel*samplesPerPixel; t+=1.0F)
        {
            const int row = round(origin_row + (t*t/(length_squared*samplesPerPixel*samplesPerPixel))*delta_row);
            const int col = round(origin_col + (t*t/(length_squared*samplesPerPixel*samplesPerPixel))*delta_col);
            if(image.isPixelInBounds(row, col))
            {
                image(row, col) = value;
            }
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw_vertices(Graph<T> const& graph, GenericImage<T, Height, Width, Padding> & image)
    {
        for (Vertex const& vertex : graph._vertices)
        {
            draw(graph._transformation * vertex, graph._value, image);
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw_edges(Graph<T> const& graph, GenericImage<T, Height, Width, Padding> & image)
    {
        for (std::pair<int, int> const& edge : graph._edges)
        {
            draw(graph._transformation * graph._vertices[edge.first],
                 graph._transformation * graph._vertices[edge.second],
                 graph._value,
                 image);
        }
    }

    template <typename T, int Height, int Width, int Padding>
    void draw(Graph<T> const& graph, GenericImage<T, Height, Width, Padding> & image)
    {
        draw_vertices(graph, image);
        draw_edges(graph, image);
    }
}
