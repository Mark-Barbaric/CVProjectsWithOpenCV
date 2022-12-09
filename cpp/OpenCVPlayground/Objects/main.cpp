#ifdef _WIN_32
#include <Windows.h>
#endif

#include <iostream>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "Shape.h"

void getBalls(cv::Mat& img, Objects::Color color, std::vector<Objects::Shape>& balls){

    Objects::Shape ball (color);
    cv::Mat mask;
    cv::inRange(img, ball.getLowMaskScalar(), ball.getHighMaskScalar(), mask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    for(const auto& contour : contours){
        ball.setBounds(cv::boundingRect(contour));
        balls.push_back(ball);
    }
}

void drawBalls(cv::Mat& background, std::vector<Objects::Shape>& balls){

    for(const auto& ball : balls){

        const auto ballColor = ball.getColor();

        switch(ballColor){

            case Objects::Color::Red:
                cv::rectangle(background, ball.getBounds().tl(), ball.getBounds().br(), CV_RGB(255, 0, 0), 2);
                break;
            case Objects::Color::Blue:
                cv::rectangle(background, ball.getBounds().tl(), ball.getBounds().br(), CV_RGB(0, 0, 255), 2);
                break;
            case Objects::Color::Green:
                cv::rectangle(background, ball.getBounds().tl(), ball.getBounds().br(), CV_RGB(0, 255, 0), 2);
                break;
            case Objects::Color::Yellow:
                cv::rectangle(background, ball.getBounds().tl(), ball.getBounds().br(), CV_RGB(255, 255, 0), 2);
                break;
            case Objects::Color::Purple:
                cv::rectangle(background, ball.getBounds().tl(), ball.getBounds().br(), CV_RGB(128, 0, 128), 2);
                break;
        }
    }
}

void runPurpleTest(){
    // https://stackoverflow.com/questions/29331666/hsv-color-detection-with-opencv
}

int main(int argc, char** argv) {

    if(argc == 1){
        std::cerr << "Can't run program without image.\n";
        return 1;
    }

    const std::string imageName = argv[1];
    const auto imageFileName = R"(C:\Users\mark.barbaric\Documents\Developer\CPP\CasualGamer\)" + imageName;

    std::cout << "Attempting to load image: " << imageFileName << "from file.\n";
    cv::Mat sourceImage = cv::imread(imageFileName, cv::IMREAD_COLOR);

    if(sourceImage.empty() || !sourceImage.data){
        std::cerr << "Couldn't find example image.\n";
        return 1;
    }

    std::cout <<"Image: " << imageFileName << " loaded.\n";

    std::cout << "Converting image to HSV.\n";
    cv::Mat sourceImageHSV;
    cv::cvtColor(sourceImage, sourceImageHSV, cv::COLOR_BGR2HSV);

    if(imageName == "image1.jpeg"){
        cv::rectangle(sourceImageHSV, cv::Point(0,0), cv::Point(sourceImage.cols, 90), CV_RGB(0,0,0), cv::FILLED);
    }

    cv::imshow("HSV Image", sourceImageHSV);

    cv::waitKey(30);

    std::vector<Objects::Shape> balls;

    while(cv::waitKey(0) != 27){

        for(int color = static_cast<int>(Objects::Color::Yellow); static_cast<Objects::Color>(color) != Objects::Color::Purple; color++){
            getBalls(sourceImageHSV, static_cast<Objects::Color>(color), balls);
        }

        drawBalls(sourceImage, balls);
        cv::imshow("output", sourceImage);
    }

    return 0;
}
