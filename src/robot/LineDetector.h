#ifndef BIONIK_TBD_LINEDETECTOR_H
#define BIONIK_TBD_LINEDETECTOR_H


#include <opencv2/core/mat.hpp>

class LineDetector {
public:
    double getLineOffset(cv::Mat frame, cv::Rect2d roi);
};


#endif //BIONIK_TBD_LINEDETECTOR_H
