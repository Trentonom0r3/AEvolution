#pragma once
#include "MessageQueueManager.h"
#include "commands.h"
#include <queue>


class SessionManager {
public:
    static SessionManager& GetInstance() {
        static SessionManager instance;
        return instance;
    }

    SessionManager() {
        //commandQueue.empty();
        std::thread t(&SessionManager::handleMessageQueue, this);
        t.detach();
    }

    SessionManager(const SessionManager&) = delete;
    void operator=(const SessionManager&) = delete;

    void cleanAll() {
        std::lock_guard<std::mutex> lock(commandQueueMutex);
        //commandQueue.empty();
    }

    bool areCommandsAvailable() {
		std::lock_guard<std::mutex> lock(commandQueueMutex);
        if (!commandQueue.empty()) {
			return true;
		}
        return false;
	}

    // Adjust popCommand to match the new queue type
    boost::shared_ptr<Command> popCommand() {
        std::lock_guard<std::mutex> lock(commandQueueMutex);
        if (!commandQueue.empty()) {
            boost::shared_ptr<Command> cmd = std::move(commandQueue.front()); // Explicit type instead of auto
            commandQueue.pop();
            return cmd;
        }
        return nullptr;
    }

protected:
    std::mutex commandQueueMutex;
    std::queue<boost::shared_ptr<Command>> commandQueue;


    void handleMessageQueue() {
        auto& mqm = MessageQueueManager::getInstance();

        while (true) {
            boost::shared_ptr<Command> receivedCmd;
            if (mqm.tryReceiveCommand(receivedCmd)) {
                std::lock_guard<std::mutex> lock(commandQueueMutex);
                commandQueue.push(std::move(receivedCmd));
                AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
                suites.UtilitySuite6()->AEGP_CauseIdleRoutinesToBeCalled();
            }
            else {
                // No command received, sleep for a bit
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }


};
