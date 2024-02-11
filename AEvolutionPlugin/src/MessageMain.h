#pragma once
#include "main.h"
#include "AEnums.h"

using null = NullType;

typedef boost::variant<int, double, std::string, bool, TwoDVal<double>, TwoDVal<int>, ThreeDVal<double>, FourDVal<double>, null,
                       Item, CollectionItemV2, AEGP_ItemType, AEGP_LabelID, DownsampleFactor> CommandArg;

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

typedef boost::variant<Result<int>, Result<double>, Result<std::string>, Result<bool>, Result<TwoDVal<double>>,
                       Result<TwoDVal<int>>, Result<ThreeDVal<double>>, Result<FourDVal<double>>, Result<null>,
                       Result<Item>, Result<CollectionItemV2>, Result<AEGP_ItemType>, Result<AEGP_LabelID>, Result<DownsampleFactor>> ResponseArg;

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