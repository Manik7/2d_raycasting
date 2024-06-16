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
}
