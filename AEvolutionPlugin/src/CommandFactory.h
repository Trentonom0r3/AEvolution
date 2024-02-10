#pragma once
#include "MessageQueueManager.h"
#include "SuitesManager.h"

class CommandBase {
public:
    CommandBase() = default;
    explicit CommandBase(Command cmd) : cmd(std::move(cmd)) {}
    virtual void execute() = 0;
    virtual ~CommandBase() = default;

    Command cmd;
};

class CommandFactory {
public:
    using CreatorFunc = std::function<std::unique_ptr<CommandBase>(Command)>;

    static CommandFactory& get() {
        static CommandFactory instance;
        return instance;
    }

    // Use CommandID for registration
    void registerCommand(CommandID id, CreatorFunc creator) {
        creators[id] = std::move(creator);
    }

    // Use CommandID to create a command
    std::unique_ptr<CommandBase> createCommand(CommandID id, Command cmd) {
        auto it = creators.find(id);
        if (it != creators.end()) {
            return it->second(std::move(cmd));
        }
        return nullptr;
    }

private:
    // Map using CommandID as the key
    std::unordered_map<CommandID, CreatorFunc> creators;
    CommandFactory() = default;
};

#define REGISTER_COMMAND(ID, TYPE) \
static bool _reg_##TYPE = []() -> bool { \
    CommandFactory::get().registerCommand(ID, [](Command cmd) -> std::unique_ptr<CommandBase> { \
        auto command = std::make_unique<TYPE>(std::move(cmd)); \
        return command; \
    }); \
    return true; \
}();
