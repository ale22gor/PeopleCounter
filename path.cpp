#include "path.h"
#include <opencv2/imgproc.hpp>
#include "center.h"

using namespace cv;

Path::Path() : m_lostFrames{0} ,m_minLenght{7000}{}

Path::Path(const Center &c) : Path() { m_points.push_back(c.m_coordinates); }

void Path::AddPoint(const Point point) {
    if (m_points.size() == m_maxPoints)
        m_points.pop_back();
    m_points.push_front(point);
    m_minLenght = 7000;
}

bool Path::CheckLength(const Point b) {
    Point a{predictPoint()};

    int length;
    length = ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
    if (length < m_minLenght && length >= 0) {
        m_minLenght = length;
        return true;
    } else {
        return false;
    }
}

bool Path::CheckLost() { return m_lostFrames > m_lostFrameCup; }

int Path::DrawPath(const Mat &sourceFrame) {

    for (auto ptr = m_points.begin(); ptr != m_points.end(); ++ptr) {

        auto i = std::distance(m_points.begin(), ptr);
        if (i >= 1) {
            auto x = ptr - 1;
            line(sourceFrame, *x, *ptr, Scalar(0, 255, 0));
        }
        circle(sourceFrame, *ptr, 2, Scalar(0, 0, 255), -1);
    }
    return 0;
}

Point Path::predictPoint() {
    if(m_points.size() == 1)
        return m_points[0];
    Point first = m_points[0];
    Point second = m_points[1];
    int deltaX{first.x - second.x};
    int deltaY{first.y - second.y};
    return Point{first.x + deltaX, first.y + deltaY};
}

bool Path::CheckExit(const Mat &maskedFrame) {
    if (m_points.size() < 5)
        return false;


    for (auto ptr = m_points.begin() + 1; ptr != m_points.end(); ++ptr) {
        auto x = ptr - 1;

        if (static_cast<int>(maskedFrame.at<uchar>(*ptr)) == 0 &&
                static_cast<int>(maskedFrame.at<uchar>(*x)) == 255)
            return true;

    }

    return false;
}
bool Path::CheckInArea(const Mat &maskedFrame) {
    if (m_points.size() < 8)
        return false;

    for (auto ptr = m_points.begin(); ptr != m_points.end(); ++ptr)
        if (static_cast<int>(maskedFrame.at<uchar>(*ptr)) == 0)
            return false;

    return true;
}

Path &Path::operator=(const Path &p) {

    if (this != &p) {
        m_points = p.m_points;
        m_lostFrames = p.m_lostFrames;
    }
    return *this;
}
