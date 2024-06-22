#include <opencv2/core/mat.hpp>

#include "constants.hpp"
#include "image.hpp"
#include "io.hpp"

namespace io
{
    cv::Mat to_cvmat(rc::Image const& image)
    {
        cv::Mat result = cv::Mat::zeros(image.height(), image.width(), CV_8UC3); // BGR color
        for (int h = 0; h < image.height(); ++h)
        {
            for (int w = 0; w < image.width(); ++w)
            {
                rc::BGR pixel = image(h, w);
                result.at<cv::Vec3b>(h, w) = cv::Vec3b(pixel._blue, pixel._green, pixel._red);
            }
        }
        return result;
    }
}
