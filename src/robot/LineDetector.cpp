#include <opencv2/imgproc.hpp>
#include "LineDetector.h"

double LineDetector::getLineOffset(cv::Mat frame, cv::Rect2d roi) {

    // crop to a given ROI
    frame = frame(roi);

    // convert to grayscale
    cv::cvtColor(frame, frame, CV_BGR2GRAY);

    // remove image imperfections
    cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0);

    // make pixels lighter than the threshold black and the rest white
    cv::threshold(frame, frame, 60, 255, CV_THRESH_BINARY_INV);

    // find contours
    cv::Mat contourMat(frame);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(contourMat, contours, 1, CV_CHAIN_APPROX_NONE);
    if (contours.empty()) {
        return -1;
    }

    // find a contour with the largest area
    std::vector<cv::Point> biggestContour = contours[0];
    double biggestContourArea = cv::contourArea(biggestContour);
    for (int i = 1; i < contours.size(); ++i) {
        std::vector<cv::Point> contour = contours[i];
        double contourArea = cv::contourArea(contour);
        if (contourArea > biggestContourArea) {
            biggestContour = contour;
            biggestContourArea = contourArea;
        }
    }

    // find the X coordinate of the center of the largest contour
    cv::Moments moments = cv::moments(biggestContour);
    double cx = moments.m10 / moments.m00;

    return cx;
}
