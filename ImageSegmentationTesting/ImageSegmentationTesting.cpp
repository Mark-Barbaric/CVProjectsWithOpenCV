#include <ObjectDetection/Preprocessing.h>
#include <OpenCVHelpers/MultipleImageWindow.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>


const char* cliKeys = {
        "{help h usage ? | | print this message}"
        "{@imageDirectory | | Image Directory to use}"
};


int main(int argc, char** argv){
    cv::CommandLineParser cliParser(argc, argv, cliKeys);

    if(cliParser.has("help")){
        cliParser.printMessage();
        return 0;
    }

    const auto imageDirectory = cliParser.get<cv::String>(0);

    if(imageDirectory.empty()){
        std::cout << "Cannot proceed without providing Image Directory \n";
        return 1;
    }

    const auto multipleImageWindow =
            std::make_shared<OpenCVHelpers::MultipleImageWindow>("Extract Features Testing", cv::WINDOW_AUTOSIZE);

    std::vector<cv::String> testImageFiles;
    cv::glob(imageDirectory + "/*.jpg", testImageFiles, false);

    std::for_each(testImageFiles.begin(), testImageFiles.end(), [&](const auto& testImageFile){

        const auto imageMat = cv::imread(testImageFile, cv::IMREAD_COLOR);

        if(imageMat.data == nullptr){
            std::cout << "Failed to read image date for: " << testImageFile << "/n";
            return 1;
        }

        cv::Mat imageMatClone = imageMat.clone();
        cv::Mat preProcesssedImage;

        std::cout << "Attempting to preprocess image: " << testImageFile << " \n";

        try{
            preProcesssedImage = ObjectDetection::Preprocessing::Preprocess(imageMatClone);
        } catch(const std::exception& e){
            std::cout << "Failed to preprocess image: " << testImageFile << " with error: << " << e.what() << "\n";
            return 1;
        }

        std::cout << "Attempting to add Mat to Multiple Image Window.\n";

        try {
            multipleImageWindow->addImage(testImageFile, preProcesssedImage);
        } catch(const std::exception& e){
            std::cout << "Failed to add image: " << testImageFile
            << " to Multiple Image Window with error: " << e.what() << "\n";
            return 1;
        }

    });

    multipleImageWindow->render();
    cv::waitKey();
    return 0;
}