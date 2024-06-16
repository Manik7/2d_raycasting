#pragma once

#include <array>
#include "constants.hpp"

namespace rc {

template <typename T, int Height, int Width, int Padding = 0>
struct GenericImage
{
    static constexpr int height()                { return Height; }
    static constexpr int width()                 { return Width; }
    static constexpr int size()                  { return Height * Width; }
    static constexpr int padding()               { return Padding; }
    static constexpr int padded_height()         { return Height+2*Padding; }
    static constexpr int padded_width()          { return Width+2*Padding; }
    static constexpr int padded_size()           { return padded_height() * padded_width(); }
    static constexpr int index(int row, int col) { return (row+Padding)*padded_width() + (col+Padding); } // row-major
    static constexpr bool isPixelInBounds(int row, int col){ return 0 <= row && row < Height && 0 <= col && col < Width; }

    GenericImage() = default;
    GenericImage(std::array<T, size()> const& contents, T padding_value)
    {
        std::fill(_data.begin(), _data.end(), padding_value);
        for (int h = 0; h < Height; ++h)
        {
            for (int w = 0; w < Width; ++w)
            {
                (*this)(h, w) = contents[h*Width + w];
            }
        }
    }
    
    T& operator()(int row, int col)              { return _data[index(row, col)]; }
    const T& operator()(int row, int col) const  { return _data[index(row, col)]; }

    std::array<T, padded_size()> _data{};
};

using Image = GenericImage<BGR, image::height, image::width, image::padding>;

}
