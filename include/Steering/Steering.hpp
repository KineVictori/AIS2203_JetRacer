
#ifndef AIS2203_JETRACER_STEERING_HPP
#define AIS2203_JETRACER_STEERING_HPP

#include "simple_socket/TCPSocket.hpp"
#include "simple_socket/SimpleConnection.hpp"

#include "nlohmann/json.hpp"

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
    void sendData(const SteeringData& data) const;

private:
    simple_socket::TCPClientContext _clientCtx;
    std::unique_ptr<simple_socket::SimpleConnection> _conn;

    static std::string toJson(const SteeringData &data);
};


#endif //AIS2203_JETRACER_STEERING_HPP