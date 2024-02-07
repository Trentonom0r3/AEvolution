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
		.def_property("name", &Item::name, &Item::setName)
		.def_property_readonly("duration", &Item::duration)
		.def_property_readonly("time", &Item::currentTime)
		.def_property("comment", &Item::getComment, &Item::setComment)
		.def_property("selected", &Item::isSelected, &Item::setSelected)
		.def_property("proxy", &Item::getProxy, &Item::setProxy)
		.def_property("parent", &Item::getParent, &Item::setParent)
		.def("delete", &Item::Delete);


	py::class_<CompItem, Item>(m, "CompItem")
		.def(py::init<ItemH>())
		//.def_property_readonly("layers", &CompItem::getLayers)
		.def_property("duration", &CompItem::duration, &CompItem::setDuration)
		.def_property("time", &CompItem::currentTime, &CompItem::setCurrentTime)
		.def_property("dimensions", &CompItem::getDimensions, &CompItem::setDimensions)
		.def_property("frameRate", &CompItem::getFrameRate, &CompItem::setFrameRate)
		.def_property("workAreaStart", &CompItem::WorkAreaStart, &CompItem::setWorkStart)
		.def_property("workAreaDuration", &CompItem::WorkAreaDuration, &CompItem::setWorkDuration)
		.def_property("displayStartTime", &CompItem::getDisplayStartTime, &CompItem::setDisplayStartTime)
		.def_property("displayDropFrame", &CompItem::getDisplayDropFrame, &CompItem::setDisplayDropFrame)
		.def("createSolid", &CompItem::createSolid)
		.def("createCamera", &CompItem::createCamera)
		.def("createLight", &CompItem::createLight)
		.def("createNull", &CompItem::createNull)
		.def("createVector", &CompItem::createVector);

	py::class_<FolderItem, Item>(m, "FolderItem")
		.def(py::init<ItemH>());

	py::class_<FootageItem, Item>(m, "FootageItem")
		.def(py::init<ItemH>());

	py::class_<Layer>(m, "Layer")
		.def(py::init<LayerH>())
		.def_property_readonly("name", &Layer::getName)
		.def_property("index", &Layer::LayerIndex, &Layer::setLayerIndex)
		.def_property("sourceName", &Layer::LayerSourceName, &Layer::SetLayerName)
		.def_property("video", &Layer::isVideo, &Layer::isAudio)
		.def_property("offset", &Layer::LayerOffset, &Layer::setLayerOffset)
		.def_property("is2D", &Layer::is2D, &Layer::is3D)
		.def_property("parent", &Layer::LayerParent, &Layer::setParent)
		.def("duplicate", &Layer::duplicate)
		.def("delete", &Layer::deleteLayer);
}
