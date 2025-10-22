
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

    int numBytes = conn->read(buffer);
    int nextNumBytes = conn->read(buffer);

    std::cout << "Received bytes: ";
    for (auto b : buffer) std::cout << int(b) << " ";
    std::cout << "\n";

    std::cout << numBytes << " | " << nextNumBytes << "\n";
}