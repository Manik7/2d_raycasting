#pragma once

#include <Eigen/Dense>
#include "constants.hpp"

namespace rc
{
    using Vertex         = Eigen::Vector3f;
    using Transformation = Eigen::Matrix3f;

    Vertex vertex(float x, float y);
}
