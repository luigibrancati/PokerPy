#include "global.h"
#include "algo_new.h"
#include "algo_old.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(Test, m) {
    m.def("profiling_old", &algo_old::profiling);
    m.def("profiling_new", &algo_new::profiling);
}
