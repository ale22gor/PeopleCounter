#include "CheckPeopleInOut.h"

#include <opencv2/highgui.hpp>

#include "path.h"
#include "center.h"

using namespace cv;
using namespace std;


void checkPeopleInOut(vector<Path> &inputPaths,vector<Center> &inputCenters,const Size videoSize,int& inCount, int& outCount){

    for (Path &path : inputPaths) {

        int pointIndex{-1};
        int i{0};
        for(Center &center:inputCenters){
            if (path.CheckLength(center.m_coordinates))
                pointIndex = i;
            i++;
        }
        if (pointIndex >= 0) {
            path.AddPoint(inputCenters[pointIndex].m_coordinates);
            inputCenters[pointIndex].m_isAdded = true;
            path.m_lostFrames = 0;
        } else {
            path.m_lostFrames++;
        }
    }

    inputCenters.erase(
                std::remove_if(inputCenters.begin(), inputCenters.end(),
                               [](Center center) { return center.m_isAdded; }),
            inputCenters.end());

    Mat outZone{Mat::zeros(videoSize, CV_8UC1)};
    fillConvexPoly(outZone,
                   vector<Point> {Point{0,0},Point{315,0},
                                    Point{315,500}, Point{0,500},},
                   255);

    Mat inZone{Mat::zeros(videoSize, CV_8UC1)};
    fillConvexPoly(inZone,
                   vector<Point> {Point{410,0},Point{800,0},
                                  Point{800,500},Point{410,500}},
                   255);


    inputPaths.erase(std::remove_if(inputPaths.begin(), inputPaths.end(),
                                    [outZone,inZone,&outCount,&inCount](Path &path) {
        if (path.CheckLost())
            return true;
        if (path.CheckExit(outZone)){
            outCount++;
            return true;
        }
        if (path.CheckExit(inZone)){
            inCount++;
            return true;
        }
        return false;
    }),inputPaths.end());

    inputPaths.insert(inputPaths.end(), inputCenters.begin(),
                      inputCenters.end());
}
