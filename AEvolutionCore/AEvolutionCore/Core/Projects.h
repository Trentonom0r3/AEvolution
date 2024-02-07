#pragma once
#include "../include/Core.h"
#include "../include/MessageQueue.h"

AEvolution_API ProjectH getProject();

AEvolution_API void ExecuteCommand(int commandId);

AEvolution_API std::string GetProjectName( ProjectH projH);

AEvolution_API std::string GetProjectPath( ProjectH projH);

AEvolution_API void SaveProjectToPath( ProjectH projH, const std::string& path);

//Result<AEGP_TimeDisplay3> GetProjectTimeDisplay(AEvolution_API ProjectH projH);

//AEvolution_API void SetProjectTimeDisplay2(ProjectH projH);

AEvolution_API bool IsProjectDirty( ProjectH projH);

AEvolution_API void SaveProjectAs( ProjectH projH, const std::string& path);

AEvolution_API ProjectH NewProject();

AEvolution_API ProjectH OpenProjectFromPath(const std::string& path);

AEvolution_API std::string GetProjectBitDepth( ProjectH projH);

AEvolution_API void SetProjectBitDepth( ProjectH projH, std::string bit_depth);

ItemH getProjectRootFolder();
