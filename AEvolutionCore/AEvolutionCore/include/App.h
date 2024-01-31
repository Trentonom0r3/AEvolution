#pragma once
#include "MessageQueue.h"
#include "Project.h"


class AEvolution_API App {
public:
    App() : sessionID(createUUID()) {}  // Default constructor
    Project getProject();

    void beginUndoGroup(std::string undo_name = "Default Undo Group Name");
    void endUndoGroup();
    void executeCommand(int commandId);
    void reportInfo(std::string info);
    std::string pluginPaths();

private:
    std::string sessionID;
};
