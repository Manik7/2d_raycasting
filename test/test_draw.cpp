#include <gtest/gtest.h>
#include "../src/constants.hpp"
#include "../src/draw.hpp"
#include "../src/image.hpp"
#include "../src/transformations.hpp"

namespace
{

TEST(draw, point)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::draw(rc::point(1,1), rc::color::white, image);
    rc::BGR color = image(1,1);
    EXPECT_EQ(color._blue, 255U);
    EXPECT_EQ(color._green, 255U);
    EXPECT_EQ(color._red, 255U);
}

}
