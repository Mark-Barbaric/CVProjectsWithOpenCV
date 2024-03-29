#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <lib/ObjectDetection/Preprocessing.h>
#include <lib/ObjectDetection/Segmentation.h>

//https://github.com/PacktPublishing/Building-Computer-Vision-Projects-with-OpenCV4-and-CPlusPlus/blob/master/Chapter05/main.cpp
constexpr auto imageFolder = "/Users/markbarbaric/Documents/Developer/CPP/OpenCV/CVProjectsWithOpenCV/Images/";

const char* keys ={
                "{help h usage ? | | print this message}"
                "{@image || Image to process}"
                "{@lightPattern || Image light pattern to apply to image input}"
                "{lightMethod | 1 | Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal' }"
                "{segMethod | 1 | Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours }"
};

int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    cv::String imageFile;

    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }

    imageFile = parser.get<cv::String>(0).empty() ? cv::String(imageFolder) + "pins.jpg" :
                parser.get<cv::String>(0);

    const auto image = cv::imread(imageFile, cv::IMREAD_COLOR);

    if(image.data == nullptr){
        std::cout << "Failed to load image.\n";
        return -1;
    }

    cv::namedWindow("Test");
    cv::imshow("Image Before" , image);

    cv::Mat imageGreyscale, imageNoise, imageWithoutLight, imageThreshold;

    try{
        imageGreyscale = cv::imread(imageFile, cv::IMREAD_COLOR);
        imageNoise = ObjectDetection::Preprocessing::RemoveNoise(image);
        imageWithoutLight = ObjectDetection::Preprocessing::RemoveLight(imageGreyscale, imageNoise);
        imageThreshold = ObjectDetection::Preprocessing::BinarizeImage(imageWithoutLight);
    } catch(const std::exception& e){
        std::cout << e.what() << ".\n";
    }

    cv::imshow("Image Greyscale" , imageGreyscale);
    cv::imshow("Image Noise" , imageNoise);
    cv::imshow("Image Without Light" , imageWithoutLight);
    cv::imshow("Image Threshold" , imageThreshold);

    for (auto i = 0; i < 3; ++i) {
        const auto connectedComponents = ObjectDetection::Segmentation::segmentImage(imageThreshold,
                                                                                     static_cast<ObjectDetection::SegmentationMethod>(i));
        cv::imshow("Segmentation #" + std::to_string(i), connectedComponents);
    }

    cv::waitKey(0);
    return 0;
}