#include "Preprocessing.h"
#include <opencv2/imgcodecs.hpp>

namespace ObjectDetection{

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

    cv::Mat Preprocessing::removeLight(const cv::Mat &image, const cv::Mat& lightPattern, LightDifferenceMethod difference) {
        cv::Mat aux;
        switch(difference){
            case LightDifferenceMethod::Division: {
                cv::Mat img32, pattern32;
                cv::Mat imageCopy = image.clone(), lightPatternCopy = lightPattern.clone();
                imageCopy.convertTo(img32, CV_32F);
                lightPatternCopy.convertTo(pattern32, CV_32F);
                aux = 1 - (img32 / pattern32);
                aux.convertTo(aux, CV_8U, 255);
                break;
            }
            case LightDifferenceMethod::Difference:{
                aux = lightPattern - image;
                break;
            }

            default:{
                break;
            }

        }
        return aux;
    }

    cv::Mat Preprocessing::applyLightPattern(const cv::Mat& image, const cv::Mat& imageNoise, LightDifferenceMethod method) {

        cv::Mat lightPattern = calculateLightPattern(image);
        cv::medianBlur(lightPattern, lightPattern, 3);
        cv::Mat imageNoLight;
        imageNoise.copyTo(imageNoLight);
        imageNoLight = removeLight(imageNoise, lightPattern, method);
        return imageNoLight;
    }

    cv::Mat Preprocessing::binarizeImage(const cv::Mat &imageNoLight, LightDifferenceMethod method) {
        cv::Mat imageThreshold;

        if(method == LightDifferenceMethod::None){
            cv::threshold(imageNoLight, imageThreshold, 150, 255, cv::THRESH_BINARY_INV);
        } else {
            cv::threshold(imageNoLight, imageThreshold, 30, 255, cv::THRESH_BINARY);
        }

        return imageThreshold;
    }

    cv::Mat Preprocessing::Preprocess(const cv::String &image) {
        assert(!image.empty());
        const auto imageGreyscale = cv::imread(image, cv::IMREAD_GRAYSCALE);
        const auto imageNoise = removeNoise(imageGreyscale);
        const auto imageWithoutLight = applyLightPattern(imageGreyscale, imageNoise, ObjectDetection::LightDifferenceMethod::Division);
        return binarizeImage(imageWithoutLight, ObjectDetection::LightDifferenceMethod::Division);
    }

    cv::Mat Preprocessing::Preprocess(const cv::Mat &input) {

        auto newInput = input.clone();

        if(newInput.channels() == 3){
            cv::cvtColor(newInput, newInput, cv::COLOR_RGB2GRAY);
        }

        const auto imageNoise = removeNoise(newInput);
        const auto imageWithoutLight = applyLightPattern(newInput, imageNoise, ObjectDetection::LightDifferenceMethod::Division);
        return binarizeImage(imageWithoutLight, ObjectDetection::LightDifferenceMethod::Division);
    }
}