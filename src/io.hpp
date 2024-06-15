#pragma once

#include <opencv2/core/mat.hpp>
#include "image.hpp"

namespace io
{
    cv::Mat to_cvmat(rc::Image const& image);
}
