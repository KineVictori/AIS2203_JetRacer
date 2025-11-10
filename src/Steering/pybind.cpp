
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>   // enables automatic conversion of std::string, std::vector, etc.
#include "Steering/Steering.hpp"

namespace py = pybind11;

PYBIND11_MODULE(SteeringPython, m) {
    m.doc() = "Python bindings for Steering library";

    // --- SteeringData struct ---
    py::class_<SteeringData>(m, "SteeringData")
        .def(py::init<>())  // default constructor
        .def_readwrite("steering", &SteeringData::steering)
        .def_readwrite("throttle", &SteeringData::throttle)
        .def_readwrite("steering_gain", &SteeringData::steering_gain)
        .def_readwrite("throttle_gain", &SteeringData::throttle_gain)
        .def_readwrite("steering_offset", &SteeringData::steering_offset)
        .def("__repr__", [](const SteeringData &d) {
            return "<SteeringData steering=" + std::to_string(d.steering) +
                   " throttle=" + std::to_string(d.throttle) +
                   " steering_gain=" + std::to_string(d.steering_gain) +
                   " throttle_gain=" + std::to_string(d.throttle_gain) +
                   " steering_offset=" + std::to_string(d.steering_offset) + ">";
        });

    // --- Steering class ---
    py::class_<Steering>(m, "Steering")
        .def(py::init<const std::string&, int>(), py::arg("ip"), py::arg("port"))
        .def("isReady", &Steering::isReady, "Check if connected to car.")
        .def("sendData", &Steering::sendData, py::arg("data"),
             "Send SteeringData to the remote host");
}
