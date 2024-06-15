#include <cstdlib>
#include <iostream>
#include <Eigen/Dense>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "constants.hpp"
#include "image.hpp"
#include "io.hpp"
#include "raycast.hpp"

int main()
{
    Eigen::Matrix3d a;
    a << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    Eigen::Matrix3d b;
    b << 2, 3, 1,
         4, 6, 7,
         8, 5, 9;
    std::cout << "a + b =\n" << a + b << std::endl;
    std::cout << "a - b =\n" << a - b << std::endl;

    using namespace rc;

    // INPUT

    // SCENE GRAPH

    // RAYCASTING
    const Image image = raycast();

    // OUTPUT
    auto cvmat = io::to_cvmat(image);
    cv::imshow("Display window", cvmat);
    cv::waitKey(0); // Wait for a keystroke in the window
    return EXIT_SUCCESS;
}
