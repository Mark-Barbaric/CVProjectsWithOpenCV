#include <iostream>
#include <string>
#include <sstream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

const char* keys = {
	"{help h usage ? | | print this message}"
    "{@video | | Video file, if not defined try to use webcamera}"
};


int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Chapter 2");

    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::String videoFile = parser.get<cv::String>(0);

    if(!parser.check()){
        parser.printErrors();
        return 0;
    }

    cv::VideoCapture cap;

    if(!videoFile.empty()){
        cap.open(videoFile);
    } else {
        cap.open("Recording3.webm");
    }

    if(!cap.isOpened()){
        
        std::cout << "Failed to open Video Capture.\n";
        return -1;
    }

    cv::namedWindow("Video",1);

    for(;;){

        cv::Mat frame;
        cap >> frame;

        if(frame.empty()){
            return 0;
        }

        cv::imshow("Video", frame);
        
        if(cv::waitKey(30) >= 0){
            break;
        }

    }

    cap.release();

    return 0;
}