#include "Preprocessing.h"

namespace ObjectDetection{

    cv::Mat Preprocessing::CalculateLightPattern(const cv::Mat& image) {
        cv::Mat pattern;
        cv::blur(image, pattern, cv::Size(image.cols / 3, image.cols / 3));
        return pattern;
    }

    cv::Mat Preprocessing::RemoveNoise(cv::Mat input) {

        if(input.channels() == 3){
            cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
        }

        cv::Mat imageNoise;
        cv::medianBlur(input, imageNoise, 3);
        return imageNoise;
    }

    cv::Mat Preprocessing::RemoveLight(cv::Mat image, cv::Mat lightPattern) {
        cv::Mat aux;
        cv::Mat img32, pattern32;
        image.convertTo(img32, CV_32F);
        lightPattern.convertTo(pattern32, CV_32F);
        aux = 1 - (img32 / pattern32);
        aux.convertTo(aux, CV_8U, 255);
        return aux;
    }

    cv::Mat Preprocessing::BinarizeImage(const cv::Mat& imageNoLight) {
        cv::Mat imageThreshold;
        cv::threshold(imageNoLight, imageThreshold, 150, 255, cv::THRESH_BINARY_INV);
        return imageThreshold;
    }

    cv::Mat Preprocessing::Preprocess(cv::Mat input) {

        if(input.channels() == 3){
            cv::cvtColor(input, input, cv::COLOR_BGR2GRAY);
        }

        cv::Mat imageNoise = RemoveNoise(input);
        cv::Mat lightPattern = CalculateLightPattern(imageNoise);
        cv::Mat imageWithoutLight = RemoveLight(imageNoise, lightPattern);
        cv::Mat binarizedImage = BinarizeImage(imageWithoutLight);
        return binarizedImage;
    }
}