#include <opencv2/imgproc.hpp>

namespace ObjectDetection{

    enum class SegmentationMethod : int {
        ConnectedComponents = 0, ConnectedComponentsWithStats, FindContoursBasic
    };

    class Segmentation{

        static cv::Mat connectedComponents(const cv::Mat& image);
        static cv::Mat connectComponentsWithStats(const cv::Mat& image);
        static cv::Mat contourBasic(const cv::Mat& image);

    public:

        static cv::Mat segmentImage(const cv::Mat& image, SegmentationMethod method);
    };

}