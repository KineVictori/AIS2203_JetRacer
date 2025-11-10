
#include <iostream>
#include "visionClient/visionClient.hpp"

visionClient::visionClient(std::string ip, int port)
    : _clientCtx() {

    _conn = _clientCtx.connect(ip, port);

    if (_conn != nullptr) {
        _conn->write("AUTO");
        _thread = std::thread(&visionClient::runConnection, this);

        _isReady = true;
    }
}

visionClient::~visionClient() {
    _stopFlag = true;

    if (_conn != nullptr) {
        _thread.join();
    }
}

bool visionClient::isReady() const {
    return _isReady;
}


std::vector<unsigned char> visionClient::getFrame() {
    if (!_firstFrameRecieved)
        return {};

    std::lock_guard<std::mutex> lock(_mutex);
    return _frame;
}

void visionClient::runConnection() {
    while (!_stopFlag) {
        std::vector<unsigned char> bufferSmol(4);
        int headerBytesRead = 0;
        while ((headerBytesRead < 4) && !_stopFlag) {
            int n = _conn->read(bufferSmol.data() + headerBytesRead, 4 - headerBytesRead);
            headerBytesRead += n;
        }

        if (_stopFlag) {break;}

        int nextNumBytes = 0;
        nextNumBytes |= bufferSmol[0];
        nextNumBytes |= bufferSmol[1] << 8;
        nextNumBytes |= bufferSmol[2] << 16;
        nextNumBytes |= bufferSmol[3] << 24;

        std::vector<unsigned char> buffer(nextNumBytes);
        int totalRead = 0;
        while ((totalRead < nextNumBytes) && !_stopFlag) {
            totalRead += _conn->read(buffer.data() + totalRead, nextNumBytes - totalRead);
        }

        if (_stopFlag) {break;}

        std::lock_guard<std::mutex> lock(_mutex);
        _frame = std::move(buffer);
        _firstFrameRecieved = true;
    }
}
