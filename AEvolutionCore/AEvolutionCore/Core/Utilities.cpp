#include "../pch.h"
#include "Utilities.h"

void ReportInfo(std::string info)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ReportInfo", CommandArgs{ info }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in ReportInfo: " << e.what() << std::endl;
		throw std::runtime_error("Error in ReportInfo: " + std::string(e.what()));
	}
}

void StartUndoGroup(std::string undo_name)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "StartUndoGroup", CommandArgs{ undo_name }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in StartUndoGroup: " << e.what() << std::endl;
		throw std::runtime_error("Error in StartUndoGroup: " + std::string(e.what()));
	}
}

void EndUndoGroup()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "EndUndoGroup", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in EndUndoGroup: " << e.what() << std::endl;
		throw std::runtime_error("Error in EndUndoGroup: " + std::string(e.what()));
	}
}

std::string GetPluginPaths()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetPluginPaths", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}

		std::string pluginPaths = boost::get<std::string>(resp.args[0]); // Extract the plugin paths from the response
		return pluginPaths; // Return the plugin paths
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetPluginPaths: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetPluginPaths: " + std::string(e.what()));
	}
}
