#pragma once
#include "AE_GeneralWrap.h"
#include "AEnums.h"

using null = NullType;


struct Command {
    CommandID id;
    Command() = default;
    Command(CommandID id) : id(id) {};
    A_Err err = A_Err_NONE;
    virtual void execute() = 0; //execute method. This method will be overridden by the derived classes
                                //Execute will pull args in derived methods, execute them, and send the response.
                                //Each command will have a unique response.

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& id;
    }
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Command)

struct Response {
    CommandID id;
    std::string error;
    // Default constructor
    Response() = default;
    virtual ~Response() = default;
    Response(CommandID id, std::string error) : id(id), error(error) {};
    //serialize method
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
    ar& id;
    }
};      // Response to be sent to the client
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Response)