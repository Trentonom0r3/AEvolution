#pragma once
#include "main.h"
#include "AEnums.h"

using null = NullType;

typedef boost::variant<int, double, std::string, bool, Size,
    Position, Position3D, Color, AETime, Item, Comp, Range,
    Layer, Project, Footage, null, Collection2H, CollectionItemV2, AEGP_ItemType, AEGP_LabelID> CommandArg;

using CommandArg = boost::mp11::mp_apply<boost::variant, commandTypes>;

typedef std::vector<CommandArg> CommandArgs;

struct Command {
    CommandID id;
    CommandArgs args; // Vector of arguments
    Command() = default;
    Command(CommandID id, CommandArgs args) : id(id), args(args) {};
    Command(CommandID id, CommandArg arg) : id(id) {
        args.push_back(arg);
    }
    Command(CommandID id) : id(id) {};
    Command(CommandArgs args) : args(args) {};

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& id;
        ar& args;
    }
};

typedef boost::variant<Result<null>, Result<Collection2H>, Result<CollectionItemV2>, Result<int>, Result<double>, Result<std::string>, Result<bool>,
    Result<Size>, Result<Position>, Result<Position3D>, Result<Color>, Result<AETime>, Result<Item>, Result<Range>,
    Result<Comp>, Result<Layer>, Result<Project>, Result<Footage>, Result<AEGP_ItemType>, Result<AEGP_LabelID>> ResponseArg;

typedef std::vector<ResponseArg> ResponseArgs;

struct Response {
    ResponseArgs args; // Vector of arguments
    // Default constructor
    Response() = default;

    // Constructor from ResponseArgs
    Response(const ResponseArgs& args) : args(args) {}

    // Constructor from a single ResponseArg
    Response(const ResponseArg& arg) {
        args.push_back(arg);
    }

    // Copy constructor
    Response(const Response& other) : args(other.args) {}
    //serialize method
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& args;
    }
};      // Response to be sent to the client