#include <cstdlib>
#include <cstdint>
#include "image.hpp"
#include <opencv2/opencv.hpp>

namespace IMAGE {
    constexpr int height  = 500;
    constexpr int width   = 500;
    constexpr int padding = 0;
}

struct BGR
{
    uint8_t blue{0U};
    uint8_t green{0U};
    uint8_t red{0U};
};

int main()
{
    rc::Image<BGR, IMAGE::height, IMAGE::width, IMAGE::padding> im{};
    for (int i = 0; i < im.height() && im.width(); ++i)
    {
        im(i,i) = BGR{255U, 255U, 255U};
    }
    im(220, 270) = BGR{255U, 255U, 255U};
    im(270, 220) = BGR{255U, 255U, 255U};

    // for some reason the code will not link correctly if I move this opencv code to another cpp file :(
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3); // BGR color

    for (int h = 0; h < IMAGE::height; ++h)
    {
        for (int w = 0; w < IMAGE::width; ++w)
        {
            BGR pixel = im(h, w);
            image.at<cv::Vec3b>(h, w) = cv::Vec3b(pixel.blue, pixel.green, pixel.red);
        }
    }

    cv::imshow("Display window", image);
    cv::waitKey(0); // Wait for a keystroke in the window
    return EXIT_SUCCESS;
}
