#ifndef CHECKPEOPLEINOUT_H
#define CHECKPEOPLEINOUT_H
#include<vector>
#include <opencv2/imgproc.hpp>

class Path;
class Center;

void checkPeopleInOut(std::vector<Path> &,std::vector<Center> &,const cv::Size , int& , int& );
#endif // CHECKPEOPLEINOUT_H
