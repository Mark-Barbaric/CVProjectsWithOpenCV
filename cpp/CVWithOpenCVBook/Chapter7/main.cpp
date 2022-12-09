#include <opencv2/core/utility.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _WIN32
constexpr auto RESOURCE_FILE_PATH = R"(C:\Users\mark.barbaric\Documents\Developer\CPP\OpenCV\CVProjectsWithOpenCV\CVWithOpenCV\Chapter7\Resources\)";
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
    cv::Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
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

            faceCascade.detectMultiScale(frameGray, faces, 1.1, 2,
                                         0| cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

            for(const auto& face : faces){

                cv::Rect rect(face.x, face.y, face.width, face.height);

                const auto x = face.x - static_cast<int>(0.1 * face.width);
                const auto y = face.y - static_cast<int>(0.1 * face.height);
                const auto w = static_cast<int>(1.1 * face.width);
                const auto h = static_cast<int>(1.3 * face.height);

                frameROI = frame(cv::Rect(x, y, w, h));
                cv::resize(faceMask, faceMaskSmall, cv::Size(w, h));
                cv::cvtColor(faceMaskSmall, grayMaskSmall, cv::COLOR_BGR2GRAY);
                cv::threshold(grayMaskSmall, grayMaskSmallThresh, 230, 255, cv::THRESH_BINARY_INV);
                cv::bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);
                cv::bitwise_and(faceMaskSmall, faceMaskSmall, maskedFace, grayMaskSmallThresh);
                cv::bitwise_and(frameROI, frameROI, maskedFrame, grayMaskSmallThresh);

                if(x > 0 && y > 0 && x + w < frame.cols && y + h < frame.rows){
                    cv::add(maskedFace, maskedFrame, frame(cv::Rect(x,y,w,h)));
                }

            }

        } catch(const std::exception& e){
            std::cout << "Failed to apply mask to frame with error: " << e.what() << "\n";
            return 1;
        }

        cv::imshow("Frame", frame);

        if(cv::waitKey(30) == 27){
            break;
        }
    }

    return 0;
}