#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../src/constants.hpp"
#include "../src/geometry.hpp"
#include "../src/transformations.hpp"

namespace {

    TEST(geometry, empty)
    {
        rc::Graph const g{};

        EXPECT_EQ(g._transformation, Eigen::Matrix3f::Identity());
        EXPECT_EQ(g._vertices.size(), 0);
        EXPECT_EQ(g._edges.size(), 0);
        EXPECT_EQ(g._color._blue, rc::color::black._blue);
        EXPECT_EQ(g._color._green, rc::color::black._green);
        EXPECT_EQ(g._color._red, rc::color::black._red);
    }

    TEST(geometry, coordinate)
    {
        rc::Graph const g = rc::coordinate(rc::translate(2, 3));
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        EXPECT_EQ(g._vertices.size(), 0);
        EXPECT_EQ(g._edges.size(), 0);
        EXPECT_EQ(g._color._blue, rc::color::black._blue);
        EXPECT_EQ(g._color._green, rc::color::black._green);
        EXPECT_EQ(g._color._red, rc::color::black._red);
    }

    TEST(geometry, point)
    {
        rc::Graph const g = rc::point(rc::translate(2, 3), rc::color::green);
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        ASSERT_EQ(g._vertices.size(), 1);

        rc::Vertex const& v = g._vertices[0];

        EXPECT_EQ(v[0], 0);
        EXPECT_EQ(v[1], 0);
        EXPECT_EQ(v[2], 1);
        EXPECT_EQ(g._edges.size(), 0);
        EXPECT_EQ(g._color._blue, 0U);
        EXPECT_EQ(g._color._green, 255U);
        EXPECT_EQ(g._color._red, 0U);

        rc::Vertex v_globl_coordinates = t * v;
        EXPECT_EQ(v_globl_coordinates[0], 2);
        EXPECT_EQ(v_globl_coordinates[1], 3);
        EXPECT_EQ(v_globl_coordinates[2], 1);

    }

    TEST(geometry, line)
    {
        rc::Graph const g = rc::line(rc::translate(2, 3), rc::vertex(5, 7), rc::color::green);
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        ASSERT_EQ(g._vertices.size(), 2);

        rc::Vertex const& v0 = g._vertices[0];
        rc::Vertex const& v1 = g._vertices[1];

        EXPECT_EQ(v0[0], 0);
        EXPECT_EQ(v0[1], 0);
        EXPECT_EQ(v0[2], 1);
        EXPECT_EQ(v1[0], 5);
        EXPECT_EQ(v1[1], 7);
        EXPECT_EQ(v1[2], 1);

        rc::Vertex v0_globl_coordinates = t * v0;
        rc::Vertex v1_globl_coordinates = t * v1;
        EXPECT_EQ(v0_globl_coordinates[0], 2);
        EXPECT_EQ(v0_globl_coordinates[1], 3);
        EXPECT_EQ(v0_globl_coordinates[2], 1);
        EXPECT_EQ(v1_globl_coordinates[0], 7);
        EXPECT_EQ(v1_globl_coordinates[1], 10);
        EXPECT_EQ(v1_globl_coordinates[2], 1);

        ASSERT_EQ(g._edges.size(), 1);

        std::pair<int, int> const& edge = g._edges[0];

        EXPECT_EQ(edge.first, 0);
        EXPECT_EQ(edge.second, 1);
        EXPECT_EQ(g._color._blue, 0U);
        EXPECT_EQ(g._color._green, 255U);
        EXPECT_EQ(g._color._red, 0U);
    }

    TEST(geometry, rectangle)
    {
        rc::Graph const g = rc::rectangle(rc::translate(2, 3), rc::vertex(5, 7), rc::color::green);
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        ASSERT_EQ(g._vertices.size(), 4);

        rc::Vertex const& v0 = g._vertices[0];
        rc::Vertex const& v1 = g._vertices[1];
        rc::Vertex const& v2 = g._vertices[2];
        rc::Vertex const& v3 = g._vertices[3];

        EXPECT_EQ(v0[0], 0);
        EXPECT_EQ(v0[1], 0);
        EXPECT_EQ(v0[2], 1);
        EXPECT_EQ(v1[0], 5);
        EXPECT_EQ(v1[1], 0);
        EXPECT_EQ(v1[2], 1);
        EXPECT_EQ(v2[0], 5);
        EXPECT_EQ(v2[1], 7);
        EXPECT_EQ(v2[2], 1);
        EXPECT_EQ(v3[0], 0);
        EXPECT_EQ(v3[1], 7);
        EXPECT_EQ(v3[2], 1);
        ASSERT_EQ(g._edges.size(), 4);
        EXPECT_EQ(g._edges[0].first, 0);
        EXPECT_EQ(g._edges[0].second, 1);
        EXPECT_EQ(g._edges[1].first, 1);
        EXPECT_EQ(g._edges[1].second, 2);
        EXPECT_EQ(g._edges[2].first, 2);
        EXPECT_EQ(g._edges[2].second, 3);
        EXPECT_EQ(g._edges[3].first, 3);
        EXPECT_EQ(g._edges[3].second, 0);
        EXPECT_EQ(g._color._blue, 0U);
        EXPECT_EQ(g._color._green, 255U);
        EXPECT_EQ(g._color._red, 0U);
    }

    TEST(geometry, right_triangle)
    {
        rc::Graph const g = rc::right_triangle(rc::translate(2, 3), rc::vertex(5, 7), rc::color::green);
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        ASSERT_EQ(g._vertices.size(), 3);

        rc::Vertex const& v0 = g._vertices[0];
        rc::Vertex const& v1 = g._vertices[1];
        rc::Vertex const& v2 = g._vertices[2];

        EXPECT_EQ(v0[0], 0);
        EXPECT_EQ(v0[1], 0);
        EXPECT_EQ(v0[2], 1);
        EXPECT_EQ(v1[0], 5);
        EXPECT_EQ(v1[1], 0);
        EXPECT_EQ(v1[2], 1);
        EXPECT_EQ(v2[0], 5);
        EXPECT_EQ(v2[1], 7);
        EXPECT_EQ(v2[2], 1);
        ASSERT_EQ(g._edges.size(), 3);
        EXPECT_EQ(g._edges[0].first, 0);
        EXPECT_EQ(g._edges[0].second, 1);
        EXPECT_EQ(g._edges[1].first, 1);
        EXPECT_EQ(g._edges[1].second, 2);
        EXPECT_EQ(g._edges[2].first, 2);
        EXPECT_EQ(g._edges[2].second, 0);
        EXPECT_EQ(g._color._blue, 0U);
        EXPECT_EQ(g._color._green, 255U);
        EXPECT_EQ(g._color._red, 0U);
    }

    TEST(geometry, triangle)
    {
        rc::Graph const g = rc::triangle(rc::translate(2, 3), rc::vertex(5, 7), rc::vertex(11, 13), rc::color::green);
        rc::Transformation const& t = g._transformation;

        EXPECT_EQ(t(0,0), 1);
        EXPECT_EQ(t(0,1), 0);
        EXPECT_EQ(t(0,2), 2);
        EXPECT_EQ(t(1,0), 0);
        EXPECT_EQ(t(1,1), 1);
        EXPECT_EQ(t(1,2), 3);
        EXPECT_EQ(t(2,0), 0);
        EXPECT_EQ(t(2,1), 0);
        EXPECT_EQ(t(2,2), 1);
        ASSERT_EQ(g._vertices.size(), 3);

        rc::Vertex const& v0 = g._vertices[0];
        rc::Vertex const& v1 = g._vertices[1];
        rc::Vertex const& v2 = g._vertices[2];

        EXPECT_EQ(v0[0], 0);
        EXPECT_EQ(v0[1], 0);
        EXPECT_EQ(v0[2], 1);
        EXPECT_EQ(v1[0], 5);
        EXPECT_EQ(v1[1], 7);
        EXPECT_EQ(v1[2], 1);
        EXPECT_EQ(v2[0], 11);
        EXPECT_EQ(v2[1], 13);
        EXPECT_EQ(v2[2], 1);
        ASSERT_EQ(g._edges.size(), 3);
        EXPECT_EQ(g._edges[0].first, 0);
        EXPECT_EQ(g._edges[0].second, 1);
        EXPECT_EQ(g._edges[1].first, 1);
        EXPECT_EQ(g._edges[1].second, 2);
        EXPECT_EQ(g._edges[2].first, 2);
        EXPECT_EQ(g._edges[2].second, 0);
        EXPECT_EQ(g._color._blue, 0U);
        EXPECT_EQ(g._color._green, 255U);
        EXPECT_EQ(g._color._red, 0U);
    }

    TEST(geometry, rectangle_bounding_box)
    {
        rc::Graph const g = rc::rectangle(rc::translate(2, 3), rc::vertex(-5, 7), rc::color::green);
        std::pair<rc::Vertex, rc::Vertex> const aabb = rc::bounding_box(g);
        rc::Vertex const& min = aabb.first;
        rc::Vertex const& max = aabb.second;

        EXPECT_EQ(min[0], -5);
        EXPECT_EQ(min[1], 0);
        EXPECT_EQ(max[0], 0);
        EXPECT_EQ(max[1], 7);
    }

}