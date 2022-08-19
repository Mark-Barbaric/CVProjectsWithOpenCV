#pragma once
#include "opencv2/core/types.hpp"
#include "Color.h"

namespace Objects{
    
    class Ball{

        Color m_color;
        cv::Rect m_bounds;
        ColorThreshold m_colorThreshold;

    public:

        explicit Ball(Color color)
        :m_color(color)
        {
            m_colorThreshold = getColorThreshold(color);
        }

        void setBounds(cv::Rect bounds){
            m_bounds = bounds;
        }

        [[nodiscard]] Color getColor() const noexcept {return m_color;}
        [[nodiscard]] cv::Rect getBounds() const noexcept {return m_bounds;}
        [[nodiscard]] cv::Scalar getLowMaskScalar() const noexcept {return m_colorThreshold.m_low;}
        [[nodiscard]] cv::Scalar getHighMaskScalar() const noexcept {return m_colorThreshold.m_high;}

    };

}
