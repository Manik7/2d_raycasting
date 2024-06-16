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
        // naive line drawing algorithm from: https://en.wikipedia.org/wiki/Line_drawing_algorithm
        const float x1 = from[0];
        const float y1 = from[1];
        const float x2 = to[0];
        const float y2 = to[1];
        const float dx = x2 - x1;
        const float dy = y2 - y1;
        for(float x = x1; x <= x2; ++x)
        {
            const float y = y1 + dy * (x - x1) / dx;
            const int i = static_cast<int>(x);
            const int j = static_cast<int>(y);
            if(0 <= i && i < image.height() && 0 <= j && j < image.width())
            {
                image(i,j) = value;
            }
        }
    }
}
