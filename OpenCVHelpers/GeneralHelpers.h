#include <opencv2/imgproc.hpp>

namespace OpenCVHelpers::GeneralHelpers{

    cv::Scalar red(255, 0, 0);
    cv::Scalar green(0, 255,0);
    cv::Scalar blue(0, 0, 255);

    inline cv::Scalar generateRandomColor(cv::RNG& rng){
        cv::Scalar randomColor(static_cast<unsigned>(rng)&255,
                          static_cast<unsigned>(rng) >> 8 &255,
                          static_cast<unsigned>(rng) >> 16 & 255);
        return randomColor;
    }
}