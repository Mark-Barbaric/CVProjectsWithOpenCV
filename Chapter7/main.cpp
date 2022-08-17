#include <opencv2/core/utility.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _WIN32
constexpr auto RESOURCE_FILE_PATH = R"(C:\Users\mark.barbaric\Documents\Developer\CPP\OpenCV\CVProjectsWithOpenCV\Chapter7\Resources\)";
#endif

int main(int argc, char** argv){

    if(argc < 3){
        std::cerr << "Cannot start without cascade file and face image.\n";
        return 1;
    }

    std::cout << "Loading Cascade File.\n";

    std::string cascadeFileName = std::string(RESOURCE_FILE_PATH) + argv[1];
    cv::CascadeClassifier faceCascade;

    if(!faceCascade.load(cascadeFileName)){
        std::cerr << "Failed to load cascade file: " << cascadeFileName << "\n";
        return 1;
    }

    std::cout << "Loading Face Mask.\n";

    std::string faceMaskFilePath = std::string(RESOURCE_FILE_PATH) + argv[2];
    cv::Mat faceMask = cv::imread(faceMaskFilePath, cv::IMREAD_COLOR);

    if(!faceMask.data){
        std::cerr << "Unable to load face image: " << faceMaskFilePath << "\n";
        return 1;
    }

    cv::Mat frame, frameGray;
    cv::Mat frameROI, faceMaskSmall;
    cv::Mat grayMaskSmall, grayMaksSmallThresh, grayMaskSmallThreshInv;
    cv::Mat maskedFace, maskedFrame;

    cv::VideoCapture videoCapture(0);

    if(!videoCapture.isOpened()){
        std::cerr << "Failed to load webcam.\n";
        return -1;
    }

    cv::namedWindow("Frame");
    float scalingFactor = 0.75f;

    std::vector<cv::Rect> faces;

    while(true){

        videoCapture >> frame;
        try{
            cv::resize(frame, frame, cv::Size(), scalingFactor, scalingFactor, cv::INTER_AREA);

            cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

            cv::equalizeHist(frameGray, frameGray);

        } catch(const std::exception& e){
            std::cout << "Failed to apply mask to frame with error: " << e.what() << "\n";
            return 1;
        }
        if(cv::waitKey(30) == 27){
            break;
        }
    }

    return 0;
}