#include "constants.hpp"
#include "draw.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "raycast.hpp"
#include "transformations.hpp"

namespace rc 
{
    Image raycast()
    {
        Image image{};
        for (int i = 0; i < image.height() && image.width(); ++i)
        {
            image(i,i) = color::white;
        }

        Vertex p1 = vertex(220, 270);
        Vertex p2 = translate(50, -50) * p1;
        draw(p1, color::green, image);
        draw(p2, color::magenta, image);

        draw(p1, p2, color::magenta, image);

        Transformation R = rotate(Degrees{-10});
        Vertex a = vertex(0, 200);
        draw(a, color::cyan, image);
        draw(R*a, color::cyan, image);
        draw(R*R*a, color::cyan, image);
        draw(R*R*R*a, color::cyan, image);
        draw(R*R*R*R*a, color::cyan, image);
        draw(R*R*R*R*R*a, color::cyan, image);
        draw(R*R*R*R*R*R*a, color::cyan, image);
        draw(R*R*R*R*R*R*R*a, color::cyan, image);
        draw(R*R*R*R*R*R*R*R*a, color::cyan, image);
        draw(R*R*R*R*R*R*R*R*R*a, color::cyan, image);
        return image;
    }

}
