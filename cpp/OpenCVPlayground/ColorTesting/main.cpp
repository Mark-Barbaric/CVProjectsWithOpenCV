#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

enum struct ColorName : int {
    Red = 0, Blue, Green, Purple, Yellow
};

using HSVThreshold = std::pair<cv::Scalar, cv::Scalar>;

inline HSVThreshold getColorThreshold(ColorName color, size_t hueRange){
    switch(color){
        case ColorName::Red:
            return std::make_pair(cv::Scalar(0, 53, 185), cv::Scalar(255, 255, 0));
        default:
            return {};
    }
}

// res hsv sits between 0 - 10 and 160 - 180

int main(int argc, char** argv){

    const std::string testImage = R"(C:\Users\mark.barbaric\Documents\Developer
\CPP\OpenCV\CVProjectsWithOpenCV\OpenCVPlayground\ColorTesting\img.png)";

    cv::Mat input = cv::imread(testImage, cv::IMREAD_COLOR);
    cv::Mat inputBGR;
    cv::cvtColor(input, inputBGR, cv::COLOR_BGR2HSV);

    if(!input.data){
        std::cerr << "Failed to load test image.";
        return 1;
    }



}