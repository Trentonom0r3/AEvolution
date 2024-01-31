#include "pch.h"
#include "include/App.h"

Project App::getProject()
{
	try {
		Command cmd;
		std::string sessionID = createUUID(); // Generate a new session ID for the Project
		cmd.sessionID = sessionID;
		cmd.name = "getProject";
		cmd.args.push_back(sessionID);

		auto& mqm = MessageQueueManager::getInstance();
		mqm.sendCommand(cmd);

		Response resp;
		while (!mqm.tryReceiveResponse(resp)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		if (resp.error != "") {
			throw std::runtime_error("Error getting project: " + resp.error);
		}
		std::string ID = resp.sessionID;

		std::string projectID = boost::get<std::string>(resp.args[0]);
		Project project(projectID);
		return project;
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		throw std::runtime_error("Error getting project + " + std::string(e.what()));
	}
}


void App::reportInfo(std::string info) { //should modify to accept string, int, float, etc.
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "reportInfo";
	cmd.args.push_back(info);

	// Send the Command
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error reporting info: " + resp.error);
	}
}

void App::beginUndoGroup(std::string undoName) {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "beginUndoGroup";
	cmd.args.push_back(undoName);

	// Send the Command
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error beginning undo group: " + resp.error);
	}
}

void App::endUndoGroup() {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "endUndoGroup";

	// Send the Command
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error ending undo group: " + resp.error);
	}
}

void App::executeCommand(int commandId) {
		auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "executeCommand";
	cmd.args.push_back(commandId);

	// Send the Command
	mqm.sendCommand(cmd);
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error executing command: " + resp.error);
	}
}

std::string App::pluginPaths() {
	auto& mqm = MessageQueueManager::getInstance();

	// Construct a Command
	Command cmd;
	cmd.sessionID = this->sessionID;
	cmd.name = "getPluginPaths";
	cmd.args.push_back(this->sessionID);
	// Send the Command
	mqm.sendCommand(cmd);

	// Receive the Response
	Response resp;
	while (!mqm.tryReceiveResponse(resp)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (resp.error != "") {
		throw std::runtime_error("Error getting plugin paths: " + resp.error);
	}
	std::string ID = resp.sessionID;

	// Return the result
	std::string output = boost::get<std::string>(resp.args[0]);
	return output;
}