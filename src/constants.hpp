#pragma once

#include <cstdint>

namespace rc
{
    struct BGR
    {
        uint8_t _blue{0U};
        uint8_t _green{0U};
        uint8_t _red{0U};
    };

    namespace image
    {
        constexpr int height  = 500;
        constexpr int width   = 800;
        constexpr int padding = 0;
    }

    namespace color
    {
        constexpr BGR white   = BGR{255U, 255U, 255U};
        constexpr BGR grey    = BGR{122U, 122U, 122U};
        constexpr BGR black   = BGR{  0U,   0U,   0U};
        constexpr BGR blue    = BGR{255U,   0U,   0U};
        constexpr BGR cyan    = BGR{255U, 255U,   0U};
        constexpr BGR green   = BGR{  0U, 255U,   0U};
        constexpr BGR yellow  = BGR{  0U, 255U, 255U};
        constexpr BGR red     = BGR{  0U,   0U, 255U};
        constexpr BGR magenta = BGR{255U,   0U, 255U};
    }

}
