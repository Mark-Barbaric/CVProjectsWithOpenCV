#include "Segmentation.h"
#include <Lib/OpenCVHelpers/GeneralHelpers.h>
#include <iostream>

namespace ObjectDetection{

    cv::Mat Segmentation::connectedComponents(const cv::Mat& image){
        cv::Mat output;

        cv::Mat labels;
        const auto numObjects = cv::connectedComponents(image, labels) - 1;

        if(numObjects == 0){
            return {};
        }

        output = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
        cv::RNG rng (0xFFFFFFFF);

        for(auto i = 0; i < numObjects; ++i){
            cv::Mat mask = labels == i;
            output.setTo(OpenCVHelpers::GeneralHelpers::generateRandomColor(rng),
                         mask);
        }

        return output;
    }

    cv::Mat Segmentation::connectComponentsWithStats(const cv::Mat &image) {
        cv::Mat labels, stats, centroids;
        const auto numObjects = cv::connectedComponentsWithStats(image, labels, stats, centroids) - 1;

        if(numObjects == 0){
            return {};
        }

        cv::Mat output = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
        cv::RNG rng (0xFFFFFFFF);

        for(auto i = 0; i < numObjects; ++i){
            std::cout << "Object " << i << " with pos: " << centroids.at<cv::Point2d>(i) << " with area "
            << stats.at<int>(i, cv::CC_STAT_AREA) << std::endl;

            cv::Mat mask = labels == i;
            output.setTo(OpenCVHelpers::GeneralHelpers::generateRandomColor(rng), mask);
            std::stringstream ss;
            ss << "area: " << stats.at<int>(i, cv::CC_STAT_AREA);

            cv::putText(output,
                        ss.str(),
                        centroids.at<cv::Point2d>(i),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.4,
                    cv::Scalar(255,255,255));
        }
        return output;
    }

    cv::Mat Segmentation::contourBasic(const cv::Mat &image) {
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::Mat output = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);

        if(contours.empty()){
            return {};
        }

        cv::RNG rng(0xFFFFFFFF);

        for(auto i = 0; i < contours.size(); ++i){
            cv::drawContours(output, contours, i,
                             OpenCVHelpers::GeneralHelpers::generateRandomColor(rng));
        }

        return output;
    }

    cv::Mat Segmentation::segmentImage(const cv::Mat &image, SegmentationMethod method) {

        switch(method){
            case SegmentationMethod::ConnectedComponents: {
                return connectedComponents(image);
            }

            case SegmentationMethod::ConnectedComponentsWithStats:{
                return connectComponentsWithStats(image);
            }

            case SegmentationMethod::FindContoursBasic:{
                return contourBasic(image);
            }

            default: {
                return {};
            }
        }
    }
}