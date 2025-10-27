#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // needed for std::vector and std::string conversions
#include "visionClient/visionClient.hpp"  // your header file

namespace py = pybind11;

PYBIND11_MODULE(VisionPython, m) {
	m.doc() = "Python bindings for visionClient using pybind11";

	py::class_<visionClient>(m, "visionClient")
		.def(py::init<std::string, int>(), py::arg("ip"), py::arg("port"))
		.def("getFrame", &visionClient::getFrame,
			 "Get the latest frame as raw bytes.");
}
