#pragma once
#include "PyUtils/MessageManager.h"
#include "Commands.h"
#include "Library.h"

typedef std::variant<std::monostate, std::shared_ptr<Project>, std::shared_ptr<Item>, std::shared_ptr<ItemCollection>,
        std::shared_ptr<ProjectCollection>, std::shared_ptr<Layer>, std::shared_ptr<LayerCollection>, std::shared_ptr<CompItem>, std::shared_ptr<FolderItem>,
        std::shared_ptr<SolidItem>, std::shared_ptr<FootageItem>> SessionObject;

typedef std::map<std::string, SessionObject> SessionMap;


class SessionManager {
public:
    static SessionManager& GetInstance() {
        static SessionManager instance;
        return instance;
    }

    SessionManager() {
        sessions.clear();
        std::thread messageQueueThread(&SessionManager::handleMessageQueue, this);
        messageQueueThread.detach();
    }



    SessionManager(const SessionManager&) = delete;
    void operator=(const SessionManager&) = delete;

    const SessionObject& getSessionObject(const std::string& sessionID) {
        auto it = sessions.find(sessionID);
        if (it == sessions.end()) {
            throw std::runtime_error("Session ID not found: " + sessionID);
        }

        return it->second;
    }

    bool sessionExists(const std::string& sessionID) {
		auto it = sessions.find(sessionID);
        if (it == sessions.end()) {
			return false;
		}
		return true;
	}

    void addToSessions(const std::string& sessionID, const SessionObject& sessionObject) {
		sessions[sessionID] = sessionObject;
	}

    void removeFromSessions(const std::string& sessionID) {
		sessions.erase(sessionID);
	}

    void cleanAll() {
		sessions.clear();
	}

protected:
    SessionMap sessions;

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
