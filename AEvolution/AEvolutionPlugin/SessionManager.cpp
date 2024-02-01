#include "SessionManager.h"

std::string createUUID() {
	// Use the generate_uuid method from the UUID class
	std::string myUUID = CustomUUID::generate_uuid();
	return myUUID;
}

void ReportInfoCommand::execute() {
  	auto& mqm = MessageQueueManager::getInstance();
    try {
		std::string message = boost::get<std::string>(cmd.args[0]);
		auto& message2 = enqueueSyncTask(ReportInfo, message);
		message2->wait();
		Result<void> result = message2->getResult();
		if (result.error != A_Err_NONE) {
			mqm.sendErrorResponse(cmd.sessionID, errToString(result.error));
		}
		else {
			mqm.sendEmptyResponse(cmd.sessionID);
		}
    }
    catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
    }
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getProjectCommand::execute() {
  	auto& mqm = MessageQueueManager::getInstance();
    try {

	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void StartUndoGroupCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
    try {

	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void EndUndoGroupCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
    try {

	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getActiveItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		auto& message = enqueueSyncTask(getActiveItem);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			Response response(cmd.sessionID, result.error);
			mqm.sendResponse(response);
		}
		std::string sessionID = createUUID();
		ItemH item(sessionID);
		SessionManager::GetInstance().addSession(result, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}


void ActiveLayerCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		
	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getItemTypeCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		boost::shared_ptr<ItemH> item = boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		auto itemP = SessionManager::GetInstance().getSession(item->getSessionID());
		Result<AEGP_ItemH> result = std::get<ItemPtr>(itemP);
		if (result.error != A_Err_NONE) {
			Response response(cmd.sessionID, result.error);
			mqm.sendResponse(response);
		}
		auto& message = enqueueSyncTask(getItemType, result);
		message->wait();
		Result<AEGP_ItemType> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			Response response(cmd.sessionID, result2.error);
			mqm.sendResponse(response);
		}
		std::vector<std::string> types;
		types.push_back("Folder");
		types.push_back("Comp");
		types.push_back("Footage");
		types.push_back("Unknown");
		switch (result2.value) {
		case AEGP_ItemType_FOLDER:
		{
			Response response;
			response.sessionID = cmd.sessionID;
			response.args.push_back(types[0]);
			mqm.sendResponse(response);
		}
		break;
		case AEGP_ItemType_COMP:
			{
			Response response;
			response.sessionID = cmd.sessionID;
			response.args.push_back(types[1]);
			mqm.sendResponse(response);
			}
			break;
		case AEGP_ItemType_FOOTAGE:
			{
			Response response;
			response.sessionID = cmd.sessionID;
			response.args.push_back(types[2]);
			mqm.sendResponse(response);
			}
			break;
		default:
			{
			Response response;
			response.sessionID = cmd.sessionID;
			response.args.push_back(types[3]);
			mqm.sendResponse(response);
			}
			break;
		}

	}
	catch (const boost::bad_get& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}
