#include "pch.h"
#include "PyCore.h"


PYBIND11_MODULE(AEvolutionPy, m) {//define class
	py::class_<App>(m, "App")
		.def(py::init<>())
		.def("reportInfo", &App::reportInfo)
		.def_property_readonly("path", &App::path)
		.def_property_readonly("project", &App::getProject);

	py::class_<UndoGroup>(m, "UndoGroup")
		.def(py::init<const std::string&>())
		.def("__enter__", &UndoGroup::__enter__)
		.def("__exit__", &UndoGroup::__exit__);

	py::class_<Project>(m, "Project")
		.def(py::init<>())
		.def_property_readonly("name", &Project::name)
		.def_property_readonly("path", &Project::path)
		.def("save", &Project::saveToPath)
		.def("isDirty", &Project::isDirty)
		.def("saveAs", &Project::saveAs)
		.def_property("bitDepth", &Project::bitDepth, &Project::setBitDepth)
		.def_property_readonly("activeItem", &Project::GetActiveItem);

	py::class_<Item>(m, "Item")
		.def(py::init<ItemH>())
		.def_property_readonly("name", &Item::name);

	py::class_<CompItem, Item>(m, "CompItem")
		.def(py::init<ItemH>());

	py::class_<FolderItem, Item>(m, "FolderItem")
		.def(py::init<ItemH>());

	py::class_<FootageItem, Item>(m, "FootageItem")
		.def(py::init<ItemH>());

}
