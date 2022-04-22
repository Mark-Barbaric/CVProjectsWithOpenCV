#include "Preprocessing.h"
#include <opencv2/highgui.hpp>

namespace ObjectDetection{
    Preprocessing::Preprocessing(){

    }

    cv::Mat Preprocessing::calculateLightPattern(const cv::Mat& image) {
        cv::Mat pattern;
        cv::blur(image, pattern, cv::Size(image.cols / 3, image.cols / 3));
        return pattern;
    }

    cv::Mat Preprocessing::removeNoise(const cv::Mat& image) {
        cv::Mat imageGreyscale;
        cv::cvtColor(image, imageGreyscale, cv::COLOR_BGR2GRAY);
        cv::Mat imageNoise;
        cv::medianBlur(imageGreyscale, imageNoise, 3);
        cv::blur(imageGreyscale, imageNoise, cv::Size(3,3));
        return imageNoise;
    }

    cv::Mat Preprocessing::removeLight(const cv::Mat &image, const cv::Mat& lightPattern, LightDifference difference) {
        cv::Mat aux;
        switch(difference){
            case LightDifference::Division: {
                cv::Mat img32, pattern32;
                cv::Mat imageCopy = image.clone(), lightPatternCopy = lightPattern.clone();
                imageCopy.convertTo(img32, CV_32F);
                lightPatternCopy.convertTo(pattern32, CV_32F);
                aux = 1 - (img32 / pattern32);
                aux.convertTo(aux, CV_8U, 255);
                break;
            }
            case LightDifference::Difference:{
                aux = lightPattern - image;
                break;
            }

            default:{
                break;
            }

        }
        return aux;
    }

    cv::Mat Preprocessing::applyLightPattern(const cv::Mat& image, const cv::Mat& imageNoise, LightDifference difference) {

        cv::Mat lightPattern = calculateLightPattern(image);
        cv::medianBlur(lightPattern, lightPattern, 3);
        cv::Mat imageNoLight;
        imageNoise.copyTo(imageNoLight);
        imageNoLight = removeLight(imageNoise, lightPattern, difference);
        return imageNoLight;
    }
}