#pragma once
#include "MessageMain.h"

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
            std::cout << "Error: Serialized response is empty" << std::endl;
            return;
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

    void sendErrorResponse(std::string error) {
        Response response;
        sendResponse(response);
    }

    void sendEmptyResponse() {
        Response response;
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