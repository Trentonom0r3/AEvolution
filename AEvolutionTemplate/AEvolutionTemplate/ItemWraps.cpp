#include "pch.h"

Result<Item> GetFirstProjItem() {
	auto& mqm = MessageQueueManager::getInstance();

	Command cmd(CommandID::GetFirstProjItem, CommandArgs());
	Response resp = mqm.sendAndReceive(cmd);

	Result<Item> result = boost::get<Result<Item>>(resp.args[0]);
	return result;
}

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

Result<ItemType> GetItemType(Item item) {
	auto& mqm = MessageQueueManager::getInstance();
	Command cmd(CommandID::GetItemType, CommandArgs{item});
	Response resp = mqm.sendAndReceive(cmd);

	Result<ItemType> result = boost::get<Result<ItemType>>(resp.args[0]);
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
