#pragma once
#ifdef AEvolution_EXPORTS
#define AEvolution_API __declspec(dllexport)
#else
#define AEvolution_API __declspec(dllimport)
#endif

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
#include <memory>
#include <vector>
#include "UUID.hpp"
#include "Core.h"

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

    void sendCommand(Command command) {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa << command;
        std::string serializedCommand = ss.str();
        commandQueue->send(serializedCommand.c_str(), serializedCommand.size(), 0);
    }

    bool tryReceiveResponse(Response& response) {
        boost::interprocess::message_queue::size_type recvd_size;
        unsigned int priority;
        std::size_t max_msg_size = responseQueue->get_max_msg_size();
        std::vector<char> buffer(max_msg_size);
        if (responseQueue->timed_receive(buffer.data(), buffer.size(), recvd_size, priority,
            boost::posix_time::microsec_clock::universal_time() +
            boost::posix_time::milliseconds(100))) {
            std::string serializedResponse(buffer.begin(), buffer.begin() + recvd_size);
            std::stringstream ss(serializedResponse);
            boost::archive::text_iarchive ia(ss);
           ia >> response;
            return true;
        }
        return false;
    }

    Response waitForResponse() {
        const std::chrono::milliseconds timeoutDuration(5000); // 5 seconds timeout
        auto start = std::chrono::steady_clock::now();
        Response resp;

        while (!tryReceiveResponse(resp)) {
            if (std::chrono::steady_clock::now() - start > timeoutDuration) {
                throw std::runtime_error("Timeout exceeded while waiting for response");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        return resp;
    }

private:
    MessageQueueManager() {
        // Using smart pointers for automatic resource management
        commandQueue = std::make_unique<boost::interprocess::message_queue>(
            boost::interprocess::open_or_create, "PyC21", 100, 1024);
        responseQueue = std::make_unique<boost::interprocess::message_queue>(
            boost::interprocess::open_or_create, "PyR21", 100, 1024);
    }

    std::unique_ptr<boost::interprocess::message_queue> commandQueue;
    std::unique_ptr<boost::interprocess::message_queue> responseQueue;

};