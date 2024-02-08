#include "pch.h"
#include "Comp.h"
#include "Collection.h"
#include "Item.h"
#include "Comp.h"
#include "Folder.h"
#include "Footage.h"


/*
std::vector<std::shared_ptr<Item>> ItemCollection::getItems()
{
	std::vector<std::shared_ptr<Item>> items = {};
	auto item = this->itemHandle_;

	Result<AEGP_ItemH> itemhandle = item;

	// Check if the current folder item is valid
	if (itemhandle.value == NULL) {
		throw std::runtime_error("No active item");
	}

	auto& projectMessage = enqueueSyncTask(getProject);
	projectMessage->wait();

	Result<AEGP_ProjectH> projectResult = projectMessage->getResult();

	Result<AEGP_ItemH> currentItemResult = itemhandle;

	while (currentItemResult.value != NULL) {
		// Check if the current item is a child of the folder
		auto& message = enqueueSyncTask(GetItemParentFolder, currentItemResult);
		message->wait();

		Result<AEGP_ItemH> parentItemH = message->getResult();

		if (parentItemH.value == itemhandle.value) {
			// Get the type of the current item
			auto& typeMessage = enqueueSyncTask(getItemType, currentItemResult);
			typeMessage->wait();
			Result<AEGP_ItemType> itemTypeResult = typeMessage->getResult();
			if (itemTypeResult.error != A_Err_NONE) {
				throw std::runtime_error("Error getting item type");
			}

			// Add the current item to the list based on its type
			switch (itemTypeResult.value) {
			case AEGP_ItemType_FOLDER:
				items.push_back(std::make_shared<FolderItem>(currentItemResult));
				break;
			case AEGP_ItemType_FOOTAGE:
				items.push_back(std::make_shared<FootageItem>(currentItemResult));
				break;
			case AEGP_ItemType_COMP:
				items.push_back(std::make_shared<CompItem>(currentItemResult));
				break;
				// Handle other types as needed
			}
		}

		// Get the next project item
		auto& nextItemMessage = enqueueSyncTask(GetNextProjItem, projectResult, currentItemResult);
		nextItemMessage->wait();
		currentItemResult = nextItemMessage->getResult();
		//if ItemH.getsessionID = "", then break
	}

	return items;
}
*/
std::vector<std::unique_ptr<Item>> ItemCollection::initialize()
{
	ItemH item = this->handle_->getItemH();
	ProjectH proj = getProject();
	std::vector<std::unique_ptr<Item>> items = {};

	ItemH currentItem = item;

	while (currentItem.getSessionID() != "") {

		ItemH parentItemh = getItemParentFolder(currentItem);
		float parentID = getUniqueItemID(parentItemh);
		float itemID = getUniqueItemID(currentItem);
		if (parentID == itemID) {
			ItemType type = checkType(currentItem);
			if (type == ItemType::Folder) {
				items.push_back(std::make_unique<FolderItem>(currentItem));
			}
			else if (type == ItemType::Comp) {
				items.push_back(std::make_unique<CompItem>(currentItem));
			}
			else if (type == ItemType::Footage) {
				items.push_back(std::make_unique<FootageItem>(currentItem));
			}
			else {
				throw std::invalid_argument("Invalid item type");
			}
		}

		currentItem = getNextProjItem(proj, currentItem);

	}

}


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
