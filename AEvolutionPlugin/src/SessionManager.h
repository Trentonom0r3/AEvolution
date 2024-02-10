#pragma once
#include "CommandFactory.h"
#include <queue>

typedef std::variant<AEGP_ItemH, AEGP_CompH, AEGP_FootageH, AEGP_LayerH, AEGP_ProjectH, AEGP_Collection2H, AEGP_CollectionItemV2,
                     AEGP_LayerCollectionItem, AEGP_MaskCollectionItem, AEGP_EffectCollectionItem, AEGP_StreamCollectionItem,
                     AEGP_MaskStreamCollectionItem, AEGP_LayerStreamCollectionItem, AEGP_EffectStreamCollectionItem,
                     AEGP_KeyframeCollectionItem, AEGP_MaskVertexCollectionItem, AEGP_StreamRefH> SessionObject;

typedef std::map<int, SessionObject> Sessions;

class SessionManager {
public:
    static SessionManager& GetInstance() {
        static SessionManager instance;
        return instance;
    }

    SessionManager() {
        sessions.clear();
        std::thread t(&SessionManager::handleMessageQueue, this);
        t.detach();
    }

    SessionManager(const SessionManager&) = delete;
    void operator=(const SessionManager&) = delete;

    void addSession(SessionObject session, int sessionID) {
        std::lock_guard<std::mutex> lock(sessionListMutex);
        //make sure the sessionID is unique, if it isn't return early
        for (auto& s : sessions) {
            if (s.first == sessionID) {
				return;
			}
		}
        sessions[sessionID] = std::move(session);
    }

    SessionObject getSession(int sessionID) {
        std::lock_guard<std::mutex> lock(sessionListMutex);
		return sessions[sessionID];
    }

    void cleanAll() {
        std::lock_guard<std::mutex> lock(sessionListMutex);
        sessions.clear();
    }

    bool areCommandsAvailable() {
		std::lock_guard<std::mutex> lock(commandQueueMutex);
        if (!commandQueue.empty()) {
			return true;
		}
        return false;
	}

    // Adjust popCommand to match the new queue type
    std::unique_ptr<CommandBase> popCommand() {
        std::lock_guard<std::mutex> lock(commandQueueMutex);
        if (!commandQueue.empty()) {
            std::unique_ptr<CommandBase> cmd = std::move(commandQueue.front()); // Explicit type instead of auto
            commandQueue.pop();
            return cmd;
        }
        return nullptr;
    }

    void removeSession(int sessionID) {
		std::lock_guard<std::mutex> lock(sessionListMutex);
		sessions.erase(sessionID);
	}

protected:
    std::mutex sessionListMutex;
    Sessions sessions;
    std::mutex commandQueueMutex;
    std::queue<std::unique_ptr<CommandBase>> commandQueue;


    void handleMessageQueue() {
        auto& mqm = MessageQueueManager::getInstance();
        auto& factory = CommandFactory::get();

        while (true) {
            Command receivedCmd;
            if (mqm.tryReceiveCommand(receivedCmd)) {
                // Try to create the command object from the received command name
                auto cmd = factory.createCommand(receivedCmd.id, receivedCmd);
                if (cmd) {
                    std::lock_guard<std::mutex> lock(commandQueueMutex);
                    // Queue the created command object for execution
                    commandQueue.push(std::move(cmd));

                    AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
                    suites.UtilitySuite6()->AEGP_CauseIdleRoutinesToBeCalled();
                }
                else {
                    std::cout << "Command not found: " << std::endl;
                }
            }
            else {
                // No command received, sleep for a bit
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }


};
