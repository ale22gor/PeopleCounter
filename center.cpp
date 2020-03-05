#include "center.h"

Center::Center(const cv::Point coordinates)
    : m_coordinates{coordinates}, m_isAdded{false} {}
Center::Center(const Center &center)
    : m_coordinates{center.m_coordinates}, m_isAdded{center.m_isAdded} {}
