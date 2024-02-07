#pragma once
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include "../UUID.hpp"
#include "../CoreLib/CoreUtils.h"

std::string createUUID();

typedef boost::variant<int, float, std::string, bool, std::vector<std::string>, boost::shared_ptr<ItemH>,
    boost::shared_ptr<CompH>, boost::shared_ptr<LayerH>, boost::shared_ptr<ProjectH>, boost::shared_ptr<StreamRefH>,
    boost::shared_ptr<FootageH>, dimensionsH, colorH> CommandArg;

typedef std::vector<CommandArg> CommandArgs;


struct Command {
    std::string sessionID = "0";
    std::string name = "name";
    CommandArgs args; // Vector of arguments
    Command() = default;
    Command(std::string sessionID, std::string name, CommandArgs args) : sessionID(sessionID), name(name), args(args) {};
    Command(std::string sessionID, std::string name, CommandArg arg) : sessionID(sessionID), name(name) {
        args.push_back(arg);
    }
    Command(std::string sessionID, std::string name) : sessionID(sessionID), name(name) {};
    Command(std::string sessionID, CommandArgs args) : sessionID(sessionID), args(args) {};

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& sessionID;
        ar& name;
        ar& args;
    }
};


struct Response {
    std::string sessionID = "0";
    CommandArgs args; // Vector of arguments
    std::string error = "";
    Response() = default;
    Response(std::string sessionID, CommandArgs args, std::string error) : sessionID(sessionID), args(args), error(error) {};
    Response(std::string sessionID, CommandArg arg) : sessionID(sessionID) {
		args.push_back(arg);
	}
    Response(std::string sessionID, std::string error) : sessionID(sessionID), error(error) {};
    Response(std::string sessionID, CommandArgs args) : sessionID(sessionID), args(args) {};
    //serialize method
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& sessionID;
        ar& args;
        ar& error;
    }
};      // Response to be sent to the client


class MessageQueueManager {
public:
    // Deletes copy constructor and assignment operator
    MessageQueueManager(const MessageQueueManager&) = delete;
    MessageQueueManager& operator=(const MessageQueueManager&) = delete;

    // Static method to get the instance of the class
    static MessageQueueManager& getInstance() {
        static MessageQueueManager instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }
 

    void clearQueues() {
		clearQueue("PyC21");
		clearQueue("PyR21");
	}

    Command receiveCommand() {
        boost::interprocess::message_queue::size_type recvd_size;
        unsigned int priority;
        std::size_t max_msg_size = commandQueue->get_max_msg_size();
        std::vector<char> buffer(max_msg_size);
        commandQueue->receive(buffer.data(), buffer.size(), recvd_size, priority);
        std::string serializedCommand(buffer.begin(), buffer.begin() + recvd_size);
        std::stringstream ss(serializedCommand);
        boost::archive::text_iarchive ia(ss);
        Command command;
        ia >> command;
        return command;
    }

    void sendResponse(Response response) {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa << response;
        std::string serializedResponse = ss.str();
        if (serializedResponse.empty()) {
			std::cout << "Empty response" << std::endl;
            throw std::runtime_error("Empty response");
		}
        responseQueue->send(serializedResponse.c_str(), serializedResponse.size(), 0);
    }

    // In MessageQueueManager
    bool tryReceiveCommand(Command& command) {
        boost::interprocess::message_queue::size_type recvd_size;
        unsigned int priority;
        std::size_t max_msg_size = commandQueue->get_max_msg_size();
        std::vector<char> buffer(max_msg_size);
        if (commandQueue->timed_receive(buffer.data(), buffer.size(), recvd_size, priority,
            boost::posix_time::microsec_clock::universal_time() +
            boost::posix_time::milliseconds(100))) {
            std::string serializedCommand(buffer.begin(), buffer.begin() + recvd_size);
            std::stringstream ss(serializedCommand);
            boost::archive::text_iarchive ia(ss);
            ia >> command;
            return true;
        }
        return false;
    }

    void sendErrorResponse(std::string sessionID, std::string error) {
		Response response;
		response.sessionID = sessionID;
		response.error = error;
		sendResponse(response);
	}

    void sendEmptyResponse(std::string sessionID) {
        Response response;
        response.sessionID = sessionID;
        response.error = "";
        sendResponse(response);
    }


private:
    MessageQueueManager() {
        clearQueue("PyC21");
        clearQueue("PyR21");
        // Using smart pointers for automatic resource management
        commandQueue = std::make_unique<boost::interprocess::message_queue>(
            boost::interprocess::create_only, "PyC21", 100, 1024);
        responseQueue = std::make_unique<boost::interprocess::message_queue>(
            boost::interprocess::create_only, "PyR21", 100, 1024);
    }

    std::unique_ptr<boost::interprocess::message_queue> commandQueue;
    std::unique_ptr<boost::interprocess::message_queue> responseQueue;
    void clearQueue(const char* queueName) {
        if (boost::interprocess::message_queue::remove(queueName)) {
            std::cout << "Cleared existing queue: " << queueName << std::endl;
        }
    }


};