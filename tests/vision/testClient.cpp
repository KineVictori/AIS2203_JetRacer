
#include <iostream>
#include <string>
#include <vector>
#include <iostream>

#include <simple_socket/SimpleConnection.hpp>
#include "simple_socket/TCPSocket.hpp"


int main() {
    simple_socket::TCPClientContext clientCtx;
    constexpr int port = 45678;
    const auto conn = clientCtx.connect("10.22.21.121", port);

    std::string output = "AUTO";
    conn->write(output);

    std::vector<unsigned char> buffer(1024);
    auto bytesRead = 0;
    while (bytesRead == 0) {
        bytesRead += conn->read(buffer);
    }

    std::string response{buffer.begin(), buffer.end()};
    std::cout << response << std::endl;
}