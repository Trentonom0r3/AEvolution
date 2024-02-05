#include "pch.h"
#include "Items.h"


ItemH getActiveItem()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getActiveItem", CommandArgs{}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemType", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemName", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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

void setItemName(ItemH item, const std::string& name)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setItemName", CommandArgs{ boost::make_shared<ItemH>(item), name }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setItemName: " << e.what() << std::endl;
		throw std::runtime_error("Error in setItemName: " + std::string(e.what()));
	}
}

float getItemDuration(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getItemDuration", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemDimensions", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemPixelAspectRatio", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "deleteItem", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getItemComment", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "setItemComment", CommandArgs{ boost::make_shared<ItemH>(item), comment }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in setItemComment: " << e.what() << std::endl;
		throw std::runtime_error("Error in setItemComment: " + std::string(e.what()));
	}
}

float getUniqueItemID(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getUniqueItemID", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "createFolderItem", CommandArgs{ name, boost::make_shared<ItemH>(parentFolder)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getFirstProjItem", CommandArgs{ boost::make_shared<ProjectH>(project)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "getNextProjItem", CommandArgs{ boost::make_shared<ProjectH>(project), boost::make_shared<ItemH>(currentItem)}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return item;
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
		Command cmd(createUUID(), "isItemSelected", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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
		Command cmd(createUUID(), "selectItem", CommandArgs{ boost::make_shared<ItemH>(item), select, deselectOthers }); // Command to be sent to the server
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
	return 0.0f;
}

float getCompItemCurrentTime(ItemH item, float frameRate)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item), frameRate }); // Command to be sent to the server
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
		Command cmd(createUUID(), "setCompItemCurrentTime", CommandArgs{ boost::make_shared<ItemH>(item), time, frameRate }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in setCompItemCurrentTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompItemCurrentTime: " + std::string(e.what()));
	}
}

void setItemUseProxy(ItemH item, bool useProxy)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setItemUseProxy", CommandArgs{ boost::make_shared<ItemH>(item), useProxy }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in setItemUseProxy: " << e.what() << std::endl;
		throw std::runtime_error("Error in setItemUseProxy: " + std::string(e.what()));
	}
}

ItemH getItemParentFolder(ItemH item)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getItemParentFolder", CommandArgs{ boost::make_shared<ItemH>(item)}); // Command to be sent to the server
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

void setItemParentFolder(ItemH item, ItemH parentFolder)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setItemParentFolder", CommandArgs{ boost::make_shared<ItemH>(item), boost::make_shared<ItemH>(parentFolder) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		//std::cerr << "Error in setItemParentFolder: " << e.what() << std::endl;
		throw std::runtime_error("Error in setItemParentFolder: " + std::string(e.what()));
	}
}
