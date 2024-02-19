#include "UtilityCommands.h"
#include "../MessageQueueManager.h"

void ReportInfoUnicodeCmd::execute()
{
	std::vector<A_UTF16Char> info = convertUTF8ToUTF16(info_string);
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID *pluginID = SuiteManager::GetInstance().GetPluginID();
	ERR(suites.UtilitySuite6()->AEGP_ReportInfoUnicode(*pluginID, info.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<ReportInfoUnicodeResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetDriverSpecVersionCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
    A_short major_version;
	A_short minor_version;
	ERR(suites.UtilitySuite6()->AEGP_GetDriverImplementationVersion(&major_version, &minor_version));
	boost::shared_ptr<Response> resp = boost::make_shared<GetDriverSpecVersionResp>(major_version, minor_version, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void StartQuietErrorsCmd::execute()
{
	AEGP_ErrReportState state;
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_StartQuietErrors(&state));
	boost::shared_ptr<Response> resp = boost::make_shared<StartQuietErrorsResp>(state, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void EndQuietErrorsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ErrReportState state;
	ERR(suites.UtilitySuite6()->AEGP_EndQuietErrors(report, &state));
	boost::shared_ptr<Response> resp = boost::make_shared<EndQuietErrorsResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void StartUndoGroupCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_StartUndoGroup(undo_name.c_str()));
	boost::shared_ptr<Response> resp = boost::make_shared<StartUndoGroupResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void EndUndoGroupCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_EndUndoGroup());
	boost::shared_ptr<Response> resp = boost::make_shared<EndUndoGroupResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void ShowHideAllFloatersCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_ShowHideAllFloaters(include_tool_pal));
	boost::shared_ptr<Response> resp = boost::make_shared<ShowHideAllFloatersResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void PaintPalGetForeColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal fore_color;
	ERR(suites.UtilitySuite6()->AEGP_PaintPalGetForeColor(&fore_color));
	boost::shared_ptr<Response> resp = boost::make_shared<PaintPalGetForeColorResp>(fore_color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void PaintPalGetBackColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal back_color;
	ERR(suites.UtilitySuite6()->AEGP_PaintPalGetBackColor(&back_color));
	boost::shared_ptr<Response> resp = boost::make_shared<PaintPalGetBackColorResp>(back_color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void PaintPalSetForeColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_PaintPalSetForeColor(&fore_color));
	boost::shared_ptr<Response> resp = boost::make_shared<PaintPalSetForeColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void PaintPalSetBackColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_PaintPalSetBackColor(&back_color));
	boost::shared_ptr<Response> resp = boost::make_shared<PaintPalSetBackColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CharPalGetFillColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal fill_color;
	ERR(suites.UtilitySuite6()->AEGP_CharPalGetFillColor(&is_swatch, &fill_color));
	boost::shared_ptr<Response> resp = boost::make_shared<CharPalGetFillColorResp>(is_swatch, fill_color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CharPalGetStrokeColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal stroke_color;
	ERR(suites.UtilitySuite6()->AEGP_CharPalGetStrokeColor(&is_defined, &stroke_color));
	boost::shared_ptr<Response> resp = boost::make_shared<CharPalGetStrokeColorResp>(is_defined, stroke_color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CharPalSetFillColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_CharPalSetFillColor(&fill_color));
	boost::shared_ptr<Response> resp = boost::make_shared<CharPalSetFillColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CharPalSetStrokeColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_CharPalSetStrokeColor(&stroke_color));
	boost::shared_ptr<Response> resp = boost::make_shared<CharPalSetStrokeColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CharPalIsFillColorUIFrontmostCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean is_frontmost;
	ERR(suites.UtilitySuite6()->AEGP_CharPalIsFillColorUIFrontmost(&is_frontmost));
	boost::shared_ptr<Response> resp = boost::make_shared<CharPalIsFillColorUIFrontmostResp>(is_frontmost, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetSuppressInteractiveUICmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean suppress;
	ERR(suites.UtilitySuite6()->AEGP_GetSuppressInteractiveUI(&suppress));
	boost::shared_ptr<Response> resp = boost::make_shared<GetSuppressInteractiveUIResp>(suppress, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void WriteToOSConsoleCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_WriteToOSConsole(text.c_str()));
	boost::shared_ptr<Response> resp = boost::make_shared<WriteToOSConsoleResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void WriteToDebugLogCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_WriteToDebugLog(subsystem.c_str(), event_type.c_str(), info.c_str()));
	boost::shared_ptr<Response> resp = boost::make_shared<WriteToDebugLogResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLastErrorMessageCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_char *buffer = new A_char[buffer_size];
	ERR(suites.UtilitySuite6()->AEGP_GetLastErrorMessage(buffer_size, buffer, &err));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLastErrorMessageResp>(buffer_size, *buffer, err, errToString(err));
	delete[] buffer;
	MessageQueueManager::getInstance().sendResponse(resp);
}

void UpdateFontListCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.UtilitySuite6()->AEGP_UpdateFontList());
	boost::shared_ptr<Response> resp = boost::make_shared<UpdateFontListResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetPluginPathsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
	AEGP_MemHandle pathH = NULL;
	A_UTF16Char* unicode_nameP;
	ERR(suites.UtilitySuite6()->AEGP_GetPluginPaths(*pluginID, path_type, &pathH));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(pathH, (void**)&unicode_nameP));
	std::string path = convertUTF16ToUTF8(unicode_nameP);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(pathH));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(pathH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetPluginPathsResp>(path, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

