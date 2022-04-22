#include "Segmentation.h"

namespace ObjectDetection{

    cv::Mat Segmentation::connectedComponents(const cv::Mat& image){
        cv::Mat output;

        cv::Mat labels;
        const auto numObjects = cv::connectedComponents(image, labels) - 1;

        if(numObjects == 0){
            return {};
        }

        output = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
        cv::RNG rng(0XFFFFFFFF);

        for(auto i = 0; i < numObjects; ++i){
            cv::Mat mask = labels == i;
            output.setTo(cv::Scalar(static_cast<unsigned>(rng)&255,
                                    static_cast<unsigned>(rng) >> 8 &255,
                         static_cast<unsigned>(rng) >> 16 & 255),
                         mask);
        }

        return output;
    }

    cv::Mat Segmentation::segmentImage(const cv::Mat &image, SegmentationMethod method) {

        switch(method){
            case SegmentationMethod::ConnectedComponents: {
                return connectedComponents(image);
            }

            default: {
                return {};
            }
        }
    }
}