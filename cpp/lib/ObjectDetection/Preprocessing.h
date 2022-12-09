#pragma once

#include "platformAPIDefs.h"

#ifndef OBJECT_DETECTION_EXPORT
#define OBJECT_DETECTION_API PLATFORM_DLL_EXPORT
#else
#define OBJECT_DETECTION_API PLATFORM_DLL_IMPORT
#endif

#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    class OBJECT_DETECTION_API Preprocessing{
        static cv::Mat CalculateLightPattern(const cv::Mat& image);
    public:
        Preprocessing() = default;
        static cv::Mat RemoveNoise(cv::Mat image);
        static cv::Mat RemoveLight(cv::Mat image, cv::Mat lightPattern);
        static cv::Mat BinarizeImage(const cv::Mat& image);
        static cv::Mat Preprocess(cv::Mat image);

    };
}