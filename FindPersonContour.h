#ifndef  FINDPERSONСONTOUR_H
#define  FINDPERSONСONTOUR_H

#include <opencv2/imgproc.hpp>
class Center;

void findPersonContour(const cv::Mat &, std::vector<cv::Rect> &, std::vector<Center> &);
#endif // FINDPERSONСONTOUR_H
