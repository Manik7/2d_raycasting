#include "constants.hpp"
#include "image.hpp"
#include "raycast.hpp"

namespace rc 
{

rc::Image raycast()
{
    rc::Image image{};
    for (int i = 0; i < image.height() && image.width(); ++i)
    {
        image(i,i) = BGR{255U, 255U, 255U};
    }
    image(220, 270) = BGR{255U, 255U, 255U};
    image(270, 220) = BGR{255U, 255U, 255U};
    return image;
}

}
