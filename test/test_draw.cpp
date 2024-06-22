#include <iostream>
#include <gtest/gtest.h>
#include "../src/constants.hpp"
#include "../src/draw.hpp"
#include "../src/image.hpp"
#include "../src/transformations.hpp"

namespace
{

TEST(draw, vertex)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::draw(rc::vertex(2,1), true, image);

    EXPECT_EQ(image(0,0), false);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), false);
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), false);
    EXPECT_EQ(image(2,0), false);
    EXPECT_EQ(image(2,1), true);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, point)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::point(rc::translate(2,1), true);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0), false);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), false);
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), false);
    EXPECT_EQ(image(2,0), false);
    EXPECT_EQ(image(2,1), true);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, line)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::line(rc::translate(0, 0), rc::vertex(0,2), true);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0), true);
    EXPECT_EQ(image(0,1), true);
    EXPECT_EQ(image(0,2), true);
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), false);
    EXPECT_EQ(image(2,0), false);
    EXPECT_EQ(image(2,1), false);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, translated_line)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::line(rc::translate(1, 1), rc::vertex(0,2), true);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0), false);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), false);
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), true);
    EXPECT_EQ(image(1,2), true);
    EXPECT_EQ(image(2,0), false);
    EXPECT_EQ(image(2,1), false);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, rotated_line)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::line(rc::rotate(rc::Degrees(-90)), rc::vertex(0,2), true);
    rc::draw(graph, image);

    EXPECT_EQ(image(0,0), true);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), false);
    EXPECT_EQ(image(1,0), true);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), false);
    EXPECT_EQ(image(2,0), true);
    EXPECT_EQ(image(2,1), false);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, transform_point)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::point(rc::translate(0, 0), true);
    rc::Transformation const t = rc::rotate(rc::Degrees(-90)) * rc::translate(0, 2);
    // TODO: changing the rotation angle to -88 degrees fixes the unit test, which suggests rounding error might be to blame
    // or some other problem in the line drawing code

    rc::draw(t * graph, image);

    EXPECT_EQ(image(0,0), false);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), false);
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), false);
    EXPECT_EQ(image(2,0), true);
    EXPECT_EQ(image(2,1), false);
    EXPECT_EQ(image(2,2), false);
}

TEST(draw, transform_line)
{
    rc::GenericImage<bool, 3, 3, 0> image{};
    rc::Graph<bool> const graph = rc::line(rc::translate(0, 0), rc::vertex(0,2), true);
    rc::Transformation const t = rc::translate(0, 2) * rc::rotate(rc::Degrees(-90));
    // TODO: changing the rotation angle to -88 degrees fixes the unit test, which suggests rounding error might be to blame
    // or some other problem in the line drawing code

    EXPECT_FLOAT_EQ(graph._vertices[0][0], 0.0F);
    EXPECT_FLOAT_EQ(graph._vertices[0][1], 0.0F);
    EXPECT_FLOAT_EQ(graph._vertices[0][2], 1.0F);
    EXPECT_FLOAT_EQ(graph._vertices[1][0], 0.0F);
    EXPECT_FLOAT_EQ(graph._vertices[1][1], 2.0F);
    EXPECT_FLOAT_EQ(graph._vertices[1][2], 1.0F);

    rc::Graph<bool> g = t * graph;
    rc::Vertex v0 = g._transformation * g._vertices[0];
    rc::Vertex v1 = g._transformation * g._vertices[1];
    ASSERT_FLOAT_EQ(v0[0], 0.0F);
    ASSERT_FLOAT_EQ(v0[1], 2.0F);
    ASSERT_FLOAT_EQ(v0[2], 1.0F);
    ASSERT_FLOAT_EQ(v1[0], 2.0F);
    ASSERT_FLOAT_EQ(v1[1], 2.0F);
    ASSERT_FLOAT_EQ(v1[2], 1.0F);
    ASSERT_EQ(g._edges[0].first, 0);
    ASSERT_EQ(g._edges[0].second, 1);

    rc::draw(g, image);

    EXPECT_EQ(image(0,0), false);
    EXPECT_EQ(image(0,1), false);
    EXPECT_EQ(image(0,2), true); // error
    EXPECT_EQ(image(1,0), false);
    EXPECT_EQ(image(1,1), false);
    EXPECT_EQ(image(1,2), true); // error
    EXPECT_EQ(image(2,0), false); //   error
    EXPECT_EQ(image(2,1), false); //   error
    EXPECT_EQ(image(2,2), true);
}

}
