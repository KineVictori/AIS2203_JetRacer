
#ifndef AIS2203_JETRACER_VISIONCLIENT_HPP
#define AIS2203_JETRACER_VISIONCLIENT_HPP

#include <thread>
#include <mutex>
#include <atomic>

#include <string>
#include <vector>

#include "simple_socket/TCPSocket.hpp"
#include "simple_socket/SimpleConnection.hpp"

class visionClient {
public:
    visionClient(std::string ip, int port);
    ~visionClient();

    bool isReady() const;
    std::vector<unsigned char> getFrame();

private:
    simple_socket::TCPClientContext _clientCtx;
    std::unique_ptr<simple_socket::SimpleConnection> _conn;
    bool _isReady = false;

    std::vector<unsigned char> _frame;
    std::mutex _mutex;

    std::atomic<bool> _firstFrameRecieved = false;
    std::atomic<bool> _stopFlag = false;
    std::thread _thread;
    void runConnection();
};


#endif //AIS2203_JETRACER_VISIONCLIENT_HPP