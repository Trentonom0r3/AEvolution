#include "pch.h"
#include "Collections.h"
#include "LayerObject.h"
#include "ItemObjects.h"

wLayerCollection::wLayerCollection(wComp comp)
{
	CommandH cmd = boost::make_shared<GetCompNumLayersCmd>(comp.comp);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<GetCompNumLayersResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting number of layers: " + resp->error);
	}
	layers.reserve(resp->num_layers);
	for (int i = 1; i <= resp->num_layers; i++) {
		CommandH cmd = boost::make_shared<GetCompLayerByIndexCmd>(comp.comp, i);
		auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
		auto resp = boost::dynamic_pointer_cast<GetCompLayerByIndexResp>(response);
		if (resp->error != "A_Err_NONE") {
			throw std::runtime_error("Error getting layer: " + resp->error);
		}
		layers.push_back(wLayer(resp->layer));
	}
}

std::size_t wLayerCollection::size() const
{
	return layers.size();
}

wLayer& wLayerCollection::operator[](std::size_t index)
{
	return layers[index];
}

const wLayer& wLayerCollection::operator[](std::size_t index) const
{
	return layers[index];
}

void wLayerCollection::append(const wItem& layer)
{
	CommandH cmd = boost::make_shared<IsAddLayerValidCmd>(comp.comp);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<IsAddLayerValidResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error checking if layer can be added: " + resp->error);
	}
	if (resp->valid) {
		CommandH cmd = boost::make_shared<AddLayerCmd>(layer, comp.comp);
		auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
		auto resp = boost::dynamic_pointer_cast<AddLayerResp>(response);
		if (resp->error != "A_Err_NONE") {
			throw std::runtime_error("Error adding layer: " + resp->error);
		}
		layers.push_back(wLayer(resp->layer));
	}
	else {
		throw std::runtime_error("Layer cannot be added");
	}
}

void wLayerCollection::remove(std::size_t index)
{
	CommandH cmd = boost::make_shared<DeleteLayerCmd>(layers[index].layer);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<DeleteLayerResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error deleting layer: " + resp->error);
	}
	layers.erase(layers.begin() + index);
}

std::vector<wLayer> wLayerCollection::getAllItems() const
{
	return layers;
}

wItemCollection::wItemCollection(wFolder folder)
{
	CommandH cmd = boost::make_shared<GetProjectByIndexCmd>(0);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<GetProjectByIndexResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting project: " + resp->error);
	}
	auto project = resp->project; //AE_Project
	AE_Item item = folder.item;
	AEGP_ItemH currentItem = item.handle;
	while (currentItem != NULL) {
		// Check if the current item is a child of the folder
		CommandH cmd = boost::make_shared<GetItemParentFolderCmd>(currentItem);
		auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
		auto resp = boost::dynamic_pointer_cast<GetItemParentFolderResp>(response);
		if (resp->error != "A_Err_NONE") {
			throw std::runtime_error("Error getting parent folder: " + resp->error);
		}
		if (resp->parent_itemPH.handle == folder.item.handle) {
			// Get the type of the current item
			CommandH cmd = boost::make_shared<GetItemTypeCmd>(currentItem);
			auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
			auto resp = boost::dynamic_pointer_cast<GetItemTypeResp>(response);
			if (resp->error != "A_Err_NONE") {
				throw std::runtime_error("Error getting item type: " + resp->error);
			}
			// Add the current item to the list based on its type
			switch (resp->item_type) {
			case AEGP_ItemType::AEGP_ItemType_FOLDER:
				items.push_back(std::make_unique<wFolder>(item));
				break;
			case AEGP_ItemType::AEGP_ItemType_FOOTAGE:
				items.push_back(std::make_unique<wFootage>(item));
				break;
			case AEGP_ItemType::AEGP_ItemType_COMP:
				items.push_back(std::make_unique<wComp>(item));
				break;
			}
		}
		// Get the next project item
		CommandH cmd = boost::make_shared<GetNextProjItemCmd>(project, currentItem);
		auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
		auto resp = boost::dynamic_pointer_cast<GetNextProjItemResp>(response);
		if (resp->error != "A_Err_NONE") {
			throw std::runtime_error("Error getting next project item: " + resp->error);
		}
		item = resp->parent_itemPH;
	}
}

std::size_t wItemCollection::size() const
{
	return std::size_t();
}

std::unique_ptr<wItem>& wItemCollection::operator[](std::size_t index)
{
	return items[index];
}

const std::unique_ptr<wItem>& wItemCollection::operator[](std::size_t index) const
{
	return items[index];
}

void wItemCollection::append(const std::unique_ptr<wItem>& item)
{
	AE_Item itemToAdd = item->item;
	AE_Item folder = this->folder.item;
	CommandH cmd = boost::make_shared<SetItemParentFolderCmd>(itemToAdd, folder);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error setting parent folder: " + response->error);
	}
	items.push_back(std::move(item));
}

void wItemCollection::remove(std::size_t index)
{
	CommandH cmd = boost::make_shared<DeleteItemCmd>(items[index]->item);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error deleting item: " + response->error);
	}
	items.erase(items.begin() + index);
}

std::vector<std::unique_ptr<wItem>> wItemCollection::getAllItems() const
{
	return items;
}
