#pragma once
#include "../CoreSDK/TaskUtils.h"
#include "../CoreSDK/Utils.h"
#include "Project.h"


class App {
public:
	App() {
		project = Project();
	}
    Project getProject();

    Project project;

    void beginUndoGroup(std::string undo_name = "Default Undo Group Name");
    void endUndoGroup();
    void executeCommand(int commandId);
    void reportInfo(std::string info);
    std::string pluginPaths();

};
