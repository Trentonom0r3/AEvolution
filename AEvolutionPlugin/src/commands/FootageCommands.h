#pragma once
#include "../CommandFactory.h"
#include "../SessionManager.h"

/*
* 
* 
*/

class GetMainFootageFromItem : public CommandBase {
public: 
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[0]));
		
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		AEGP_FootageH footageH;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetMainFootageFromItem(itemH, &footageH));

		Footage footage;
		if (!err) {
			footage = Footage(createUUID());
			SessionManager::GetInstance().addSession(footageH, footage.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Footage>(footage), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetMainFootageFromItem, GetMainFootageFromItem);

/*
Result<Item> GetMainFootageFromItem(Item item) {
    Command cmd(CommandID::GetMainFootageFromItem, { item });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Item> result = resp.getResult<Item>();
	return result;
}
*/

class GetProxyFootageFromItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[0]));

		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		AEGP_FootageH footageH;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetProxyFootageFromItem(itemH, &footageH));

		Footage footage;
		if (!err) {
			footage = Footage(createUUID());
			SessionManager::GetInstance().addSession(footageH, footage.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Footage>(footage), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetProxyFootageFromItem, GetProxyFootageFromItem);

/*
Result<Footage> GetProxyFootageFromItem(Item item) {
	Command cmd(CommandID::GetProxyFootageFromItem, { item });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Footage> result = boost::get<Result<Footage>>(resp.args[0]);
	return result;
}
*/

class GetFootageNumFiles : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		A_long num_filesPL0;
		A_long files_per_frmPL0;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootageNumFiles(footageH, &num_filesPL0, &files_per_frmPL0));
		Result<int> resultH(num_filesPL0, errToString(err));
		Result<int> resultL(files_per_frmPL0, errToString(err));

		Response response({resultH, resultL});
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootageNumFiles, GetFootageNumFiles);

/*
* Result<std::pair<A_long, A_long>> GetFootageNumFiles(Footage footage) {
	Command cmd(CommandID::GetFootageNumFiles, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<std::pair<A_long, A_long>> result = boost::get<Result<std::pair<A_long, A_long>>>(resp.args[0]);
	return result;
}
*/

class GetFootagePath : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		A_long frame_numL = boost::get<A_long>(cmd.args[1]);
		A_long file_indexL = boost::get<A_long>(cmd.args[2]);

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_MemHandle unicode_pathPH;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootagePath(footageH, frame_numL, file_indexL, &unicode_pathPH));
		A_UTF16Char* path;
		ERR(suites.MemorySuite1()->AEGP_LockMemHandle(unicode_pathPH, reinterpret_cast<void**>(&path)));

		std::string pathS = convertUTF16ToUTF8(path);
		suites.MemorySuite1()->AEGP_UnlockMemHandle(unicode_pathPH);
		suites.MemorySuite1()->AEGP_FreeMemHandle(unicode_pathPH);

		Result<std::string> result(pathS, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootagePath, GetFootagePath);
	
/*
* Result<std::string> GetFootagePath(Footage footage, A_long frame_numL, A_long file_indexL) {
	Command cmd(CommandID::GetFootagePath, { footage, frame_numL, file_indexL });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}
*/

class GetFootageSignature : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_FootageSignature sigP;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootageSignature(footageH, &sigP));

		Result<AEGP_FootageSignature> result(sigP, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootageSignature, GetFootageSignature);

/*
* Result<AEGP_FootageSignature> GetFootageSignature(Footage footage) {
	Command cmd(CommandID::GetFootageSignature, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<AEGP_FootageSignature> result = boost::get<Result<AEGP_FootageSignature>>(resp.args[0]);
	return result;
}
*/

class NewFootage : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		std::string path = boost::get<std::string>(cmd.args[0]);
		AEGP_FootageLayerKey layer_infoP0;
		AEGP_FileSequenceImportOptions sequence_optionsP0;

		try {
			FootageLayerKey layer_info = *boost::dynamic_pointer_cast<FootageLayerKey>(boost::get<baseobj>(cmd.args[1]));
			layer_infoP0 = layer_info.toAEGP_FootageLayerKey();
		} catch (boost::bad_get& e) {
			std::cout << "No layer info" << e.what() << std::endl;
		}
		try {
			FileSequenceImportOptions sequence_options = *boost::dynamic_pointer_cast<FileSequenceImportOptions>(boost::get<baseobj>(cmd.args[2]));
			sequence_optionsP0 = sequence_options.toAEGP_FileSequenceImportOptions();
		} catch (boost::bad_get& e) {
			std::cout << "No sequence options" << e.what() << std::endl;
		}

		AEGP_InterpretationStyle interp_style = boost::get<AEGP_InterpretationStyle>(cmd.args[3]);

		AEGP_FootageH footageH;
		A_Err err = A_Err_NONE;
		std::vector<A_UTF16Char> pathUTF16 = convertUTF8ToUTF16(path);
		AEGP_PluginID pluginID = *SuiteManager::GetInstance().GetPluginID();

		ERR(suites.FootageSuite5()->AEGP_NewFootage(pluginID, pathUTF16.data(), &layer_infoP0, &sequence_optionsP0, interp_style, nullptr, &footageH));

		Footage footage;

		if (!err) {
			footage = Footage(createUUID());
			SessionManager::GetInstance().addSession(footageH, footage.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Footage>(footage), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::NewFootage, NewFootage);

/*
* == None, == None. If none, pass null() instead of FootageLayerKey or FileSequenceImportOptions
Result<Footage> NewFootage(std::string path, FootageLayerKey layer_infoP0, FileSequenceImportOptions sequence_optionsP0, AEGP_InterpretationStyle interp_style) {
	Command cmd(CommandID::NewFootage, { path, layer_infoP0, sequence_optionsP0, interp_style });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Footage> result = boost::get<Result<Footage>>(resp.args[0]);
	return result;
}
*/

class AddFootageToProject : public CommandBase {
public: //"import" footage
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		Item folder = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[1]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_ItemH folderH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(folder.getSessionID()));
		AEGP_ItemH add_itemPH0;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_AddFootageToProject(footageH, folderH, &add_itemPH0));

		Item item;
		if (!err) {
			item = Item(createUUID());
			SessionManager::GetInstance().addSession(add_itemPH0, item.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Item>(item), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::AddFootageToProject, AddFootageToProject);

/*
Result<Item> AddFootageToProject(Footage footage, Item folder) {
	Command cmd(CommandID::AddFootageToProject, { footage, folder });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}
*/

class SetItemProxyFootage : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[1]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_SetItemProxyFootage(footageH, itemH));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetItemProxyFootage, SetItemProxyFootage);

/*
Result<null> SetItemProxyFootage(Footage footage, Item item) {
	Command cmd(CommandID::SetItemProxyFootage, { footage, item });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class ReplaceItemMainFootage : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[1]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_ReplaceItemMainFootage(footageH, itemH));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::ReplaceItemMainFootage, ReplaceItemMainFootage);

/*
* Result<null> ReplaceItemMainFootage(Footage footage, Item item) {
	Command cmd(CommandID::ReplaceItemMainFootage, { footage, item });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class DisposeFootage : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));

		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_DisposeFootage(footageH));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::DisposeFootage, DisposeFootage);

/*
* Result<null> DisposeFootage(Footage footage) {
	Command cmd(CommandID::DisposeFootage, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/


class GetFootageLayerKey : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_FootageLayerKey layerKeyP;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootageLayerKey(footageH, &layerKeyP));

		FootageLayerKey layerKey(layerKeyP.layer_idL, layerKeyP.layer_indexL, layerKeyP.nameAC, layerKeyP.layer_draw_style);
		Result<baseobj> result(boost::make_shared<FootageLayerKey>(layerKey), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootageLayerKey, GetFootageLayerKey);

/*
Result<FootageLayerKey> GetFootageLayerKey(Footage footage) {
	Command cmd(CommandID::GetFootageLayerKey, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<FootageLayerKey> result = boost::get<Result<FootageLayerKey>>(resp.args[0]);
	return result;
}
*/

class NewPlaceholderFootageWithPath : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_PluginID plugin_id = *SuiteManager::GetInstance().GetPluginID();
		std::string path = boost::get<std::string>(cmd.args[0]);
		AEIO_FileType file_type = boost::get<AEIO_FileType>(cmd.args[1]);
		A_long widthL = boost::get<A_long>(cmd.args[2]);
		A_long heightL = boost::get<A_long>(cmd.args[3]);
		Time duration = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[4]));
		A_Time durationPT = duration.toA_Time();

		AEGP_FootageH footageH;
		A_Err err = A_Err_NONE;
		std::vector<A_UTF16Char> pathUTF16 = convertUTF8ToUTF16(path);
		AEGP_Platform path_platform = AEGP_Platform_WIN;

		ERR(suites.FootageSuite5()->AEGP_NewPlaceholderFootageWithPath(plugin_id, pathUTF16.data(), path_platform, file_type, widthL, heightL, &durationPT, &footageH));

		Footage footage;

		if (!err) {
			footage = Footage(createUUID());
			SessionManager::GetInstance().addSession(footageH, footage.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Footage>(footage), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::NewPlaceholderFootageWithPath, NewPlaceholderFootageWithPath);

/*
Result<Footage> NewPlaceholderFootageWithPath(std::string path, AEIO_FileType file_type, A_long widthL, A_long heightL, A_Time durationPT) {
	Command cmd(CommandID::NewPlaceholderFootageWithPath, { path, file_type, widthL, heightL, durationPT });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Footage> result = boost::get<Result<Footage>>(resp.args[0]);
	return result;
}
*/

class NewSolidFootage : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		std::string name = boost::get<std::string>(cmd.args[0]);
		Size size = *boost::dynamic_pointer_cast<Size>(boost::get<baseobj>(cmd.args[1]));
		Color colorH = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[2]));
		AEGP_ColorVal color = colorH.toAEGP_ColorVal();
		A_long width = static_cast<A_long>(size.x);
		A_long height = static_cast<A_long>(size.y);

		AEGP_FootageH footageH;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_NewSolidFootage(name.c_str(), width, height, &color, &footageH));

		Footage footage;

		if (!err) {
			footage = Footage(createUUID());
			SessionManager::GetInstance().addSession(footageH, footage.getSessionID());
		}

		Result<baseobj> result(boost::make_shared<Footage>(footage), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::NewSolidFootage, NewSolidFootage);

/*
Result<Footage> NewSolidFootage(std::string name, Size size, Color color) {
	Command cmd(CommandID::NewSolidFootage, { name, size, color });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Footage> result = boost::get<Result<Footage>>(resp.args[0]);
	return result;
}
*/

class GetSolidFootageColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[0]));
		A_Boolean proxyB = boost::get<A_Boolean>(cmd.args[1]);
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		AEGP_ColorVal colorP;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetSolidFootageColor(itemH, proxyB, &colorP));

		Color color(colorP);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetSolidFootageColor, GetSolidFootageColor);

/*
Result<Color> GetSolidFootageColor(Item item, A_Boolean proxyB) {
	Command cmd(CommandID::GetSolidFootageColor, { item, proxyB });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(resp.args[0]);
	return result;
}
*/

class SetSolidFootageColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[0]));
		bool proxyB = boost::get<bool>(cmd.args[1]);
		Color colorH = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[2]));
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		AEGP_ColorVal color = colorH.toAEGP_ColorVal();
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_SetSolidFootageColor(itemH, proxyB, &color));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetSolidFootageColor, SetSolidFootageColor);

/*
* Result<null> SetSolidFootageColor(Item item, A_Boolean proxyB, Color color) {
	Command cmd(CommandID::SetSolidFootageColor, { item, proxyB, color });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/	

class SetSolidFootageDimensions : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Item item = *boost::dynamic_pointer_cast<Item>(boost::get<baseobj>(cmd.args[0]));
		bool proxyB = boost::get<bool>(cmd.args[1]);
		Size size = *boost::dynamic_pointer_cast<Size>(boost::get<baseobj>(cmd.args[2]));
		A_long widthL = static_cast<A_long>(size.x);
		A_long heightL = static_cast<A_long>(size.y);
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_SetSolidFootageDimensions(itemH, proxyB, widthL, heightL));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetSolidFootageDimensions, SetSolidFootageDimensions);

/*
Result<null> SetSolidFootageDimensions(Item item, A_Boolean proxyB, Size size) {
	Command cmd(CommandID::SetSolidFootageDimensions, { item, proxyB, size });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class GetFootageSoundDataFormat : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_SoundDataFormat formatP;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootageSoundDataFormat(footageH, &formatP));

		SoundDataFormat format(formatP);
		Result<baseobj> result(boost::make_shared<SoundDataFormat>(format), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootageSoundDataFormat, GetFootageSoundDataFormat);

/*
Result<SoundDataFormat> GetFootageSoundDataFormat(Footage footage) {
	Command cmd(CommandID::GetFootageSoundDataFormat, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<SoundDataFormat> result = boost::get<Result<SoundDataFormat>>(resp.args[0]);
	return result;
}
*/

class GetFootageSequenceImportOptions : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Footage footage = *boost::dynamic_pointer_cast<Footage>(boost::get<baseobj>(cmd.args[0]));
		AEGP_FootageH footageH = std::get<AEGP_FootageH>(SessionManager::GetInstance().getSession(footage.getSessionID()));
		AEGP_FileSequenceImportOptions optionsP;
		A_Err err = A_Err_NONE;

		ERR(suites.FootageSuite5()->AEGP_GetFootageSequenceImportOptions(footageH, &optionsP));

		FileSequenceImportOptions options(optionsP);
		Result<baseobj> result(boost::make_shared<FileSequenceImportOptions>(options), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetFootageSequenceImportOptions, GetFootageSequenceImportOptions);

/*
Result<FileSequenceImportOptions> GetFootageSequenceImportOptions(Footage footage) {
	Command cmd(CommandID::GetFootageSequenceImportOptions, { footage });
	Response resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<FileSequenceImportOptions> result = boost::get<Result<FileSequenceImportOptions>>(resp.args[0]);
	return result;
}
*/

