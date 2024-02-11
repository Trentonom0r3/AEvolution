#include "pch.h"
#include "ItemWraps.h"

Result<Item> GetFirstProjItem() {
	auto& mqm = MessageQueueManager::getInstance();

	Command cmd(CommandID::GetFirstProjItem, CommandArgs());
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}
/*
AEGP_GetNewStreamValue

Get value, at a time you specify, of stream. valueP must be disposed by the plug-in. The AEGP_LTimeMode indicates whether the time is in compositions or layer time.

AEGP_GetNewStreamValue(
  AEGP_PluginID      aegp_plugin_id,
  AEGP_StreamRefH    streamH,
  AEGP_LTimeMode     time_mode,
  const A_Time       *timePT,
  A_Boolean          pre_exprB,
  AEGP_StreamValue2  *valueP);
 */


Result<Item> GetNextProjItem(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetNextProjItem, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}

Result<Item> GetActiveItem() {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetActiveItem, CommandArgs());
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}

Result<bool> IsItemSelected(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::IsItemSelected, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}

Result<bool> SelectItem(Item item, bool select, bool deselectOthers) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SelectItem, CommandArgs{item, select, deselectOthers});
	Response resp = mqm.sendAndReceive(cmd);

	Result<bool> result = boost::get<Result<bool>>(resp.args[0]);
	return result;
}

Result<AEGP_ItemType> GetItemType(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemType, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<AEGP_ItemType> result = boost::get<Result<AEGP_ItemType>>(resp.args[0]);
	return result;
}

Result<std::string> GetItemName(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemName, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}

Result<null> SetItemName(Item item, std::string name) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemName, CommandArgs{item, name});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<int> GetItemID(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemID, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<int> result = boost::get<Result<int>>(resp.args[0]);
	return result;
}

Result<null> SetItemUseProxy(Item item, bool useProxy) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemUseProxy, CommandArgs{item, useProxy});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<Item> GetItemParentFolder(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemParentFolder, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}

Result<null> SetItemParentFolder(Item item, Item parentFolder) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemParentFolder, CommandArgs{item, parentFolder});
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<AETime> GetItemDuration(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemDuration, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<AETime> result = boost::get<Result<AETime>>(resp.args[0]);
	return result;
}

Result<int> GetItemCurrentTime(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemCurrentTime, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<int> result = boost::get<Result<int>>(resp.args[0]);
	return result;
}

Result<Size> GetItemDimensions(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemDimensions, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<Size> result = boost::get<Result<Size>>(resp.args[0]);
	return result;
}

Result<double> GetItemPixelAspectRatio(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemPixelAspectRatio, CommandArgs{ item });
	Response resp = mqm.sendAndReceive(cmd);

	Result<double> result = boost::get<Result<double>>(resp.args[0]);
	return result;
}

Result<null> DeleteItem(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::DeleteItem, CommandArgs{ item });
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<std::string> GetItemComment(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemComment, CommandArgs{ item });
	Response resp = mqm.sendAndReceive(cmd);

	Result<std::string> result = boost::get<Result<std::string>>(resp.args[0]);
	return result;
}

Result<Item> CreateNewFolder(std::string name, Item parentFolder) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::CreateNewFolder, CommandArgs{ name, parentFolder });
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}

Result<null> SetItemCurrentTime(Item item, AETime time) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemCurrentTime, CommandArgs{ item, time });
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<null> SetItemComment(Item item, std::string comment) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemComment, CommandArgs{ item, comment });
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}

Result<AEGP_LabelID> GetItemLabel(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemLabel, CommandArgs{ item });
	Response resp = mqm.sendAndReceive(cmd);

	Result<AEGP_LabelID> result = boost::get<Result<AEGP_LabelID>>(resp.args[0]);
	return result;
}

Result<null> SetItemLabel(Item item, AEGP_LabelID label) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::SetItemLabel, CommandArgs{ item, label });
	Response resp = mqm.sendAndReceive(cmd);

	Result<null> result = boost::get<Result<null>>(resp.args[0]);
	return result;
}