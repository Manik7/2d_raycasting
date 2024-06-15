#include <cmath>
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include "../src/radians.hpp"

namespace {

TEST(radians, pi)
{
    EXPECT_FLOAT_EQ(rc::pi(), M_PI);
}

TEST(radians, deg_rad_0)
{
    const rc::Degrees deg = rc::Degrees{0.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = 0.0F;

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

TEST(radians, deg_rad_90)
{
    const rc::Degrees deg = rc::Degrees{90.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = rc::pi() / 2.0F;

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

TEST(radians, deg_rad_180)
{
    const rc::Degrees deg = rc::Degrees{180.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = rc::pi();

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

TEST(radians, deg_rad_360)
{
    const rc::Degrees deg = rc::Degrees{360.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = 2.0F * rc::pi(); 

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

TEST(radians, deg_rad_minus_90)
{
    const rc::Degrees deg = rc::Degrees{-90.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = -rc::pi() / 2.0F;

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

TEST(radians, deg_rad_minus_180)
{
    const rc::Degrees deg = rc::Degrees{-180.0F};
    const rc::Radians rad = rc::to_radians(deg);
    const rc::Degrees rev = rc::to_degrees(rad);
    const float expected  = -rc::pi();

    EXPECT_FLOAT_EQ(rad._radians, expected);
    EXPECT_FLOAT_EQ(deg._degrees, rev._degrees);
}

}
