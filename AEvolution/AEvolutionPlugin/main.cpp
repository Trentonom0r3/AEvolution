#include "main.h"


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

BOOST_CLASS_EXPORT(Item);
BOOST_CLASS_EXPORT(Project);
BOOST_CLASS_EXPORT(Comp);
BOOST_CLASS_EXPORT(Layer);
BOOST_CLASS_EXPORT(Footage);