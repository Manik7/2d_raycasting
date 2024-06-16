#pragma once

#include "geometry.hpp"
#include "image.hpp"

namespace rc
{
    template <typename T, int Height, int Width, int Padding>
    void draw(Point const& point, T const& value, GenericImage<T, Height, Width, Padding>& image)
    {
        const int x = point[0];
        const int y = point[1];
        image(x,y) = value;
    }
}
