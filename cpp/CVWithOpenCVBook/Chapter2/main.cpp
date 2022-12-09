#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char* argv[]){

    cv::Mat image = cv::imread("lena.jpg");
    int myRow = 511;
    int myCol = 511;
    int B = *(image.data+myRow*image.cols*image.channels() + myCol + 0);
    int G = *(image.data+myRow*image.cols*image.channels() + myCol + 1);
    int R = *(image.data+myRow*image.cols*image.channels() + myCol + 2);

    std::cout << "Pixel value (B,G,R): (" << B << "," << G << "," << R << ")\n";
    cv::imshow("Lena", image);
    cv::waitKey(0);
    return 0;
}
