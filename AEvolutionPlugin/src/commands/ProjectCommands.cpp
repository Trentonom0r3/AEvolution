#include "ProjectCommands.h"
#include "../MessageQueueManager.h"

// Implementation for GetNumProjectsCmd
void GetNumProjectsCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    A_long numProjects;
    ERR(suites.ProjSuite6()->AEGP_GetNumProjects(&numProjects));
    boost::shared_ptr<Response> resp = boost::make_shared<GetNumProjectsResp>(numProjects, errToString(err));
    MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectByIndexCmd
void GetProjectByIndexCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ProjectH projH;
	ERR(suites.ProjSuite6()->AEGP_GetProjectByIndex(proj_indexL, &projH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectByIndexResp>(projH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectNameCmd
void GetProjectNameCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_char nameZ[AEGP_MAX_ITEM_NAME_SIZE];
	ERR(suites.ProjSuite6()->AEGP_GetProjectName(project.handle, nameZ));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectNameResp>(std::string(nameZ), errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectPathCmd --- TODO
void GetProjectPathCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_MemHandle pathH = NULL;
	A_UTF16Char* unicode_nameP;
	ERR(suites.ProjSuite6()->AEGP_GetProjectPath(project.handle, &pathH));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(pathH, (void**)&unicode_nameP));
	std::string path = convertUTF16ToUTF8(unicode_nameP);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(pathH));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(pathH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectPathResp>(path, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectRootFolderCmd
void GetProjectRootFolderCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH rootFolderH;
	ERR(suites.ProjSuite6()->AEGP_GetProjectRootFolder(project.handle, &rootFolderH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectRootFolderResp>(rootFolderH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for SaveProjectToPathCmd
void SaveProjectToPathCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> pathH = convertUTF8ToUTF16(pathZ);
	ERR(suites.ProjSuite6()->AEGP_SaveProjectToPath(project.handle, pathH.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<SaveProjectToPathResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectTimeDisplayCmd
void GetProjectTimeDisplayCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_TimeDisplay3 timeDisplay;
	ERR(suites.ProjSuite6()->AEGP_GetProjectTimeDisplay(project.handle, &timeDisplay));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectTimeDisplayResp>(timeDisplay, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for SetProjectTimeDisplayCmd
void SetProjectTimeDisplayCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ProjSuite6()->AEGP_SetProjectTimeDisplay(project.handle, &time_display));
	boost::shared_ptr<Response> resp = boost::make_shared<SetProjectTimeDisplayResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for ProjectIsDirtyCmd
void ProjectIsDirtyCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean isDirty;
	ERR(suites.ProjSuite6()->AEGP_ProjectIsDirty(project.handle, &isDirty));
	boost::shared_ptr<Response> resp = boost::make_shared<ProjectIsDirtyResp>(isDirty, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for SaveProjectAsCmd
void SaveProjectAsCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> pathH = convertUTF8ToUTF16(pathZ);
	ERR(suites.ProjSuite6()->AEGP_SaveProjectAs(project.handle, pathH.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<SaveProjectAsResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for NewProjectCmd
void NewProjectCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ProjectH newProjectH;
	ERR(suites.ProjSuite6()->AEGP_NewProject(&newProjectH));
	boost::shared_ptr<Response> resp = boost::make_shared<NewProjectResp>(newProjectH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for OpenProjectFromPathCmd
void OpenProjectFromPathCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> pathH = convertUTF8ToUTF16(pathZ);
	AEGP_ProjectH projectH;
	ERR(suites.ProjSuite6()->AEGP_OpenProjectFromPath(pathH.data(), &projectH));
	boost::shared_ptr<Response> resp = boost::make_shared<OpenProjectFromPathResp>(projectH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProjectBitDepthCmd
void GetProjectBitDepthCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ProjBitDepth bitDepth;
	ERR(suites.ProjSuite6()->AEGP_GetProjectBitDepth(project.handle, &bitDepth));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProjectBitDepthResp>(bitDepth, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for SetProjectBitDepthCmd
void SetProjectBitDepthCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ProjSuite6()->AEGP_SetProjectBitDepth(project.handle, bit_depth));
	boost::shared_ptr<Response> resp = boost::make_shared<SetProjectBitDepthResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}
