#include "pch.h"
#include "Comps.h"

/*
* BACKGROUND:
* ------------
* To Summarize, the custom structs/classes you see here are all defined in 'Core.h'
* 
* In Particular, this file makes use of:
* 
* - CompH: A handle to a composition-- Really, its just a string that uniquely identifies a composition, but this helps keep
* things clear and organized.The actual object is mapped by sessionID in After Effects.
* 
* - ItemH: A handle to an item-- Really, its just a string that uniquely identifies an item, but this helps keep things clear
* and organized. The actual object is mapped by sessionID in After Effects.
* 
* - Command: A struct that represents a command to be sent to the server. It contains a sessionID, a name, and a vector of
* CommandArgs. CommandArgs is a variant type that can hold a variety of types, including shared pointers to the handles
* defined above.
* 
* - Response: A struct that represents a response to be sent to the client. It contains a sessionID, a vector of CommandArgs, and
* an error string. CommandArgs is a variant type that can hold a variety of types, including shared pointers to the handles
* defined above.
* 
* - MessageQueueManager: A class that manages the message queue. It contains a sendCommand method and a tryReceiveResponse
* method. The sendCommand method sends a command to the server, and the tryReceiveResponse method tries to receive a response
* from the server. If a response is received, it is stored in the response parameter and the method returns true. If no response
* is received, the method returns false.
* 
*- colorH: a struct representing RGBA color values, floating point [0,1]
*/
CompH addComp(const std::string& name, dimensionsH dimensions, float frameRate, float duration, float pixelAspectRatio, ItemH parentFolder)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "addComp", CommandArgs{ name, dimensions, frameRate, duration, pixelAspectRatio, boost::make_shared<ItemH>(parentFolder) });
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(resp.args[0]);
		return comp;
	}
	catch (std::exception& e) {
		std::cerr << "Error in addComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in addComp: " + std::string(e.what()));
	}
}

CompH GetCompFromItem(ItemH itemH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetCompFromItem", CommandArgs{ boost::make_shared<ItemH>(itemH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(resp.args[0]); // Extract the CompH from the response
		return comp; // Return the CompH
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetCompFromItem: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetCompFromItem: " + std::string(e.what()));
	}
}

ItemH GetItemFromComp(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetItemFromComp", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]); // Extract the ItemH from the response
		return item; // Return the ItemH
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetItemFromComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetItemFromComp: " + std::string(e.what()));
	}
}

std::pair<int, int> GetCompDownsampleFactor(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetCompDownsampleFactor", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		std::pair<int, int> factor = std::make_pair(boost::get<int>(resp.args[0]), boost::get<int>(resp.args[1])); // Extract the downsample factor from the response
		return factor; // Return the downsample factor
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetCompDownsampleFactor: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetCompDownsampleFactor: " + std::string(e.what()));
	}
}

void SetCompDownsampleFactor(CompH compH, std::pair<int, int> factor)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetCompDownsampleFactor", CommandArgs{ boost::make_shared<CompH>(compH), factor.first, factor.second }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SetCompDownsampleFactor: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetCompDownsampleFactor: " + std::string(e.what()));
	}
}

colorH GetCompBGColor(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetCompBGColor", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		colorH color = boost::get<colorH>(resp.args[0]); // Extract the color from the response
		return color; // Return the color
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetCompBGColor: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetCompBGColor: " + std::string(e.what()));
	}
}

void SetCompBGColor(CompH compH, colorH color)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetCompBGColor", CommandArgs{ boost::make_shared<CompH>(compH), color }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SetCompBGColor: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetCompBGColor: " + std::string(e.what()));
	}
}

float getCompFlags(CompH compH)
{
	return 0.0f;
}

bool getShowLayerNameOrSourceName(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getShowLayerNameOrSourceName", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in getShowLayerNameOrSourceName: " << e.what() << std::endl;
		throw std::runtime_error("Error in getShowLayerNameOrSourceName: " + std::string(e.what()));
	}
}

void setShowLayerNameOrSourceName(CompH compH, bool showLayerNames)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setShowLayerNameOrSourceName", CommandArgs{ boost::make_shared<CompH>(compH), showLayerNames }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setShowLayerNameOrSourceName: " << e.what() << std::endl;
		throw std::runtime_error("Error in setShowLayerNameOrSourceName: " + std::string(e.what()));
	}
}

bool getShowBlendModes(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getShowBlendModes", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		bool showBlendModes = boost::get<bool>(resp.args[0]); // Extract the showBlendModes from the response
		return showBlendModes; // Return the showBlendModes
	}
	catch (std::exception& e) {
		std::cerr << "Error in getShowBlendModes: " << e.what() << std::endl;
		throw std::runtime_error("Error in getShowBlendModes: " + std::string(e.what()));
	}
}

void setShowBlendModes(CompH compH, bool showBlendModes)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setShowBlendModes", CommandArgs{ boost::make_shared<CompH>(compH), showBlendModes }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setShowBlendModes: " << e.what() << std::endl;
		throw std::runtime_error("Error in setShowBlendModes: " + std::string(e.what()));
	}
}

float getCompFramerate(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompFramerate", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float framerate = boost::get<float>(resp.args[0]); // Extract the framerate from the response
		return framerate; // Return the framerate
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompFramerate: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompFramerate: " + std::string(e.what()));
	}
}

void setCompFramerate(CompH compH, float fps)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompFramerate", CommandArgs{ boost::make_shared<CompH>(compH), fps }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompFramerate: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompFramerate: " + std::string(e.what()));
	}
}

std::pair<float, float> getCompShutterAnglePhase(CompH compH)
{
	return std::pair<float, float>();
}

void setCompSuggestedMotionBlurSamples(CompH compH, int samples)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompSuggestedMotionBlurSamples", CommandArgs{ boost::make_shared<CompH>(compH), samples }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompSuggestedMotionBlurSamples: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompSuggestedMotionBlurSamples: " + std::string(e.what()));
	}
}

float getCompWorkAreaStart(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompWorkAreaStart", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float start = boost::get<float>(resp.args[0]); // Extract the start from the response
		return start; // Return the start
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompWorkAreaStart: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompWorkAreaStart: " + std::string(e.what()));
	}
}

float getCompWorkAreaDuration(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompWorkAreaDuration", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		float duration = boost::get<float>(resp.args[0]); // Extract the duration from the response
		return duration; // Return the duration
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompWorkAreaDuration: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompWorkAreaDuration: " + std::string(e.what()));
	}
}

void setCompWorkAreaStartAndDuration(CompH compH, float start, float dur)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompWorkAreaStartAndDuration", CommandArgs{ boost::make_shared<CompH>(compH), start, dur }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompWorkAreaStartAndDuration: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompWorkAreaStartAndDuration: " + std::string(e.what()));
	}
}

LayerH createSolidInComp(const std::string& name, dimensionsH dimensions, colorH color, CompH parentCompH, float dur)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "createSolidInComp", CommandArgs{ name, dimensions, color, boost::make_shared<CompH>(parentCompH), dur }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
		return layer;
	}
	catch (std::exception& e) {
		std::cerr << "Error in createSolidInComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in createSolidInComp: " + std::string(e.what()));
	}
}

LayerH createCameraInComp(const std::string& name, dimensionsH position, CompH parentCompH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		float x = position.width;
		float y = position.height;
		Command cmd(createUUID(), "createCameraInComp", CommandArgs{ name, x, y , boost::make_shared<CompH>(parentCompH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
		return layer;
	}
	catch (std::exception& e) {
		std::cerr << "Error in createCameraInComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in createCameraInComp: " + std::string(e.what()));
	}
}

LayerH createLightInComp(const std::string& name, dimensionsH position, CompH parentCompH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		float x = position.width;
		float y = position.height;
		Command cmd(createUUID(), "createLightInComp", CommandArgs{ name, x, y, boost::make_shared<CompH>(parentCompH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
		return layer;
	}
	catch (std::exception& e) {
		std::cerr << "Error in createLightInComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in createLightInComp: " + std::string(e.what()));
	}
}

float getCompDisplayStartTime(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompDisplayStartTime", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}

		float startTime = boost::get<float>(resp.args[0]); // Extract the start time from the response
		return startTime; // Return the start time
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompDisplayStartTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompDisplayStartTime: " + std::string(e.what()));
	}
}

void setCompDisplayStartTime(CompH compH, float startTimeInSeconds)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompDisplayStartTime", CommandArgs{ boost::make_shared<CompH>(compH), startTimeInSeconds }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompDisplayStartTime: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompDisplayStartTime: " + std::string(e.what()));
	}
}

void setCompDuration(CompH compH, float durationInSeconds)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompDuration", CommandArgs{ boost::make_shared<CompH>(compH), durationInSeconds }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompDuration: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompDuration: " + std::string(e.what()));
	}
}

LayerH createNullInComp(const std::string& name, CompH parentCompH, float dur)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "createNullInComp", CommandArgs{ name, boost::make_shared<CompH>(parentCompH), dur }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
		return layer;
	}
	catch (std::exception& e) {
		std::cerr << "Error in createNullInComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in createNullInComp: " + std::string(e.what()));
	}
}

void setCompPixelAspectRatio(CompH compH, float pixelAspect)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompPixelAspectRatio", CommandArgs{ boost::make_shared<CompH>(compH), pixelAspect }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompPixelAspectRatio: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompPixelAspectRatio: " + std::string(e.what()));
	}
}

CompH duplicateComp(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "duplicateComp", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(resp.args[0]);
		return comp;
	}
	catch (std::exception& e) {
		std::cerr << "Error in duplicateComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in duplicateComp: " + std::string(e.what()));
	}
}

float getCompFrameDuration(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompFrameDuration", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}

		float frameDuration = boost::get<float>(resp.args[0]); // Extract the frame duration from the response
		return frameDuration; // Return the frame duration
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompFrameDuration: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompFrameDuration: " + std::string(e.what()));
	}
}

CompH getMostRecentlyUsedComp()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getMostRecentlyUsedComp", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(resp.args[0]);
		return comp;
	}
	catch (std::exception& e) {
		std::cerr << "Error in getMostRecentlyUsedComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in getMostRecentlyUsedComp: " + std::string(e.what()));
	}
}

LayerH createVectorLayerInComp(CompH parentCompH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "createVectorLayerInComp", CommandArgs{ boost::make_shared<CompH>(parentCompH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(resp.args[0]);
		return layer;
	}
	catch (std::exception& e) {
		std::cerr << "Error in createVectorLayerInComp: " << e.what() << std::endl;
		throw std::runtime_error("Error in createVectorLayerInComp: " + std::string(e.what()));
	}
}

StreamRefH getNewCompMarkerStream(CompH parentCompH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getNewCompMarkerStream", CommandArgs{ boost::make_shared<CompH>(parentCompH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		StreamRefH stream = *boost::get<boost::shared_ptr<StreamRefH>>(resp.args[0]);
		return stream;
	}
	catch (std::exception& e) {
		std::cerr << "Error in getNewCompMarkerStream: " << e.what() << std::endl;
		throw std::runtime_error("Error in getNewCompMarkerStream: " + std::string(e.what()));
	}
}

bool getCompDisplayDropFrame(CompH compH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "getCompDisplayDropFrame", CommandArgs{ boost::make_shared<CompH>(compH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
		bool dropFrame = boost::get<bool>(resp.args[0]); // Extract the drop frame from the response
		return dropFrame; // Return the drop frame
	}
	catch (std::exception& e) {
		std::cerr << "Error in getCompDisplayDropFrame: " << e.what() << std::endl;
		throw std::runtime_error("Error in getCompDisplayDropFrame: " + std::string(e.what()));
	}
}

void setCompDisplayDropFrame(CompH compH, bool dropFrame)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "setCompDisplayDropFrame", CommandArgs{ boost::make_shared<CompH>(compH), dropFrame }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in setCompDisplayDropFrame: " << e.what() << std::endl;
		throw std::runtime_error("Error in setCompDisplayDropFrame: " + std::string(e.what()));
	}
}

void reorderCompSelection(CompH compH, int index)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "reorderCompSelection", CommandArgs{ boost::make_shared<CompH>(compH), index }); // Command to be sent to the server
		mqm.sendCommand(cmd);
		
		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in reorderCompSelection: " << e.what() << std::endl;
		throw std::runtime_error("Error in reorderCompSelection: " + std::string(e.what()));
	}
}
