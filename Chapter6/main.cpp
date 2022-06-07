#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <ObjectDetection/Preprocessing.h>
#include <ObjectDetection/Segmentation.h>
#include <OpenCVHelpers/MultipleImageWindow.h>
#include <OpenCVHelpers/GeneralHelpers.h>
#include <iostream>
#include <opencv2/ml.hpp>
#include <opencv2/imgproc.hpp>

const char* keys = {
"{help h usage ? | | print this message}"
"{@image || Image to classify}"
};

#ifdef WIN32
constexpr auto TrainingDataPrefix = R"(C:\Users\mark.barbaric\Documents\Developer\CPP\OpenCV\CVProjectsWithOpenCV\TrainingData\)";
#endif

#ifdef linux
constexpr auto TrainingDataPrefix = "/home/markbarbaric/Documents/Mirriad/Developer/cpp/CVProjectsWithOpenCV/";
#endif

std::vector<std::vector<float>> ExtractFeatures(const std::weak_ptr<OpenCVHelpers::MultipleImageWindow>& sharedWindow, cv::Mat image, std::vector<int>* left = nullptr, std::vector<int>* top = nullptr){
    std::vector<std::vector<float>> output;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat input = image.clone();

    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(input, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    if(contours.empty()){
        std::cout << "Failed to find contours with image.\n";
        return output;
    }

    cv::RNG rng(0XFFFFFFFF);

    for(int i = 0; i < contours.size(); ++i){
        cv::Mat mask = cv::Mat::zeros(input.rows, input.cols, CV_8UC1);
        cv::drawContours(mask, contours, i, cv::Scalar(1), cv::FILLED, cv::LINE_8, hierarchy, 1);
        cv::Scalar areaS = cv::sum(mask);
        float area = areaS[0];

        if(area > 500){
            cv::RotatedRect r = cv::minAreaRect(contours[i]);
            const float width = r.size.width;
            const float height = r.size.height;
            const auto ar = (width < height) ? height / width : width / height;

            std::vector<float> row;
            row.push_back(area);
            row.push_back(ar);

            output.push_back(row);

            if(left){
                left->push_back(static_cast<int>(r.center.x));
            }

            if(top){
                top->push_back(static_cast<int>(r.center.y));
            }

            if(const auto tempWindow = sharedWindow.lock()) {
                tempWindow->addImage("Extract Features", mask * 255);
                tempWindow->render();
                cv::waitKey(10);
            }
        }
    }
    return output;
}

bool readFolderAndExtractFeatures(const std::weak_ptr<OpenCVHelpers::MultipleImageWindow>& sharedWindow,
                                  const std::string& folder, int label, int numForTest,
                                  std::vector<float>& trainingData, std::vector<int>& responsesData,
                                  std::vector<float>& testData, std::vector<float>& testResponsesData){
    cv::VideoCapture images;

    if(!images.open(folder)){
        std::cout << "Can't open the folder images.\n";
        return false;
    }

    cv::Mat frame;
    int img_index = 0;

    while(images.read(frame)){

        cv::Mat preprocessedImage;

        const auto numChannels = frame.channels();

        try {
            preprocessedImage = ObjectDetection::Preprocessing::Preprocess(frame);
        } catch(const std::exception& e){
            std::cout << "Failed to preprocess image#" << img_index << " with error: " << e.what() << "\n.";
            return false;
        }

        std::vector<std::vector<float>> features;

        try {
            features = ExtractFeatures(sharedWindow, preprocessedImage);
        } catch (const std::exception& e){
            std::cout << "Failed to extract features for image#" << img_index << " with error: " << e.what() << "\n.";
            return false;
        }

        for(int i = 0; i < features.size(); ++i){
            if(img_index >= numForTest){
                trainingData.push_back(features[i][0]);
                trainingData.push_back(features[i][1]);
                responsesData.push_back(label);
            } else {
                testData.push_back(features[i][0]);
                testData.push_back(features[i][1]);
                testResponsesData.push_back(static_cast<float>(label));
            }
        }
        img_index++;
    }

    return true;
}

void plotTrainData(const std::weak_ptr<OpenCVHelpers::MultipleImageWindow>& sharedWindow,
                   cv::Mat trainData, cv::Mat labels, float *error = nullptr)
{
    float area_max, ar_max, area_min, ar_min;
    area_max= ar_max= 0;
    area_min= ar_min= 99999999;
    // Get the min and max of each feature for normalize plot image
    for(int i=0; i< trainData.rows; i++){
        float area= trainData.at<float>(i,0);
        float ar= trainData.at<float>(i,1);
        if(area > area_max)
            area_max= area;
        if( ar > ar_max )
            ar_max= ar;
        if(area < area_min)
            area_min= area;
        if(ar < ar_min)
            ar_min= ar;
    }

    // Create Image for plot
    cv::Mat plot = cv::Mat::zeros(512,512,CV_8UC3);
    // Plot each of two features in a 2D graph using an image
    // where x is area and y is aspect ratio
    for(int i=0; i< trainData.rows; i++){
        // Set the X y pos for each data
        float area= trainData.at<float>(i,0);
        float ar= trainData.at<float>(i,1);
        int x= (int)(512.0f*((area-area_min)/(area_max-area_min)));
        int y= (int)(512.0f*((ar-ar_min)/(ar_max-ar_min)));

        // Get label
        int label= labels.at<int>(i);
        // Set color depend of label
        cv::Scalar color;

        if(label==0) {
            color = OpenCVHelpers::GeneralHelpers::green;
        }// NUT
        else if(label==1) {
            color = OpenCVHelpers::GeneralHelpers::blue; // RING
        }
        else if(label==2) {
            color = OpenCVHelpers::GeneralHelpers::red; // SCREW
            circle(plot, cv::Point(x, y), 3, color, -1, 8);
        }
    }

    if(error){
        std::stringstream ss;
        ss << "Error: " << *error << "%\n";
        putText(plot, ss.str(), cv::Point(20,512-40), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(200,200,200), 1, cv::LINE_AA);
    }

    if(const auto tempWindow = sharedWindow.lock()){
        tempWindow->addImage("Plot", plot);
    }
}

void trainAndTest(cv::Ptr<cv::ml::SVM>& svm,
        const std::weak_ptr<OpenCVHelpers::MultipleImageWindow>& window){

    std::vector<float> trainingData;
    std::vector<int> responsesData;
    std::vector<float> testData;
    std::vector<float> testResponsesData;

    int num_for_test = 20;

    std::string prefix = TrainingDataPrefix;
    // Get the nut images
    if(!readFolderAndExtractFeatures(window, prefix + "TrainingData/nut/tuerca_%04d.pgm", 0, num_for_test, trainingData, responsesData, testData, testResponsesData)){
        std::cout << "Failed to extract features for nut images.\n";
        return;
    }
    // Get and process the ring images
    if(!readFolderAndExtractFeatures(window, prefix + "TrainingData/ring/arandela_%04d.pgm", 1, num_for_test, trainingData, responsesData, testData, testResponsesData)){
        std::cout << "Failed to extract features for ring images.\n";
        return;
    }
    // get and process the screw images
    if(!readFolderAndExtractFeatures(window, prefix + "TrainingData/screw/tornillo_%04d.pgm", 2, num_for_test, trainingData, responsesData, testData, testResponsesData)){
        std::cout << "Failed to extract features for screw images.\n";
        return;
    }

    std::cout << "Num of train samples: " << responsesData.size() << ".\n";
    std::cout << "Num of test samples: " << testResponsesData.size() << ".\n";

    // Merge all data
    cv::Mat trainingDataMat(trainingData.size()/2, 2, CV_32FC1, &trainingData[0]);
    cv::Mat responses(responsesData.size(), 1, CV_32SC1, &responsesData[0]);

    cv::Mat testDataMat(testData.size()/2, 2, CV_32FC1, &testData[0]);
    cv::Mat testResponses(testResponsesData.size(), 1, CV_32FC1, &testResponsesData[0]);

    if(!svm.get()){
        throw std::logic_error("SVM Model is not valid.");
    }

    cv::Ptr<cv::ml::TrainData> tdata= cv::ml::TrainData::create(trainingDataMat, cv::ml::ROW_SAMPLE, responses);
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setNu(0.05);
    svm->setKernel(cv::ml::SVM::CHI2);
    svm->setDegree(1.0);
    svm->setGamma(2.0);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(tdata);

    if(!testResponsesData.empty()){
        std::cout << "Evaluation" << std::endl;
        std::cout << "==========" << std::endl;
        // Test the ML Model
        cv::Mat testPredict;
        svm->predict(testDataMat, testPredict);
        std::cout << "Prediction Done" << std::endl;
        // Error calculation
        cv::Mat errorMat= testPredict!=testResponses;
        float error= 100.0f * countNonZero(errorMat) / testResponsesData.size();
        std::cout << "Error: " << error << "%" << std::endl;
        // Plot training data with error label
        plotTrainData(window, trainingDataMat, responses, &error);

    }else{
        plotTrainData(window, trainingDataMat, responses);
    }
}

int main(int argc, char* argv[]){

    cv::CommandLineParser cli (argc, argv, keys);
    cli.about("Chapter 6");

    if(cli.has("help")){
        cli.printMessage();
        return 1;
    }

    if(!cli.check()){
        cli.printErrors();
        return 1;
    }

    const auto miw = std::make_shared<OpenCVHelpers::MultipleImageWindow>("Main window", cv::WINDOW_AUTOSIZE);

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    std::cout << "Training and testing SVM Model.\n";
    try{
        trainAndTest(svm, miw);
    } catch(const std::exception& e){
        std::cout << "Failed to train and test SVM Model with error: " << e.what() << "\n.";
        return 1;
    }

    const auto inputImageFilePath = cli.get<cv::String>(0);
    cv::Mat inputImage = cv::imread(inputImageFilePath, cv::IMREAD_COLOR);

    if(inputImage.data == nullptr){
        std::cout << "Failed to load image: " << inputImageFilePath << "\n.";
        return 1;
    }

    cv::Mat inputImageClone = inputImage.clone();

    cv::Mat pre;
    std::cout << "Preprocessing input image.\n";
    try{
        pre = ObjectDetection::Preprocessing::Preprocess(inputImageClone);
    } catch(const std::exception& e){
        std::cout << "Failed to preprocess image with error: " << e.what() << "\n.";
        return 1;
    }

    std::vector<int> posLeft, posTop;
    std::vector<std::vector<float>> features = ExtractFeatures(miw, pre, &posLeft, &posTop);

    if(features.empty()){
        std::cout << "Failed to extract features from source image \n.";
        return 1;
    }

    for(int i = 0; i < features.size(); ++i){

        cv::Mat trainingDataMat(1, 2, CV_32FC1, &features[i][0]);
        float result = svm->predict(trainingDataMat);

        std::stringstream ss;
        cv::Scalar color;

        if(result == 0){
            color = OpenCVHelpers::GeneralHelpers::green;
            ss << "NUT";
        } else if (result == 1){
            color = OpenCVHelpers::GeneralHelpers::blue;
            ss << "RING";
        } else if (result == 2){
            color = OpenCVHelpers::GeneralHelpers::red;
            ss << "SCREW";
        }

        std::cout << "Image classified as :" << ss.str() << ".\n";

        cv::putText(inputImageClone, ss.str(),
                    cv::Point2d(posLeft[i], posTop[i]),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.4,
                    color);

    }

    miw->addImage("Binary Image", pre);
    miw->addImage("Result", inputImageClone);
    miw->render();
    cv::waitKey(5000);

    return 0;
}
