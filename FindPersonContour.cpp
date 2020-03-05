#include "FindPersonContour.h"
#include "center.h"

using namespace cv;
using namespace std;
void findPersonContour(const Mat& inputFrame, vector<Rect>& outputCountors, vector<Center>& outputCenters)
{

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(inputFrame, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);


    vector<Point> contours_poly(4);

    outputCountors.clear();
    outputCenters.clear();

    int m_maxObjectArea{50000};
    int m_minObjectArea{10000};

    for (auto contour : contours) {
        approxPolyDP(Mat{contour}, contours_poly, 3, true);
        Rect tmp{boundingRect(Mat{contours_poly})};

        if (tmp.area() < m_maxObjectArea && tmp.area() > m_minObjectArea) {
            outputCenters.push_back(
                        Center{(tmp.br() + tmp.tl()) *
                               0.5}); // save countour center
            outputCountors.push_back(std::move(tmp)); // save countour

        }
    }


}
