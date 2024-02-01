#pragma once
#include "pch.h"
#include <filesystem>

#include <Python.h>
#define Py_LIMITED_API 0x030A0000  // for python 3.10
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>  // for the embedded interpreter
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/functional.h>

namespace py = pybind11;

void bindItem(py::module_& m);
void bindPrint(py::module_& m);
void bindGetItem(py::module_& m);
void bindgetItemType(py::module_& m);