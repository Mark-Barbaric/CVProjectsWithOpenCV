#pragma once

#include "../platformAPIDefs.h"

#ifndef OBJECT_DETECTION_EXPORT
#define OBJECT_DETECTION_API PLATFORM_DLL_EXPORT
#else
#define OBJECT_DETECTION_API PLATFORM_DLL_IMPORT
#endif

#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    enum class OBJECT_DETECTION_API  LightDifferenceMethod : char {
        Division = 0, Difference, None
    };

    class OBJECT_DETECTION_API Preprocessing{
        static cv::Mat calculateLightPattern(const cv::Mat& image);
        static cv::Mat removeLight(const cv::Mat& image, const cv::Mat& lightPattern, LightDifferenceMethod difference);
    public:
        Preprocessing() = default;
        static cv::Mat removeNoise(const cv::Mat& image);
        static cv::Mat applyLightPattern(const cv::Mat& image, const cv::Mat& imageNoise, LightDifferenceMethod difference);
        static cv::Mat binarizeImage(const cv::Mat& image, LightDifferenceMethod difference);
        static cv::Mat Preprocess(const cv::String& image);
        static cv::Mat Preprocess(const cv::Mat& image);

    };
}