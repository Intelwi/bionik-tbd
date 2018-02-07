#include "FrameJpgUdpStreamer.h"

FrameJpgUdpStreamer::FrameJpgUdpStreamer(std::string host, std::string port, int chunkSize) {
    this->chunkSize = chunkSize;
    endpoint = *resolver.resolve(ip::udp::v4(), host, port).begin();
}

void FrameJpgUdpStreamer::pushFrame(cv::Mat frame) {
    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf, std::vector<int>());

    std::size_t bytesSent = 0;
    for (auto it = buf.begin(); it < buf.end(); it += chunkSize) {
        auto end = it + chunkSize;
        if (end >= buf.end()) {
            end = buf.end();
        }
        bytesSent += socket.send_to(
                boost::asio::buffer(std::string(it, end)),
                (const ip::basic_endpoint<ip::udp> &) endpoint,
                0,
                errorCode
        );
    }

    if (bytesSent != buf.size()) {
        std::cerr << "warning: sent " << bytesSent << " of " << buf.size() << " bytes" << std::endl;
    }
}
