#include <cstdlib>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "constants.hpp"
#include "draw.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "io.hpp"
#include "raycast.hpp"
#include "transformations.hpp"

int main()
{
    using namespace rc;

    // INPUT

    // SCENE GRAPH

    // RAYCASTING

    Image image{};

    // points above and below the diagonal
    Vertex p1 = vertex(220, 270);
    Vertex p2 = translate(50, -50) * p1;
    draw(p1, color::green, image);
    draw(p2, color::magenta, image);

    // a point to check that (height, width) and (1st coordinate, 2nd coordinate) are consistent
    draw(vertex(image::height-100, image::width-100), color::red, image);

    // diagonal
    draw(vertex(0, 0), vertex(499, 499), color::white, image);

    // multi-color square
    draw(vertex(400, 60), vertex(400, 100), color::yellow, image);
    draw(vertex(400, 100), vertex(360, 100), color::cyan, image);
    draw(vertex(360, 100), vertex(360, 60), color::magenta, image);
    draw(vertex(360, 60), vertex(400, 60), color::white, image);

    // points along an arc
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

    // rectangle
    Graph rect = rectangle(translate(100, 400), vertex(40, 40), color::white);
    draw_vertices(rect, image);
    draw_lines(rect, image);

    // OUTPUT
    auto cvmat = io::to_cvmat(image);
    cv::imshow("Display window", cvmat);
    cv::waitKey(0); // Wait for a keystroke in the window
    return EXIT_SUCCESS;
}
