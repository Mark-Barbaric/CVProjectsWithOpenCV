#pragma once
#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    class Preprocessing{

    public:
        Preprocessing();
        static cv::Mat removeNoise(const cv::Mat& image);

    };
}