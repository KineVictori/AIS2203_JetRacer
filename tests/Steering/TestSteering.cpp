
#include "Steering/Steering.hpp"

int main() {

	Steering steering{"10.22.22.217", 43457};
	SteeringData data{0.0, 0.0, 0.65, 0.8, 0.0};

	double throttle = 0.0;
	while (throttle <= 1.0) {

		data.throttle = throttle;
		steering.sendData(data);

		throttle += 0.01;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	data.throttle = 0.0;
	steering.sendData(data);

}