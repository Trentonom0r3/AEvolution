#include "pch.h"
#include "Items.h"


ItemH getActiveItem()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetActiveItem", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("No Active Item."); // Throw an error if the response contains an error (Propogated from the server)
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return item;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error in getActiveItem: " + std::string(e.what()));
	}
}

std::string getItemType(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemType", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Unable to determine Item type."); // Throw an error if the response contains an error (Propogated from the server)
		}

		std::string type = boost::get<std::string>(resp.args[0]);
		return type;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error in getItemType: " + std::string(e.what()));
	}
}

std::string getItemName(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemName", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		std::string name = boost::get<std::string>(resp.args[0]);
		return name;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error in getItemName: " + std::string(e.what()));
	}
}

void SetItemName(ItemH item, const std::string& name)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemName", CommandArgs{ boost::make_shared<ItemH>(item), name }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SetItemName: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemName: " + std::string(e.what()));
	}
}

float getItemDuration(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemDuration", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float duration = boost::get<float>(resp.args[0]);
		return duration;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error in getItemDuration: " + std::string(e.what()));
	}
}

float getItemCurrentTime(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float time = boost::get<float>(resp.args[0]);
		return time;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemCurrentTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemCurrentTime: " + std::string(e.what()));
	}
}

dimensionsH getItemDimensions(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemDimensions", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		dimensionsH dimensions = boost::get<dimensionsH>(resp.args[0]);
		return dimensions;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemDimensions: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemDimensions: " + std::string(e.what()));
	}
}

float getItemPixelAspectRatio(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemPixelAspectRatio", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float aspectRatio = boost::get<float>(resp.args[0]);
		return aspectRatio;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemPixelAspectRatio: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemPixelAspectRatio: " + std::string(e.what()));
	}
}

void deleteItem(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "DeleteItem", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in deleteItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in deleteItem: " + std::string(e.what()));
	}
}

std::string getItemComment(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemComment", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		std::string comment = boost::get<std::string>(resp.args[0]);
		return comment;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemComment: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemComment: " + std::string(e.what()));
	}
}

void setItemComment(ItemH item, const std::string& comment)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemComment", CommandArgs{ boost::make_shared<ItemH>(item), comment }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetItemComment: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemComment: " + std::string(e.what()));
	}
}

void SetItemComment(ItemH item, const std::string& comment)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemComment", CommandArgs{ boost::make_shared<ItemH>(item), comment }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetItemComment: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemComment: " + std::string(e.what()));
	}
}

float getUniqueItemID(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetUniqueItemID", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float uniqueID = boost::get<float>(resp.args[0]);
		return uniqueID;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getUniqueItemID: " << e.what() << std::endl;
		throw std::runtime_error("Error in getUniqueItemID: " + std::string(e.what()));
	}
}

ItemH createFolderItem(const std::string& name, ItemH parentFolder)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "CreateFolderItem", CommandArgs{ name, boost::make_shared<ItemH>(parentFolder)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		ItemH folderItem = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return folderItem;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in createFolderItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in createFolderItem: " + std::string(e.what()));
	}
}

ItemH getFirstProjItem(ProjectH project)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetFirstProjItem", CommandArgs{ boost::make_shared<ProjectH>(project)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return item;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getFirstProjItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in getFirstProjItem: " + std::string(e.what()));
	}
}

ItemH getNextProjItem(ProjectH project, ItemH currentItem)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetNextProjItem", CommandArgs{ boost::make_shared<ProjectH>(project), boost::make_shared<ItemH>(currentItem)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		if (auto item = boost::get<boost::shared_ptr<ItemH>>(resp.args[0])) {
			return *item;
		}
		else {
			ItemH itemP(nullptr);
			return itemP;
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getNextProjItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in getNextProjItem: " + std::string(e.what()));
	}
}

bool isItemSelected(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsItemSelected", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		bool selected = boost::get<bool>(resp.args[0]);
		return selected;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in isItemSelected: " << e.what() << std::endl;
		throw std::runtime_error("Error in isItemSelected: " + std::string(e.what()));
	}
}

void selectItem(ItemH item, bool select, bool deselectOthers)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SelectItem", CommandArgs{ boost::make_shared<ItemH>(item), select, deselectOthers }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in selectItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in selectItem: " + std::string(e.what()));
	}
}

float getItemFlags(ItemH item)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemFlags", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		float flags = boost::get<float>(resp.args[0]);
		return flags;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemFlags: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemFlags: " + std::string(e.what()));
	}
}

float getCompItemCurrentTime(ItemH item, float frameRate)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetCompItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item), frameRate }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		float time = boost::get<float>(resp.args[0]);
		return time;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getCompItemCurrentTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompItemCurrentTime: " + std::string(e.what()));
	}
}

void setCompItemCurrentTime(ItemH item, float time, float frameRate)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetCompItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item), time, frameRate }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetCompItemCurrentTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetCompItemCurrentTime: " + std::string(e.what()));
	}
}

void setItemUseProxy(ItemH item, bool useProxy)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemUseProxy", CommandArgs{ boost::make_shared<ItemH>(item), useProxy }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetItemUseProxy: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemUseProxy: " + std::string(e.what()));
	}
}

void SetCompItemCurrentTime(ItemH item, float time, float frameRate)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetCompItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item), time, frameRate }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetCompItemCurrentTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetCompItemCurrentTime: " + std::string(e.what()));
	}
}

void SetItemUseProxy(ItemH item, bool useProxy)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemUseProxy", CommandArgs{ boost::make_shared<ItemH>(item), useProxy }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetItemUseProxy: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemUseProxy: " + std::string(e.what()));
	}
}

ItemH getItemParentFolder(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemParentFolder", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		ItemH parentFolder = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return parentFolder;
	}
	catch (std::exception& e) {
		//std::cerr << "Error in getItemParentFolder: " << e.what() << std::endl;
		throw std::runtime_error("Error in getItemParentFolder: " + std::string(e.what()));
	}
}

void SetItemParentFolder(ItemH item, ItemH parentFolder)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemParentFolder", CommandArgs{ boost::make_shared<ItemH>(item), boost::make_shared<ItemH>(parentFolder) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in SetItemParentFolder: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetItemParentFolder: " + std::string(e.what()));
	}
}
