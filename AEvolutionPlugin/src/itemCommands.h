#pragma once
#include "main.h"
#include "MessageQueueManager.h"
#include "SessionManager.h"
#include "SuitesManager.h"

class GetFirstProjItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		AEGP_ProjectH projectH;
		A_Err err = A_Err_NONE;
		int itemID;
		
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ProjSuite6()->AEGP_GetProjectByIndex(1, &projectH));
		ERR(suites.ItemSuite9()->AEGP_GetFirstProjItem(projectH, &itemH));
		ERR(suites.ItemSuite9()->AEGP_GetItemID(itemH, &itemID));

		// Check err, if no error, add the session to the map
		if (err == A_Err_NONE) {
			SessionManager::GetInstance().addSession(itemH, itemID);
		}

		// Create the result and response
		Result<Item> result = Result<Item>(Item(itemID), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
// Register the command
REGISTER_COMMAND(CommandID::GetFirstProjItem, GetFirstProjItem);

/*
Result<Item> GetFirstProjItem() {
		auto& mqm = MessageQueueManager::getInstance();
		Command cmd(CommandID::GetFirstProjItem, CommandArgs());
		Response resp = mqm.sendAndReceive(cmd);

		Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
		return result;
}
*/

class GetNextProjItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ProjectH projectH;
		AEGP_ItemH nextItemH;
		A_Err err = A_Err_NONE;
		int itemID;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		Result<Item> result = Result<Item>(Item(), errToString(err));
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ProjSuite6()->AEGP_GetProjectByIndex(1, &projectH));
		ERR(suites.ItemSuite9()->AEGP_GetNextProjItem(projectH, itemH, &nextItemH));
		// if the next item exists, add the session to the map
		if (nextItemH) {
			ERR(suites.ItemSuite9()->AEGP_GetItemID(nextItemH, &itemID));
			SessionManager::GetInstance().addSession(nextItemH, itemID);
			result = Result<Item>(Item(itemID), errToString(err));
		}

		// Create the result and respons
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::GetNextProjItem, GetNextProjItem);

/*
Result<Item> GetNextProjItem(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetNextProjItem, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
*/

class GetActiveItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		A_Err err = A_Err_NONE;
		int itemID;
		Result<Item> result = Result<Item>(Item(), errToString(err));
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetActiveItem(&itemH));

		if (itemH) {
			ERR(suites.ItemSuite9()->AEGP_GetItemID(itemH, &itemID));
			SessionManager::GetInstance().addSession(itemH, itemID);
			result = Result<Item>(Item(itemID), errToString(err));
		}

		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
//
REGISTER_COMMAND(CommandID::GetActiveItem, GetActiveItem);

/*
Result<Item> GetActiveItem() {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetActiveItem, CommandArgs());
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}
*/

class IsItemSelected : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		A_Err err = A_Err_NONE;
		A_Boolean selected;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_IsItemSelected(itemH, &selected));

		// Create the result and response
		Result<bool> result = Result<bool>(selected, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::IsItemSelected, IsItemSelected);

/*
* 
* Result<bool> IsItemSelected(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::IsItemSelected, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class SelectItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		A_Err err = A_Err_NONE;
		A_Boolean selected = FALSE;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		bool select = boost::get<bool>(cmd.args[1]);
		bool deselectOthers = boost::get<bool>(cmd.args[2]);

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SelectItem(itemH, select, deselectOthers));

		// Create the result and response
		Result<bool> result = Result<bool>(true, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::SelectItem, SelectItem);

/*
*	
* Result<bool> SelectItem(Item item, bool select, bool deselectOthers) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SelectItem, CommandArgs{item, select, deselectOthers});
	Response resp = mqm.sendAndReceive(cmd);

	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class GetItemType : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		A_Err err = A_Err_NONE;
		AEGP_ItemType itemType;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemType(itemH, &itemType));

		// Create the result and response
		ItemType type = ItemType(itemType);
		Result<ItemType> result = Result<ItemType>(type, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::GetItemType, GetItemType);

/*
* Result<AEGP_ItemType> GetItemType(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemType, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<AEGP_ItemType> result = boost::get<Result<AEGP_ItemType>>(resp.args[0]);
	return result;
}
*/

class GetItemName : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		AEGP_MemHandle unicode_nameMH = NULL;
		A_UTF16Char* unicode_nameP = NULL;
		std::string name;
		A_Err err = A_Err_NONE;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		AEGP_PluginID* pluginIDPtr = SuiteManager::GetInstance().GetPluginID();
		if (pluginIDPtr != nullptr) {
			// Dereference the pointer to get the plugin ID
			AEGP_PluginID pluginID = *pluginIDPtr;
			// Replace ERR with PT_ETX macro to check and throw error if not A_Err_NONE
			ERR(suites.ItemSuite9()->AEGP_GetItemName(pluginID, itemH, &unicode_nameMH));
        }
		if (unicode_nameMH) {
			ERR(suites.MemorySuite1()->AEGP_LockMemHandle(unicode_nameMH, (void**)&unicode_nameP));
			name = convertUTF16ToUTF8(unicode_nameP);
			// Unlock and dispose of the memory handle
			ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(unicode_nameMH));
			ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(unicode_nameMH));
		}

		// Create the result and response
		Result<std::string> result = Result<std::string>(name, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemName, GetItemName);

/*
* Result<std::string> GetItemName(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemName, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}
*/

class SetItemName : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		AEGP_ItemH itemH;
		A_Err err = A_Err_NONE;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		std::string name = boost::get<std::string>(cmd.args[1]);

		std::vector<A_UTF16Char> utf16Name = convertUTF8ToUTF16(name);
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemName(itemH, utf16Name.data()));
		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::SetItemName, SetItemName);

/*
* Result<null> SetItemName(Item item, std::string name) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemName, CommandArgs{item, name});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}
*/

class GetItemID : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_long itemID;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemID(itemH, &itemID));

		// Create the result and response
		Result<int> result = Result<int>(static_cast<int>(itemID), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::GetItemID, GetItemID);

/*
* Result<int> GetItemID(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemID, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<int> result = boost::get<Result<int>>(resp.args[0]);
	return result;
}
*/


class GetItemFlags : public CommandBase {
};

class SetItemUseProxy : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		bool useProxy = boost::get<bool>(cmd.args[1]);

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemUseProxy(itemH, useProxy));

		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}

};
REGISTER_COMMAND(CommandID::SetItemUseProxy, SetItemUseProxy);

/*
* Result<null> SetItemUseProxy(Item item, bool useProxy) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemUseProxy, CommandArgs{item, useProxy});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class GetItemParentFolder : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		AEGP_ItemH parentFolderH;
		A_long parentFolderID;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemParentFolder(itemH, &parentFolderH));
		ERR(suites.ItemSuite9()->AEGP_GetItemID(parentFolderH, &parentFolderID));
		if (err == A_Err_NONE) {
			SessionManager::GetInstance().addSession(parentFolderH, parentFolderID);
		}

		// Create the result and response
		Result<Item> result = Result<Item>(Item(static_cast<int>(parentFolderID)), errToString(err));
		Response resp(ResponseArgs{ result });
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemParentFolder, GetItemParentFolder);


/*
* Result<Item> GetItemParentFolder(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemParentFolder, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}
*/

class SetItemParentFolder : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		AEGP_ItemH parentFolderH;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		Item parentFolder = boost::get<Item>(cmd.args[1]);
		 parentFolderH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(parentFolder.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemParentFolder(itemH, parentFolderH));

		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::SetItemParentFolder, SetItemParentFolder);

/*
* Result<null> SetItemParentFolder(Item item, Item parentFolder) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemParentFolder, CommandArgs{item, parentFolder});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class GetItemDuration : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_Time duration;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemDuration(itemH, &duration));

		// Create the result and response
		Result<AETime> result = Result<AETime>(AETime(duration), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemDuration, GetItemDuration);

/*
* Result<AETime> GetItemDuration(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemDuration, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<AETime> result = boost::get<Result<AETime>>(resp.args[0]);
	return result;
}
*/

class GetItemCurrentTime : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_Time currentTime;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		 itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemCurrentTime(itemH, &currentTime));

		// Create the result and response
		AETime time = AETime(currentTime);
		Result<AETime> result = Result<AETime>(time, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemCurrentTime, GetItemCurrentTime);


/*
* Result<int> GetItemCurrentTime(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemCurrentTime, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<int> result = boost::get<Result<int>>(resp.args[0]);
	return result;
}
*/

class GetItemDimensions : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_long width;
		A_long height;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemDimensions(itemH, &width, &height));

		// Create the result and response
		Size size = Size(width, height);
		Result<Size> result = Result<Size>(size, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
}; 
REGISTER_COMMAND(CommandID::GetItemDimensions, GetItemDimensions);

/*
* Result<Size> GetItemDimensions(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemDimensions, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Size> result = boost::get<Result<Size>>(resp.args[0]);
	return result;
}
*/


class GetItemPixelAspectRatio : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_Ratio ratio;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemPixelAspectRatio(itemH, &ratio));
		double aspectRatio = RATIO2DOUBLE(ratio);

		Result<double> result = Result<double>(aspectRatio, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemPixelAspectRatio, GetItemPixelAspectRatio);

/*
* Result<double> GetItemPixelAspectRatio(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemPixelAspectRatio, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<double> result = boost::get<Result<double>>(resp.args[0]);
	return result;
}
*/

class DeleteItem : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_DeleteItem(itemH));

		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::DeleteItem, DeleteItem);

/*
* Result<null> DeleteItem(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::DeleteItem, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class CreateNewFolder : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH newFolderH;
		AEGP_ItemH parentFolderH = NULL;
		//get the command arguments
		std::string name = boost::get<std::string>(cmd.args[0]);
		if (cmd.args.size() > 1) {
			Item parentFolder = boost::get<Item>(cmd.args[1]);
			parentFolderH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(parentFolder.getSessionID()));
		}
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_CreateNewFolder(convertUTF8ToUTF16(name).data(), parentFolderH, &newFolderH));
		if (err == A_Err_NONE) {
			A_long newFolderID;
			ERR(suites.ItemSuite9()->AEGP_GetItemID(newFolderH, &newFolderID));
			SessionManager::GetInstance().addSession(newFolderH, newFolderID);
		}
		// Create the result and response
		Result<Item> result = Result<Item>(Item(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::CreateNewFolder, CreateNewFolder);

/*
* Result<Item> CreateNewFolder(std::string name, Item parentFolder) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::CreateNewFolder, CommandArgs{name, parentFolder});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}
*/

class SetItemCurrentTime : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		A_Time time = { 0, 0 };
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		AETime aeTime = boost::get<AETime>(cmd.args[1]);
		time.value = static_cast<A_long>(aeTime.value);
		time.scale = static_cast<A_u_long>(aeTime.scale);

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemCurrentTime(itemH, &time));

		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::SetItemCurrentTime, SetItemCurrentTime);

/*
* Result<null> SetItemCurrentTime(Item item, AETime time) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemCurrentTime, CommandArgs{item, time});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class GetItemComment : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		AEGP_MemHandle unicode_nameMH = NULL;
		A_UTF16Char* unicode_nameP = NULL;
		std::string comment;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		AEGP_PluginID* pluginIDPtr = SuiteManager::GetInstance().GetPluginID();
		if (pluginIDPtr != nullptr) {
			// Dereference the pointer to get the plugin ID
			AEGP_PluginID pluginID = *pluginIDPtr;
			// Replace ERR with PT_ETX macro to check and throw error if not A_Err_NONE
			ERR(suites.ItemSuite9()->AEGP_GetItemComment(itemH, &unicode_nameMH));
		}
		if (unicode_nameMH) {
			ERR(suites.MemorySuite1()->AEGP_LockMemHandle(unicode_nameMH, (void**)&unicode_nameP));
			comment = convertUTF16ToUTF8(unicode_nameP);
			// Unlock and dispose of the memory handle
			ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(unicode_nameMH));
			ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(unicode_nameMH));
		}

		// Create the result and response
		Result<std::string> result = Result<std::string>(comment, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemComment, GetItemComment);

/*
* Result<std::string> GetItemComment(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemComment, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}
*/

class SetItemComment : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		std::string comment = boost::get<std::string>(cmd.args[1]);

		std::vector<A_UTF16Char> utf16Comment = convertUTF8ToUTF16(comment);
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemComment(itemH, utf16Comment.data()));
		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::SetItemComment, SetItemComment);

/*
* Result<null> SetItemComment(Item item, std::string comment) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemComment, CommandArgs{item, comment});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}
*/

class GetItemLabel : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		AEGP_LabelID label;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));

		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_GetItemLabel(itemH, &label));

		LabelType labelType = LabelType(label);
		// Create the result and response
		Result<LabelType> result = Result<LabelType>(labelType, errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetItemLabel, GetItemLabel);

/*
* Result<LabelType> GetItemLabel(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemLabel, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<LabelType> result = boost::get<Result<LabelType>>(resp.args[0]);
	return result;
}
*/

class SetItemLabel : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		//define the variables
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;
		//get the command arguments
		Item item = boost::get<Item>(cmd.args[0]);
		itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item.getSessionID()));
		LabelType label = boost::get<LabelType>(cmd.args[1]);
		AEGP_LabelID labelID;
		labelID = static_cast<AEGP_LabelID>(label.type);
		// Get the suite handler
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		// Perform the action
		ERR(suites.ItemSuite9()->AEGP_SetItemLabel(itemH, labelID));

		// Create the result and response
		Result<null> result = Result<null>(null(), errToString(err));
		Response resp(ResponseArgs{result});
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::SetItemLabel, SetItemLabel);

