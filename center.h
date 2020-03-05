#ifndef CENTER_H
#define CENTER_H

#include <opencv2/core/types.hpp>


struct Center {
  Center(const cv::Point );
  Center(const Center &);

  cv::Point m_coordinates;
  bool m_isAdded;
};
#endif
