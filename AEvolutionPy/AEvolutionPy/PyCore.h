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
void bindCompItem(py::module_& m);
void bindFootageItem(py::module_& m);
void bindFolderItem(py::module_& m);

void bindProject(py::module_& m);
void bindApp(py::module_& m);
void bindLayer(py::module_& m);
void bindLayerEnum(py::module_& m);
void bindLayerCollection(py::module_& m);
void bindSolidItem(py::module_& m);
void bindProjectCollection(py::module_& m);
void bindItemCollection(py::module_& m);
void bindAdjustmentLayerItem(py::module_& m);
void bindManifest(py::module_& m);

class Manifest {
public:
    Manifest() :
		_validVersions({ "AE2020", "AE2021", "AE2022", "AE2023", "AE2024", "AE2025", "AE2026", "AE2027", "AE2028", "AE2029", "AE2030" }),
		_pythonDefault("3.11"),
		name("Plugin Name"),
		version("1.0.0"),
        useJS(false),
		author("Author Name"),
		description("A Python-based plugin for After Effects."),
		entryPath("path/to/entry_script.py"),
        mainPath("path/to/main_script.py"),
		dependenciesFolder({ "PyShiftAE" })
	{}


    std::string name;
    std::string version;
    std::string author;
    std::string description;
    std::vector<std::string> AE_VERS;
    std::string entryPath;
    std::string mainPath;
    std::vector<std::string> dependenciesFolder;
    bool useJS = false;

private:
    std::vector<std::string> _validVersions = {"AE2020", "AE2021", "AE2022", "AE2023", "AE2024", "AE2025", "AE2026", "AE2027", "AE2028", "AE2029", "AE2030"};
    std::string _pythonDefault = "3.11";
    std::string _entry;
    std::vector<std::string> _dependencies;
  
};
