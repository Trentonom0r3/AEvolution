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
#include "Base.h"
namespace py = pybind11;

class UndoGroup {
public:
    UndoGroup(const std::string& name) : groupName(name) {
        // Equivalent to app.beginUndoGroup(name)
        beginUndoGroup(groupName);
    }

    void beginUndoGroup(const std::string& name);

    void endUndoGroup();

    UndoGroup* __enter__() {
        // Return this object upon entering the context
        return this;
    }

    void __exit__(const py::object& type, const py::object& value, const py::object& traceback) {
        endUndoGroup();
    }

private:
    std::string groupName;
};