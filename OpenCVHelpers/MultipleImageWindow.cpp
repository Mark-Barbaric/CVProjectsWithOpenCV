#include "MultipleImageWindow.h"

namespace OpenCVHelpers{

    MultipleImageWindow* MultipleImageWindow::getInstance()
    {
        if(m_instance == nullptr){
            m_instance = new MultipleImageWindow();
        }

        return m_instance;
    }

    MultipleImageWindow::~MultipleImageWindow()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    MultipleImageWindow::MultipleImageWindow()
    {
        cv::namedWindow(m_windowTitle, m_flag);
        m_canvas = cv::Mat(m_canvasHeight, m_canvasWidth, CV_8UC3);
        cv::imshow(m_windowTitle, m_canvas);
    }

    int MultipleImageWindow::addImage(std::string windowTitle, const cv::Mat& image, bool render)
    {
        m_windowTitles.push_back(std::move(windowTitle));
        m_images.push_back(image);

        if(render){
            render();
        }

        return static_cast<int>(m_images.size() - 1);
    }

    void MultipleImageWindow::removeImage(int pos)
    {
        m_windowTitles.erase(m_windowTitles.begin() + pos);
        m_images.erase(m_images.begin() + pos);
    }

    void MultipleImageWindow::render()
    {
        m_canvas.setTo(cv::Scalar(20, 20, 20));
        const auto cellWidth = std::floor(m_canvasWidth / m_cols),
        cellHeight = std::floor(m_canvasHeight / m_rows);
        const auto margin = 10;
        const auto maxImages = m_images.size() > (m_cols * m_rows) ? m_cols * m_rows
                : m_images.size();

        auto i = 0;
        auto titlesBegin = m_windowTitles.begin();

        for(auto it = m_images.begin(); it != m_images.end(); ++it){

        }

        imshow(m_windowTitle, m_canvas);
    }
}