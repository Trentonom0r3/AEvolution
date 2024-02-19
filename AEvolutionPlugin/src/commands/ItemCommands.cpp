#include "ItemCommands.h"
#include "../MessageQueueManager.h"

void GetFirstProjItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH item;
	ERR(suites.ItemSuite9()->AEGP_GetFirstProjItem(project.handle, &item));
	boost::shared_ptr<Response> resp = boost::make_shared<GetFirstProjItemResp>(item, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetNextProjItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH next_item;
	ERR(suites.ItemSuite9()->AEGP_GetNextProjItem(project.handle, item.handle, &next_item));
	boost::shared_ptr<Response> resp = boost::make_shared<GetNextProjItemResp>(next_item, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetActiveItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH active_item;
	ERR(suites.ItemSuite9()->AEGP_GetActiveItem(&active_item));
	boost::shared_ptr<Response> resp = boost::make_shared<GetActiveItemResp>(active_item, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsItemSelectedCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean selectedB;
	ERR(suites.ItemSuite9()->AEGP_IsItemSelected(item.handle, &selectedB));
	boost::shared_ptr<Response> resp = boost::make_shared<IsItemSelectedResp>(selectedB, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SelectItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_SelectItem(item.handle, selectB, deselect_othersB));
	boost::shared_ptr<Response> resp = boost::make_shared<SelectItemResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemTypeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemType type;
	ERR(suites.ItemSuite9()->AEGP_GetItemType(item.handle, &type));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemTypeResp>(type, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
	AEGP_MemHandle nameH = NULL;
	A_UTF16Char* unicode_nameP;
	ERR(suites.ItemSuite9()->AEGP_GetItemName(*pluginID, item.handle, &nameH));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(nameH, (void**)&unicode_nameP));
	std::string name = convertUTF16ToUTF8(unicode_nameP);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(nameH));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(nameH));

	boost::shared_ptr<Response> resp = boost::make_shared<GetItemNameResp>(std::string(name), errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> unicode_name = convertUTF8ToUTF16(nameZ);
	ERR(suites.ItemSuite9()->AEGP_SetItemName(item.handle, unicode_name.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemNameResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}


void GetItemIDCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long itemID;
	ERR(suites.ItemSuite9()->AEGP_GetItemID(item.handle, &itemID));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemIDResp>(itemID, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemFlagsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long flags;
	ERR(suites.ItemSuite9()->AEGP_GetItemFlags(item.handle, &flags));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemFlagsResp>(flags, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemUseProxyCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_SetItemUseProxy(item.handle, use_proxyB));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemUseProxyResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemParentFolderCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH parent_folder;
	ERR(suites.ItemSuite9()->AEGP_GetItemParentFolder(item.handle, &parent_folder));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemParentFolderResp>(parent_folder, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemParentFolderCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_SetItemParentFolder(item.handle, parent_folder.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemParentFolderResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time duration;
	ERR(suites.ItemSuite9()->AEGP_GetItemDuration(item.handle, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemDurationResp>(duration, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemCurrentTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time current_timePT;
	ERR(suites.ItemSuite9()->AEGP_GetItemCurrentTime(item.handle, &current_timePT));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemCurrentTimeResp>(current_timePT, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemDimensionsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long widthL;
	A_long heightL;
	ERR(suites.ItemSuite9()->AEGP_GetItemDimensions(item.handle, &widthL, &heightL));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemDimensionsResp>(widthL, heightL, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemPixelAspectRatioCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Ratio aspect_ratioF;
	ERR(suites.ItemSuite9()->AEGP_GetItemPixelAspectRatio(item.handle, &aspect_ratioF));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemPixelAspectRatioResp>(aspect_ratioF, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void DeleteItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_DeleteItem(item.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<DeleteItemResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateNewFolderCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH new_folder;
	std::vector<A_UTF16Char> unicode_name = convertUTF8ToUTF16(nameZ);
	ERR(suites.ItemSuite9()->AEGP_CreateNewFolder(unicode_name.data(), parent_folder.handle, &new_folder));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateNewFolderResp>(new_folder, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemCurrentTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_SetItemCurrentTime(item.handle, &new_timePT));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemCurrentTimeResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemCommentCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_MemHandle commentH = NULL;
	A_UTF16Char* unicode_commentP;
	ERR(suites.ItemSuite9()->AEGP_GetItemComment(item.handle, &commentH));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(commentH, (void**)&unicode_commentP));
	std::string comment = convertUTF16ToUTF8(unicode_commentP);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(commentH));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(commentH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemCommentResp>(std::string(comment), errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemCommentCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> unicode_comment = convertUTF8ToUTF16(commentZ);
	ERR(suites.ItemSuite9()->AEGP_SetItemComment(item.handle, unicode_comment.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemCommentResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemLabelCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LabelID label;
	ERR(suites.ItemSuite9()->AEGP_GetItemLabel(item.handle, &label));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemLabelResp>(label, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetItemLabelCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.ItemSuite9()->AEGP_SetItemLabel(item.handle, label));
	boost::shared_ptr<Response> resp = boost::make_shared<SetItemLabelResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}














