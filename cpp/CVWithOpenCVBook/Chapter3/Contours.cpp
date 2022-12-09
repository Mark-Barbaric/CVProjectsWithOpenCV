#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

cv::Mat srcGray;
int thresh = 100;
cv::RNG rng(12345);

void threshCallback(int, void*);

int main(int argc, char* argv[]){
    cv::CommandLineParser parser(argc, argv, "{@input | stuff.jpg | input image}");
    cv::Mat src = cv::imread(cv::samples::findFile(parser.get<cv::String>("@input")));

    if(src.empty()){
        std::cout << "Couldn't find or open the image.\n";
        std::cout << "usage: " << argv[0] << "<Input image>.\n";
        return -1;
    }

    cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
    cv::blur(srcGray, srcGray, cv::Size(3,3));

    const char* sourceWindow = "Source";
    cv::namedWindow(sourceWindow);
    cv::imshow(sourceWindow, src);

    const int maxThreshold = 255;
    cv::createTrackbar("Canny thresh:", sourceWindow, &thresh, maxThreshold, threshCallback);
    threshCallback(0,0);

    while(cv::waitKey() != 27){

    }
    return 0;
}

void threshCallback(int, void*){
    cv::Mat cannyOutput;
    cv::Canny(srcGray, cannyOutput, thresh, thresh*2);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(cannyOutput, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
    std::vector<cv::Rect> boundRect (contours.size());
    std::vector<cv::Point2f> centers (contours.size());
    std::vector<float> radius (contours.size());

    for(size_t i = 0; i < contours.size(); ++i){
        cv::approxPolyDP(contours[i], contoursPoly[i], 3, true);
        boundRect[i] = cv::boundingRect(contoursPoly[i]);
        cv::minEnclosingCircle(contoursPoly[i], centers[i], radius[i]);
    }

    cv::Mat drawing = cv::Mat::zeros(cannyOutput.size(), CV_8UC3);

    for(size_t i = 0; i < contours.size(); ++i){
        cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        cv::drawContours(drawing, contoursPoly, static_cast<int>(i), color);
        cv::rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
        cv::circle(drawing, centers[i], static_cast<int>(radius[i]), color, 2);
    }

    cv::imshow("Contours", drawing);
}

