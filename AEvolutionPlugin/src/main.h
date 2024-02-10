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
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
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

int createUUID();

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

    Base() : sessionID(-1), isValidFlag(false) {} // Default constructor marks as invalid
    Base(int sessionID) : sessionID(sessionID), isValidFlag(true) {} // Valid instance

    bool isValid() const { return isValidFlag; } // Corrected accessor for isValidFlag
    int getSessionID() const { return sessionID; }

protected:
    int sessionID;
    bool isValidFlag; // Corrected member name to avoid confusion with isValid() method

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& sessionID;
        ar& isValidFlag; // Ensure serialization includes the isValidFlag
    }
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseH)

/**
* @brief Class representing an item in After Effects.
* Used for anything involving an AEGP_ItemH.
*/
class Item : public Base {
public:
    Item() : Base() {}
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
    Project() : Base() {}
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
    Comp() : Base() {}
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
    Layer() : Base() {}
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
    Footage() : Base() {}
    Footage(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Base>(*this);
    }
};

class Collection : public Base {
public:
	Collection() : Base() {}
	Collection(int sessionID) : Base(sessionID) {}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
    Position(AEGP_TwoDVal val) : x(static_cast<double>(val.x)), y(static_cast<double>(val.y)) {}
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
    Color(AEGP_ColorVal color) : r(static_cast<double>(color.redF)), g(static_cast<double>(color.greenF)), b(static_cast<double>(color.blueF)),
								 a(static_cast<double>(color.alphaF)) {}
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    // Utility Suites
    ReportInfoUnicode,
    GetDriverSpecVersion,
    StartQuietErrors,
    EndQuietErrors,
    StartUndoGroup,
    EndUndoGroup,
    GetMainHWND,
    ShowHideAllFloaters,
    PaintPalGetForeColor,
    PaintPalGetBackColor,
    PaintPalSetForeColor,
    PaintPalSetBackColor,
    CharPalGetFillColor,
    CharPalGetStrokeColor,
    CharPalSetFillColor,
    CharPalSetStrokeColor,
    CharPalIsFillColorUIFrontmost,
    GetSuppressInteractiveUI,
    WriteToOSConsole,
    WriteToDebugLog,
    HostIsActivated,
    GetPluginPlatformRef,
    UpdateFontList,
    GetPluginPaths,

};

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

struct PathType {
	enum Type {
		PLUGIN = 0,
		USER_PLUGIN,
		ALLUSER_PLUGIN,
		APP
	};
	Type type;
	PathType() {}
	PathType(AEGP_GetPathTypes type) : type(static_cast<Type>(type)) {}
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& type;
	}
};

/*

enum  {
    AEGP_CollectionItemType_NONE,

    AEGP_CollectionItemType_LAYER,
    AEGP_CollectionItemType_MASK,
    AEGP_CollectionItemType_EFFECT,
    AEGP_CollectionItemType_STREAM,
    AEGP_CollectionItemType_KEYFRAME,
    AEGP_CollectionItemType_MASK_VERTEX,
    AEGP_CollectionItemType_STREAMREF,

    AEGP_CollectionItemType_END,
    AEGP_CollectionItemType_BEGIN = AEGP_CollectionItemType_LAYER
};
typedef A_LegacyEnumType AEGP_CollectionItemType;

typedef struct {
    AEGP_LayerH	layerH;		/comp derived from layerH 
} AEGP_LayerCollectionItem;

typedef struct {
    AEGP_LayerH		layerH;		/ containing layer 
    AEGP_MaskIndex	index;		/index to layer. 	
}AEGP_MaskCollectionItem;

typedef struct {
    AEGP_LayerH			layerH;		 containing layer		
    AEGP_EffectIndex	index;		 index to the effect	
}AEGP_EffectCollectionItem;

enum {
    AEGP_StreamCollectionItemType_NONE,
    AEGP_StreamCollectionItemType_LAYER,
    AEGP_StreamCollectionItemType_MASK,
    AEGP_StreamCollectionItemType_EFFECT,
    AEGP_StreamCollectionItemType_END,
    AEGP_StreamCollectionItemType_BEGIN = AEGP_StreamCollectionItemType_LAYER
};
typedef A_LegacyEnumType AEGP_StreamCollectionItemType;

typedef struct {
    AEGP_MaskCollectionItem		mask;
    AEGP_MaskStream				mask_stream;
} AEGP_MaskStreamCollectionItem;

typedef struct {
    AEGP_EffectCollectionItem	effect;
    A_long						param_index;
} AEGP_EffectStreamCollectionItem;

typedef struct {
    AEGP_LayerH						layerH;
    AEGP_LayerStream				layer_stream;
} AEGP_LayerStreamCollectionItem;

typedef struct {
    AEGP_StreamCollectionItemType	type;
    union {
        AEGP_LayerStreamCollectionItem	layer_stream;
        AEGP_MaskStreamCollectionItem	mask_stream;
        AEGP_EffectStreamCollectionItem	effect_stream;
    } u;
}AEGP_StreamCollectionItem;

typedef struct {
    AEGP_MaskCollectionItem	mask_sel;	 the mask must be selected for a vertex to be selected 
    AEGP_VertexIndex		index;
}AEGP_MaskVertexCollectionItem;

typedef struct {
    AEGP_StreamCollectionItem	stream_coll;
    AEGP_KeyframeIndex	index;
}AEGP_KeyframeCollectionItem;

typedef struct {
    AEGP_CollectionItemType	type;
    // the union is not used for AEGP_CollectionItemType_STREAMREF
    union {
        AEGP_LayerCollectionItem		layer;
        AEGP_MaskCollectionItem			mask;
        AEGP_EffectCollectionItem		effect;
        AEGP_StreamCollectionItem		stream;
        AEGP_MaskVertexCollectionItem	mask_vertex;
        AEGP_KeyframeCollectionItem		keyframe;
    } u;

    AEGP_StreamRefH						stream_refH; // valid for all types
} AEGP_CollectionItemV2; 
*/
struct Stream {
    enum Type {
        NONE,
        THREE_D_SPATIAL,
        THREE_D,
        TWO_D_SPATIAL,
        TWO_D,
        ONE_D,
        COLOR,
        ARB,
        MARKER,
        LAYER_ID,
        MASK_ID,
        MASK,
        TEXT_DOCUMENT
    };
    Type type;
    Stream() {}
    Stream(AEGP_StreamType type) : type(static_cast<Type>(type)) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
	    ar& type;
    }
};

struct Object {
	enum Type {
		NONE = -1,
		AV,			/* Includes all pre-AE 5.0 layer types (audio or video source, including adjustment layers)	*/
		LIGHT,
		CAMERA,
		TEXT,
		VECTOR,
		RESERVED1,
		RESERVED2,
		RESERVED3,
		RESERVED4,
		RESERVED5,
		NUM_TYPES
	};
	Type type;
	Object() {}
	Object(AEGP_ObjectType type) : type(static_cast<Type>(type)) {}
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& type;
	}
};

struct LayerStream {
    enum Type {
        NONE = -1,
		ANCHORPOINT,
		POSITION,
		SCALE,
		ROTATION,
		ROTATE_Z = ROTATION, // for 3D streams
		OPACITY,
		AUDIO,
		MARKER,
		TIME_REMAP,
		ROTATE_X,
		ROTATE_Y,
		ORIENTATION,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_CAMERA
		ZOOM,
		DEPTH_OF_FIELD,
		FOCUS_DISTANCE,
		APERTURE,
		BLUR_LEVEL,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_LIGHT
		INTENSITY,
		COLOR,
		CONE_ANGLE,
		CONE_FEATHER,
		SHADOW_DARKNESS,
		SHADOW_DIFFUSION,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_AV
		ACCEPTS_SHADOWS,
		ACCEPTS_LIGHTS,
		AMBIENT_COEFF,
		DIFFUSE_COEFF,
		SPECULAR_INTENSITY,
		SPECULAR_SHININESS,
		CASTS_SHADOWS, // LIGHT, and AV only, no CAMERA
		LIGHT_TRANSMISSION, // AV Layer only
		METAL, // AV layer only
		SOURCE_TEXT,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_CAMERA
		IRIS_SHAPE,
		IRIS_ROTATION,
		IRIS_ROUNDNESS,
		IRIS_ASPECT_RATIO,
		IRIS_DIFFRACTION_FRINGE,
		IRIS_HIGHLIGHT_GAIN,
		IRIS_HIGHLIGHT_THRESHOLD,
		IRIS_HIGHLIGHT_SATURATION,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_LIGHT
		LIGHT_FALLOFF_TYPE,
		LIGHT_FALLOFF_START,
		LIGHT_FALLOFF_DISTANCE,

        // only valid for AEGP_ObjectType == AEGP_ObjectType_AV
		REFLECTION_INTENSITY,
		REFLECTION_SHARPNESS,
		REFLECTION_ROLLOFF,
		TRANSPARENCY_COEFF,
		TRANSPARENCY_ROLLOFF,
		INDEX_OF_REFRACTION,
		EXTRUSION_BEVEL_STYLE,
		EXTRUSION_BEVEL_DIRECTION,
		EXTRUSION_BEVEL_DEPTH,
		EXTRUSION_HOLE_BEVEL_DEPTH,
		EXTRUSION_DEPTH,
		PLANE_CURVATURE,
		PLANE_SUBDIVISION,

        /*********************************************************/
		NUMTYPES,
		BEGIN = NONE + 1,
		END = NUMTYPES
    };
    Type type;
    LayerStream() {}
    LayerStream(AEGP_LayerStream stream) : type(static_cast<Type>(type)) {}
    template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& type;
	}
};

struct StreamFlags {
    // Enumeration to represent various stream flags
    enum Type {
        NONE = 0,        // No flags set
        HAS_MIN = 0x01,  // Stream has a minimum value
        HAS_MAX = 0x02,  // Stream has a maximum value
        IS_SPATIAL = 0x04 // Stream is spatial
    };

    Type type; // Holds the combination of flags

    // Default constructor initializes with no flags set
    StreamFlags() : type(NONE) {}

    // Constructor for initializing with specific flags
    StreamFlags(Type flags) : type(flags) {}
    StreamFlags(AEGP_StreamFlags flags) : type(static_cast<Type>(flags)) {}
    // Serialization function to support saving/loading
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& type; // Serialize the 'type' member
    }

    // Sets (adds) a flag to the current flag combination
    void setFlag(Type flag) {
        type = static_cast<Type>(type | flag);
    }

    // Clears (removes) a flag from the current flag combination
    void clearFlag(Type flag) {
        type = static_cast<Type>(type & ~flag);
    }

    // Checks if a specific flag is set
    bool isFlagSet(Type flag) const {
        return (type & flag) == flag;
    }
};

/*
int main() {
    StreamFlags flags;

    // Set HAS_MIN and IS_SPATIAL flags
    flags.setFlag(StreamFlags::HAS_MIN);
    flags.setFlag(StreamFlags::IS_SPATIAL);

    // Check if a specific flag is set
    if (flags.isFlagSet(StreamFlags::HAS_MIN)) {
        std::cout << "HAS_MIN flag is set." << std::endl;
    }

    // Clear the HAS_MIN flag
    flags.clearFlag(StreamFlags::HAS_MIN);

    // Check again
    if (!flags.isFlagSet(StreamFlags::HAS_MIN)) {
        std::cout << "HAS_MIN flag is now cleared." << std::endl;
    }

    // The IS_SPATIAL flag should still be set
    if (flags.isFlagSet(StreamFlags::IS_SPATIAL)) {
        std::cout << "IS_SPATIAL flag is still set." << std::endl;
    }

    return 0;
}
*/

struct Position3D {
    double x;
    double y;
    double z;
    Position3D() {}
    Position3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Position3D(AEGP_ThreeDVal val) : x(static_cast<double>(val.x)), y(static_cast<double>(val.y)), z(static_cast<double>(val.z)) {}
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& x;
        ar& y;
        ar& z;
    }
};


/// <summary>
/// ///////////////////////////////////////////////////////////////////
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
struct Result {
    T value;
    std::string error;

    // Default constructor
    Result() {}

    // Constructor for result and error (general case)
    Result(T result, std::string error) : value(result), error(error) {}

    // Constructor for error only
    explicit Result(std::string error) : error(error) {}

    // Constructor for result only (disables if T is std::string to avoid ambiguity)
    template<typename U = T>
    explicit Result(U result, typename std::enable_if<!std::is_same<U, std::string>::value, U>::type* = 0) : value(result) {}

    // Constructor for result and error (specific case for std::string, disabled if T is not std::string)
    // This uses std::enable_if to enable this constructor only when T is std::string
    template<typename U = T>
    explicit Result(std::string result, std::string error, typename std::enable_if<std::is_same<U, std::string>::value, U>::type* = 0) : value(result), error(error) {}

    // Serialization function
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& value;
        ar& error;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using null = NullType;

typedef boost::variant<int, double, std::string, bool, Size,
                       Position, Color, AETime, Item, Comp,
                       Layer, Project, Footage, null, PathType, LabelType, Collection> CommandArg;
     
typedef std::vector<CommandArg> CommandArgs;

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

typedef boost::variant<Result<NullType>, Result<LabelType>, Result<Collection>, Result<int>, Result<double>, Result<std::string>, Result<bool>,
                       Result<Size>, Result<Position>, Result<Color>, Result<AETime>, Result<Item>,
                       Result<Comp>, Result<Layer>, Result<Project>, Result<Footage>, Result<ItemType>, Result<PathType>> ResponseArg;

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

typedef std::variant<AEGP_ItemH, AEGP_CompH, AEGP_FootageH, AEGP_LayerH, AEGP_ProjectH, AEGP_Collection2H> SessionObject;

typedef std::map<int, SessionObject> Sessions;


#define REGISTER_COMMAND(ID, TYPE) \
static bool _reg_##TYPE = []() -> bool { \
    CommandFactory::get().registerCommand(ID, [](Command cmd) -> std::unique_ptr<CommandBase> { \
        auto command = std::make_unique<TYPE>(std::move(cmd)); \
        return command; \
    }); \
    return true; \
}();