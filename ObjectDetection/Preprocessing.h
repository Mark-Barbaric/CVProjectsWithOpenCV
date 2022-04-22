#pragma once
#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    enum class  LightDifference : char {
        Division = 0, Difference
    };

    enum class SegmentationMethod : char {
        ConnectedComponents = 0, ConnectedComponentsWithStats, FindContoursBasic
    };

    class Preprocessing{
    public:
        static cv::Mat calculateLightPattern(const cv::Mat& image);
        static cv::Mat removeLight(const cv::Mat& image, const cv::Mat& lightPattern, LightDifference difference);
        Preprocessing();
        static cv::Mat removeNoise(const cv::Mat& image);
        static cv::Mat applyLightPattern(const cv::Mat& image, const cv::Mat& imageNoise, LightDifference difference);

    };
}