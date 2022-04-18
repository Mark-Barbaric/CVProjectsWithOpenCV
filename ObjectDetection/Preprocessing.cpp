#include "Preprocessing.h"
#include <opencv2/highgui.hpp>

namespace ObjectDetection{
    Preprocessing::Preprocessing(){

    }

    cv::Mat Preprocessing::removeNoise(const cv::String& imageFile) {
        cv::Mat imageGreyscale = cv::imread(imageFile, cv::IMREAD_GRAYSCALE);
        cv::Mat imageNoise;
        cv::medianBlur(imageGreyscale, imageNoise, 3);
        cv::blur(imageGreyscale, imageNoise, cv::Size(3,3));
        return imageNoise;
    }

}