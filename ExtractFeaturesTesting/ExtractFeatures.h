#pragma once
#include <opencv2/imgcodecs.hpp>
#include <vector>

class SegmentationTesting{

public:
    static std::vector<std::vector<float>> ExtractFeatures(cv::Mat& input);
};