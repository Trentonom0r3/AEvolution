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
#include "AE_GeneralPlug.h"
#include <mutex>
#include <type_traits>
#include <unicode/unistr.h>
#include <unordered_map>

//define a macro that converts ratio float, then float into double.
// use existing macro for float conversion ,make new one for double; 
// 		//#define	RATIO2FLOAT(R)		(A_FpLong)((A_FpLong)(R).num / ((A_FpLong)(R).den))
#define RATIO2DOUBLE(R)		(A_FpLong)((A_FpLong)(R).num / ((A_FpLong)(R).den))
// Convert UTF-16 to UTF-8 using ICU
std::string convertUTF16ToUTF8(const A_UTF16Char* utf16String);
/*
* const A_UTF16Char* utf16String = ...; // Your UTF-16 string
  std::string utf8String = convertUTF16ToUTF8(utf16String);
*/

std::vector<UChar> convertUTF8ToUTF16UnSafe(const std::string& utf8String);


std::vector<A_UTF16Char> convertUTF8ToUTF16(const std::string& utf8String);
/**

  std::string utf8String = "example"; // Your UTF-8 string
  std::vector<A_UTF16Char> utf16Vector = convertUTF8ToUTF16Safe(utf8String);
  const A_UTF16Char* utf16String = utf16Vector.data();

*/

/**
*
File: main.h
 * Description: Contains the main header file for the plugin.
 *
 * Guidelines for Contributors:
 * 1. Do not modify this file. It is crucial for the stable operation of the entire plugin.
 */

/**
* @brief Function to convert an A_Err to a string.
* @param err The A_Err to convert.
* @return The string representation of the A_Err.
*/
std::string errToString(A_Err err);

/**
* @brief Base class for all objects that can be serialized and deserialized.
*/
class Base {
public:
    virtual ~Base() {}
    Base() {}
    Base(int sessionID) : sessionID(sessionID) {}
    int getSessionID() { return sessionID; }

protected:
    int sessionID;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& sessionID;
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseH)

/**
* @brief Class representing an item in After Effects.
* Used for anything involving an AEGP_ItemH.
*/
class Item : public Base {
public:
    Item() {}
    Item(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

/**
* @brief Class representing a project in After Effects.
* Used for anything involving an AEGP_ProjectH.
*/
class Project : public Base {
public:
    Project() {}
    Project(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

/**
* @brief Class representing a composition in After Effects.
* Used for anything involving an AEGP_CompH.
*/
class Comp : public Base {
public:
    Comp() {}
    Comp(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

/**
* @brief Class representing a layer in After Effects.
* Used for anything involving an AEGP_LayerH.
*/
class Layer : public Base {
public:
    Layer() {}
    Layer(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

/**
* @brief Class representing a footage in After Effects.
* Used for anything involving an AEGP_FootageH.
*/
class Footage : public Base {
public:
    Footage() {}
    Footage(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

/**
* @brief struct to simplify transer of width/height.
* Used for anything involving a float.
*/

struct Size {
	double width;
    double height;
	Size() {}
	Size(double width, double height) : width(width), height(height) {}
    Size(A_long width, A_long height) : width(static_cast<float>(width)), height(static_cast<float>(height)) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
		ar& width;
		ar& height;
	}
};

/**
* @brief struct to simplify transfer of x/y position.
* Used for anything involving a float.
*/

struct Position {
    double x;
    double y;
	Position() {}
	Position(double x, double y) : x(x), y(y) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
		ar& x;
		ar& y;
	}
};

/**
* @brief struct to simplify transfer of color.
* Used for anything involving a float [0.0, 1.0].
* 	typedef struct {
		A_u_char	alpha, red, green, blue;
	} PF_Pixel;
*/
struct Color {
    double r;
    double g;
    double b;
    double a;
    Color() {}
    Color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
    Color(PF_Pixel pixel) : r(static_cast<double>(pixel.red)), g(static_cast<double>(pixel.green)), b(static_cast<double>(pixel.blue)),
                            a(static_cast<double>(pixel.alpha)) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
		ar& r;
		ar& g;
		ar& b;
		ar& a;
	}
};

/**
* @brief struct to simplify transfer of AE's representation of time.
* Used for anything involving a float.
*/
struct AETime {
    double value;
    double scale;
    AETime() {}
    AETime(double value, double scale) : value(value), scale(scale) {}
    AETime(A_Time time) : value(static_cast<float>(time.value)), scale(static_cast<float>(time.scale)) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& value;
        ar& scale;
    }
};

/**
* @brief struct to represent a null type.
* Used for anything involving a null type.
*/
struct NullType {
    NullType() {}

   // Serialization function
	template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
	}
};

/*
enum {
    AEGP_ItemType_NONE,
    AEGP_ItemType_FOLDER,
    AEGP_ItemType_COMP,
    AEGP_ItemType_SOLID_defunct,	// as of AE6, solids are now just AEGP_ItemType_FOOTAGE with AEGP_FootageSignature_SOLID
    AEGP_ItemType_FOOTAGE,
    AEGP_ItemType_NUM_TYPES1
};
typedef A_short AEGP_ItemType;
*/

struct ItemType {
	enum Type {
		None,
		Folder,
		Comp,
		Solid,
		Footage
	};
	Type type;
	ItemType() {}
	ItemType(AEGP_ItemType type) : type(static_cast<Type>(type)) {}
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& type;
	}
};

struct LabelType {
	enum Type {
		None = -1,
		NoLabel = 0,
		Label1,
		Label2,
		Label3,
		Label4,
		Label5,
		Label6,
		Label7,
		Label8,
		Label9,
		Label10,
		Label11,
		Label12,
		Label13,
		Label14,
		Label15,
		Label16
	};
	Type type;
	LabelType() {}
	LabelType(AEGP_LabelID type) : type(static_cast<Type>(type)) {}
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& type;
	}
};

template <typename T>
struct Result {
    T result;
    std::string error;

    // Default constructor
    Result() {}

    // Constructor for result and error (general case)
    Result(T result, std::string error) : result(result), error(error) {}

    // Constructor for error only
    explicit Result(std::string error) : error(error) {}

    // Constructor for result only (disables if T is std::string to avoid ambiguity)
    template<typename U = T>
    explicit Result(U result, typename std::enable_if<!std::is_same<U, std::string>::value, U>::type* = 0) : result(result) {}

    // Constructor for result and error (specific case for std::string, disabled if T is not std::string)
    // This uses std::enable_if to enable this constructor only when T is std::string
    template<typename U = T>
    explicit Result(std::string result, std::string error, typename std::enable_if<std::is_same<U, std::string>::value, U>::type* = 0) : result(result), error(error) {}

    // Serialization function
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& result;
        ar& error;
    }
};

using null = NullType;

typedef boost::variant<int, double, std::string, bool, Size, Position, Color, AETime, Item, Comp, Layer, Project, Footage, null, LabelType> CommandArg;
     
typedef std::vector<CommandArg> CommandArgs;


enum class CommandID : uint16_t {
    // Item Suites
    GetFirstProjItem = 0,
    GetNextProjItem,
    GetActiveItem,
    IsItemSelected,
    SelectItem,
    GetItemType,
    GetItemName,
    SetItemName,
    GetItemID,
    SetItemUseProxy,
    GetItemParentFolder,
    SetItemParentFolder,
    CreateNewFolder,
    GetItemDuration,
    GetItemCurrentTime,
    GetItemDimensions,
    GetItemPixelAspectRatio,
    DeleteItem,
    SetItemCurrentTime,
    GetItemComment,
    SetItemComment,
    GetItemLabel,
    SetItemLabel,
};


namespace boost {
    namespace serialization {

        template<class Archive>
        void serialize(Archive& ar, CommandID& commandID, const unsigned int version) {
            // Serialize the enum class as its underlying type
            uint16_t value = static_cast<uint16_t>(commandID);
            ar& value;
            if (Archive::is_loading::value) {
                commandID = static_cast<CommandID>(value);
            }
        }

    } // namespace serialization
} // namespace boost


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

typedef boost::variant<Result<NullType>, Result<LabelType>, Result<int>, Result<double>, Result<std::string>, Result<bool>,
                       Result<Size>, Result<Position>, Result<Color>, Result<AETime>, Result<Item>,
                       Result<Comp>, Result<Layer>, Result<Project>, Result<Footage>, Result<ItemType>> ResponseArg;

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

typedef std::variant<AEGP_ItemH, AEGP_CompH, AEGP_FootageH, AEGP_LayerH, AEGP_ProjectH> SessionObject;

typedef std::map<int, SessionObject> Sessions;


