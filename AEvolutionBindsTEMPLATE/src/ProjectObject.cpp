#include "pch.h"
#include "ProjectObject.h"
#include "ItemObjects.h"

wProject::wProject()
{
	CommandH cmd = boost::make_shared<GetProjectByIndexCmd>(0);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<GetProjectByIndexResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting project: " + resp->error);
	}
	project = resp->project;
}

wProject::wProject(const std::string& path)
{
	CommandH cmd = boost::make_shared<NewProjectCmd>();
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<NewProjectResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error creating new project: " + resp->error);
	}
	project = resp->new_project;
	CommandH cmd2 = boost::make_shared<SaveProjectAsCmd>(project, path);
	auto response2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	if (response2->error != "A_Err_NONE") {
		throw std::runtime_error("Error saving project to path: " + resp->error);
	}
}

std::string wProject::projectName()
{
	CommandH cmd = boost::make_shared<GetProjectNameCmd>(project);
    auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getProjectNameResponse = boost::dynamic_pointer_cast<GetProjectNameResp>(response);
	if (getProjectNameResponse->error != "A_Err_None") {
		throw std::runtime_error(getProjectNameResponse->error);
	}
	return getProjectNameResponse->name;
}

std::string wProject::projectPath()
{
	CommandH cmd = boost::make_shared<GetProjectPathCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getProjectPathResponse = boost::dynamic_pointer_cast<GetProjectPathResp>(response);
	if (getProjectPathResponse->error != "A_Err_None") {
		throw std::runtime_error(getProjectPathResponse->error);
	}
	return getProjectPathResponse->path;
}

std::unique_ptr<wItem> wProject::activeItem()
{
	CommandH cmd = boost::make_shared<GetActiveItemCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getActiveItemResponse = boost::dynamic_pointer_cast<GetActiveItemResp>(response);
	if (getActiveItemResponse->error != "A_Err_None") {
		throw std::runtime_error(getActiveItemResponse->error);
	}
	auto item = getActiveItemResponse->itemH;

	//get the type of the item
	CommandH cmd2 = boost::make_shared<GetItemTypeCmd>(item);
	auto response2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	auto getItemTypeResponse = boost::dynamic_pointer_cast<GetItemTypeResp>(response2);
	if (getItemTypeResponse->error != "A_Err_None") {
		throw std::runtime_error(getItemTypeResponse->error);
	}
	AEGP_ItemType itemType = getItemTypeResponse->item_type;
	switch (itemType) {
		case AEGP_ItemType::AEGP_ItemType_COMP:
			return std::make_unique<wComp>(item);
		case AEGP_ItemType::AEGP_ItemType_FOLDER:
			return std::make_unique<wFolder>(item);
		case AEGP_ItemType::AEGP_ItemType_FOOTAGE:
			return std::make_unique<wFootage>(item);
		default:
			return std::make_unique<wItem>(item);
	}
}

wFolder wProject::rootFolder()
{
	CommandH cmd = boost::make_shared<GetProjectRootFolderCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getProjectRootFolderResponse = boost::dynamic_pointer_cast<GetProjectRootFolderResp>(response);
	if (getProjectRootFolderResponse->error != "A_Err_None") {
		throw std::runtime_error(getProjectRootFolderResponse->error);
	}
	return wFolder(getProjectRootFolderResponse->root_folder);
}

void wProject::saveToPath(const std::string& path)
{
	CommandH cmd = boost::make_shared<SaveProjectToPathCmd>(project, path);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_None") {
		throw std::runtime_error(response->error);
	}
}

void wProject::saveAs(const std::string& path)
{
	CommandH cmd = boost::make_shared<SaveProjectAsCmd>(project, path);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_None") {
		throw std::runtime_error(response->error);
	}
}

AEGP_TimeDisplay3 wProject::timeDisplay()
{
	CommandH cmd = boost::make_shared<GetProjectTimeDisplayCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getProjectTimeDisplayResponse = boost::dynamic_pointer_cast<GetProjectTimeDisplayResp>(response);
	if (getProjectTimeDisplayResponse->error != "A_Err_None") {
		throw std::runtime_error(getProjectTimeDisplayResponse->error);
	}
	return getProjectTimeDisplayResponse->time_display;
}

void wProject::setTimeDisplay(AEGP_TimeDisplay3 time_display)
{
	CommandH cmd = boost::make_shared<SetProjectTimeDisplayCmd>(project, time_display);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_None") {
		throw std::runtime_error(response->error);
	}
}

AEGP_ProjBitDepth wProject::bitDepth()
{
	CommandH cmd = boost::make_shared<GetProjectBitDepthCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto getProjectBitDepthResponse = boost::dynamic_pointer_cast<GetProjectBitDepthResp>(response);
	if (getProjectBitDepthResponse->error != "A_Err_None") {
		throw std::runtime_error(getProjectBitDepthResponse->error);
	}
	return getProjectBitDepthResponse->bit_depth;
}

void wProject::setBitDepth(AEGP_ProjBitDepth bit_depth)
{
	CommandH cmd = boost::make_shared<SetProjectBitDepthCmd>(project, bit_depth);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (response->error != "A_Err_None") {
		throw std::runtime_error(response->error);
	}
}

bool wProject::isDirty()
{
	CommandH cmd = boost::make_shared<ProjectIsDirtyCmd>(project);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto projectIsDirtyResponse = boost::dynamic_pointer_cast<ProjectIsDirtyResp>(response);
	if (projectIsDirtyResponse->error != "A_Err_None") {
		throw std::runtime_error(projectIsDirtyResponse->error);
	}
	return projectIsDirtyResponse->is_dirtyB;
}
