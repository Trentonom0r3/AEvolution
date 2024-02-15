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
#include <boost/mp11.hpp>

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

using Project = Item;
using Comp = Item;
using Layer = Item;
using Footage = Item;
using Collection2H = Item;
using StreamRef = Item;
using Folder = Item;

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
class SoundDataFormat : public Base {
public:
SoundDataFormat() : Base() {}
	SoundDataFormat(A_FpLong sample_rateF, AEGP_SoundEncoding encoding, A_long bytes_per_sampleL, A_long num_channelsL) : Base(createUUID()), sample_rateF(sample_rateF), encoding(encoding), bytes_per_sampleL(bytes_per_sampleL), num_channelsL(num_channelsL) {}
	SoundDataFormat(AEGP_SoundDataFormat format) : Base(createUUID()), sample_rateF(format.sample_rateF), encoding(format.encoding), bytes_per_sampleL(format.bytes_per_sampleL), num_channelsL(format.num_channelsL) {}

	A_FpLong sample_rateF;
	AEGP_SoundEncoding encoding;
	A_long bytes_per_sampleL;
	A_long num_channelsL;

	AEGP_SoundDataFormat toAEGP_SoundDataFormat() const {
		AEGP_SoundDataFormat format;
		format.sample_rateF = sample_rateF;
		format.encoding = encoding;
		format.bytes_per_sampleL = bytes_per_sampleL;
		format.num_channelsL = num_channelsL;
		return format;
	}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& sample_rateF;
		ar& encoding;
		ar& bytes_per_sampleL;
		ar& num_channelsL;
	}
};

class FootageLayerKey : public Base {
public:
	FootageLayerKey() : Base() {}
	FootageLayerKey(A_long layer_idL, A_long layer_indexL, A_char nameAC[AEGP_FOOTAGE_LAYER_NAME_LEN + 1], AEGP_LayerDrawStyle layer_draw_style) : Base(createUUID()), layer_idL(layer_idL), layer_indexL(layer_indexL), layer_draw_style(layer_draw_style) {
		strcpy_s(this->nameAC, nameAC);
	}

	A_long layer_idL;
	A_long layer_indexL;
	A_char nameAC[AEGP_FOOTAGE_LAYER_NAME_LEN + 1];
	AEGP_LayerDrawStyle layer_draw_style;

	AEGP_FootageLayerKey toAEGP_FootageLayerKey() const {
		AEGP_FootageLayerKey key;
		key.layer_idL = layer_idL;
		key.layer_indexL = layer_indexL;
		strcpy_s(key.nameAC, nameAC);
		key.layer_draw_style = layer_draw_style;
		return key;
	}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& layer_idL;
		ar& layer_indexL;
		ar& nameAC;
		ar& layer_draw_style;
	}
};

class FileSequenceImportOptions : public Base {
public:
	FileSequenceImportOptions() : Base() {}
	FileSequenceImportOptions(bool all_in_folderB, bool force_alphabeticalB, A_long start_frameL, A_long end_frameL) : Base(createUUID()), all_in_folderB(all_in_folderB), force_alphabeticalB(force_alphabeticalB), start_frameL(start_frameL), end_frameL(end_frameL) {}
	FileSequenceImportOptions(AEGP_FileSequenceImportOptions options) : Base(createUUID()), all_in_folderB(options.all_in_folderB), force_alphabeticalB(options.force_alphabeticalB), start_frameL(options.start_frameL), end_frameL(options.end_frameL) {}

	AEGP_FileSequenceImportOptions toAEGP_FileSequenceImportOptions() const {
		AEGP_FileSequenceImportOptions options;
		options.all_in_folderB = all_in_folderB;
		options.force_alphabeticalB = force_alphabeticalB;
		options.start_frameL = start_frameL;
		options.end_frameL = end_frameL;
		return options;
	}

	bool all_in_folderB;
	bool force_alphabeticalB;
	A_long start_frameL;
	A_long end_frameL;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<Base>(*this);
		ar& all_in_folderB;
		ar& force_alphabeticalB;
		ar& start_frameL;
		ar& end_frameL;
	}
};

class NullType : public Base {
public:
	NullType() : Base(), valid(false) {}
	NullType(int sessionID) : Base(sessionID), valid(false) {}

	bool valid;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& valid;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ^^^^^^ The Structs above are for all base classes that will be stored as sessions. ^^^^^^
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vvvvvv The Structs below are for all the data types that will be used in the commands, to simplify things. vvvvvv
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Range : public Base {
public:
Range() : Base() {}
	Range(A_FpLong minF, A_FpLong maxF) : Base(createUUID()), minF(minF), maxF(maxF) {}

	A_FpLong minF;
	A_FpLong maxF;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& minF;
		ar& maxF;
	}
};

class Time : public Base {
public:
Time() : Base() {}
	Time(A_Time time) : Base(createUUID()), scale(time.scale) {}
	Time(A_long value, A_u_long scale) : Base(createUUID()),  val(value), scale(scale) {}
	Time(A_Ratio ratio) : Base(createUUID()), val(ratio.num), scale(ratio.den) {}
	Time(double value, double scale) : Base(createUUID()), val(static_cast<A_long>(value)), scale(static_cast<A_u_long>(scale)) {}
	A_long val;
	A_u_long scale;

	A_Time toA_Time() const {
		A_Time time;
		time.value = val;
		time.scale = scale;
		return time;
	}

	A_Ratio toA_Ratio() const {
		A_Ratio ratio;
		ratio.num = val;
		ratio.den = scale;
		return ratio;
	}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& val;
		ar& scale;
	}
};

class Position : public Base {
public:
Position() : Base() {}
	Position(A_FpLong x, A_FpLong y) : Base(createUUID()), x(x), y(y) {}
	Position(AEGP_TwoDVal val) : Base(createUUID()), x(val.x), y(val.y) {}
	Position(AEGP_DownsampleFactor factor) : Base(createUUID()), x(factor.xS), y(factor.yS) {}
	Position(A_FloatPoint point) : Base(createUUID()), x(point.x), y(point.y) {}
	A_FpLong x;
	A_FpLong y;

	AEGP_DownsampleFactor toAEGP_DownsampleFactor() const {
		AEGP_DownsampleFactor factor;
		factor.xS = static_cast<A_short>(x);
		factor.yS = static_cast<A_short>(y);
		return factor;
	}

	AEGP_TwoDVal toAEGP_TwoDVal() const {
		AEGP_TwoDVal val;
		val.x = x;
		val.y = y;
		return val;
	}

	A_FloatPoint toA_FloatPoint() const {
		A_FloatPoint point;
		point.x = x;
		point.y = y;
		return point;
	}
private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& x;
		ar& y;
	}
};

using Ratio = Time;
using Size = Position;
using Point = Position;
using DownsampleFactor = Position;
using ShutterAnglePhase = Time;
using AspectRatio = Time;

class Color : public Base {
public:
Color() : Base() {}
	Color(A_FpLong r, A_FpLong g, A_FpLong b, A_FpLong a) : Base(createUUID()), r(r), g(g), b(b), a(a) {}
	Color(AEGP_ColorVal color) : Base(createUUID()), r(color.redF), g(color.greenF), b(color.blueF), a(color.alphaF) {}
	Color(PF_Pixel pixel) : Base(createUUID()), r(pixel.red), g(pixel.green), b(pixel.blue), a(pixel.alpha) {}

	AEGP_ColorVal toAEGP_ColorVal() const {
		AEGP_ColorVal color;
		color.redF = r;
		color.greenF = g;
		color.blueF = b;
		color.alphaF = a;
		return color;
	}

	PF_Pixel toPF_Pixel() const {
		PF_Pixel pixel;
		pixel.red = static_cast<A_u_char>(r);
		pixel.green = static_cast<A_u_char>(g);
		pixel.blue = static_cast<A_u_char>(b);
		pixel.alpha = static_cast<A_u_char>(a);
		return pixel;
	}

	A_FpLong r;
	A_FpLong g;
	A_FpLong b;
	A_FpLong a;

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& r;
		ar& g;
		ar& b;
		ar& a;
	}
};

class Position3D : public Base {
public:
Position3D() : Base() {}
	Position3D(A_FpLong x, A_FpLong y, A_FpLong z) : Base(createUUID()), x(x), y(y), z(z) {}
	Position3D(AEGP_ThreeDVal val) : Base(createUUID()), x(val.x), y(val.y), z(val.z) {}

	A_FpLong x;
	A_FpLong y;
	A_FpLong z;

	AEGP_ThreeDVal toAEGP_ThreeDVal() const {
		AEGP_ThreeDVal val;
		val.x = x;
		val.y = y;
		val.z = z;
		return val;
	}

private:
friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Base>(*this);
		ar& x;
		ar& y;
		ar& z;
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
