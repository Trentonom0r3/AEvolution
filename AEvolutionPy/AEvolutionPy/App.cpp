#include "pch.h"
#include "App.h"
#include "Project.h"

void App::reportInfo(std::string info) {
	ReportInfo(info);
}

std::string App::path() {
	std::string path = GetPluginPaths();
	return path;
}

Project App::getProject()
{
	return Project();
}
