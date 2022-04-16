#include "Preprocessing.h"

namespace ObjectDetection{
    Preprocessing::Preprocessing(){

    }

    cv::Mat Preprocessing::removeNoise(const cv::Mat& image) {
        cv::Mat imageNoise;
        cv::medianBlur(image, imageNoise, 3);
        cv::blur(image, imageNoise, cv::Size(3,3));
        return imageNoise;
    }

}