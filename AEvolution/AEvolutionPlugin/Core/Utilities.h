#pragma once
#include "..\CoreSDK\Core.h"

#include "..\CoreSDK\UtilitySuites.h"


Result<void>ReportInfo(std::string info);

Result<void> StartUndoGroup(std::string undo_name);

Result<void> EndUndoGroup();

Result<std::string> getPluginPaths();