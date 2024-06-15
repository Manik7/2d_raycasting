#pragma once

#include <array>

namespace rc {

struct Coordinate
{
    int row{};
    int col{};
    int cha{};
};

template <typename T, int Height, int Width, int Depth, int Padding = 0>
struct Image
{
    static constexpr int height()                         { return Height; }
    static constexpr int width()                          { return Width; }
    static constexpr int depth()                          { return Depth; }
    static constexpr int size()                           { return Height * Width * Depth; }
    static constexpr int padding()                        { return Padding; }
    static constexpr int padded_height()                  { return Height+2*Padding; }
    static constexpr int padded_width()                   { return Width+2*Padding; }
    static constexpr int padded_depth()                   { return Depth+2*Padding; }
    static constexpr int padded_size()                    { return padded_height() * padded_width() * padded_depth(); }
    static constexpr int index(int row, int col, int cha) { return (row+Padding)*padded_width()*padded_depth() + (col+Padding)*padded_depth() + cha+Padding; } // row-major

    Image() = default;
    Image(std::array<T, size()> const& contents, T padding_value)
    {
        std::fill(_data.begin(), _data.end(), padding_value);
        for (int h = 0; h < Height; ++h)
        {
            for (int w = 0; w < Width; ++w)
            {
                for (int d = 0; d < Depth; ++d)
                {
                    (*this)(h, w, d) = contents[h*Width*Depth + w*Depth + d];
                }
            }
        }
    }
    
    T& operator()(int row, int col, int cha)             { return _data[index(row, col, cha)]; }
    T& operator()(Coordinate c)                          { return _data[index(c.row, c.col, c.cha)]; }
    const T& operator()(int row, int col, int cha) const { return _data[index(row, col, cha)]; }
    const T& operator()(Coordinate c) const              { return _data[index(c.row, c.col, c.cha)]; }

    std::array<T, padded_size()> _data{};
};

}
