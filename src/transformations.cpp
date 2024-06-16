#include <cmath>
#include "transformations.hpp"

namespace rc
{
    Point point(float x, float y)
    {
        return Point{x, y, 1.0F};
    }

    Transformation translate(float x, float y)
    {
        return Transformation{{1.0F, 0.0F, x,},
                               {0.0F, 1.0F, y,},
                               {0.0F, 0.0F, 1.0F}};
    }

    // theta is positive when rotating from the x to the y axis (i.e. counter-clockwise)
    Transformation rotate(Radians theta)
    {
        return Transformation{{std::cos(theta._radians), -std::sin(theta._radians), 0.0F},
                              {std::sin(theta._radians),  std::cos(theta._radians), 0.0F},
                              {0.0F,                      0.0F,                     1.0F}};
    }

    // theta is positive when rotating from the x to the y axis (i.e. counter-clockwise)
    Transformation rotate(Degrees theta)
    {
        return rotate(to_radians(theta));
    }

}
