#include <Eigen/Dense>
#include <gtest/gtest.h>

namespace {

TEST(transformations, multiplication)
{
    const int x = 0;
    const int y = 0;
    Eigen::Vector3d point;
    point << x,
             y,
             1;
    
    const int r = 5; // right
    const int u = 2; // up
    Eigen::Matrix3d transform;
    transform << 1, 0, r,
                 0, 1, u,
                 0, 0, 1;

    Eigen::Vector3d result = transform * point;

    EXPECT_FLOAT_EQ(result[0], x+r);
    EXPECT_FLOAT_EQ(result[1], y+u);
    EXPECT_FLOAT_EQ(result[2], 1);
}

}
