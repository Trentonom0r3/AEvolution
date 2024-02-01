#include "pch.h"
#include "PyCore.h"


void bindItem(py::module_& m) {
	py::class_<ItemH>(m, "Item")
		.def(py::init<>()) // Provide a default constructor if needed
		.def("get_session_id", &ItemH::getSessionID);
}
void bindPrint(py::module_& m) {
	m.def("report", &reportInfo, py::arg("msg") = "Hello, World!");
}

void bindGetItem(py::module_& m) {
	m.def("getItem", &activeItem);
}

void bindgetItemType(py::module_& m) {
	m.def("getItemType", &getItemType);
}
