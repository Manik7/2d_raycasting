#pragma once

#include <Eigen/Dense>
#include "radians.hpp"

namespace rc
{
    using Point          = Eigen::Vector3f;
    using Transformation = Eigen::Matrix3f;

    Eigen::Vector3f point(float x, float y);
    Eigen::Matrix3f translate(float x, float y);
    Eigen::Matrix3f rotate(Radians theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
    Eigen::Matrix3f rotate(Degrees theta); // theta is positive when rotating from the x to y axis (counter-clockwise)
}
