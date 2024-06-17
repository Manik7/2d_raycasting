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
    rc::draw(rc::vertex(1,1), rc::color::green, image);

    EXPECT_EQ(image(0,0)._green, 0U);
    EXPECT_EQ(image(0,1)._green, 0U);
    EXPECT_EQ(image(0,2)._green, 0U);
    EXPECT_EQ(image(1,0)._green, 0U);
    EXPECT_EQ(image(1,1)._green, 255U);
    EXPECT_EQ(image(1,2)._green, 0U);
    EXPECT_EQ(image(2,0)._green, 0U);
    EXPECT_EQ(image(2,1)._green, 0U);
    EXPECT_EQ(image(2,2)._green, 0U);
    for (rc::BGR const& color : image._data)
    {
        EXPECT_EQ(color._blue, 0U);
        EXPECT_EQ(color._red, 0U);
    }
}

TEST(draw, point)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::Graph const graph = rc::point(rc::translate(1,1), rc::color::green);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0)._green, 0U);
    EXPECT_EQ(image(0,1)._green, 0U);
    EXPECT_EQ(image(0,2)._green, 0U);
    EXPECT_EQ(image(1,0)._green, 0U);
    EXPECT_EQ(image(1,1)._green, 255U);
    EXPECT_EQ(image(1,2)._green, 0U);
    EXPECT_EQ(image(2,0)._green, 0U);
    EXPECT_EQ(image(2,1)._green, 0U);
    EXPECT_EQ(image(2,2)._green, 0U);
    for (rc::BGR const& color : image._data)
    {
        EXPECT_EQ(color._blue, 0U);
        EXPECT_EQ(color._red, 0U);
    }
}

TEST(draw, line)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::Graph const graph = rc::line(rc::translate(0, 0), rc::vertex(0,2), rc::color::green);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0)._green, 255U);
    EXPECT_EQ(image(0,1)._green, 255U);
    EXPECT_EQ(image(0,2)._green, 255U);
    EXPECT_EQ(image(1,0)._green, 0U);
    EXPECT_EQ(image(1,1)._green, 0U);
    EXPECT_EQ(image(1,2)._green, 0U);
    EXPECT_EQ(image(2,0)._green, 0U);
    EXPECT_EQ(image(2,1)._green, 0U);
    EXPECT_EQ(image(2,2)._green, 0U);
    for (rc::BGR const& color : image._data)
    {
        EXPECT_EQ(color._blue, 0U);
        EXPECT_EQ(color._red, 0U);
    }
}

TEST(draw, translated_line)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::Graph const graph = rc::line(rc::translate(1, 1), rc::vertex(0,2), rc::color::green);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0)._green, 0U);
    EXPECT_EQ(image(0,1)._green, 0U);
    EXPECT_EQ(image(0,2)._green, 0U);
    EXPECT_EQ(image(1,0)._green, 0U);
    EXPECT_EQ(image(1,1)._green, 255U);
    EXPECT_EQ(image(1,2)._green, 255U);
    EXPECT_EQ(image(2,0)._green, 0U);
    EXPECT_EQ(image(2,1)._green, 0U);
    EXPECT_EQ(image(2,2)._green, 0U);
    for (rc::BGR const& color : image._data)
    {
        EXPECT_EQ(color._blue, 0U);
        EXPECT_EQ(color._red, 0U);
    }
}

TEST(draw, rotated_line)
{
    rc::GenericImage<rc::BGR, 3, 3, 0> image{};
    rc::Graph const graph = rc::line(rc::rotate(rc::Degrees(-90)), rc::vertex(0,2), rc::color::green);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0)._green, 255U);
    EXPECT_EQ(image(0,1)._green, 0U);
    EXPECT_EQ(image(0,2)._green, 0U);
    EXPECT_EQ(image(1,0)._green, 255U);
    EXPECT_EQ(image(1,1)._green, 0U);
    EXPECT_EQ(image(1,2)._green, 0U);
    EXPECT_EQ(image(2,0)._green, 255U);
    EXPECT_EQ(image(2,1)._green, 0U);
    EXPECT_EQ(image(2,2)._green, 0U);
    for (rc::BGR const& color : image._data)
    {
        EXPECT_EQ(color._blue, 0U);
        EXPECT_EQ(color._red, 0U);
    }
}

}
