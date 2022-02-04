#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char *argv[])
{
	cv::Mat doc = cv::imread("test.jpg");
	cv::imshow("depressed", doc);
	cv::waitKey(0);
	return 0;
}