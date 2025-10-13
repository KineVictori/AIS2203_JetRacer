
#ifndef AIS2203_JETRACER_STEERING_HPP
#define AIS2203_JETRACER_STEERING_HPP

#include "simple_socket/TCPSocket.hpp"
#include "simple_socket/SimpleConnection.hpp"

struct SteeringData {
    double steering;
    double throttle;

    double steering_gain;
    double throttle_gain;
    double steering_offset;
};

class Steering {
public:
    Steering(const std::string& ip, int port);

private:
    simple_socket::TCPClientContext _clientCtx;
    std::unique_ptr<simple_socket::SimpleConnection> _conn;
};


#endif //AIS2203_JETRACER_STEERING_HPP