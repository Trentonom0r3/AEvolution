#include "pch.h"
#include "Layers.h"

int getNumLayers(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetNumLayers");
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<int>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

int getLayerIndex(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerIndex");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<int>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

std::string getLayerName(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerName");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<std::string>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

std::string getLayerSourceName(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerSourceName");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<std::string>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void setLayerName(LayerH layerH, const std::string& name)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetLayerName");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(name);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH ActiveLayer()
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ActiveLayer");
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH getLayerFromComp(CompH compH, int index)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerFromComp");
		cmd.args.push_back(boost::make_shared<CompH>(compH));
		cmd.args.push_back(index);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void changeLayerIndex(LayerH layerH, int index)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ChangeLayerIndex");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(index);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool isAddLayerValid(ItemH itemH, CompH compH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsAddLayerValid");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(boost::make_shared<CompH>(compH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH AddLayer(ItemH itemH, CompH compH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "AddLayer");
		cmd.args.push_back(boost::make_shared<ItemH>(itemH));
		cmd.args.push_back(boost::make_shared<CompH>(compH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

ItemH getLayerSourceItem(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerSourceItem");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

int GetLayerSourceItemID(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerSourceItemID");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<int>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

CompH GetLayerParentComp(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerParentComp");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<CompH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

std::string GetLayerQuality(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerQuality");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<std::string>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void SetLayerQuality(LayerH layerH, int qualityint)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetLayerQuality");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(qualityint);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

std::vector<std::string> GetLayerFlags(LayerH layerH)
{
	return std::vector<std::string>();
}

bool IsLayerVideoReallyOn(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsLayerVideoReallyOn");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool IsLayerAudioReallyOn(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsLayerAudioReallyOn");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

float GetLayerOffset(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerOffset");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<float>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void SetLayerOffset(LayerH layerH, float offsetH, float frameRate)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetLayerOffset");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(offsetH);
		cmd.args.push_back(frameRate);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool IsLayer3D(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsLayer3D");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool IsLayer2D(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsLayer2D");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool IsLayerUsedAsTrackMatte(LayerH layerH, bool fill_must_be_active)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsLayerUsedAsTrackMatte");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(fill_must_be_active);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool DoesLayerHaveTrackMatte(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "DoesLayerHaveTrackMatte");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<bool>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

float ConvertCompToLayerTime(LayerH layerH, float comp_time)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ConvertCompToLayerTime");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(comp_time);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<float>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

float ConvertLayerToCompTime(LayerH layerH, float layer_time, float frameRate)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ConvertLayerToCompTime");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(layer_time);
		cmd.args.push_back(frameRate);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<float>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

float GetLayerDancingRandValue(LayerH layerH, float comp_time, float frameRate)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerDancingRandValue");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(comp_time);
		cmd.args.push_back(frameRate);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<float>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

int GetLayerID(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerID");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return boost::get<int>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH GetLayerFromLayerID(CompH parent_comp, int id)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerFromLayerID");
		cmd.args.push_back(boost::make_shared<CompH>(parent_comp));
		cmd.args.push_back(id);
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH GetTrackMatteLayer(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetTrackMatteLayer");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void RemoveTrackMatte(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "RemoveTrackMatte");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

void DeleteLayer(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "DeleteLayer");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH DuplicateLayer(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "DuplicateLayer");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

LayerH GetLayerParent(LayerH layerH)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetLayerParent");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}

		return *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
	}
	catch (std::exception& e) {
		throw e;
	}
}

void SetLayerParent(LayerH layerH, LayerH parent_layer)
{
auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetLayerParent");
		cmd.args.push_back(boost::make_shared<LayerH>(layerH));
		cmd.args.push_back(boost::make_shared<LayerH>(parent_layer));
		mqm.sendCommand(cmd);
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response: " + resp.error);
		}
	}
	catch (std::exception& e) {
		throw e;
	}
}
