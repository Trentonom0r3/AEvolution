#pragma once
#include "..\..\AEvolutionPlugin\src\MessageMain.h"

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

    void sendCommand(const boost::shared_ptr<Command>& command) {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa << command; // Serialize the boost::shared_ptr<Command>
        std::string serializedCommand = ss.str();
        commandQueue->send(serializedCommand.data(), serializedCommand.size(), 0);
    }


    bool tryReceiveResponse(boost::shared_ptr<Response>& response) {
        boost::interprocess::message_queue::size_type recvd_size;
        unsigned int priority;
        std::size_t max_msg_size = responseQueue->get_max_msg_size();
        std::vector<char> buffer(max_msg_size);
        if (responseQueue->timed_receive(buffer.data(), buffer.size(), recvd_size, priority,
            boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(100))) {
            std::string serializedResponse(buffer.begin(), buffer.begin() + recvd_size);
            std::stringstream ss(serializedResponse);
            boost::archive::text_iarchive ia(ss);
            ia >> response; // Deserialize directly into a boost::shared_ptr<Response>
            return true;
        }
        return false;
    }


    boost::shared_ptr<Response> waitForResponse() {
        const std::chrono::milliseconds timeoutDuration(5000); // 5-second timeout
        auto start = std::chrono::steady_clock::now();
        boost::shared_ptr<Response> resp;

        while (!tryReceiveResponse(resp)) {
            if (std::chrono::steady_clock::now() - start > timeoutDuration) {
                throw std::runtime_error("Timeout exceeded while waiting for response");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        return resp;
    }


    boost::shared_ptr<Response> sendAndReceive(const boost::shared_ptr<Command>& command) {
        sendCommand(command);
        return waitForResponse();
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