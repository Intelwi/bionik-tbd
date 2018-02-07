#include <iostream>
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include "LineDetector.h"
#include "FrameJpgUdpStreamer.h"

int main(int argc, char *argv[]) {
    const int frameWidth = 640;
    const int frameHeight = 480;

    const cv::Rect roi(0, 2 * frameHeight / 4, frameWidth, frameHeight / 4);

    LineDetector lineDetector;
    FrameJpgUdpStreamer frameJpgUdpStreamer("127.0.0.1", "5001");

    cv::VideoCapture videoCapture(0);
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, frameHeight);

    while (true) {
        cv::Mat frame;
        videoCapture >> frame;
        cv::rectangle(frame, roi, cv::Scalar(255, 0, 0));

        double cx = lineDetector.getLineOffset(frame, roi);
        cv::circle(frame, cv::Point(roi.x + static_cast<int>(cx), roi.y + roi.height / 2), 1, cv::Scalar(0, 255, 0), 2);

        frameJpgUdpStreamer.pushFrame(frame);
    }
}
