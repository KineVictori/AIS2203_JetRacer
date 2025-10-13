
#include <iostream>

#include "Steering/Steering.hpp"

int main() {
	SteeringData data{1.0, 1.0, 0.65, 0.8, 0.0};

	Steering steering{"10.22.22.217", 43537};
	steering.sendData(data);

}