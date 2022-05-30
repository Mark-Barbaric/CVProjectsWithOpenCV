#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "platformAPIDefs.h"

namespace OpenCVHelpers{

    class MultipleImageWindow{

        const std::string m_windowName {"Main window"};
        const std::string m_windowTitle;
        const int m_flag {cv::WINDOW_AUTOSIZE};
        const int m_cols {3};
        const int m_rows {2};
        const int m_canvasWidth {1200};
        const int m_canvasHeight {700};
        std::vector<std::string> m_windowTitles;
        std::vector<cv::Mat> m_images;
        cv::Mat m_canvas;


    public:

        MultipleImageWindow(std::string windowTitle, int flag);

        int addImage(const std::string& windowTitle, const cv::Mat& image, bool render=false);
        void removeImage(int pos);
        void render();

    };

}