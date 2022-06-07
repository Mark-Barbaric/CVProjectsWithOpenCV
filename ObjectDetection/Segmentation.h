#pragma once

#include "../platformAPIDefs.h"

#ifndef OBJECT_DETECTION_EXPORT
#define OBJECT_DETECTION_API PLATFORM_DLL_EXPORT
#else
#define OBJECT_DETECTION_API PLATFORM_DLL_IMPORT
#endif

#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    enum class SegmentationMethod : int {
        ConnectedComponents = 0, ConnectedComponentsWithStats, FindContoursBasic
    };

    class OBJECT_DETECTION_API Segmentation{

        static cv::Mat connectedComponents(const cv::Mat& image);
        static cv::Mat connectComponentsWithStats(const cv::Mat& image);
        static cv::Mat contourBasic(const cv::Mat& image);

    public:

        static cv::Mat segmentImage(const cv::Mat& image, SegmentationMethod method);
    };

}