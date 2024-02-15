#include "main.h"

int createUUID() {
    // Generate a UUID
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    // Convert UUID to a string
    std::string uuidString = boost::uuids::to_string(uuid);

    // Use a hash function to convert the UUID string to an integer
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(uuidString);

    // Narrowing conversion, size_t to int (with potential overflow)
    // This is just for demonstration and may not be suitable for all purposes
    int uuidInt = static_cast<int>(hash);

    return uuidInt;
}

std::string errToString(A_Err err) {
    switch (err) {
    case A_Err_NONE:
        return "A_Err_NONE";
    case A_Err_GENERIC:
        return "A_Err_GENERIC";
    case A_Err_ALLOC:
        return "A_Err_ALLOC";
    case A_Err_STRUCT:
        return "A_Err_STRUCT";
    case A_Err_MISSING_SUITE:
        return "A_Err_MISSING_SUITE";
    case A_Err_NOT_IN_CACHE_OR_COMPUTE_PENDING:
        return "A_Err_NOT_IN_CACHE_OR_COMPUTE_PENDING";
    case A_Err_PARAMETER:
        return "A_Err_PARAMETER";
    case A_Err_PROJECT_LOAD_FATAL:
        return "A_Err_PROJECT_LOAD_FATAL";
    case A_Err_WRONG_THREAD:
        return "A_Err_WRONG_THREAD";
    case A_Err_CONST_PROJECT_MODIFICATION:
        return "A_Err_CONST_PROJECT_MODIFICATION";
    default:
        return "Unknown error";
    }
}

std::string convertUTF16ToUTF8(const A_UTF16Char* utf16String) {
    icu::UnicodeString unicodeString(reinterpret_cast<const UChar*>(utf16String));
    std::string utf8String;
    unicodeString.toUTF8String(utf8String);
    return utf8String;
}


std::vector<UChar> convertUTF8ToUTF16UnSafe(const std::string& utf8String) {
    icu::UnicodeString unicodeString = icu::UnicodeString::fromUTF8(utf8String);
    std::vector<UChar> utf16Vector(unicodeString.length() + 1); // +1 for null terminator
    UErrorCode status = U_ZERO_ERROR;
    unicodeString.extract(&utf16Vector[0], unicodeString.length() + 1, status);

    // Check the status to ensure the operation was successful
    if (U_FAILURE(status)) {
        // Handle the error, possibly clearing the vector or logging the failure
        utf16Vector.clear();
    }
    else {
        // Ensure null termination if needed. The extract method should already do this,
        // but this is just in case your logic requires it.
        utf16Vector[unicodeString.length()] = 0;
    }

    return utf16Vector;
}


std::vector<A_UTF16Char> convertUTF8ToUTF16(const std::string& utf8String) {
    auto utf16Vector = convertUTF8ToUTF16UnSafe(utf8String);
    return std::vector<A_UTF16Char>(utf16Vector.begin(), utf16Vector.end());
}


BOOST_CLASS_EXPORT_GUID(Item, "Item");
BOOST_CLASS_EXPORT_GUID(LayerCollectionItem, "LayerCollectionItem");
BOOST_CLASS_EXPORT_GUID(MaskCollectionItem, "MaskCollectionItem");
BOOST_CLASS_EXPORT_GUID(EffectCollectionItem, "EffectCollectionItem");
BOOST_CLASS_EXPORT_GUID(MaskStreamCollectionItem, "MaskStreamCollectionItem");
BOOST_CLASS_EXPORT_GUID(EffectStreamCollectionItem, "EffectStreamCollectionItem");
BOOST_CLASS_EXPORT_GUID(LayerStreamCollectionItem, "LayerStreamCollectionItem");
BOOST_CLASS_EXPORT_GUID(StreamCollectionItem, "StreamCollectionItem");
BOOST_CLASS_EXPORT_GUID(MaskVertexCollectionItem, "MaskVertexCollectionItem");
BOOST_CLASS_EXPORT_GUID(KeyframeCollectionItem, "KeyframeCollectionItem");
BOOST_CLASS_EXPORT_GUID(CollectionItemV2, "CollectionItemV2");
BOOST_CLASS_EXPORT_GUID(SoundDataFormat, "SoundDataFormat");
BOOST_CLASS_EXPORT_GUID(FootageLayerKey, "FootageLayerKey");
BOOST_CLASS_EXPORT_GUID(FileSequenceImportOptions, "FileSequenceImportOptions");
BOOST_CLASS_EXPORT_GUID(NullType, "NullType");
BOOST_CLASS_EXPORT_GUID(Range, "Range");
BOOST_CLASS_EXPORT_GUID(Time, "Time");
BOOST_CLASS_EXPORT_GUID(Position, "Position");
BOOST_CLASS_EXPORT_GUID(Color, "Color");
BOOST_CLASS_EXPORT_GUID(Position3D, "Position3D");
