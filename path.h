
#ifndef PATH_H
#define PATH_H

#include <deque>

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

class Center;




struct Path {

  void AddPoint(const cv::Point);
  int DrawPath(const cv::Mat &);
  bool CheckLength(const cv::Point);
  bool CheckExit(const cv::Mat &);
  bool CheckInArea(const cv::Mat &);

  bool CheckLost();

  Path &operator=(const Path &p);
  Path(const Center &c);
  Path();

  int m_lostFrames;
  std::deque<cv::Point> m_points;

private:
  cv::Point predictPoint();

  constexpr static int m_maxPoints = 10;
  constexpr static int m_lostFrameCup = 7;

  int m_minLenght;
};
#endif
