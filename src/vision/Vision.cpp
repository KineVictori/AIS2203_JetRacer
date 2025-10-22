
#include "vision/Vision.hpp"


Vision::Vision(): _server(simple_socket::TCPServer(45678)) {
    std::string pipeline = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, framerate=30/1 ! "
                           "nvvidconv ! videoconvert ! appsink";
    _cap = cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);
    if(!_cap.isOpened()) {
        std::cerr << "Failed to open CSI camera\n";
        isOkay = false;
    }
}

Vision::~Vision() {
    _cap.release();

    for (auto &t : _connectionThreads) {
        t.join();
    }
}

void Vision::update() {
    _cap >> _frame;

    try {
        std::unique_ptr<simple_socket::SimpleConnection> conn = _server.accept();
        std::thread t([c = std::move(conn), this]() mutable {
            socketHandler(std::move(c));
        });

        _connectionThreads.push_back(std::move(t));
    } catch(...) {}

}

cv::Mat Vision::getFrame() {
    return _frame;
}

void Vision::socketHandler(std::unique_ptr<simple_socket::SimpleConnection> conn) {
    std::vector<unsigned char> buffer(1024);
    const auto bytesRead = conn->read(buffer);
    std::string msg(buffer.begin(), buffer.begin() + bytesRead);

    int mode = 0;
    if (msg == "AUTO") {
        mode = 1;
    } // TODO: implement mode switching (example AUTO: frames as fast as possible, one: just get one frame)

    auto frame = getFrame();
    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);
    buf = {1, 2, 3}; // TODO: remove lol

    int numBytes = buf.size();
    conn->write(std::to_string(numBytes));
    conn->write(buf);
}
