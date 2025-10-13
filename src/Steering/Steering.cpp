
#include <iostream>

#include "Steering/Steering.hpp"

Steering::Steering(const std::string& ip, const int port) {
    try {
        _conn = _clientCtx.connect(ip, port);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Steering::sendData(const SteeringData& data) const {
    auto jsonData = toJson(data);
    jsonData += "\n";

    try {
        _conn->write(jsonData);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

std::string Steering::toJson(const SteeringData &data) {
    nlohmann::json jsonObj;

    jsonObj["steering"] = data.steering;
    jsonObj["throttle"] = data.throttle;

    jsonObj["steering_gain"] = data.steering_gain;
    jsonObj["throttle_gain"] = data.throttle_gain;
    jsonObj["steering_offset"] = data.steering_offset;

    return jsonObj.dump();
}
