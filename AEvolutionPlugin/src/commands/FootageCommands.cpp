#include "FootageCommands.h"
#include "../MessageQueueManager.h"

// Implementation for GetMainFootageFromItemCmd
void GetMainFootageFromItemCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    AEGP_FootageH mainFootage;
    ERR(suites.FootageSuite5()->AEGP_GetMainFootageFromItem(item.handle, &mainFootage));
    boost::shared_ptr<Response> resp = boost::make_shared<GetMainFootageFromItemResp>(mainFootage, errToString(err));
    MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetProxyFootageFromItemCmd
void GetProxyFootageFromItemCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_FootageH proxyFootage;
	ERR(suites.FootageSuite5()->AEGP_GetProxyFootageFromItem(item.handle, &proxyFootage));
	boost::shared_ptr<Response> resp = boost::make_shared<GetProxyFootageFromItemResp>(proxyFootage, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetFootageNumFilesCmd
void GetFootageNumFilesCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long numFiles;
    A_long numFilesPerFrame;
	ERR(suites.FootageSuite5()->AEGP_GetFootageNumFiles(footage.handle, &numFiles, &numFilesPerFrame));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootageNumFilesResp>(numFiles, numFilesPerFrame, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetFootagePathCmd
void GetFootagePathCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_MemHandle pathH = NULL;
	A_UTF16Char* unicode_nameP;
	ERR(suites.FootageSuite5()->AEGP_GetFootagePath(footage.handle, frame_num, file_index, &pathH));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(pathH, (void**)&unicode_nameP));
	std::string path = convertUTF16ToUTF8(unicode_nameP);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(pathH));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(pathH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootagePathResp>(frame_num, file_index, path, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for GetFootageSignatureCmd
void GetFootageSignatureCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    AEGP_FootageSignature signature;
    ERR(suites.FootageSuite5()->AEGP_GetFootageSignature(footage.handle, &signature));
    boost::shared_ptr<Response> resp = boost::make_shared<GetFootageSignatureResp>(signature, errToString(err));
    MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for NewFootageCmd --used for image sequences and stills
void NewSequenceCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
    AEGP_FootageH newFootage;
    std::vector<A_UTF16Char> pathZ = convertUTF8ToUTF16(path);
    ERR(suites.FootageSuite5()->AEGP_NewFootage(*pluginID, pathZ.data(), &layer_info, &sequence_options, interp_style, NULL, &newFootage));
	boost::shared_ptr<Response> resp = boost::make_shared<NewFootageResp>(newFootage, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for NewFootageCmd --used for videos and audio files
void NewFootageCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
	AEGP_FootageH newFootage;
	std::vector<A_UTF16Char> pathZ = convertUTF8ToUTF16(path);
	ERR(suites.FootageSuite5()->AEGP_NewFootage(*pluginID, pathZ.data(), NULL, NULL, interp_style, NULL, &newFootage));
	boost::shared_ptr<Response> resp = boost::make_shared<NewFootageResp>(newFootage, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for AddFootageToProjectCmd
void AddFootageToProjectCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    AEGP_ItemH footageItem;
    ERR(suites.FootageSuite5()->AEGP_AddFootageToProject(footage.handle, folder.handle, &footageItem));
    boost::shared_ptr<Response> resp = boost::make_shared<AddFootageToProjectResp>(footageItem, errToString(err));
    MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for SetItemProxyFootageCmd
void SetItemProxyFootageCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    ERR(suites.FootageSuite5()->AEGP_SetItemProxyFootage(footage.handle, item.handle));
    boost::shared_ptr<Response> resp = boost::make_shared<SetItemProxyFootageResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for ReplaceItemMainFootageCmd
void ReplaceItemMainFootageCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    ERR(suites.FootageSuite5()->AEGP_ReplaceItemMainFootage(footage.handle, item.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<ReplaceItemMainFootageResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

// Implementation for DisposeFootageCmd
void DisposeFootageCmd::execute() {
    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.FootageSuite5()->AEGP_DisposeFootage(footage.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<DisposeFootageResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetFootageInterpretationCmd::execute() {
AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    AEGP_FootageInterp interpH;
	ERR(suites.FootageSuite5()->AEGP_GetFootageInterpretation(item.handle, proxy, &interpH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootageInterpretationResp>(interpH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetFootageInterpretationCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.FootageSuite5()->AEGP_SetFootageInterpretation(item.handle, proxy, &interp));
	boost::shared_ptr<Response> resp = boost::make_shared<SetFootageInterpretationResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetFootageLayerKeyCmd::execute() {
AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_FootageLayerKey layerKey;
	ERR(suites.FootageSuite5()->AEGP_GetFootageLayerKey(footage.handle, &layerKey));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootageLayerKeyResp>(layerKey, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void NewPlaceholderFootageWithPathCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
	AEGP_FootageH newFootage;
	std::vector<A_UTF16Char> pathZ = convertUTF8ToUTF16(path);
	ERR(suites.FootageSuite5()->AEGP_NewPlaceholderFootageWithPath(*pluginID, pathZ.data(), path_platform, file_type, width, height, &duration, &newFootage));
	boost::shared_ptr<Response> resp = boost::make_shared<NewPlaceholderFootageWithPathResp>(newFootage, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void NewSolidFootageCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_FootageH newFootage;
	ERR(suites.FootageSuite5()->AEGP_NewSolidFootage(name.c_str(), width, height, &color, &newFootage));
	boost::shared_ptr<Response> resp = boost::make_shared<NewSolidFootageResp>(newFootage, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetSolidFootageColorCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal color;
	ERR(suites.FootageSuite5()->AEGP_GetSolidFootageColor(item.handle, proxy, &color));
	boost::shared_ptr<Response> resp = boost::make_shared<GetSolidFootageColorResp>(color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetSolidFootageColorCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.FootageSuite5()->AEGP_SetSolidFootageColor(item.handle, proxy, &color));
	boost::shared_ptr<Response> resp = boost::make_shared<SetSolidFootageColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetSolidFootageDimensionsCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.FootageSuite5()->AEGP_SetSolidFootageDimensions(item.handle, proxy, width, height));
	boost::shared_ptr<Response> resp = boost::make_shared<SetSolidFootageDimensionsResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetFootageSoundDataFormatCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_SoundDataFormat format;
	ERR(suites.FootageSuite5()->AEGP_GetFootageSoundDataFormat(footage.handle, &format));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootageSoundDataFormatResp>(format, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetFootageSequenceImportOptionsCmd::execute() {
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_FileSequenceImportOptions options;
	ERR(suites.FootageSuite5()->AEGP_GetFootageSequenceImportOptions(footage.handle, &options));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFootageSequenceImportOptionsResp>(options, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}




