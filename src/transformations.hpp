#pragma once

#include <Eigen/Dense>
#include "geometry.hpp"
#include "radians.hpp"

namespace rc
{
    Point point(float x, float y);
    Transformation translate(float x, float y);
    Transformation rotate(Radians theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
    Transformation rotate(Degrees theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
}
