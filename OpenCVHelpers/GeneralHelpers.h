#include <opencv2/imgproc.hpp>

namespace OpenCVHelpers::GeneralHelpers{

    inline cv::Scalar generateRandomColor(cv::RNG& rng){
        cv::Scalar randomColor(static_cast<unsigned>(rng)&255,
                          static_cast<unsigned>(rng) >> 8 &255,
                          static_cast<unsigned>(rng) >> 16 & 255);
        return randomColor;
    }
}