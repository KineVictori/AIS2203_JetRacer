
#include "visionClient/visionClient.hpp"

void testLoc() {
    simple_socket::TCPClientContext clientCtx;
    constexpr int port = 45678;
    const auto conn = clientCtx.connect("10.22.22.165", port);

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

visionClient::visionClient(std::string ip, int port)
    : _clientCtx() {
    // testLoc();

    _conn = _clientCtx.connect(ip, port);
    _conn->write("AUTO");
    _thread = std::thread(&visionClient::runConnection, this);
}

visionClient::~visionClient() {
    _stopFlag = true;
    _thread.join();
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
