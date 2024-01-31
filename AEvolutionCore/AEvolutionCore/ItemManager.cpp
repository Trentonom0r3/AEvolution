#include "pch.h"
#include "include/ItemManager.h"

void Item::deleteItem()
{
	Command cmd;
	cmd.name = "DeleteItem";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error(resp.error);
	}
}

std::string Item::getItemHandle()
{
	return this->sessionID;
}


bool Item::isSelected()
{
	Command cmd;
	cmd.name = "IsItemSelected";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	bool output = boost::get<bool>(resp.args[0]);
	return output;
}

void Item::setSelected(bool select)
{
	Command cmd;
	cmd.name = "SelectItem";
	cmd.args.push_back(select);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error(resp.error);
	}
}

std::string Item::getName()
{
	Command cmd;
	cmd.name = "GetItemName";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Item::setName(std::string name)
{
	Command cmd;
	cmd.name = "SetItemName";
	cmd.args.push_back(name);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting name:" + resp.error);
	}

}

float Item::getWidth()
{
	try {
	Command cmd;
	cmd.name = "GetItemWidth";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
} catch (boost::bad_get& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in gathering Width:" + std::string(e.what()));
}
catch (std::exception& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in gathering Width:" + std::string(e.what()));
}
}

float Item::getHeight()
{
	try {
	Command cmd;
	cmd.name = "GetItemHeight";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
} catch (boost::bad_get& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in gathering Height:" + std::string(e.what()));
}
catch (std::exception& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in gathering Height:" + std::string(e.what()));
}
}

float Item::getCurrentTime()
{
	Command cmd;
	cmd.name = "GetItemCurrentTime";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Item::getDuration()
{
	Command cmd;
	cmd.name = "GetItemDuration";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void Item::setCurrentTime(float time)
{
	Command cmd;
	cmd.name = "SetItemCurrentTime";
	cmd.args.push_back(time);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting current time:" + resp.error);
	}
}

float CompItem::getFrameRate()
{
	Command cmd;
	cmd.name = "GetCompFramerate";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void CompItem::setFrameRate(float frameRate)
{
	Command cmd;
	cmd.name = "SetCompFramerate";
	cmd.args.push_back(frameRate);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting framerate:" + resp.error);
	}
}

float CompItem::getDuration()
{
	Command cmd;
	cmd.name = "GetCompWorkAreaDuration";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
}


void CompItem::setDuration(float duration)
{
	Command cmd;
	cmd.name = "SetCompDuration";
	cmd.args.push_back(duration);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting duration:" + resp.error);
	}
}

void CompItem::setWidth(float width)
{
	Command cmd;
	cmd.name = "SetCompWidth";
	cmd.args.push_back(width);
	cmd.sessionID = this->sessionID;

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting width:" + resp.error);
	}
}

void CompItem::setHeight(float height)
{
	Command cmd;
	cmd.name = "SetCompHeight";
	cmd.args.push_back(height);
	cmd.sessionID = this->sessionID;

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting height:" + resp.error);
	}
}

std::shared_ptr<Layer> CompItem::newSolid(std::string name, float width, float height,float red, float green, float blue, float alpha,
						float duration)
{
	Command cmd;
	cmd.name = "CreateSolidInComp";
	cmd.args.push_back(name);
	cmd.args.push_back(width);
	cmd.args.push_back(height);
	cmd.args.push_back(red);
	cmd.args.push_back(green);
	cmd.args.push_back(blue);
	cmd.args.push_back(alpha);
	cmd.args.push_back(duration);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string layerHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(layerHandle);
	return layer;
}


std::shared_ptr<LayerCollection> CompItem::getSelectedLayers()
{
	Command cmd;
	cmd.name = "GetSelectedLayers";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::string compHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<LayerCollection> layerCollection = std::make_shared<LayerCollection>(compHandle);
	return layerCollection;
}

std::shared_ptr<CompItem> CompItem::CreateNew(std::string name, float width, float height, float frameRate, float duration, float aspectRatio)
{
	return std::shared_ptr<CompItem>();
}

std::shared_ptr<LayerCollection> CompItem::getLayers()
{
	try {
		Command cmd;
		cmd.name = "GetLayers";
		cmd.sessionID = this->sessionID;

			auto& mqm = MessageQueueManager::getInstance();
		mqm.sendCommand(cmd);
		Response resp;
		while (!mqm.tryReceiveResponse(resp)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::string outID = boost::get<std::string>(resp.args[0]);
		std::shared_ptr<LayerCollection> layerCollection = std::make_shared<LayerCollection>(outID);
		return layerCollection;

	} catch (boost::bad_get& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int CompItem::NumLayers()
{
	Command cmd;
	cmd.name = "GetNumLayers";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	int output = boost::get<int>(resp.args[0]);
	return output;
}

float CompItem::getCurrentTime()
{
	Command cmd;
	cmd.name = "GetCompItemCurrentTime";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	float output = boost::get<float>(resp.args[0]);
	return output;
}

void CompItem::setCurrentTime(float time)
{
	Command cmd;
	cmd.name = "SetCompItemCurrentTime";
	cmd.args.push_back(time);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting current time:" + resp.error);
	}
}

void CompItem::addLayer(std::string name, std::string path, int index)
{
	Command cmd;
	cmd.name = "AddLayerToComp";
	cmd.args.push_back(name);
	cmd.args.push_back(path);
	cmd.args.push_back(index);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in adding layer:" + resp.error);
	}
}

std::string Layer::GetLayerName()
{
Command cmd;
	cmd.name = "GetLayerName";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

std::string Layer::GetSourceName()
{
	Command cmd;
	cmd.name = "GetLayerSourceName";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Layer::SetLayerName(std::string name)
{
	Command cmd;
	cmd.name = "SetLayerName";
	cmd.args.push_back(name);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting layer name:" + resp.error);
	}
}

int Layer::index()
{
	Command cmd;
	cmd.name = "GetLayerIndex";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	int output = boost::get<int>(resp.args[0]);
	return output;
}

void Layer::changeIndex(int index)
{
	Command cmd;
	cmd.name = "ChangeLayerIndex";
	cmd.args.push_back(index);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
	throw std::runtime_error("Error in changing layer index:" + resp.error);
	}
}

std::shared_ptr<FootageItem> Layer::duplicate()
{
	Command cmd;
	cmd.name = "DuplicateLayer";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(output);
	return footageItem;
}

float Layer::layerTime() // time in # frames
{
	Command cmd;
	cmd.name = "GetLayerCurrentTime";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}



float Layer::layerCompTime()
{
Command cmd;
	cmd.name = "GetLayerCompTime";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}



float Layer::inPoint()
{	
	Command cmd;
	cmd.name = "GetLayerInPoint";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::compInPoint()
{
	Command cmd;
	cmd.name = "GetLayerInPoint";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::duration()
{
	Command cmd;
	cmd.name = "GetLayerDuration";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}

float Layer::compDuration()
{
	Command cmd;
	cmd.name = "GetLayerCompDuration";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}


std::string Layer::getQuality()
{
	Command cmd;
	cmd.name = "GetLayerQuality";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}


void Layer::setQuality(int quality)
{
	Command cmd;
	cmd.name = "SetLayerQuality";
	cmd.args.push_back(quality);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in setting quality:" + resp.error);
	}
}


void Layer::deleteLayer()
{
	Command cmd;
	cmd.name = "DeleteLayer";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
throw std::runtime_error("Error in deleting layer:" + resp.error);
	}
}

float Layer::getOffset()
{
	Command cmd;
	cmd.name = "GetLayerOffset";
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	float output = boost::get<float>(resp.args[0]);
	return output;
}

void Layer::setOffset(float offset)
{
	Command cmd;
	cmd.name = "SetLayerOffset";
	cmd.args.push_back(offset);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
throw std::runtime_error("Error in setting offset:" + resp.error);
	}
}

void Layer::setFlag(LayerFlag flag, bool value)
{
	Command cmd;
	cmd.name = "SetLayerFlag";
	cmd.args.push_back(flag);
	cmd.args.push_back(value);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
}

bool Layer::getFlag(LayerFlag flag)
{
	Command cmd;
	cmd.name = "GetLayerFlag";

	cmd.args.push_back(flag);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	bool output = boost::get<bool>(resp.args[0]);
	return output;
}


std::string Layer::getLayerSessionID()
{
return this->sessionID;
}

std::shared_ptr<Item> Layer::getSource()
{
	Command cmd;
	cmd.name = "GetLayerSource";

	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<FootageItem> item = std::make_shared<FootageItem>(output); //adjust to return correct item type
	return item;
}

std::shared_ptr<FolderItem> FolderItem::createNew(std::string name)
{
	try {
	Command cmd;
	cmd.sessionID = createUUID();
	cmd.name = "CreateFolderItem";
	cmd.args.push_back(name);

	auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error in creating folder:" + resp.error);
	}
	std::string folderHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<FolderItem> folderItem = std::make_shared<FolderItem>(folderHandle);
	return folderItem;
} catch (boost::bad_get& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in creating folder:" + std::string(e.what()));
}
catch (std::exception& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in creating folder:" + std::string(e.what()));
}
}

std::shared_ptr<ItemCollection> FolderItem::ChildItems()
{
	Command cmd;
	cmd.name = "getFolderChildren";
	cmd.sessionID = this->sessionID;

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	std::string ID = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<ItemCollection> itemCollection = std::make_shared<ItemCollection>(ID);
	return itemCollection;
}

void LayerCollection::removeLayerFromCollection(Layer layerHandle)
{
	Command cmd;
	cmd.name = "RemoveLayerFromCollection";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(layerHandle.getLayerSessionID());

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {

		throw std::runtime_error("Error in removing layer from collection:" + resp.error);
	}
}

void LayerCollection::RemoveLayerByIndex(int index)
{
	Command cmd;
	cmd.name = "RemoveLayerByIndex";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(index);

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
throw std::runtime_error("Error in removing layer from collection:" + resp.error);
	}

}

std::vector<std::shared_ptr<Layer>> LayerCollection::getAllLayers()
{
	try {
		std::vector<std::shared_ptr<Layer>> layers;
		Command cmd;
		cmd.name = "GetAllLayers";
		cmd.sessionID = this->compHandle_;

		auto& mqm = MessageQueueManager::getInstance();
		mqm.sendCommand(cmd);

		Response resp;
		while (!mqm.tryReceiveResponse(resp)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		std::vector<std::string> layerHandles = boost::get<std::vector<std::string>>(resp.args[0]);

		for (int i = 0; i < layerHandles.size(); i++) {
			std::shared_ptr<Layer> layer = std::make_shared<Layer>(layerHandles[i]);
			layers.push_back(layer);
		}
		return layers;
	}
	catch (boost::bad_get& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

std::string LayerCollection::getCompName()
{
	Command cmd;
	cmd.name = "GetCompName";
	cmd.sessionID = this->compHandle_;

		auto& mqm = MessageQueueManager::getInstance();

	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

std::shared_ptr<Layer> LayerCollection::addLayerToCollection(Item itemHandle, int index) {
	Command cmd;
	cmd.name = "AddLayerToCollection";
	cmd.sessionID = this->compHandle_;
	cmd.args.push_back(itemHandle.getItemHandle());
	cmd.args.push_back(index);

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(output);
	return layer;
}


std::vector<std::shared_ptr<Item>> ItemCollection::getItems()
{
	std::vector<std::shared_ptr<Item>> items = {};
	Command cmd;
	cmd.name = "getItems";
	cmd.sessionID = this->sessionID;
	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {

		throw std::runtime_error("Error in getting items:" + resp.error);
	}

	std::vector<std::string> itemHandles = boost::get<std::vector<std::string>>(resp.args[0]);
	std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(resp.args[1]);

	for (int i = 0; i < itemHandles.size(); i++) {
		if (itemTypes[i] == "Folder") {
			std::shared_ptr<FolderItem> folderItem = std::make_shared<FolderItem>(itemHandles[i]);
			items.push_back(folderItem);
		}
		else if (itemTypes[i] == "Footage") {
			std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(itemHandles[i]);
			items.push_back(footageItem);
		}
		else if (itemTypes[i] == "Comp") {
			std::shared_ptr<CompItem> compItem = std::make_shared<CompItem>(itemHandles[i]);
			items.push_back(compItem);
		}
		else if (itemTypes[i] == "Solid") {
			std::shared_ptr<SolidItem> solidItem = std::make_shared<SolidItem>(itemHandles[i]);
			items.push_back(solidItem);
		}
	}

	return items;
}

std::vector<std::shared_ptr<Item>> ItemCollection::append(std::shared_ptr<Item> item)
{
	Command cmd;
	cmd.name = "AppendItem";
	cmd.sessionID = this->sessionID;
	cmd.args.push_back(item->getItemHandle());
	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	std::vector<std::shared_ptr<Item>> items;
	std::vector<std::string> itemHandles = boost::get<std::vector<std::string>>(resp.args[0]);
	std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(resp.args[1]);

	for (int i = 0; i < itemHandles.size(); i++) {
		if (itemTypes[i] == "Folder") {
			std::shared_ptr<FolderItem> folderItem = std::make_shared<FolderItem>(itemHandles[i]);
			items.push_back(folderItem);
		}
		else if (itemTypes[i] == "Footage") {
			std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(itemHandles[i]);
			items.push_back(footageItem);
		}
		else if (itemTypes[i] == "Comp") {
			std::shared_ptr<CompItem> compItem = std::make_shared<CompItem>(itemHandles[i]);
			items.push_back(compItem);
		}
		else if (itemTypes[i] == "Solid") {
			std::shared_ptr<SolidItem> solidItem = std::make_shared<SolidItem>(itemHandles[i]);
			items.push_back(solidItem);
		}
	}
	items_ = items;
	return items;
}

std::vector<std::shared_ptr<Item>> ItemCollection::remove(std::shared_ptr<Item> item)
{
	Command cmd;
	cmd.name = "RemoveItem";
	cmd.sessionID = this->sessionID;
	cmd.args.push_back(item->getItemHandle());
	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;

	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	if (resp.error != "") {

		throw std::runtime_error("Error in removing item:" + resp.error);
	}

	std::vector<std::shared_ptr<Item>> items;

	std::vector<std::string> itemHandles = boost::get<std::vector<std::string>>(resp.args[0]);
	std::vector<std::string> itemTypes = boost::get<std::vector<std::string>>(resp.args[1]);

	for (int i = 0; i < itemHandles.size(); i++) {
		if (itemTypes[i] == "Folder") {
			std::shared_ptr<FolderItem> folderItem = std::make_shared<FolderItem>(itemHandles[i]);
			items.push_back(folderItem);
		}
		else if (itemTypes[i] == "Footage") {
			std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(itemHandles[i]);
			items.push_back(footageItem);
		}
		else if (itemTypes[i] == "Comp") {
			std::shared_ptr<CompItem> compItem = std::make_shared<CompItem>(itemHandles[i]);
			items.push_back(compItem);
		}
		else if (itemTypes[i] == "Solid") {
			std::shared_ptr<SolidItem> solidItem = std::make_shared<SolidItem>(itemHandles[i]);
			items.push_back(solidItem);
		}
	}
	items_ = items;
	return items_;

}

std::shared_ptr<FootageItem> FootageItem::createNew(std::string name, std::string path, int index)
{
	Command cmd;
	cmd.name = "CreateFootageItem";
	cmd.args.push_back(name);
	cmd.args.push_back(path);
	cmd.args.push_back(index);

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	std::string footageHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<FootageItem> footageItem = std::make_shared<FootageItem>(footageHandle);
	return footageItem;
}

std::string FootageItem::getPath()
{
	Command cmd;
	cmd.name = "GetFootagePath";

	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}

void FootageItem::replaceWithNewSource(std::string name, std::string path)
{
	Command cmd;
	cmd.name = "ReplaceFootage";

	cmd.args.push_back(name);
	cmd.args.push_back(path);
	cmd.sessionID = this->sessionID;

		auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
throw std::runtime_error("Error in replacing footage:" + resp.error);
	}
}

std::shared_ptr<SolidItem> SolidItem::createNew(std::string name, std::tuple<float, float> dimensions, std::tuple<float, float, float, float> rgba, float duration, int index)
{
	try {
	Command cmd;
	cmd.sessionID = createUUID();
	cmd.name = "CreateSolidItem";
	cmd.args.push_back(name);
	cmd.args.push_back(std::get<0>(dimensions));
	cmd.args.push_back(std::get<1>(dimensions));
	cmd.args.push_back(std::get<0>(rgba));
	cmd.args.push_back(std::get<1>(rgba));
	cmd.args.push_back(std::get<2>(rgba));
	cmd.args.push_back(std::get<3>(rgba));
	cmd.args.push_back(duration);
	cmd.args.push_back(index);

	auto& mqm = MessageQueueManager::getInstance();
	mqm.sendCommand(cmd);

	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	std::string solidHandle = boost::get<std::string>(resp.args[0]);
	std::shared_ptr<SolidItem> solidItem = std::make_shared<SolidItem>(solidHandle);
	return solidItem;
} catch (boost::bad_get& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in creating solid:" + std::string(e.what()));
}
catch (std::exception& e) {
	std::cout << e.what() << std::endl;
	throw std::runtime_error("Error in creating solid:" + std::string(e.what()));
}
}

std::shared_ptr<AdjustmentLayer> AdjustmentLayer::createNew(std::shared_ptr<CompItem> compH, std::string name)
{
	return std::shared_ptr<AdjustmentLayer>();
}
