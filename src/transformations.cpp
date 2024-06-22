#include <cmath>
#include "transformations.hpp"

namespace rc
{
    Vertex vertex(float row, float col)
    {
        return Vertex{row, col, 1.0F};
    }

    Transformation translate(float row, float col)
    {
        return Transformation{{1.0F, 0.0F, row,},
                              {0.0F, 1.0F, col,},
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
