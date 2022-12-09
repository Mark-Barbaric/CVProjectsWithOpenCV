#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

inline int readWriteFile(){

    cv::Mat color = cv::imread("lena.jpg");
    cv::Mat gray = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);

    if(!color.data){
        std::cout << "Failed to load lena.jpg\n";
        return 1;
    }

    cv::imwrite("lenaGray.jpg", gray);
    const auto myRow = color.cols-1;
    const auto myCol = color.rows-1;

    cv::Vec3b pixel = color.at<cv::Vec3b>(myRow, myCol);
    std::cout << "Pixel value (B,G,R): (" << static_cast<int>(pixel[0]) << ","
        << static_cast<int>(pixel[1]) << "," 
        << static_cast<int>(pixel[2]) << ")\n";

    cv::imshow("Lena BGR", color);
    cv::imshow("Lena Gray", gray);
    cv::waitKey(0);
    return 0;

}