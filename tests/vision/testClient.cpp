
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

#include <simple_socket/SimpleConnection.hpp>
#include "simple_socket/TCPSocket.hpp"

int main() {
    simple_socket::TCPClientContext clientCtx;
    constexpr int port = 45678;
    const auto conn = clientCtx.connect("10.22.21.121", port);

    std::string output = "AUTO";
    conn->write(output);

    std::vector<unsigned char> bufferSmol(4);
    int headerBytesRead = 0;

    // Make sure we actually get 4 bytes for the size header
    while (headerBytesRead < 4) {
        int n = conn->read(bufferSmol.data() + headerBytesRead, 4 - headerBytesRead);
        headerBytesRead += n;
    }

    int nextNumBytes = 0;
    nextNumBytes |= bufferSmol[0];
    nextNumBytes |= bufferSmol[1] << 8;
    nextNumBytes |= bufferSmol[2] << 16;
    nextNumBytes |= bufferSmol[3] << 24;

    std::vector<unsigned char> buffer(nextNumBytes);

    int totalRead = 0;
    while (totalRead < nextNumBytes) {
        int n = conn->read(buffer.data() + totalRead, nextNumBytes - totalRead);
        if (n <= 0) {
            std::cerr << "Connection closed while reading frame data\n";
            break;
        }
        totalRead += n;
    }

    std::cout << "Expected: " << nextNumBytes << ", actually read: " << totalRead << "\n";

    cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);

    cv::imshow("Received Frame", img);
    cv::waitKey(0);
}