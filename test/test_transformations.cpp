#include <cmath>
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include "../src/transformations.hpp"

namespace {

constexpr float epsilon = 0.000001;

TEST(transformations, multiplication)
{
    const int x = 0;
    const int y = 0;
    Eigen::Vector3f point;
    point << x,
             y,
             1;
    
    const int r = 5; // right
    const int u = 2; // up
    Eigen::Matrix3f transform;
    transform << 1, 0, r,
                 0, 1, u,
                 0, 0, 1;

    Eigen::Vector3f result = transform * point;

    EXPECT_FLOAT_EQ(result[0], x+r);
    EXPECT_FLOAT_EQ(result[1], y+u);
    EXPECT_FLOAT_EQ(result[2], 1);
}

TEST(transformations, origin)
{
    rc::Point result = rc::point(0.0F, 0.0F);
    EXPECT_FLOAT_EQ(result[0], 0.0F);
    EXPECT_FLOAT_EQ(result[1], 0.0F);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

TEST(transformations, point)
{
    rc::Point result = rc::point(3.0F, 5.0F);
    EXPECT_FLOAT_EQ(result[0], 3.0F);
    EXPECT_FLOAT_EQ(result[1], 5.0F);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

TEST(transformation, translate)
{
    rc::Transformation t = rc::translate(3.0F, 5.0F);
    rc::Point p          = rc::point(0.0F, 0.0F);
    rc::Point result     = t * p;

    EXPECT_FLOAT_EQ(result[0], 3.0F);
    EXPECT_FLOAT_EQ(result[1], 5.0F);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

TEST(transformation, translate_non_zero)
{
    rc::Point result     = rc::translate(-3.0F, 3.0F) * rc::point(8.0F, -1.0F);
    EXPECT_FLOAT_EQ(result[0], 5.0F);
    EXPECT_FLOAT_EQ(result[1], 2.0F);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

TEST(transformation, rotate_counter_clockwise)
{
    rc::Point p          = rc::point(1.0F, 0.0F);
    rc::Transformation t = rc::rotate(rc::Degrees{90.0F});
    rc::Point result     = t*p;
    EXPECT_NEAR(result[0], 0.0F, epsilon);
    EXPECT_NEAR(result[1], 1.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], -1.0F, epsilon);
    EXPECT_NEAR(result[1], 0.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], 0.0F, epsilon);
    EXPECT_NEAR(result[1], -1.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], 1.0F, epsilon);
    EXPECT_NEAR(result[1], 0.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

TEST(transformation, rotate_clockwise)
{
    rc::Point p          = rc::point(1.0F, 0.0F);
    rc::Transformation t = rc::rotate(rc::Degrees{-90.0F});
    rc::Point result     = t*p;
    EXPECT_NEAR(result[0], 0.0F, epsilon);
    EXPECT_NEAR(result[1], -1.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], -1.0F, epsilon);
    EXPECT_NEAR(result[1], 0.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], 0.0F, epsilon);
    EXPECT_NEAR(result[1], 1.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);

    result = t * result;
    EXPECT_NEAR(result[0], 1.0F, epsilon);
    EXPECT_NEAR(result[1], 0.0F, epsilon);
    EXPECT_FLOAT_EQ(result[2], 1.0F);
}

}
