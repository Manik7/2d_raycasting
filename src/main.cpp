#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include "constants.hpp"
#include "image.hpp"
#include "io.hpp"
#include "raycast.hpp"

int main()
{
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
