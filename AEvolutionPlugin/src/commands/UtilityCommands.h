#pragma once
#include "../CommandFactory.h"
#include "../SessionManager.h"

class ReportInfoUnicode : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		std::vector<A_UTF16Char> info = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[0]));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
		A_Err err = A_Err_NONE;
		if (pluginID) {
			ERR(suites.UtilitySuite6()->AEGP_ReportInfoUnicode(*pluginID, info.data()));
		}
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
//// Register the command
//REGISTER_COMMAND(CommandID::GetFirstProjItem, GetFirstProjItem);
REGISTER_COMMAND(CommandID::ReportInfoUnicode, ReportInfoUnicode);

/*
Result<null> ReportInfoUnicode(std::string info) {
    Command command(CommandType::ReportInfoUnicode, { info });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
    return result;
}
*/

class GetDriverSpecVersion : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_short major_version;
		A_short minor_version;
		A_Err err = A_Err_NONE;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.UtilitySuite6()->AEGP_GetDriverImplementationVersion(&major_version, &minor_version));
		Result<int> result(major_version, errToString(err));
		Result<int> result2(minor_version, errToString(err));
		Response response;
		response.args.push_back(result);
		response.args.push_back(result2);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetDriverSpecVersion, GetDriverSpecVersion);

/*
* Response<Result<std::vector<int>>> GetDriverSpecVersion() {
	Command command(CommandType::GetDriverSpecVersion, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<std::vector<int>> result = boost::get<Result<std::vector<int>>>(resp.args[0]);
	return result;
}
*/

class StartQuietErrors : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_ErrReportState err_state;
		A_Err err = A_Err_NONE;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.UtilitySuite6()->AEGP_StartQuietErrors(&err_state));
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::StartQuietErrors, StartQuietErrors);
/*
* Result<null> StartQuietErrors() {
	Command command(CommandType::StartQuietErrors, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class EndQuietErrors : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_ErrReportState err_state;
		A_Err err = A_Err_NONE;
		bool endOrNot = boost::get<bool>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.UtilitySuite6()->AEGP_EndQuietErrors(endOrNot,&err_state));
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::EndQuietErrors, EndQuietErrors);
/*
* Result<null> EndQuietErrors() {
	Command command(CommandType::EndQuietErrors, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class StartUndoGroup : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		std::vector<A_UTF16Char> undo_name = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[0]));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Err err = suites.UtilitySuite6()->AEGP_StartUndoGroup(reinterpret_cast<const A_char*>(undo_name.data()));
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::StartUndoGroup, StartUndoGroup);
/*
* Result<null> StartUndoGroup(std::string undo_name) {
	Command command(CommandType::StartUndoGroup, { undo_name });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class EndUndoGroup : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Err err = suites.UtilitySuite6()->AEGP_EndUndoGroup();
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::EndUndoGroup, EndUndoGroup);

/*
* Result<null> EndUndoGroup() {
	Command command(CommandType::EndUndoGroup, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class ShowHideAllFloaters : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		bool include_tool_palB = boost::get<bool>(cmd.args[0]);
		A_Err err = suites.UtilitySuite6()->AEGP_ShowHideAllFloaters(include_tool_palB);
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::ShowHideAllFloaters, ShowHideAllFloaters);

/*
* Result<null> ShowHideAllFloaters(bool include_tool_palB) {
	Command command(CommandType::ShowHideAllFloaters, { include_tool_palB });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class PaintPalGetForeColor : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_ColorVal fore_color;
		A_Err err = suites.UtilitySuite6()->AEGP_PaintPalGetForeColor(&fore_color);
		Color color(fore_color);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::PaintPalGetForeColor, PaintPalGetForeColor);

/*
* Result<Color> PaintPalGetForeColor() {
	Command command(CommandType::PaintPalGetForeColor, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(resp.args[0]);
	return result;
}
*/

class PaintPalGetBackColor : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_ColorVal back_color;
		A_Err err = suites.UtilitySuite6()->AEGP_PaintPalGetBackColor(&back_color);
		Color color(back_color);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::PaintPalGetBackColor, PaintPalGetBackColor);

/*
* Result<Color> PaintPalGetBackColor() {
	Command command(CommandType::PaintPalGetBackColor, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(resp.args[0]);
	return result;
}
*/

class PaintPalSetForeColor : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Color fore_color = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[0]));
		AEGP_ColorVal color = { 0, 0, 0, 0 };
		color.redF = fore_color.r;
		color.greenF = fore_color.g;
		color.blueF = fore_color.b;
		color.alphaF = fore_color.a;

		A_Err err = suites.UtilitySuite6()->AEGP_PaintPalSetForeColor(&color);
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::PaintPalSetForeColor, PaintPalSetForeColor);

/*
* Result<null> PaintPalSetForeColor(Color fore_color) {
	Command command(CommandType::PaintPalSetForeColor, { fore_color });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class PaintPalSetBackColor : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Color back_color = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[0]));
		AEGP_ColorVal color = { 0, 0, 0, 0 };
		color.redF = back_color.r;
		color.greenF = back_color.g;
		color.blueF = back_color.b;
		color.alphaF = back_color.a;

		A_Err err = suites.UtilitySuite6()->AEGP_PaintPalSetBackColor(&color);
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::PaintPalSetBackColor, PaintPalSetBackColor);

/*
* Result<null> PaintPalSetBackColor(Color back_color) {
	Command command(CommandType::PaintPalSetBackColor, { back_color });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class CharPalGetFillColor : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Boolean is_fcolor_definedPB;
		AEGP_ColorVal fill_color;
		A_Err err = suites.UtilitySuite6()->AEGP_CharPalGetFillColor(&is_fcolor_definedPB, &fill_color);
		Color color(fill_color);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CharPalGetFillColor, CharPalGetFillColor);

/*
* Result<Color> CharPalGetFillColor() {
	Command command(CommandType::CharPalGetFillColor, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(resp.args[0]);
	return result;
}
*/

class CharPalGetStrokeColor : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Boolean is_scolor_definedPB;
		AEGP_ColorVal stroke_color;
		A_Err err = suites.UtilitySuite6()->AEGP_CharPalGetStrokeColor(&is_scolor_definedPB, &stroke_color);
		Color color(stroke_color);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CharPalGetStrokeColor, CharPalGetStrokeColor);

/*
* Result<Color> CharPalGetStrokeColor() {
	Command command(CommandType::CharPalGetStrokeColor, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(resp.args[0]);
	return result;
}
*/

class CharPalSetFillColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Color fill_color = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[0]));
		AEGP_ColorVal color = { 0, 0, 0, 0 };
		color.redF = fill_color.r;
		color.greenF = fill_color.g;
		color.blueF = fill_color.b;
		color.alphaF = fill_color.a;

		A_Err err = suites.UtilitySuite6()->AEGP_CharPalSetFillColor(&color);
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CharPalSetFillColor, CharPalSetFillColor);

/*
* Result<null> CharPalSetFillColor(Color fill_color) {
	Command command(CommandType::CharPalSetFillColor, { fill_color });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class CharPalSetStrokeColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Color stroke_color = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[0]));
		AEGP_ColorVal color = { 0, 0, 0, 0 };
		color.redF = stroke_color.r;
		color.greenF = stroke_color.g;
		color.blueF = stroke_color.b;
		color.alphaF = stroke_color.a;

		A_Err err = suites.UtilitySuite6()->AEGP_CharPalSetStrokeColor(&color);
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CharPalSetStrokeColor, CharPalSetStrokeColor);

/*
* Result<null> CharPalSetStrokeColor(Color stroke_color) {
	Command command(CommandType::CharPalSetStrokeColor, { stroke_color });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class CharPalIsFillColorUIFrontmost : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Boolean is_fcolor_selectedPB;
		A_Err err = suites.UtilitySuite6()->AEGP_CharPalIsFillColorUIFrontmost(&is_fcolor_selectedPB);
		bool is_fcolor_selected = is_fcolor_selectedPB;
		Result<bool> result(is_fcolor_selected, errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CharPalIsFillColorUIFrontmost, CharPalIsFillColorUIFrontmost);

/*
* Result<bool> CharPalIsFillColorUIFrontmost() {
	Command command(CommandType::CharPalIsFillColorUIFrontmost, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class GetSuppressInteractiveUI : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Boolean ui_is_suppressedPB;
		A_Err err = suites.UtilitySuite6()->AEGP_GetSuppressInteractiveUI(&ui_is_suppressedPB);
		bool ui_is_suppressed = ui_is_suppressedPB;
		Result<bool> result(ui_is_suppressed, errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetSuppressInteractiveUI, GetSuppressInteractiveUI);

/*
* Result<bool> GetSuppressInteractiveUI() {
	Command command(CommandType::GetSuppressInteractiveUI, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class WriteToOSConsole : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		std::vector<A_UTF16Char> text = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[0]));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Err err = suites.UtilitySuite6()->AEGP_WriteToOSConsole(reinterpret_cast<const A_char*>(text.data()));
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::WriteToOSConsole, WriteToOSConsole);

/*
* Result<null> WriteToOSConsole(std::string text) {
	Command command(CommandType::WriteToOSConsole, { text });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class WriteToDebugLog : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		std::vector<A_UTF16Char> subsystem = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[0]));
		std::vector<A_UTF16Char> event_type = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[1]));
		std::vector<A_UTF16Char> info = convertUTF8ToUTF16(boost::get<std::string>(cmd.args[2]));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Err err = suites.UtilitySuite6()->AEGP_WriteToDebugLog(reinterpret_cast<const A_char*>(subsystem.data()), reinterpret_cast<const A_char*>(event_type.data()), reinterpret_cast<const A_char*>(info.data()));
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::WriteToDebugLog, WriteToDebugLog);

/*
* Result<null> WriteToDebugLog(std::string subsystem, std::string event_type, std::string info) {
	Command command(CommandType::WriteToDebugLog, { subsystem, event_type, info });
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/


class HostIsActivated : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Boolean is_activatedPB;
		A_Err err = suites.UtilitySuite6()->AEGP_HostIsActivated(&is_activatedPB);
		bool is_activated = is_activatedPB;
		Result<bool> result(is_activated, errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::HostIsActivated, HostIsActivated);

/*
* Result<bool> HostIsActivated() {
	Command command(CommandType::HostIsActivated, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class UpdateFontList : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		A_Err err = suites.UtilitySuite6()->AEGP_UpdateFontList();
		null nullRet;
		Result<baseobj> result(boost::make_shared<null>(nullRet), errToString(err));
		Response response(result);

		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::UpdateFontList, UpdateFontList);

/*
* Result<null> UpdateFontList() {
	Command command(CommandType::UpdateFontList, {});
	Response resp = mqm.sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/
/*
class GetPluginPaths : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		PathType type = boost::get<PathType>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_PluginID* plugin_id = SuiteManager::GetInstance().GetPluginID();
		AEGP_MemHandle unicode_nameMH = NULL;
		A_UTF16Char* unicode_nameP = NULL;
		std::string path;
		AEGP_GetPathTypes typeH;

		switch (type.type) {
			case PathType::Type::PLUGIN:
				typeH = AEGP_GetPathTypes_PLUGIN;
				break;
			case PathType::Type::USER_PLUGIN:
				typeH = AEGP_GetPathTypes_USER_PLUGIN;
				break;
			case PathType::Type::ALLUSER_PLUGIN:
				typeH = AEGP_GetPathTypes_ALLUSER_PLUGIN;
				break;
			case PathType::Type::APP:
				typeH = AEGP_GetPathTypes_APP;
				break;
		}


		A_Err err = A_Err_NONE;

		if (plugin_id) {
			err = suites.UtilitySuite6()->AEGP_GetPluginPaths(*plugin_id, typeH, &unicode_nameMH);
		}
		if (unicode_nameMH) {
			ERR(suites.MemorySuite1()->AEGP_LockMemHandle(unicode_nameMH, (void**)&unicode_nameP));
			path = convertUTF16ToUTF8(unicode_nameP);
			ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(unicode_nameMH));
			ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(unicode_nameMH));
		}
		Result<std::string> result(path, errToString(err));
		Response response(ResponseArg{ result });
		MessageQueueManager::getInstance().sendResponse(response);

	}
};
REGISTER_COMMAND(CommandID::GetPluginPaths, GetPluginPaths);
*/
/*
* Result<std::string> GetPluginPaths(PathType type) {
	Command command(CommandType::GetPluginPaths, { type });
	Response resp = mqm.sendAndReceive(cmd);
	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}
*/

