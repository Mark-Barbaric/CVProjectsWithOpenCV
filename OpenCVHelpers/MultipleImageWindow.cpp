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


    int MultipleImageWindow::addImage(std::string windowTitle, const cv::Mat& image, bool reRender)
    {
        m_windowTitles.push_back(std::move(windowTitle));
        m_images.push_back(image);

        if(reRender){
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

            const auto title= *titlesBegin;
            int cell_x= (cellWidth)*((i)%m_cols);
            int cell_y= (cellHeight)*floor((i)/(float)m_cols);
            cv::Rect mask(cell_x, cell_y, cellWidth, cellHeight);
            // Draw a rectangle for each cell mat
            rectangle(m_canvas, cv::Rect(cell_x, cell_y, cellWidth, cellHeight), cv::Scalar(200,200,200), 1);
            //For each cell draw an image if exists
            cv::Mat cell(m_canvas, mask);
            // resize image to cell size
            cv::Mat resized;
            double cell_aspect= (double)cellWidth/(double)cellHeight;
            cv::Mat img= *it;
            double img_aspect= (double)img.cols/(double)img.rows;
            double f=(cell_aspect<img_aspect)?(double)cellWidth/(double)img.cols:(double)cellHeight/(double)img.rows;
            resize(img, resized, cv::Size(0,0), f, f);
            if(resized.channels()==1){
                cvtColor(resized, resized, cv::COLOR_GRAY2BGR);
            }

            // Assign the image
            cv::Mat sub_cell(m_canvas, cv::Rect(cell_x,cell_y,resized.cols, resized.rows));
            resized.copyTo(sub_cell);
            putText(cell, title.c_str(), cv::Point(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(200,0,0), 1, cv::LINE_AA);
            i++;
            ++titlesBegin;

            if(i == maxImages){
                break;
            }
        }

        imshow(m_windowTitle, m_canvas);
    }
}