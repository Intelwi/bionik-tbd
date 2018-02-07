#ifndef BIONIK_TBD_FRAMEJPGUDPSTREAMER_H
#define BIONIK_TBD_FRAMEJPGUDPSTREAMER_H


#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>

namespace ip = boost::asio::ip;

class FrameJpgUdpStreamer {
public:
    FrameJpgUdpStreamer(std::string host, std::string port, int chunk_size = 64000);
    void pushFrame(cv::Mat frame);

private:
    int chunkSize;
    boost::system::error_code errorCode;
    boost::asio::io_context io_context;
    ip::udp::socket socket = ip::udp::socket(io_context, ip::udp::endpoint(ip::udp::v4(), 0));
    ip::udp::resolver resolver = ip::udp::resolver(io_context);
    ip::basic_resolver_entry<ip::udp> endpoint;
};


#endif //BIONIK_TBD_FRAMEJPGUDPSTREAMER_H
