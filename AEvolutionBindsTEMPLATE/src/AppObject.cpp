#include "pch.h"
#include "AppObject.h"
#include "ProjectObject.h"

wProject wApp::getProject()
{
    CommandH cmd = boost::make_shared<GetProjectByIndexCmd>(0);
    auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
    auto resp = boost::dynamic_pointer_cast<GetProjectByIndexResp>(response);
    if (resp->error != "A_Err_NONE") {
        throw std::runtime_error("Error getting project: " + resp->error);
    }
    return wProject(resp->project);
}

wProject wApp::newProject()
{
	CommandH cmd = boost::make_shared<NewProjectCmd>();
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<NewProjectResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error creating new project: " + resp->error);
	}
	return wProject(resp->new_project);
}

wProject wApp::openFromPath(const std::string& path)
{
	CommandH cmd = boost::make_shared<OpenProjectFromPathCmd>(path);
	auto response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<OpenProjectFromPathResp>(response);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error opening project from path: " + resp->error);
	}
	return wProject(resp->project);
}

void wApp::reportInfo(const std::string& info)
{
    CommandH cmd = boost::make_shared<ReportInfoUnicodeCmd>(info);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
    if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error reporting info: " + resp->error);
	}
}

void wApp::writeToOSConsole(const std::string& text)
{
	CommandH cmd = boost::make_shared<WriteToOSConsoleCmd>(text);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
    if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error writing to OS console: " + resp->error);
	}
}

void wApp::writeToDebugLog(const std::string& subsystem, const std::string& eventType, const std::string& info)
{
    CommandH cmd = boost::make_shared<WriteToDebugLogCmd>(subsystem, eventType, info);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
    if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error writing to debug log: " + resp->error);
	}
}

std::tuple<A_long, A_long> wApp::driverSpecVersion()
{
    CommandH cmd = boost::make_shared<GetDriverSpecVersionCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<GetDriverSpecVersionResp>(resp);
    if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting driver spec version: " + response->error);
	}
	return std::make_tuple(response->major_version, response->minor_version);
}

std::string wApp::getPluginPaths(AEGP_GetPathTypes pathType)
{
    CommandH cmd = boost::make_shared<GetPluginPathsCmd>(pathType);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<GetPluginPathsResp>(resp);
    if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting plugin paths: " + response->error);
	}
    return response->path;
}

A_Boolean wApp::getSuppressInteractiveUI()
{
    CommandH cmd = boost::make_shared<GetSuppressInteractiveUICmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<GetSuppressInteractiveUIResp>(resp);
    if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting suppress interactive UI: " + response->error);
	}
	return response->ui_is_suppressed;
}

void wApp::startQuietErrors()
{
	CommandH cmd = boost::make_shared<StartQuietErrorsCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error starting quiet errors: " + resp->error);
	}
}

void wApp::endQuietErrors(bool reportQuietedErrors)
{
	CommandH cmd = boost::make_shared<EndQuietErrorsCmd>(reportQuietedErrors);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error ending quiet errors: " + resp->error);
	}
}

void wApp::startUndoGroup(const std::string& undoName)
{
	CommandH cmd = boost::make_shared<StartUndoGroupCmd>(undoName);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error starting undo group: " + resp->error);
	}
}

void wApp::endUndoGroup()
{
	CommandH cmd = boost::make_shared<EndUndoGroupCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error ending undo group: " + resp->error);
	}
}

void wApp::showHideAllFloaters(bool includeToolPal)
{
	CommandH cmd = boost::make_shared<ShowHideAllFloatersCmd>(includeToolPal);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error showing/hiding all floaters: " + resp->error);
	}
}

void wApp::updateFontList()
{
	CommandH cmd = boost::make_shared<UpdateFontListCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error updating font list: " + resp->error);
	}
}

AEGP_ColorVal wApp::paintPalGetForeColor()
{
	CommandH cmd = boost::make_shared<PaintPalGetForeColorCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<PaintPalGetForeColorResp>(resp);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting paint palette foreground color: " + response->error);
	}
	return response->fore_color;
}

void wApp::paintPalSetForeColor(AEGP_ColorVal foreColor)
{
	CommandH cmd = boost::make_shared<PaintPalSetForeColorCmd>(foreColor);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error setting paint palette foreground color: " + resp->error);
	}
}

AEGP_ColorVal wApp::paintPalGetBackColor()
{
	CommandH cmd = boost::make_shared<PaintPalGetBackColorCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<PaintPalGetBackColorResp>(resp);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting paint palette background color: " + response->error);
	}
	return response->back_color;
}

void wApp::paintPalSetBackColor(AEGP_ColorVal backColor)
{
	CommandH cmd = boost::make_shared<PaintPalSetBackColorCmd>(backColor);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error setting paint palette background color: " + resp->error);
	}
}

AEGP_ColorVal wApp::charPalGetFillColor(bool is_swatch)
{
	CommandH cmd = boost::make_shared<CharPalGetFillColorCmd>(is_swatch);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<CharPalGetFillColorResp>(resp);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting character palette fill color: " + response->error);
	}
	return response->fill_color;
}

void wApp::charPalSetFillColor(AEGP_ColorVal fillColor)
{
	CommandH cmd = boost::make_shared<CharPalSetFillColorCmd>(fillColor);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error setting character palette fill color: " + resp->error);
	}
}

AEGP_ColorVal wApp::charPalGetStrokeColor(bool is_defined)
{
	CommandH cmd = boost::make_shared<CharPalGetStrokeColorCmd>(is_defined);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<CharPalGetStrokeColorResp>(resp);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error getting character palette stroke color: " + response->error);
	}
	return response->stroke_color;
}

void wApp::charPalSetStrokeColor(AEGP_ColorVal strokeColor)
{
	CommandH cmd = boost::make_shared<CharPalSetStrokeColorCmd>(strokeColor);
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error("Error setting character palette stroke color: " + resp->error);
	}
}

bool wApp::charPalIsFillColorUIFrontmost()
{
	CommandH cmd = boost::make_shared<CharPalIsFillColorUIFrontmostCmd>();
	auto resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto response = boost::dynamic_pointer_cast<CharPalIsFillColorUIFrontmostResp>(resp);
	if (response->error != "A_Err_NONE") {
		throw std::runtime_error("Error checking if character palette fill color UI is frontmost: " + response->error);
	}
	return response->is_fcolor_selected;
}
