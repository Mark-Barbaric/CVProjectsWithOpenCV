#pragma once
#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    enum class  LightDifferenceMethod : char {
        Division = 0, Difference, None
    };

    class Preprocessing{
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