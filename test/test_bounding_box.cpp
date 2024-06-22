#include <optional>
#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../src/constants.hpp"
#include "../src/geometry.hpp"
#include "../src/transformations.hpp"

namespace
{
    TEST(bounding_box, empty)
    {
        rc::Graph<bool> const g{};
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_FALSE(maybe_aabb);
    }

    TEST(bounding_box, coordinate)
    {
        rc::Graph<bool> const g = rc::coordinate<bool>(rc::translate(2, 3));
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_FALSE(maybe_aabb);
    }

    TEST(bounding_box, point)
    {
        rc::Graph<bool> const g = rc::point(rc::translate(2, 3), true);
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_FALSE(maybe_aabb);
    }

    TEST(bounding_box, two_same_points)
    {
        rc::Graph<bool> g = rc::coordinate<bool>(rc::translate(2, 3));
        g._vertices.push_back(rc::vertex(0.0F, 0.0F));
        g._vertices.push_back(rc::vertex(0.0F, 0.0F));

        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_FALSE(maybe_aabb);
    }

    TEST(bounding_box, two_different_points)
    {
        rc::Graph<bool> g = rc::coordinate<bool>(rc::translate(2, 3));
        g._vertices.push_back(rc::vertex(0.0F, 1.0F));
        g._vertices.push_back(rc::vertex(1.0F, 0.0F));

        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_TRUE(maybe_aabb);

        if(maybe_aabb)
        {
            rc::Vertex const& min = maybe_aabb.value().first;
            rc::Vertex const& max = maybe_aabb.value().second;

            EXPECT_FLOAT_EQ(min[0], 0.0F);
            EXPECT_FLOAT_EQ(min[1], 0.0F);
            EXPECT_FLOAT_EQ(max[0], 1.0F);
            EXPECT_FLOAT_EQ(max[1], 1.0F);
        }
    }

    TEST(bounding_box, rectangle)
    {
        rc::Graph<bool> const g = rc::rectangle<bool>(rc::translate(2, 3), rc::vertex(-5, 7), true);
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_TRUE(maybe_aabb);

        if(maybe_aabb)
        {
            rc::Vertex const& min = maybe_aabb.value().first;
            rc::Vertex const& max = maybe_aabb.value().second;

            EXPECT_FLOAT_EQ(min[0], -5.0F);
            EXPECT_FLOAT_EQ(min[1], 0.0F);
            EXPECT_FLOAT_EQ(max[0], 0.0F);
            EXPECT_FLOAT_EQ(max[1], 7.0F);
        }
    }

    TEST(bounding_box, right_triangle)
    {
        rc::Graph<bool> const g = rc::right_triangle<bool>(rc::translate(2, 3), rc::vertex(-5, 7), true);
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_TRUE(maybe_aabb);

        if(maybe_aabb)
        {
            rc::Vertex const& min = maybe_aabb.value().first;
            rc::Vertex const& max = maybe_aabb.value().second;

            EXPECT_FLOAT_EQ(min[0], -5.0F);
            EXPECT_FLOAT_EQ(min[1], 0.0F);
            EXPECT_FLOAT_EQ(max[0], 0.0F);
            EXPECT_FLOAT_EQ(max[1], 7.0F);
        }
    }

    TEST(bounding_box, triangle)
    {
        rc::Graph<bool> const g = rc::triangle<bool>(rc::translate(2, 3), rc::vertex(-5, -7), rc::vertex(11, 13), true);
        std::optional<std::pair<rc::Vertex, rc::Vertex>> const maybe_aabb = rc::bounding_box(g);

        ASSERT_TRUE(maybe_aabb);

        if(maybe_aabb)
        {
            rc::Vertex const& min = maybe_aabb.value().first;
            rc::Vertex const& max = maybe_aabb.value().second;

            EXPECT_FLOAT_EQ(min[0], -5.0F);
            EXPECT_FLOAT_EQ(min[1], -7.0F);
            EXPECT_FLOAT_EQ(max[0], 11.0F);
            EXPECT_FLOAT_EQ(max[1], 13.0F);
        }
    }


}