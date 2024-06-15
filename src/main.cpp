#include <cstdlib>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3); // BGR color
    image.diag().setTo(cv::Vec3b(255, 255, 255));
    image.at<cv::Vec3b>(220, 270) = cv::Vec3b(255, 255, 255); // set a particular pixel
    image.at<cv::Vec3b>(270, 220) = cv::Vec3b(255, 255, 255);
    cv::imshow("Display window", image);
    cv::waitKey(0); // Wait for a keystroke in the window
    return EXIT_SUCCESS;
}
