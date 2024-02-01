#pragma once
#include "PyUtils/MessageManager.h"
#include "Commands.h"
#include "Library.h"

typedef Result<AEGP_ItemH> ItemPtr;
typedef Result<AEGP_CompH> CompPtr;
typedef Result<AEGP_LayerH> LayerPtr;
typedef Result<AEGP_ProjectH> ProjectPtr;

typedef std::variant<ItemPtr, CompPtr, LayerPtr, ProjectPtr> SessionObject;

typedef std::map<std::string, SessionObject> Sessions;

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

    void addSession(SessionObject session, const std::string& sessionID) {
		sessions[sessionID] = session;
	}

    SessionObject getSession(const std::string& sessionID) {
        return sessions[sessionID];
        }

    void cleanAll() {
		sessions.clear();
	}

protected:
    Sessions sessions;

    void handleMessageQueue() {
        auto& mqm = MessageQueueManager::getInstance();
        CommandFactory commandFactory;

        while (true) {
            Command receivedCmd;
            if (mqm.tryReceiveCommand(receivedCmd)) {
                // Process the command
                auto cmd = commandFactory.createCommand(receivedCmd.name, receivedCmd);
                if (cmd) {
                    cmd->execute();
                }
                else {
                    std::cout << "Command not found: " << receivedCmd.name << std::endl;
                }
            }
            else {
                // No command received, sleep for a bit
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

};
