
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include <simple_socket/SimpleConnection.hpp>
#include "simple_socket/TCPSocket.hpp"

int main() {
    simple_socket::TCPClientContext clientCtx;
    constexpr int port = 45678;
    const auto conn = clientCtx.connect("10.22.21.121", port);

    std::string output = "AUTO";
    conn->write(output);

    auto t0 = std::chrono::high_resolution_clock::now();
    auto numFrames = 0;

    while (true) {
        // -----------------------
        // 1️⃣ Read header (frame size)
        // -----------------------
        std::vector<unsigned char> bufferSmol(4);
        int headerBytesRead = 0;
        while (headerBytesRead < 4) {
            int n = conn->read(bufferSmol.data() + headerBytesRead, 4 - headerBytesRead);
            if (n <= 0) {
                std::cerr << "Connection closed or error while reading header\n";
                goto end_stream;
            }
            headerBytesRead += n;
        }

        int nextNumBytes = 0;
        nextNumBytes |= bufferSmol[0];
        nextNumBytes |= bufferSmol[1] << 8;
        nextNumBytes |= bufferSmol[2] << 16;
        nextNumBytes |= bufferSmol[3] << 24;

        // -----------------------
        // 2️⃣ Read actual frame data
        // -----------------------
        std::vector<unsigned char> buffer(nextNumBytes);
        int totalRead = 0;
        while (totalRead < nextNumBytes) {
            int n = conn->read(buffer.data() + totalRead, nextNumBytes - totalRead);
            if (n <= 0) {
                std::cerr << "Connection closed or error while reading frame data\n";
                goto end_stream;
            }
            totalRead += n;
        }

        // -----------------------
        // 3️⃣ Decode and show
        // -----------------------
        cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cerr << "Failed to decode JPEG frame\n";
            continue; // skip this frame, try the next one
        }

        cv::imshow("Received Stream", img);

        // -----------------------
        // 4️⃣ Check for exit key
        // -----------------------
        int key = cv::waitKey(1); // 1ms delay, adjust for FPS if needed
        if (key == 27) { // ESC key
            break;
        }

        numFrames++;
        auto t1 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
        std::cout << "Frame: " << numFrames << " => FPS: " << static_cast<double>(numFrames) / static_cast<double>(duration) << std::endl;
    }

    end_stream:
    std::cout << "Stream ended\n";

}