#include "App.h"

Project App::getProject() {
	return this->project;
}


void App::beginUndoGroup(std::string undoName) {
	auto& message = enqueueSyncTask(StartUndoGroup, undoName);
	message->wait();

	Result<void> result = message->getResult();
}

void App::endUndoGroup() {
	auto& message = enqueueSyncTask(EndUndoGroup);
	message->wait();

	Result<void> result = message->getResult();
}

void App::executeCommand(int commandId)
{
	auto& message = enqueueSyncTask(ExecuteCommand, commandId);
	message->wait();

	Result<void> result = message->getResult();
}

void App::reportInfo(std::string info) { //should modify to accept string, int, float, etc.
	auto& message = enqueueSyncTask(ReportInfo, info);
	message->wait();

	Result<void> result = message->getResult();
}

std::string App::pluginPaths()
{
	auto& message = enqueueSyncTask(getPluginPaths);
	message->wait();

	Result<std::string> result = message->getResult();

	std::string resultString = result.value;
	return resultString;
}
