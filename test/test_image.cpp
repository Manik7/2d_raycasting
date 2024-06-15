#include <gtest/gtest.h>
#include <cmath>
#include "../src/image.hpp"

namespace {

TEST(image, index)
{
    const rc::Image<char, 3, 2, 1, 0> image{};

    EXPECT_EQ(image.index(0, 0, 0), 0);
    EXPECT_EQ(image.index(0, 1, 0), 1);
    EXPECT_EQ(image.index(1, 0, 0), 2);
    EXPECT_EQ(image.index(1, 1, 0), 3);
    EXPECT_EQ(image.index(2, 0, 0), 4);
    EXPECT_EQ(image.index(2, 1, 0), 5);
}

TEST(image, index_padded)
{
    //  .  .  .  .
    //  . 25 26  .
    //  . 29 30  .
    //  . 33 34  .
    //  .  .  .  .

    const rc::Image<char, 3, 2, 1, 1> image{};

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image.height(), 3);
    ASSERT_EQ(image.width(), 2);
    ASSERT_EQ(image.padded_size(), 60);
    ASSERT_EQ(image.padded_height(), 5);
    ASSERT_EQ(image.padded_width(), 4);
    ASSERT_EQ(image.padded_depth(), 3);

    EXPECT_EQ(image.index(0, 0, 0), 16);
    EXPECT_EQ(image.index(0, 1, 0), 19);
    EXPECT_EQ(image.index(1, 0, 0), 28);
    EXPECT_EQ(image.index(1, 1, 0), 31);
    EXPECT_EQ(image.index(2, 0, 0), 40);
    EXPECT_EQ(image.index(2, 1, 0), 43);
}

TEST(image, empty)
{
    const rc::Image<char, 0, 0, 0, 0> image{};

    ASSERT_EQ(image.size(), 0);
    ASSERT_EQ(image._data.size(), 0);
    EXPECT_EQ(image.height(), 0);
    EXPECT_EQ(image.width(), 0);
    EXPECT_EQ(image.depth(), 0);
}

TEST(image, symbols)
{
    const rc::Image<char, 1, 6, 1, 0> image({'a', 'b', 'c', 'd', 'e', 'f'}, '0');

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image._data.size(), 6);
    EXPECT_EQ(image.height(), 1);
    EXPECT_EQ(image.width(), 6);
    ASSERT_EQ(image.depth(), 1);
    EXPECT_EQ(image(0, 0, 0), 'a');
    EXPECT_EQ(image(0, 1, 0), 'b');
    EXPECT_EQ(image(0, 2, 0), 'c');
    EXPECT_EQ(image(0, 3, 0), 'd');
    EXPECT_EQ(image(0, 4, 0), 'e');
    EXPECT_EQ(image(0, 5, 0), 'f');
}

TEST(image, six)
{
    const rc::Image<char, 3, 2, 1, 0> image({'a', 'b', 'c', 'd', 'e', 'f'}, '0');

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image._data.size(), 6);
    EXPECT_EQ(image.height(), 3);
    EXPECT_EQ(image.width(), 2);
    ASSERT_EQ(image.depth(), 1);
    EXPECT_EQ(image(0, 0, 0), 'a');
    EXPECT_EQ(image(0, 1, 0), 'b');
    EXPECT_EQ(image(1, 0, 0), 'c');
    EXPECT_EQ(image(1, 1, 0), 'd');
    EXPECT_EQ(image(2, 0, 0), 'e');
    EXPECT_EQ(image(2, 1, 0), 'f');
}

TEST(image, six_padded)
{
    const rc::Image<char, 3, 2, 1, 1> image({'a', 'b', 'c', 'd', 'e', 'f'}, '0');

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image.height(), 3);
    ASSERT_EQ(image.width(), 2);
    ASSERT_EQ(image.depth(), 1);
    ASSERT_EQ(image.padded_size(), 60);
    ASSERT_EQ(image.padded_height(), 5);
    ASSERT_EQ(image.padded_width(), 4);
    ASSERT_EQ(image.padded_depth(), 3);
    EXPECT_EQ(image(0, 0, 0), 'a');
    EXPECT_EQ(image(0, 1, 0), 'b');
    EXPECT_EQ(image(1, 0, 0), 'c');
    EXPECT_EQ(image(1, 1, 0), 'd');
    EXPECT_EQ(image(2, 0, 0), 'e');
    EXPECT_EQ(image(2, 1, 0), 'f');
}

TEST(image, floats)
{
    // astoundingly, even this unit test, with a value type which cannot be converted implicitely, would not have made
    // a difference in the cryptic compiler output for the bug which cost me so much time

    const rc::Image<float, 3, 2, 1, 1> image({0.0F, 1.0F, 2.0F, 3.0F, 4.0F, 5.0F}, NAN);

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image.padded_size(), 60);
    EXPECT_FLOAT_EQ(image(0, 0, 0), 0.0F);
    EXPECT_FLOAT_EQ(image(0, 1, 0), 1.0F);
    EXPECT_FLOAT_EQ(image(1, 0, 0), 2.0F);
    EXPECT_FLOAT_EQ(image(1, 1, 0), 3.0F);
    EXPECT_FLOAT_EQ(image(2, 0, 0), 4.0F);
    EXPECT_FLOAT_EQ(image(2, 1, 0), 5.0F);
}

}
