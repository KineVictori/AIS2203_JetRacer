
#include "Steering/Steering.hpp"

#include <iostream>

Steering::Steering(const std::string& ip, const int port): _clientCtx() {
    try {
        _conn = _clientCtx.connect(ip, port);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
