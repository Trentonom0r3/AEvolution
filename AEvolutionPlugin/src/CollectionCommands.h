#pragma once
#include "main.h"
#include "MessageQueueManager.h"
#include "SessionManager.h"
#include "SuitesManager.h"

/*AEGP_CollectionSuite2¶
Function

Purpose

AEGP_NewCollection

Creates and returns a new, empty collection. To obtain the current composition’s selection as a collection, use AEGP_GetNewCollectionFromCompSelection.

AEGP_NewCollection(
  AEGP_PluginID      plugin_id,
  AEGP_Collection2H  *collectionPH);
AEGP_DisposeCollection

Disposes of a collection.

AEGP_DisposeCollection(
  AEGP_Collection2H  collectionH);
AEGP_GetCollectionNumItems

Returns the number of items contained in the given collection.

AEGP_GetCollectionNumItems(
  AEGP_Collection2H  collectionH,
  A_u_long           *num_itemsPL);
AEGP_GetCollectionItemByIndex

Retrieves (creates and populates) the index’d collection item.

AEGP_GetCollectionItemByIndex(
  AEGP_Collection2H      collectionH,
  A_u_long               indexL,
  AEGP_CollectionItemV2  *itemP);
AEGP_CollectionPushBack

Adds an item to the given collection.

AEGP_CollectionPushBack(
  AEGP_Collection2H            collectionH,
  const AEGP_CollectionItemV2  *itemP);
AEGP_CollectionErase

Removes an index’d item (or items) from a given collection. NOTE: this range is exclusive, like STL iterators. To erase the first item, you would pass 0 and 1, respectively.

AEGP_CollectionErase(
  AEGP_Collection2H  collectionH,
  A_u_long           index_firstL,
  A_u_long           index_lastL);
Ownership Of Collection Items¶
When AEGP_StreamRefHs are inserted into a collection, they are adopted by the collection; do not free them.

AEGP_EffectRefHs, on the other hand, are not adopted, and must be freed by the calling AEGP.
*/

class NewCollection : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_Collection2H collectionH;
		A_Err err = A_Err_NONE; 
		int UUID = createUUID();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_PluginID *m_plugin_id = SuiteManager::GetInstance().GetPluginID();
		ERR(suites.CollectionSuite2()->AEGP_NewCollection(*m_plugin_id, &collectionH));
		Collection collection(UUID);
		SessionManager::GetInstance().addSession(collectionH, UUID);
		Result<Collection> result(collection, errToString(err));
		Response resp(result);
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::NewCollection, NewCollection);
/*
* Result<Collection> NewCollection() {
* Command cmd(CommandID::NewCollection);
* Response resp = MessageQueueManager::getInstance().sendCommand(cmd);
* Result<Collection> result = boost::get<Result<Collection>>(resp.args[0]);
* return result;
*
*/

class DisposeCollection : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		Collection collection = boost::get<Collection>(cmd.args[0]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CollectionSuite2()->AEGP_DisposeCollection(collectionH));
		SessionManager::GetInstance().removeSession(collection.getSessionID());
		Result<null> result(null(), errToString(err));
		Response resp(result);
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::DisposeCollection, DisposeCollection);

/*
* Result<null> DisposeCollection(Collection collection) {
* Command cmd(CommandID::DisposeCollection, CommandArgs{ collection });
* Response resp = MessageQueueManager::getInstance().sendCommand(cmd);
* Result<null> result = boost::get<Result<null>>(resp.args[0]);
* return result;
* */

class GetCollectionNumItems : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		Collection collection = boost::get<Collection>(cmd.args[0]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		A_u_long num_items;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CollectionSuite2()->AEGP_GetCollectionNumItems(collectionH, &num_items));
		Result<int> result(static_cast<int>(num_items), errToString(err));
		Response resp(result);
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
REGISTER_COMMAND(CommandID::GetCollectionNumItems, GetCollectionNumItems);

/*
* Result<int> GetCollectionNumItems(Collection collection) {
* Command cmd(CommandID::GetCollectionNumItems, CommandArgs{ collection });
* Response resp = MessageQueueManager::getInstance().sendCommand(cmd);
* Result<int> result = boost::get<Result<int>>(resp.args[0]);
* return result;
* */

class GetCollectionItemByIndex : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		Collection collection = boost::get<Collection>(cmd.args[0]);
		int index = boost::get<int>(cmd.args[1]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		AEGP_CollectionItemV2 item;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CollectionSuite2()->AEGP_GetCollectionItemByIndex(collectionH, index, &item));
		Result<CollectionItem> result(CollectionItem(item), errToString(err));
		Response resp(result);
		MessageQueueManager::getInstance().sendResponse(resp);
	}
};
