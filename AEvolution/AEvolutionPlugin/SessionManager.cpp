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

void EndUndoGroupCommand::execute() {
	auto& mqm = MessageQueueManager::getInstance();
    try {
    	auto& message = enqueueSyncTask(EndUndoGroup);
		message->wait();
		Result<void> result = message->getResult();
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
            mqm.sendErrorResponse(cmd.sessionID, errToString(result2.error));
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
    // Implement the command logic here
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
void getUniqueItemIDCommand::execute() {
    // Implement the command logic here
}

void createFolderItemCommand::execute() {
    // Implement the command logic here
}

void GetFirstProjItemCommand::execute() {
    // Implement the command logic here
}

void GetNextProjItemCommand::execute() {
    // Implement the command logic here
}

void IsItemSelectedCommand::execute() {
    // Implement the command logic here
}

void SelectItemCommand::execute() {
    // Implement the command logic here
}

void GetItemFlagsCommand::execute() {
    // Implement the command logic here
}

void GetCompItemCurrentTimeCommand::execute() {
    // Implement the command logic here
}

void SetCompItemCurrentTimeCommand::execute() {
    // Implement the command logic here
}

void SetItemUseProxyCommand::execute() {
    // Implement the command logic here
}

void GetItemParentFolderCommand::execute() {
    // Implement the command logic here
}

void SetItemParentFolderCommand::execute() {
    // Implement the command logic here
}

void GetItemDurationCommand::execute() {
    // Implement the command logic here
}

void GetItemCurrentTimeCommand::execute() {
    // Implement the command logic here
}

void GetItemDimensionsCommand::execute() {
    // Implement the command logic here
}

void GetItemPixelAspectRatioCommand::execute() {
    // Implement the command logic here
}

void DeleteItemCommand::execute() {
    // Implement the command logic here
}

void SetItemCurrentTimeCommand::execute() {
    // Implement the command logic here
}

void GetItemCommentCommand::execute() {
    // Implement the command logic here
}

void SetItemCommentCommand::execute() {
    // Implement the command logic here
}

void GetItemLabelCommand::execute() {
    // Implement the command logic here
}

void SetItemLabelCommand::execute() {
    // Implement the command logic here
}

void GetItemMRUViewCommand::execute() {
    // Implement the command logic here
}


// LAYER COMMANDS
void getNumLayersCommand::execute() {
    // Implement the command logic here
}

void getLayerIndexCommand::execute() {
    // Implement the command logic here
}

void getLayerNameCommand::execute() {
    // Implement the command logic here
}

void getLayerSourceNameCommand::execute() {
    // Implement the command logic here
}

void setLayerNameCommand::execute() {
    // Implement the command logic here
}

void getLayerFromCompCommand::execute() {
    // Implement the command logic here
}

void changeLayerIndexCommand::execute() {
    // Implement the command logic here
}

void isAddLayerValidCommand::execute() {
    // Implement the command logic here
}

void AddLayerCommand::execute() {
    // Implement the command logic here
}

void getLayerSourceItemCommand::execute() {
    // Implement the command logic here
}

void GetLayerSourceItemIDCommand::execute() {
    // Implement the command logic here
}

void GetLayerParentCompCommand::execute() {
    // Implement the command logic here
}

void GetLayerQualityCommand::execute() {
    // Implement the command logic here
}

void SetLayerQualityCommand::execute() {
    // Implement the command logic here
}

void GetLayerFlagsCommand::execute() {
    // Implement the command logic here
}

void SetLayerFlagCommand::execute() {
    // Implement the command logic here
}

void IsLayerVideoReallyOnCommand::execute() {
    // Implement the command logic here
}

void IsLayerAudioReallyOnCommand::execute() {
    // Implement the command logic here
}

void GetLayerCurrentTimeCommand::execute() {
    // Implement the command logic here
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
    // Implement the command logic here
}

void SetLayerOffsetCommand::execute() {
    // Implement the command logic here
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
    // Implement the command logic here
}

void IsLayer2DCommand::execute() {
    // Implement the command logic here
}

void IsVideoActiveCommand::execute() {
    // Implement the command logic here
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
    // Implement the command logic here
}

void DuplicateLayerCommand::execute() {
    // Implement the command logic here
}

void GetLayerParentCommand::execute() {
    // Implement the command logic here
}

void SetLayerParentCommand::execute() {
    // Implement the command logic here
}

void NewMarkerCommand::execute() {
    // Implement the command logic here
}

void DisposeMarkerCommand::execute() {
    // Implement the command logic here
}

void DuplicateMarkerCommand::execute() {
    // Implement the command logic here
}

void setPanelTitleCommand::execute() {
    // Implement the command logic here
}

void togglePanelVisibilityCommand::execute() {
    // Implement the command logic here
}

void isPanelShownCommand::execute() {
    // Implement the command logic here
}


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