#include "pch.h"
#include "Comp.h"
#include "Collection.h"
#include "../Comps.h"

std::vector<std::unique_ptr<Layer>> LayerCollection::initialize()
{
	CompH comp = GetCompFromItem(this->handle_->getItemH());
	int numLayers = getNumLayers(comp);

	std::vector<std::unique_ptr<Layer>> layers;

	for (int i = 0; i < numLayers; i++) {
		LayerH layer = getLayerFromComp(comp, i);
		std::unique_ptr<Layer> layerItem = std::make_unique<Layer>(layer);
		layers.push_back(std::move(layerItem));
	}

	return layers;
}

void LayerCollection::append(std::unique_ptr<Layer> item)
{
	LayerH layer = item->getLayer();
	CompH comp = GetLayerParentComp(layer);
	ItemH itemH = getLayerSourceItem(layer);
	if (!isAddLayerValid(itemH, comp)) {
		throw std::invalid_argument("Layer cannot be added to this comp");
	}
	LayerH layerF = AddLayer(itemH, comp);

	changeLayerIndex(layerF, items_.size());
	std::unique_ptr<Layer> layerItem = std::make_unique<Layer>(layerF);

	items_.push_back(std::move(layerItem));
}

std::unique_ptr<Layer> LayerCollection::pop()
{
	if (items_.empty()) {
		throw std::out_of_range("Collection is empty");
	}
	auto item = std::move(items_.back());
	items_.pop_back();
	return item;
}
