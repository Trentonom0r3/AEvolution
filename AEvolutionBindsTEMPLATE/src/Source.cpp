#include "pch.h"
#include "ItemWraps.h"

BOOST_CLASS_EXPORT(GetActiveItem)
BOOST_CLASS_EXPORT(GetActiveItemCmd)
BOOST_CLASS_EXPORT(GetItemType)
BOOST_CLASS_EXPORT(GetItemTypeCmd)

//create module
PYBIND11_MODULE(AEvolutionTemplate, m) {
	//define the AEGP_ItemType enum for global use
    py::enum_<AEGP_ItemType>(m, "AEGP_ItemType")
        .value("NONE", AEGP_ItemType_NONE)
        .value("FOLDER", AEGP_ItemType_FOLDER)
        .value("COMP", AEGP_ItemType_COMP)
        .value("SOLID_defunct", AEGP_ItemType_SOLID_defunct) // Note: As of AE6, consider how you want to expose deprecated or defunct items
        .value("FOOTAGE", AEGP_ItemType_FOOTAGE)
        .value("NUM_TYPES", AEGP_ItemType_NUM_TYPES1) // Assuming you want to expose this as well
        .export_values();


	py::class_<AE_Item>(m, "Item")
		.def(py::init<>());

	m.def("getActiveItem", &getactiveitem);
	m.def("type", &getitemtype);
	
}