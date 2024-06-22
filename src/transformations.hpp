#pragma once

#include <Eigen/Dense>
#include "radians.hpp"

namespace rc
{
    using Vertex         = Eigen::Vector3f;
    using Transformation = Eigen::Matrix3f;

    Vertex vertex(float row, float col);
    Transformation translate(float row, float col);
    Transformation rotate(Radians theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
    Transformation rotate(Degrees theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
}
