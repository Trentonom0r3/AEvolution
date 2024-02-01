#include "pch.h"
#include "PyCore.h"

PYBIND11_MODULE(AEvolutionPy, m) {
	bindItem(m);
	bindPrint(m);
	bindGetItem(m);
	bindgetItemType(m);
};
