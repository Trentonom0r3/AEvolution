#include "pch.h"
#include "PyCore.h"

PYBIND11_MODULE(AEvolutionPy, m) {
    bindLayer(m);
    bindItem(m);
    bindCompItem(m);
    bindFootageItem(m);
    bindFolderItem(m);
    bindProject(m);
    bindApp(m);
    //bind the LayerFlag enum
    bindLayerEnum(m);
    bindLayerCollection(m);
    bindProjectCollection(m);
    bindItemCollection(m);
    bindAdjustmentLayerItem(m);
    bindSolidItem(m);
    bindManifest(m);
};
