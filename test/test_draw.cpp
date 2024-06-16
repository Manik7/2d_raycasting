#include <gtest/gtest.h>
#include "../src/constants.hpp"
#include "../src/draw.hpp"
#include "../src/image.hpp"
#include "../src/transformations.hpp"

namespace
{

TEST(draw, vertex)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::draw(rc::vertex(1,1), rc::color::white, image);
    rc::BGR color = image(1,1);
    EXPECT_EQ(color._blue, 255U);
    EXPECT_EQ(color._green, 255U);
    EXPECT_EQ(color._red, 255U);
}

}
