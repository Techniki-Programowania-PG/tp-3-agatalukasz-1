#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "signal.h"
#include <pybind11/complex.h>

namespace py = pybind11;

PYBIND11_MODULE(signal_module, m) {
    m.doc() = "Modul do generowania sygnalow (C++ z pybind11)";

    m.def("generate_sine", &generate_sine,
        py::arg("amplitude"), py::arg("frequency"), py::arg("duration"), py::arg("sample_rate"),
        "Generuje sygnal sinusoidalny jako lista floatow");
    m.def("generate_cosine", &generate_cosine,
        py::arg("amplitude"), py::arg("frequency"), py::arg("duration"), py::arg("sample_rate"),
        "Generuje sygnal cosinusoidalny jako lista floatow");
    m.def("generate_square", &generate_square,
        py::arg("amplitude"), py::arg("frequency"), py::arg("duration"), py::arg("sample_rate"),
        "Generuje sygnal prostokatny jako lista floatow");
    m.def("generate_sawtooth", &generate_sawtooth,
        py::arg("amplitude"), py::arg("frequency"), py::arg("duration"), py::arg("sample_rate"),
        "Generuje sygnal piloksztaltny jako lista floatow");

    m.def("dft", &dft, "Wykonuje Dyskretna Transformate Fouriera",
        py::arg("signal"));
    m.def("idft", &idft, "Wykonuje Odwrotna Dyskretna Transformate Fouriera",
        py::arg("spectrum"));
}