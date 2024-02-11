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
#include <boost/iterator/counting_iterator.hpp>
#include <boost/any.hpp>

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

/**
*
File: main.h
 * Description: Contains the main header file for the plugin.
 *
 * Guidelines for Contributors:
 * 1. Do not modify this file. It is crucial for the stable operation of the entire plugin.
 */
#define RATIO2DOUBLE(R)		(A_FpLong)((A_FpLong)(R).num / ((A_FpLong)(R).den))

int createUUID(); // Creates a unique ID for the session.

/*
* Usage:
* const A_UTF16Char* utf16String = ...; // Your UTF-16 string
  std::string utf8String = convertUTF16ToUTF8(utf16String);
*/
std::string convertUTF16ToUTF8(const A_UTF16Char* utf16String); // Convert UTF-16 to UTF-8 using ICU


/**
  std::string utf8String = "example"; // Your UTF-8 string
  std::vector<A_UTF16Char> utf16Vector = convertUTF8ToUTF16Safe(utf8String);
  const A_UTF16Char* utf16String = utf16Vector.data();
*/
std::vector<UChar> convertUTF8ToUTF16UnSafe(const std::string& utf8String);
std::vector<A_UTF16Char> convertUTF8ToUTF16(const std::string& utf8String);

std::string errToString(A_Err err); // Convert an error code to a string
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vvvvvv The Structs below are for all the base classes that will be stored as sessions. vvvvvv
// All must inherit from Base, have a serialize function, and be exported from 'main.cpp'.
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

/**
* @brief Class representing a collection in After Effects.
* Used for anything involving an AEGP_Collection2H.
*/
class Collection2H : public Base {
public:
	Collection2H() : Base() {}
	Collection2H(int sessionID) : Base(sessionID) {}

private:
    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
	}
};

/**
* @brief Class representing a stream reference in After Effects.
* Used for anything involving an AEGP_StreamRefH.
*/
class StreamRef : public Base {
public:
	StreamRef() : Base() {}
	StreamRef(int sessionID) : Base(sessionID) {}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
	}
};

class LayerCollectionItem : public Base {
public:
	LayerCollectionItem() : Base() {}
	explicit LayerCollectionItem(Layer layer, int sessionID) : Base(sessionID), layer(layer) {}

    Layer layer;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& layer;
	}
};
   
class MaskCollectionItem : public Base {
public:
	MaskCollectionItem() : Base() {}
	explicit MaskCollectionItem(Layer layer, AEGP_MaskIndex index, int sessionID) : Base(sessionID), layer(layer), index(index) {}

	Layer layer;
	AEGP_MaskIndex index;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& layer;
		ar& index;
	}
};

class EffectCollectionItem : public Base {
public:
	EffectCollectionItem() : Base() {}
	explicit EffectCollectionItem(Layer layer, AEGP_EffectIndex index, int sessionID) : Base(sessionID), layer(layer), index(index) {}

	Layer layer;
	AEGP_EffectIndex index; //index of the effect on the layer

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& layer;
		ar& index;
	}
};

class MaskStreamCollectionItem : public Base {
public:
	MaskStreamCollectionItem() : Base() {}
	explicit MaskStreamCollectionItem(MaskCollectionItem mask, AEGP_MaskStream maskStream, int sessionID) : Base(sessionID), mask(mask), maskStream(maskStream) {}

	MaskCollectionItem mask;
	AEGP_MaskStream maskStream;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& mask;
		ar& maskStream;
	}
};

class EffectStreamCollectionItem : public Base {
public:
	EffectStreamCollectionItem() : Base() {}
	explicit EffectStreamCollectionItem(EffectCollectionItem effect, A_long param_index, int sessionID) : Base(sessionID), effect(effect), param_index(param_index) {}

	EffectCollectionItem effect;
	A_long param_index;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& effect;
		ar& param_index;
	}
};

class LayerStreamCollectionItem : public Base {
public:
	LayerStreamCollectionItem() : Base() {}
	explicit LayerStreamCollectionItem(Layer layer, AEGP_LayerStream layerStream, int sessionID) : Base(sessionID), layer(layer), layerStream(layerStream) {}

	Layer layer;
	AEGP_LayerStream layerStream;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& layer;
		ar& layerStream;
	}
};

class StreamCollectionItem : public Base {
public:
	StreamCollectionItem() : Base() {}
	explicit StreamCollectionItem(AEGP_StreamCollectionItemType type, LayerStreamCollectionItem u, int sessionID) : Base(sessionID), type(type), u(u) {}
	explicit StreamCollectionItem(AEGP_StreamCollectionItemType type, MaskStreamCollectionItem u, int sessionID) : Base(sessionID), type(type), u(u) {}
	explicit StreamCollectionItem(AEGP_StreamCollectionItemType type, EffectStreamCollectionItem u, int sessionID) : Base(sessionID), type(type), u(u) {}

	AEGP_StreamCollectionItemType type;
	boost::variant<LayerStreamCollectionItem, MaskStreamCollectionItem, EffectStreamCollectionItem> u;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& type;
		ar& u;
	}
};
/*
auto& item = std::get<StreamCollectionItem>(cmd.args[0]); // assuming the args is a vector of variants
if (const auto* layerItem = std::get_if<LayerStreamCollectionItem>(&item.u)) {
    // layerItem is a pointer to LayerStreamCollectionItem, use it here
} else if (const auto* maskItem = std::get_if<MaskStreamCollectionItem>(&item.u)) {
    // maskItem is a pointer to MaskStreamCollectionItem, use it here
} else if (const auto* effectItem = std::get_if<EffectStreamCollectionItem>(&item.u)) {
    // effectItem is a pointer to EffectStreamCollectionItem, use it here
}
*/

class MaskVertexCollectionItem : public Base {
public:
	MaskVertexCollectionItem() : Base() {}
	explicit MaskVertexCollectionItem(MaskCollectionItem mask, AEGP_VertexIndex index, int sessionID) : Base(sessionID), mask(mask), index(index) {}

	MaskCollectionItem mask;
	AEGP_VertexIndex index;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& mask;
		ar& index;
	}
};

class KeyframeCollectionItem : public Base {
public:
	KeyframeCollectionItem() : Base() {}
	explicit KeyframeCollectionItem(StreamCollectionItem streamCollectionItem, AEGP_KeyframeIndex index, int sessionID) : Base(sessionID), stream(streamCollectionItem), index(index) {}

	StreamCollectionItem stream;
	AEGP_KeyframeIndex index;
        
private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& stream;
		ar& index;
	}
};

class CollectionItemV2 : public Base {
public:
	CollectionItemV2() : Base() {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, LayerCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, MaskCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, EffectCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, StreamCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, MaskVertexCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, KeyframeCollectionItem u, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), u(u), streamRef(streamRef) {}
	explicit CollectionItemV2(AEGP_CollectionItemType type, StreamRef streamRef, int sessionID) : Base(sessionID), type(type), streamRef(streamRef) {}
	AEGP_CollectionItemType type;
	boost::variant<LayerCollectionItem, MaskCollectionItem, EffectCollectionItem, StreamCollectionItem, MaskVertexCollectionItem, KeyframeCollectionItem> u;

	StreamRef streamRef;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& type;
		ar& u;
		ar& streamRef;
	}
};
/*
* auto& item = std::get<CollectionItemV2>(cmd.args[0]);
* if (const auto* layerItem = std::get_if<LayerCollectionItem>(&item.u)) {
*     // layerItem is a pointer to LayerCollectionItem, use it here
* } else if (const auto* maskItem = std::get_if<MaskCollectionItem>(&item.u)) {
*     // maskItem is a pointer to MaskCollectionItem, use it here
* } else if (const auto* effectItem = std::get_if<EffectCollectionItem>(&item.u)) {
*     // effectItem is a pointer to EffectCollectionItem, use it here
* } else if (const auto* streamItem = std::get_if<StreamCollectionItem>(&item.u)) {
*     // streamItem is a pointer to StreamCollectionItem, use it here
* } else if (const auto* maskVertexItem = std::get_if<MaskVertexCollectionItem>(&item.u)) {
*     // maskVertexItem is a pointer to MaskVertexCollectionItem, use it here
* } else if (const auto* keyframeItem = std::get_if<KeyframeCollectionItem>(&item.u)) {
*     // keyframeItem is a pointer to KeyframeCollectionItem, use it here
* }
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ^^^^^^ The Structs above are for all base classes that will be stored as sessions. ^^^^^^
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vvvvvv The Structs below are for all the data types that will be used in the commands, to simplify things. vvvvvv
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
* @brief struct to simplify transfer of x/y/z position.
* Used for anything involving a float.
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

/**
* @brief struct to simplify transfer of color.
* Used for anything involving a float [0.0, 1.0].
*/
struct Color {
    double r;
    double g;
    double b;
    double a;

    Color() {}
    Color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}

    Color(PF_Pixel pixel) : r(static_cast<double>(pixel.red)),
                            g(static_cast<double>(pixel.green)),
                            b(static_cast<double>(pixel.blue)),
                            a(static_cast<double>(pixel.alpha)) {}

    Color(AEGP_ColorVal color) : r(static_cast<double>(color.redF)),
                                 g(static_cast<double>(color.greenF)),
                                 b(static_cast<double>(color.blueF)),
								 a(static_cast<double>(color.alphaF)) {}

	AEGP_ColorVal toAEGP_ColorVal() {
		AEGP_ColorVal colorVal;
		colorVal.redF = static_cast<A_FpLong>(r);
		colorVal.greenF = static_cast<A_FpLong>(g);
		colorVal.blueF = static_cast<A_FpLong>(b);
		colorVal.alphaF = static_cast<A_FpLong>(a);
		return colorVal;
	}

	PF_Pixel toPF_Pixel() {
		PF_Pixel pixel;
		pixel.red = static_cast<A_u_char>(r);
		pixel.green = static_cast<A_u_char>(g);
		pixel.blue = static_cast<A_u_char>(b);
		pixel.alpha = static_cast<A_u_char>(a);
		return pixel;
	}

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

struct Range {
	int index_firstL;
	int index_lastL;

	// Default constructor
	Range() : index_firstL(0), index_lastL(0) {}
	// Constructor for a single index - sets both first and last to the same value, adjusted for exclusive range.
	explicit Range(int index)
		: index_firstL(index), index_lastL(index + 1) {}

	// Constructor for a range - sets first to the start index and last to one past the end index, 
	// considering the exclusive nature of the range.
	Range(int first, int last)
		: index_firstL(first), index_lastL(last) {}

	// Serialization function
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& index_firstL;
		ar& index_lastL;
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

struct DownsampleFactor {
	DownsampleFactor() {}
	DownsampleFactor(AEGP_DownsampleFactor factor) : xS(factor.xS), yS(factor.yS) {}
	double xS;
	double yS;
	AEGP_DownsampleFactor toAEGP_DownSampleFactor() {
		AEGP_DownsampleFactor factor;
		factor.xS = static_cast<A_short>(xS);
		factor.yS = static_cast<A_short>(yS);
		return factor;
	}

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& xS;
		ar& yS;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vvvvvvv The Result Struct is used for responses, to simplify the process of returning a value or an error. vvvvvvv
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
