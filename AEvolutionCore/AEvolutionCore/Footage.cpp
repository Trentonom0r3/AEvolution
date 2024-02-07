#include "pch.h"
#include "Footage.h"

FootageH createFootage(const std::string& path)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "CreateFootage", path);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		FootageH footage = *boost::get<boost::shared_ptr<FootageH>>(resp.args[0]);
		return footage;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error creating footage: " + std::string(e.what()));
	}
}

void disposeFootage(FootageH footageH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "DisposeFootage");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error disposing footage: " + std::string(e.what()));
	}
}

ItemH addFootageToProject(FootageH footageH, ItemH parentFolderH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "AddFootageToProject");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		if (parentFolderH.getSessionID() == "") {
			throw std::runtime_error("Parent folder is not in a session");
		}
		cmd.args.push_back(boost::make_shared<ItemH>(parentFolderH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return item;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error adding footage to project: " + std::string(e.what()));
	}
}

colorH GetItemSolidColor(ItemH itemH, bool proxyB)
{
	auto& mqm = MessageQueueManager::getInstance();
try {
		Command cmd(createUUID(), "GetItemSolidColor");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(proxyB);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		colorH color = boost::get<colorH>(resp.args[0]);
		return color;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting item solid color: " + std::string(e.what()));
	}
}

void SetSolidColor(ItemH itemH, bool proxyB, colorH color)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetSolidColor");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(proxyB);
		cmd.args.push_back(color);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error setting solid color: " + std::string(e.what()));
	}
}

dimensionsH GetSolidDimensions(ItemH itemH, bool proxyB)
{
	auto& mqm = MessageQueueManager::getInstance();
try {
		Command cmd(createUUID(), "GetSolidDimensions");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(proxyB);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		dimensionsH dims = boost::get<dimensionsH>(resp.args[0]);
		return dims;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting solid dimensions: " + std::string(e.what()));
	}
}

void SetSolidDimensions(ItemH itemH, bool proxyB, dimensionsH dims)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetSolidDimensions");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(proxyB);
		cmd.args.push_back(dims);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error setting solid dimensions: " + std::string(e.what()));
	}
}

FootageH GetMainFootageFromItem(ItemH itemH)
{
	auto& mqm = MessageQueueManager::getInstance();
try {
		Command cmd(createUUID(), "GetMainFootageFromItem");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		FootageH footage = *boost::get<boost::shared_ptr<FootageH>>(resp.args[0]);
		return footage;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting main footage from item: " + std::string(e.what()));
	}
}

FootageH GetProxyFootageFromItem(ItemH itemH)
{
auto& mqm = MessageQueueManager::getInstance();
try {
		Command cmd(createUUID(), "GetProxyFootageFromItem");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		FootageH footage = *boost::get<boost::shared_ptr<FootageH>>(resp.args[0]);
		return footage;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting proxy footage from item: " + std::string(e.what()));
	}
}

std::pair<int, int> GetFootageNumFiles(FootageH footageH)
{
auto& mqm = MessageQueueManager::getInstance();
try {
		Command cmd(createUUID(), "GetFootageNumFiles");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		//std::pair<int, int> numFiles = boost::get<std::pair<int, int>>(resp.args[0]);
		//return numFiles;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting footage num files: " + std::string(e.what()));
	}
}

std::string GetFootagePath(FootageH footageH, int frameNum, int fileIndex)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetFootagePath");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		cmd.args.push_back(frameNum);
		cmd.args.push_back(fileIndex);
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		std::string path = boost::get<std::string>(resp.args[0]);
		return path;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error getting footage path: " + std::string(e.what()));
	}
}

void SetItemProxyFootage(FootageH footageH, ItemH itemH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetItemProxyFootage");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error setting item proxy footage: " + std::string(e.what()));
	}
}

ItemH ReplaceItemMainFootage(FootageH footageH, ItemH itemH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ReplaceItemMainFootage");
		cmd.args.push_back(boost::make_shared<FootageH>(footageH));
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return item;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error replacing item main footage: " + std::string(e.what()));
	}
}

FootageH NewPlaceholderFootage(const std::string& name, dimensionsH dimensions, float duration, float frameRate)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "NewPlaceholderFootage");
		cmd.args.push_back(name);
		cmd.args.push_back(dimensions);
		cmd.args.push_back(duration);
		cmd.args.push_back(frameRate);

		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		FootageH footage = *boost::get<boost::shared_ptr<FootageH>>(resp.args[0]);
		return footage;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error creating placeholder footage: " + std::string(e.what()));
	}
}

FootageH NewSolidFootage(const std::string& name, float width, float height, colorH color)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "NewSolidFootage");
		cmd.args.push_back(name);
		cmd.args.push_back(width);
		cmd.args.push_back(height);
		cmd.args.push_back(color);

		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();

		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		FootageH footage = *boost::get<boost::shared_ptr<FootageH>>(resp.args[0]);
		return footage;
	}
	catch (std::exception& e) {
		throw std::runtime_error("Error creating solid footage: " + std::string(e.what()));
	}
}
