#include "../pch.h"
#include "Projects.h"

ProjectH getProject()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetProject", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		ProjectH projH = *boost::get<boost::shared_ptr<ProjectH>>(resp.args[0]);
		return projH;
	}
	catch (std::exception& e) {
		std::cerr << "Error in getProject: " << e.what() << std::endl;
		throw std::runtime_error("Error in getProject: " + std::string(e.what()));
	}
}

void ExecuteCommand(int commandId)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "ExecuteCommand", CommandArgs{ commandId }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in ExecuteCommand: " << e.what() << std::endl;
		throw std::runtime_error("Error in ExecuteCommand: " + std::string(e.what()));
	}
}

std::string GetProjectName(ProjectH projH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetProjectName", CommandArgs{ boost::make_shared<ProjectH>(projH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		std::string projName = boost::get<std::string>(resp.args[0]); // Extract the project name from the response
		return projName;
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetProjectName: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetProjectName: " + std::string(e.what()));
	}
}

std::string GetProjectPath(ProjectH projH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetProjectPath", CommandArgs{ boost::make_shared<ProjectH>(projH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		std::string projPath = boost::get<std::string>(resp.args[0]); // Extract the project path from the response
		return projPath;
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetProjectPath: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetProjectPath: " + std::string(e.what()));
	}
}

void SaveProjectToPath(ProjectH projH, const std::string& path)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SaveProjectToPath", CommandArgs{ boost::make_shared<ProjectH>(projH), path }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SaveProjectToPath: " << e.what() << std::endl;
		throw std::runtime_error("Error in SaveProjectToPath: " + std::string(e.what()));
	}
}

bool IsProjectDirty(ProjectH projH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "IsProjectDirty", CommandArgs{ boost::make_shared<ProjectH>(projH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		bool isDirty = boost::get<bool>(resp.args[0]); // Extract the project dirty status from the response
		return isDirty;
	}
	catch (std::exception& e) {
		std::cerr << "Error in IsProjectDirty: " << e.what() << std::endl;
		throw std::runtime_error("Error in IsProjectDirty: " + std::string(e.what()));
	}
}

void SaveProjectAs(ProjectH projH, const std::string& path)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SaveProjectAs", CommandArgs{ boost::make_shared<ProjectH>(projH), path }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SaveProjectAs: " << e.what() << std::endl;
		throw std::runtime_error("Error in SaveProjectAs: " + std::string(e.what()));
	}
}

ProjectH NewProject()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "NewProject", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		ProjectH projH = *boost::get<boost::shared_ptr<ProjectH>>(resp.args[0]);
		return projH;
	}
	catch (std::exception& e) {
		std::cerr << "Error in NewProject: " << e.what() << std::endl;
		throw std::runtime_error("Error in NewProject: " + std::string(e.what()));
	}
}

ProjectH OpenProjectFromPath(const std::string& path)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "OpenProjectFromPath", CommandArgs{ path }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		ProjectH projH = *boost::get<boost::shared_ptr<ProjectH>>(resp.args[0]);
		return projH;
	}
	catch (std::exception& e) {
		std::cerr << "Error in OpenProjectFromPath: " << e.what() << std::endl;
		throw std::runtime_error("Error in OpenProjectFromPath: " + std::string(e.what()));
	}
}

std::string GetProjectBitDepth(ProjectH projH)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetProjectBitDepth", CommandArgs{ boost::make_shared<ProjectH>(projH) }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		std::string bitDepth = boost::get<std::string>(resp.args[0]); // Extract the project bit depth from the response
		return bitDepth;
	}
	catch (std::exception& e) {
		std::cerr << "Error in GetProjectBitDepth: " << e.what() << std::endl;
		throw std::runtime_error("Error in GetProjectBitDepth: " + std::string(e.what()));
	}
}

void SetProjectBitDepth(ProjectH projH, std::string bit_depth)
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "SetProjectBitDepth", CommandArgs{ boost::make_shared<ProjectH>(projH), bit_depth }); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error in SetProjectBitDepth: " << e.what() << std::endl;
		throw std::runtime_error("Error in SetProjectBitDepth: " + std::string(e.what()));
	}
}

ItemH getProjectRootFolder()
{
	auto& mqm = MessageQueueManager::getInstance();
	try {
		Command cmd(createUUID(), "GetProjectRootFolder", CommandArgs{}); // Command to be sent to the server
		mqm.sendCommand(cmd);

		Response resp = mqm.waitForResponse();
		if (resp.error != "") {
			throw std::runtime_error("Error in Response:" + resp.error); // Throw an error if the response contains an error (Propogated from the server)
		}
		ItemH itemH = *boost::get<boost::shared_ptr<ItemH>>(resp.args[0]);
		return itemH;
	}
	catch (std::exception& e) {
		std::cerr << "Error in getProjectRootFolder: " << e.what() << std::endl;
		throw std::runtime_error("Error in getProjectRootFolder: " + std::string(e.what()));
	}
}
