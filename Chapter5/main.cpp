#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <ObjectDetection/Preprocessing.h>

constexpr char* keys ={
                "{help h usage ? | | print this message}"
                "{@image || Image to process}"
                "{@lightPattern || Image light pattern to apply to image input}"
                "{lightMethod | 1 | Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal' }"
                "{segMethod | 1 | Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours }"
};

int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    ObjectDetection::Preprocessing preprocessing;

    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }

    const auto imageFile = parser.get<cv::String>(0);
    const auto lightPatternFile = parser.get<cv::String>(0);

    return 0;
}