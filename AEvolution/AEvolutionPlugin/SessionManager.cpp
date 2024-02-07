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
			throw AEException(result.error);
		}
		else {
			mqm.sendEmptyResponse(cmd.sessionID);
		}
    }
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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
		auto& message = enqueueSyncTask(getProject);
		message->wait();
		Result<AEGP_ProjectH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		std::string sessionID = createUUID();
		ProjectH project(sessionID);
		SessionManager::GetInstance().addSession(result, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ProjectH>(project));
		mqm.sendResponse(response);
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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
        std::string undoName = boost::get<std::string>(cmd.args[0]);
        auto& message = enqueueSyncTask(StartUndoGroup, undoName);
        message->wait();
        Result<void> result = message->getResult();
        if (result.error != A_Err_NONE) {
			throw AEException(result.error);
        }
		mqm.sendEmptyResponse(cmd.sessionID);

	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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
    	auto& message = enqueueSyncTask(EndUndoGroup);
		message->wait();
		Result<void> result = message->getResult();
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
            mqm.sendEmptyResponse(cmd.sessionID);
        
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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


// ITEM COMMANDS
// PT 1
void getActiveItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		auto& message = enqueueSyncTask(getActiveItem);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
		std::string sessionID = createUUID();
		ItemH item(sessionID);
		SessionManager::GetInstance().addSession(result, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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
		auto& message = enqueueSyncTask(ActiveLayer);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		std::string sessionID = createUUID();
		LayerH layer(sessionID);
		SessionManager::GetInstance().addSession(result, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
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

void getItemTypeCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		boost::shared_ptr<ItemH> item = boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		auto itemP = SessionManager::GetInstance().getSession(item->getSessionID());
		Result<AEGP_ItemH> result = std::get<ItemPtr>(itemP);
		if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(getItemType, result);
		message->wait();
		Result<AEGP_ItemType> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result2.error);
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
            std::string type = types[0];
			response.args.push_back(type);
			mqm.sendResponse(response);
		}
		break;
		case AEGP_ItemType_COMP:
			{
			Response response;
			response.sessionID = cmd.sessionID;
			std::string type = types[1];
            response.args.push_back(type);
			mqm.sendResponse(response);
			}
			break;
		case AEGP_ItemType_FOOTAGE:
			{
			Response response;
			response.sessionID = cmd.sessionID;
            std::string type = types[2];
			response.args.push_back(type);
			mqm.sendResponse(response);
			}
			break;
		default:
			{
			Response response;
			response.sessionID = cmd.sessionID;
            std::string type = types[3];
			response.args.push_back(type);
			mqm.sendResponse(response);
			}
			break;
		}

	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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


// COLLECTION COMMANDS< LIKELY NOT IMPELEMENTED
void NewCollectionCommand::execute() {
    // Implement the command logic here
}

void DisposeCollectionCommand::execute() {
    // Implement the command logic here
}

void GetCollectionNumItemsCommand::execute() {
    // Implement the command logic here
}

void GetCollectionItemByIndexCommand::execute() {
    // Implement the command logic here
}

void CollectionPushBackCommand::execute() {
    // Implement the command logic here
}

void CollectionEraseCommand::execute() {
    // Implement the command logic here
}


// COMP COMMANDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMP COMMANDS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AddcompCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		dimensionsH dimensions = boost::get<dimensionsH>(cmd.args[1]);
		float frameRate = boost::get<float>(cmd.args[2]);
		float duration = boost::get<float>(cmd.args[3]);
		float pixelAspectRatio = boost::get<float>(cmd.args[4]);
        Result<AEGP_ItemH> parent;
        if (cmd.args[5].type() != typeid(boost::shared_ptr<ItemH>)) {
            auto& message = enqueueSyncTask(getProjectRootFolder);
            message->wait();
            parent = message->getResult();

        }
		else {
		ItemH parentFolder = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[5]);
        auto parentFolderP = SessionManager::GetInstance().getSession(parentFolder.getSessionID());
        parent = std::get<ItemPtr>(parentFolderP);
       		}
		auto& message = enqueueSyncTask(Addcomp, name, dimensions.width, dimensions.height, frameRate, duration, pixelAspectRatio, parent);
		message->wait();
		Result<AEGP_CompH> result = message->getResult();
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
		std::string sessionID = createUUID();
		CompH comp(sessionID);
		SessionManager::GetInstance().addSession(result, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<CompH>(comp));
		mqm.sendResponse(response);
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void getCompFromItemCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        ItemH compItem = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
        auto compItemP = SessionManager::GetInstance().getSession(compItem.getSessionID());
        Result<AEGP_ItemH> result = std::get<ItemPtr>(compItemP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        auto& message = enqueueSyncTask(getCompFromItem, result);
		message->wait();
		Result<AEGP_CompH> result2 = message->getResult();
        if (result2.error != A_Err_NONE) {
            throw AEException(result.error);
        }
        std::string sessionID = createUUID();
        CompH item(sessionID);
        SessionManager::GetInstance().addSession(result2, sessionID);
        Response response;
        response.sessionID = cmd.sessionID;
        response.args.push_back(boost::make_shared<CompH>(item));
        mqm.sendResponse(response);
    }
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemFromCompCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
        auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
        Result<AEGP_CompH> result = std::get<CompPtr>(compP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        auto& message = enqueueSyncTask(GetItemFromComp, result);
        message->wait();
        Result<AEGP_ItemH> result2 = message->getResult();
        if (result2.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        std::string sessionID = createUUID();
		ItemH item(sessionID);
		SessionManager::GetInstance().addSession(result2, sessionID);
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompDownsampleFactorCommand::execute() {
    // Implement the command logic here
}

void SetCompDownsampleFactorCommand::execute() {
    // Implement the command logic here
}

void GetCompBGColorCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
        auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
        Result<AEGP_CompH> result = std::get<CompPtr>(compP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
        }
        auto& message = enqueueSyncTask(GetCompBGColor, result);
        message->wait();
        Result<AEGP_ColorVal> result2 = message->getResult();
        if (result2.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        std::string sessionID = createUUID();
        colorH color;
        color.r = result2.value.redF;
        color.g = result2.value.greenF;
        color.b = result2.value.blueF;
        color.a = result2.value.alphaF;
        Response response;
        response.sessionID = cmd.sessionID;
        response.args.push_back(color);
        mqm.sendResponse(response);
    }
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompBGColorCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
        auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
        Result<AEGP_CompH> result = std::get<CompPtr>(compP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        colorH color = boost::get<colorH>(cmd.args[1]);
        auto& message = enqueueSyncTask(SetCompBGColor, result, color.r, color.g, color.b, color.a);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
            throw AEException(result.error);
        }
        mqm.sendEmptyResponse(cmd.sessionID);
    }
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompFlagsCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompFlags, result);
		message->wait();
		Result<AEGP_CompFlags> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		//convert flags to int TODO
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetShowLayerNameOrSourceNameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetShowLayerNameOrSourceName, result);
		message->wait();
		Result<bool> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetShowLayerNameOrSourceNameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		bool showLayerNames = boost::get<bool>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetShowLayerNameOrSourceName, result, showLayerNames);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetShowBlendModesCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetShowBlendModes, result);
		message->wait();
		Result<bool> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetShowBlendModesCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		bool showBlendModes = boost::get<bool>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetShowBlendModes, result, showBlendModes);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompFramerateCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompFramerate, result);
		message->wait();
		Result<float> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompFramerateCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
        auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
        Result<AEGP_CompH> result = std::get<CompPtr>(compP);
        if (result.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        float frameRate = boost::get<float>(cmd.args[1]);
        auto& message = enqueueSyncTask(SetCompFramerate, result, frameRate);
        message->wait();
        Result<void> result2 = message->getResult();
        if (result2.error != A_Err_NONE) {
            throw AEException(result.error);
		}
        mqm.sendEmptyResponse(cmd.sessionID);
    }
    catch (const AEException& e) {
        mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompShutterAnglePhaseCommand::execute() {
    // Implement the command logic here
}

void SetCompSuggestedMotionBlurSamplesCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		int samples = boost::get<int>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompSuggestedMotionBlurSamples, result, samples);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompWorkAreaStartCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompWorkAreaStart, result);
		message->wait();
		Result<float> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompWorkAreaDurationCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompWorkAreaDuration, result);
		message->wait();
		Result<float> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompWorkAreaStartAndDurationCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		float start = boost::get<float>(cmd.args[1]);
		float dur = boost::get<float>(cmd.args[2]);
		auto& message = enqueueSyncTask(SetCompWorkAreaStartAndDuration, result, start, dur);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void CreateSolidInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		dimensionsH dimensions = boost::get<dimensionsH>(cmd.args[1]);
		colorH color = boost::get<colorH>(cmd.args[2]);
		CompH parentComp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[3]);
		Result<AEGP_CompH> parentCompH = std::get<CompPtr>(SessionManager::GetInstance().getSession(parentComp.getSessionID()));
		float dur = boost::get<float>(cmd.args[4]);
		auto& message = enqueueSyncTask(CreateSolidInComp, name, dimensions.width, dimensions.height, color.r, color.g, color.b, color.a, parentCompH, dur);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void CreateCameraInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		dimensionsH position = boost::get<dimensionsH>(cmd.args[1]);
		CompH parentComp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[2]);
		Result<AEGP_CompH> parentCompH = std::get<CompPtr>(SessionManager::GetInstance().getSession(parentComp.getSessionID()));
		auto& message = enqueueSyncTask(CreateCameraInComp, name, position.width, position.height, parentCompH);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void CreateLightInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		dimensionsH position = boost::get<dimensionsH>(cmd.args[1]);
		CompH parentComp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[2]);
		Result<AEGP_CompH> parentCompH = std::get<CompPtr>(SessionManager::GetInstance().getSession(parentComp.getSessionID()));
		auto& message = enqueueSyncTask(CreateLightInComp, name, position.width, position.height, parentCompH);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetNewCollectionFromCompSelectionCommand::execute() {
// Implement the command logic here
}

void GetCompDisplayStartTimeCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompDisplayStartTime, result);
		message->wait();
		Result<float> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompDisplayStartTimeCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		float startTimeInSeconds = boost::get<float>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompDisplayStartTime, result, startTimeInSeconds);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompDurationCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		float durationInSeconds = boost::get<float>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompDuration, result, durationInSeconds);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void CreateNullInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		CompH parentComp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[1]);
		Result<AEGP_CompH> parentCompH = std::get<CompPtr>(SessionManager::GetInstance().getSession(parentComp.getSessionID()));
		float dur = boost::get<float>(cmd.args[2]);
		auto& message = enqueueSyncTask(CreateNullInComp, name, parentCompH, dur);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompPixelAspectRatioCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		float pixelAspect = boost::get<float>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompPixelAspectRatio, result, pixelAspect);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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
void SetSelectionCommand::execute() {
}

void CreateBoxTextLayerInCompCommand::execute() {
}

void CreateTextLayerInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		CompH parentComp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[1]);
		Result<AEGP_CompH> parentCompH = std::get<CompPtr>(SessionManager::GetInstance().getSession(parentComp.getSessionID()));
		float dur = boost::get<float>(cmd.args[2]);
		auto& message = enqueueSyncTask(CreateTextLayerInComp, parentCompH, dur);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetCompDimensionsCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		dimensionsH dimensions = boost::get<dimensionsH>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompDimensions, result, dimensions.width, dimensions.height);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void DuplicateCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(DuplicateComp, result);
		message->wait();
		Result<AEGP_CompH> result2 = message->getResult();
		CompH comp2(createUUID());
		SessionManager::GetInstance().addSession(result2, comp2.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<CompH>(comp2));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetCompFrameDurationCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompFrameDuration, result);
		message->wait();
		Result<float> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetMostRecentlyUsedCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		auto& message = enqueueSyncTask(GetMostRecentlyUsedComp);
		message->wait();
		Result<AEGP_CompH> result2 = message->getResult();
		CompH comp2(createUUID());
		SessionManager::GetInstance().addSession(result2, comp2.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<CompH>(comp2));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void CreateVectorLayerInCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH parentCompH = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(parentCompH.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(CreateVectorLayerInComp, result);
		message->wait();
		Result<AEGP_LayerH> result2 = message->getResult();
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result2, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetNewCompMarkerStreamCommand::execute() {
    // Implement the command logic here
}

void GetCompDisplayDropFrameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		auto& message = enqueueSyncTask(GetCompDisplayDropFrame, result);
		message->wait();
		Result<bool> result2 = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result2.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetCompDisplayDropFrameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		bool dropFrame = boost::get<bool>(cmd.args[1]);
		auto& message = enqueueSyncTask(SetCompDisplayDropFrame, result, dropFrame);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void ReorderCompSelectionCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		auto compP = SessionManager::GetInstance().getSession(comp.getSessionID());
		Result<AEGP_CompH> result = std::get<CompPtr>(compP);
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		int index = boost::get<int>(cmd.args[1]);
		auto& message = enqueueSyncTask(ReorderCompSelection, result, index);
		message->wait();
		Result<void> result2 = message->getResult();
		if (result2.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

//EFFECT COMMANDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EFFECT COMMANDS

void GetLayerNumEffectsCommand::execute() {
    // Implement the command logic here
}

void GetLayerEffectByIndexCommand::execute() {
    // Implement the command logic here
}

void GetInstalledKeyFromLayerEffectCommand::execute() {
    // Implement the command logic here
}

void GetEffectParamUnionByIndexCommand::execute() {
    // Implement the command logic here
}

void GetEffectFlagsCommand::execute() {
    // Implement the command logic here
}

void SetEffectFlagsCommand::execute() {
    // Implement the command logic here
}

void ReorderEffectCommand::execute() {
    // Implement the command logic here
}

void EffectCallGenericCommand::execute() {
    // Implement the command logic here
}

void DisposeEffectCommand::execute() {
    // Implement the command logic here
}

void ApplyEffectCommand::execute() {
    // Implement the command logic here
}

void DeleteLayerEffectCommand::execute() {
    // Implement the command logic here
}

void GetNumInstalledEffectsCommand::execute() {
    // Implement the command logic here
}

void GetNextInstalledEffectCommand::execute() {
    // Implement the command logic here
}

void GetEffectNameCommand::execute() {
    // Implement the command logic here
}

void GetEffectMatchNameCommand::execute() {
    // Implement the command logic here
}

void GetEffectCategoryCommand::execute() {
    // Implement the command logic here
}

void DuplicateEffectCommand::execute() {
    // Implement the command logic here
}

void NumEffectMaskCommand::execute() {
    // Implement the command logic here
}

void GetEffectMaskIDCommand::execute() {
    // Implement the command logic here
}

void AddEffectMaskCommand::execute() {
    // Implement the command logic here
}

void RemoveEffectMaskCommand::execute() {
    // Implement the command logic here
}

void SetEffectMaskCommand::execute() {
    // Implement the command logic here
}


//FOOTAGE COMMANDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FOOTAGE COMMANDS
void createFootageCommand::execute() {
    // Implement the command logic here
}

void disposeFootageCommand::execute() {
    // Implement the command logic here
}

void addFootageToProjectCommand::execute() {
    // Implement the command logic here
}

void GetItemSolidColorCommand::execute() {
    // Implement the command logic here
}

void SetSolidColorCommand::execute() {
    // Implement the command logic here
}

void SetSolidDimensionsCommand::execute() {
    // Implement the command logic here
}

void GetMainFootageFromItemCommand::execute() {
    // Implement the command logic here
}

void GetProxyFootageFromItemCommand::execute() {
    // Implement the command logic here
}

void GetFootageNumFilesCommand::execute() {
    // Implement the command logic here
}

void GetFootagePathCommand::execute() {
    // Implement the command logic here
}

void GetFootageSignatureCommand::execute() {
    // Implement the command logic here
}

void SetItemProxyFootageCommand::execute() {
    // Implement the command logic here
}

void ReplaceItemMainFootageCommand::execute() {
    // Implement the command logic here
}

void SetFootageInterpretationCommand::execute() {
    // Implement the command logic here
}

void GetFootageInterpretationCommand::execute() {
    // Implement the command logic here
}

void GetFootageLayerKeyCommand::execute() {
    // Implement the command logic here
}

void NewPlaceholderFootageCommand::execute() {
    // Implement the command logic here
}

void NewPlaceholderFootageWithPathCommand::execute() {
    // Implement the command logic here
}

void NewSolidFootageCommand::execute() {
    // Implement the command logic here
}

void GetFootageSoundDataFormatCommand::execute() {
    // Implement the command logic here
}

void GetFootageSequenceImportOptionsCommand::execute() {
    // Implement the command logic here
}


// ITEM COMMANDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ITEM COMMANDS
void getUniqueItemIDCommand::execute() {
    // Implement the command logic here
}

void createFolderItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		std::string name = boost::get<std::string>(cmd.args[0]);
		ItemH parentFolder = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[1]);
		Result<AEGP_ItemH> parentFolderH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(parentFolder.getSessionID()));
		auto& message = enqueueSyncTask(createFolderItem, name, parentFolderH);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		ItemH item(createUUID());
		SessionManager::GetInstance().addSession(result, item.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetFirstProjItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();	
	try {
		ProjectH proj = *boost::get<boost::shared_ptr<ProjectH>>(cmd.args[0]);
		Result<AEGP_ProjectH> projH = std::get<ProjectPtr>(SessionManager::GetInstance().getSession(proj.getSessionID()));
		auto& message = enqueueSyncTask(GetFirstProjItem, projH);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		ItemH item(createUUID());
		SessionManager::GetInstance().addSession(result, item.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}


void GetNextProjItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try{
		ProjectH proj = *boost::get<boost::shared_ptr<ProjectH>>(cmd.args[0]);
		ItemH currentItem = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[1]);
		Result<AEGP_ProjectH> projH = std::get<ProjectPtr>(SessionManager::GetInstance().getSession(proj.getSessionID()));
		Result<AEGP_ItemH> currentItemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(currentItem.getSessionID()));
		auto& message = enqueueSyncTask(GetNextProjItem, projH, currentItemH);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		ItemH item(createUUID());
		SessionManager::GetInstance().addSession(result, item.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void IsItemSelectedCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(IsItemSelected, itemH);
		message->wait();
		Result<bool> result = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SelectItemCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		bool selectItem = boost::get<bool>(cmd.args[1]);
		bool deselectOthers = boost::get<bool>(cmd.args[2]);
		auto& message = enqueueSyncTask(SelectItem, itemH, selectItem, deselectOthers);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetItemFlagsCommand::execute() {
    // Implement the command logic here
}

void GetCompItemCurrentTimeCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		float frameRate = boost::get<float>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetCompItemCurrentTime, itemH, frameRate);
		message->wait();
		Result<float> result = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}



void SetCompItemCurrentTimeCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		float time = boost::get<float>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		//auto& message = enqueueSyncTask(SetCompItemCurrentTime, itemH, time);
		//message->wait();
		//Result<void> result = message->getResult();
		//if (result.error != A_Err_NONE) {
		//	throw AEException(result.error);
		//}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetItemUseProxyCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		bool useProxy = boost::get<bool>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(SetItemUseProxy, itemH, useProxy);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetItemParentFolderCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemParentFolder, itemH);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		ItemH item2(createUUID());
		SessionManager::GetInstance().addSession(result, item2.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item2));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetItemParentFolderCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		ItemH parentFolder = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		Result<AEGP_ItemH> parentFolderH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(parentFolder.getSessionID()));
		auto& message = enqueueSyncTask(SetItemParentFolder, itemH, parentFolderH);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemDurationCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemDuration, itemH);
		message->wait();
		Result<float> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemCurrentTimeCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemCurrentTime, itemH);
		message->wait();
		Result<float> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemDimensionsCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemDimensions, itemH);
		message->wait();
		Result<size> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		dimensionsH dimensions;
		dimensions.width = result.value.width;
		dimensions.height = result.value.height;
		response.args.push_back(dimensions);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemPixelAspectRatioCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemPixelAspectRatio, itemH);
		message->wait();
		Result<float> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void DeleteItemCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(DeleteItem, itemH);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetItemCurrentTimeCommand::execute() {
}

void GetItemCommentCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemComment, itemH);
		message->wait();
		Result<std::string> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetItemCommentCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		std::string comment = boost::get<std::string>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(SetItemComment, itemH, comment);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemLabelCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemLabel, itemH);
		message->wait();
		Result<AEGP_LabelID> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetItemLabelCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		A_long label = boost::get<A_long>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(SetItemLabel, itemH, label);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetItemMRUViewCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		auto& message = enqueueSyncTask(GetItemMRUView, itemH);
		message->wait();
		Result<AEGP_ItemViewP> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
	
		Response response;
		response.sessionID = cmd.sessionID;
		//response.args.push_back(boost::make_shared<StreamRefH>(streamRef));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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


// LAYER COMMANDS ----~~~~~~~~~~~~~~------------------~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LAYER COMMANDS
void getNumLayersCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		Result<AEGP_CompH> compH = std::get<CompPtr>(SessionManager::GetInstance().getSession(comp.getSessionID()));
		auto& message = enqueueSyncTask(getNumLayers, compH);
		message->wait();
		Result<A_long> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getLayerIndexCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(getLayerIndex, layerH);
		message->wait();
		Result<A_long> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getLayerNameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(getLayerName, layerH);
		message->wait();
		Result<std::string> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getLayerSourceNameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(getLayerSourceName, layerH);
		message->wait();
		Result<std::string> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void setLayerNameCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(setLayerName, layerH, name);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void getLayerFromCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[0]);
		A_long index = boost::get<A_long>(cmd.args[1]);
		Result<AEGP_CompH> compH = std::get<CompPtr>(SessionManager::GetInstance().getSession(comp.getSessionID()));
		auto& message = enqueueSyncTask(getLayerFromComp, compH, index);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void changeLayerIndexCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		A_long newIndex = boost::get<A_long>(cmd.args[1]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(changeLayerIndex, layerH, newIndex);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void isAddLayerValidCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		Result<AEGP_CompH> compH = std::get<CompPtr>(SessionManager::GetInstance().getSession(comp.getSessionID()));
		auto& message = enqueueSyncTask(isAddLayerValid, itemH, compH);
		message->wait();
		Result<bool> result = message->getResult();
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void AddLayerCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		ItemH item = *boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
		CompH comp = *boost::get<boost::shared_ptr<CompH>>(cmd.args[1]);
		Result<AEGP_ItemH> itemH = std::get<ItemPtr>(SessionManager::GetInstance().getSession(item.getSessionID()));
		Result<AEGP_CompH> compH = std::get<CompPtr>(SessionManager::GetInstance().getSession(comp.getSessionID()));
		auto& message = enqueueSyncTask(AddLayer, itemH, compH);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		LayerH layer(createUUID());
		SessionManager::GetInstance().addSession(result, layer.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void getLayerSourceItemCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(getLayerSourceItem, layerH);
		message->wait();
		Result<AEGP_ItemH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		ItemH item(createUUID());
		SessionManager::GetInstance().addSession(result, item.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<ItemH>(item));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetLayerSourceItemIDCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerSourceItemID, layerH);
		message->wait();
		Result<int> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetLayerParentCompCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerParentComp, layerH);
		message->wait();
		Result<AEGP_CompH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		CompH comp(createUUID());
		SessionManager::GetInstance().addSession(result, comp.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<CompH>(comp));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetLayerQualityCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerQuality, layerH);
		message->wait();
		Result<std::string> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetLayerQualityCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		int quality = boost::get<int>(cmd.args[1]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(SetLayerQuality, layerH, quality);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetLayerFlagsCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerFlags, layerH);
		message->wait();
		Result<AEGP_LayerFlags> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;

	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetLayerFlagCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		// flag = boost::get<A_long>(cmd.args[1]);
		//Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		//auto& message = enqueueSyncTask(SetLayerFlag, layerH, flag);
		//message->wait();
		//Result<void> result = message->getResult();
		//if (result.error != A_Err_NONE) {
//throw AEException(result.error);
		//}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void IsLayerVideoReallyOnCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(IsLayerVideoReallyOn, layerH);
		message->wait();
		Result<bool> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void IsLayerAudioReallyOnCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
	try {
LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(IsLayerAudioReallyOn, layerH);
		message->wait();
		Result<bool> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void GetLayerCurrentTimeCommand::execute() {
}

void GetLayerInPointCommand::execute() {
    // Implement the command logic here
}

void GetLayerDurationCommand::execute() {
    // Implement the command logic here
}

void SetLayerInPointAndDurationCommand::execute() {
    // Implement the command logic here
}

void GetLayerOffsetCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerOffset, layerH);
		message->wait();
		Result<float> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void SetLayerOffsetCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		float offset = boost::get<float>(cmd.args[1]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		//auto& message = enqueueSyncTask(SetLayerOffset, layerH, offset);
		//message->wait();
		//Result<void> result = message->getResult();
		//if (result.error != A_Err_NONE) {
		//	throw AEException(result.error);
		//}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetLayerStretchCommand::execute() {
    // Implement the command logic here
}

void SetLayerStretchCommand::execute() {
    // Implement the command logic here
}

void GetLayerTransferModeCommand::execute() {
    // Implement the command logic here
}

void SetLayerTransferModeCommand::execute() {
    // Implement the command logic here
}

void GetLayerMaskedBoundsCommand::execute() {
    // Implement the command logic here
}

void GetLayerObjectTypeCommand::execute() {
    // Implement the command logic here
}

void IsLayer3DCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(IsLayer3D, layerH);
		message->wait();
		Result<A_Boolean> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void IsLayer2DCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(IsLayer2D, layerH);
		message->wait();
		Result<A_Boolean> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}

void IsVideoActiveCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		//auto& message = enqueueSyncTask(IsVideoActive, layerH);
		//message->wait();
		//Result<bool> result = message->getResult();
		//if (result.error != A_Err_NONE) {
		//	throw AEException(result.error);
		//}
		Response response;
		response.sessionID = cmd.sessionID;
		//response.args.push_back(result.value);
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (const std::exception& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
	}
	catch (...) {
		mqm.sendErrorResponse(cmd.sessionID, "Unknown error");
	}
}


void IsLayerUsedAsTrackMatteCommand::execute() {
    // Implement the command logic here
}

void DoesLayerHaveTrackMatteCommand::execute() {
    // Implement the command logic here
}

void ConvertCompToLayerTimeCommand::execute() {
    // Implement the command logic here
}

void ConvertLayerToCompTimeCommand::execute() {
    // Implement the command logic here
}

void GetLayerDancingRandValueCommand::execute() {
    // Implement the command logic here
}

void GetLayerIDCommand::execute() {
    // Implement the command logic here
}

void GetLayerFromLayerIDCommand::execute() {
    // Implement the command logic here
}

void GetLayerLabelCommand::execute() {
    // Implement the command logic here
}

void SetLayerLabelCommand::execute() {
    // Implement the command logic here
}

void GetLayerSamplingQualityCommand::execute() {
    // Implement the command logic here
}

void SetLayerSamplingQualityCommand::execute() {
    // Implement the command logic here
}

void GetTrackMatteLayerCommand::execute() {
    // Implement the command logic here
}

void SetTrackMatteCommand::execute() {
    // Implement the command logic here
}

void RemoveTrackMatteCommand::execute() {
    // Implement the command logic here
}

void DeleteLayerCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(DeleteLayer, layerH);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void DuplicateLayerCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(DuplicateLayer, layerH);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		LayerH layer2(createUUID());
		SessionManager::GetInstance().addSession(result, layer2.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer2));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void GetLayerParentCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		auto& message = enqueueSyncTask(GetLayerParent, layerH);
		message->wait();
		Result<AEGP_LayerH> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		LayerH layer2(createUUID());
		SessionManager::GetInstance().addSession(result, layer2.getSessionID());
		Response response;
		response.sessionID = cmd.sessionID;
		response.args.push_back(boost::make_shared<LayerH>(layer2));
		mqm.sendResponse(response);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

void SetLayerParentCommand::execute() {
auto& mqm = MessageQueueManager::getInstance();
	try {
		LayerH layer = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[0]);
		LayerH parent = *boost::get<boost::shared_ptr<LayerH>>(cmd.args[1]);
		Result<AEGP_LayerH> layerH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(layer.getSessionID()));
		Result<AEGP_LayerH> parentH = std::get<LayerPtr>(SessionManager::GetInstance().getSession(parent.getSessionID()));
		auto& message = enqueueSyncTask(SetLayerParent, layerH, parentH);
		message->wait();
		Result<void> result = message->getResult();
		if (result.error != A_Err_NONE) {
			throw AEException(result.error);
		}
		mqm.sendEmptyResponse(cmd.sessionID);
	}
	catch (const AEException& e) {
		mqm.sendErrorResponse(cmd.sessionID, e.what());
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

// MARKER COMMANDS

void NewMarkerCommand::execute() {
    // Implement the command logic here
}

void DisposeMarkerCommand::execute() {
    // Implement the command logic here
}

void DuplicateMarkerCommand::execute() {
    // Implement the command logic here
}


// PANEL COMMANDS
void setPanelTitleCommand::execute() {
    // Implement the command logic here
}

void togglePanelVisibilityCommand::execute() {
    // Implement the command logic here
}

void isPanelShownCommand::execute() {
    // Implement the command logic here
}

// PROJECT COMMANDS

void executecmdCommand::execute() {
    // Implement the command logic here
}

void GetProjectNameCommand::execute() {
    // Implement the command logic here
}

void GetProjectPathCommand::execute() {
    // Implement the command logic here
}

void SaveProjectToPathCommand::execute() {
    // Implement the command logic here
}

void GetProjectTimeDisplayCommand::execute() {
    // Implement the command logic here
}

void SetProjectTimeDisplay2Command::execute() {
    // Implement the command logic here
}

void IsProjectDirtyCommand::execute() {
    // Implement the command logic here
}

void SaveProjectAsCommand::execute() {
    // Implement the command logic here
}

void NewProjectCommand::execute() {
    // Implement the command logic here
}

void OpenProjectFromPathCommand::execute() {
    // Implement the command logic here
}

void GetProjectBitDepthCommand::execute() {
    // Implement the command logic here
}

void SetProjectBitDepthCommand::execute() {
    // Implement the command logic here
}

void getProjectRootFolderCommand::execute() {
    // Implement the command logic here
}

// RENDER COMMANDS
void getRenderOptionsCommand::execute() {
    // Implement the command logic here
}

void setTimeCommand::execute() {
    // Implement the command logic here
}

void getWorldTypeCommand::execute() {
    // Implement the command logic here
}

void disposeRenderOptionsCommand::execute() {
    // Implement the command logic here
}

void renderAndCheckoutFrameCommand::execute() {
    // Implement the command logic here
}

void getReceiptWorldCommand::execute() {
    // Implement the command logic here
}

void checkinFrameCommand::execute() {
    // Implement the command logic here
}

void getPluginPathsCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        auto& message = enqueueSyncTask(getPluginPaths);
        message->wait();
        Result<std::string> result = message->getResult();
        if (result.error != A_Err_NONE) {
			Response response(cmd.sessionID, result.error);
			mqm.sendResponse(response);
		}
        Response response;
        response.sessionID = cmd.sessionID;
        response.args.push_back(result.value);
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

void getBaseAddr8Command::execute() {
    // Implement the command logic here
}

void getSizeCommand::execute() {
    // Implement the command logic here
}

void getItemNameCommand::execute() {
    auto& mqm = MessageQueueManager::getInstance();
    try {
        boost::shared_ptr<ItemH> item = boost::get<boost::shared_ptr<ItemH>>(cmd.args[0]);
        auto itemP = SessionManager::GetInstance().getSession(item->getSessionID());
        Result<AEGP_ItemH> result = std::get<ItemPtr>(itemP);
        if (result.error != A_Err_NONE) {
            Response response(cmd.sessionID, result.error);
            mqm.sendResponse(response);
        }
        auto& message = enqueueSyncTask(getItemName, result);
        message->wait();
        Result<std::string> result2 = message->getResult();
        if (result2.error != A_Err_NONE) {
            Response response(cmd.sessionID, result2.error);
            mqm.sendResponse(response);
        }
        Response response;
        response.sessionID = cmd.sessionID;
        response.args.push_back(result2.value);
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