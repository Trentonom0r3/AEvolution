#pragma once
#include "include/Core.h"
#include "include/MessageQueue.h"

AEvolution_API void ReportInfo(std::string info);

AEvolution_API void StartUndoGroup(std::string undo_name);

AEvolution_API void EndUndoGroup();

AEvolution_API std::string GetPluginPaths();