#include"FilterMovementFrame.h"
using namespace cv;
void filterMovementFrame(const Mat& inputFraame,Mat& outputFrame){
    Mat element{getStructuringElement (MORPH_RECT, Size{5,5}, Point(1,1))};
    morphologyEx( inputFraame, outputFrame, MORPH_CLOSE, element );
    morphologyEx( outputFrame, outputFrame, MORPH_OPEN, element );
    threshold(outputFrame, outputFrame, 165, 255, THRESH_BINARY);
}
