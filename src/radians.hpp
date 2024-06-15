#pragma once
#include <cmath>

namespace rc
{
    struct Radians
    {
        explicit constexpr Radians(float radians) : _radians{radians} {}
        const float _radians;
    };

    struct Degrees
    {
        explicit constexpr Degrees(float degrees) : _degrees{degrees} {}
        const float _degrees;
    };

    constexpr float pi() { return std::asin(1.0F) * 2.0F; }
    constexpr Radians to_radians(Degrees deg) { return Radians{deg._degrees * pi() * 1.0F/180.0F}; }
    constexpr Degrees to_degrees(Radians rad) { return Degrees{rad._radians * 180.0F * 1.0F/pi()}; }
}
