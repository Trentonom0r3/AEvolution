#pragma once
#include "AEConfig.h"
#ifdef AE_OS_WIN
#include <windows.h>
#endif

#include "SuiteManager.h" //Singleton class that manages the suite handler

#include "PT_Err.h"
#include "AE_Macros.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <mutex>
#include <boost/locale/encoding_utf.hpp>

// Custom Exception class
class AEException : public std::exception {
public:
    // Constructor
    AEException(A_long errorCode)
        : errorCode_(errorCode), errorMessage_(ErrToString(errorCode)) {}

    // Default virtual destructor
    virtual ~AEException() noexcept {}

    // Override the what() function to provide a custom error message
    virtual const char* what() const noexcept override {
        return errorMessage_.c_str();
    }

    // Function to convert error code to string
    // You can expand this function to return more detailed messages based on errorCode_
    static std::string ErrToString(A_long errorCode) {
        switch (errorCode) {
        case A_Err_NONE: return "";
        case A_Err_GENERIC: return "Generic error";
        case A_Err_STRUCT: return "Structural error";
        case A_Err_PARAMETER: return "Parameter error"; 
        case A_Err_ALLOC: return "Allocation error";    
        case A_Err_WRONG_THREAD: return "Wrong thread error";
        case A_Err_CONST_PROJECT_MODIFICATION: return "Constant project modification error";
        case A_Err_MISSING_SUITE: return "Missing suite error";
        case A_Err_NOT_IN_CACHE_OR_COMPUTE_PENDING: return "Not in cache or compute pending error";
        case A_Err_PROJECT_LOAD_FATAL: return "Project load fatal error";
        case A_Err_EFFECT_APPLY_FATAL: return "Effect apply fatal error";
            // Add more cases as needed
        default: return "Unknown error";
        }
    }

    // Getter for the error code
    A_long ErrorCode() const {
        return errorCode_;
    }

private:
    A_long errorCode_;
    std::string errorMessage_;
};


/*
 * File: Core.h
 * Description: Header file for Core.cpp. Contains template definitions and function prototypes used in Core.cpp.
 *
 * Guidelines for Contributors:
 * 1. Consistency: Maintain consistency with the existing template and function definitions.
 * 2. Clarity: Ensure that all new templates and functions are clearly documented and easy to understand.
 * 3. Compatibility: Any additions should be compatible with the existing code structure and logic in Core.cpp.
 */

struct size {
	int width;
    int height;
};



template<typename T>
struct Result {
    T value; // The result of the function, if any
    A_Err error; // The error code returned by the AE functions

    // Constructor for error-only results
    Result(A_Err err) : error(err) {}

    // Constructor for results with a value and an error code
    Result(T val, A_Err err) : value(val), error(err) {}

    // Default constructor for no-error (assumes default-constructible T)
    Result() : value(T()), error(A_Err_NONE) {}
};

// Specialization for void since it cannot be constructed or returned
template<>
struct Result<void> {
    A_Err error;

    // Constructor for error-only results
    explicit Result(A_Err err = A_Err_NONE) : error(err) {}
};


/*


Note that A_Time values are rationals 
and thus do not map exactly into floating point 
so you may end up with off-by-one frame issues 
depending on how the floating point time values are used.
If you need precision then I suggest doing your time operations directly with rationals.

*/
A_Time ConvertFloatToATime(float seconds, float frameRate);

float ConvertATimeToFloat(const A_Time& aTime, float frameRate);

std::string convertUTF16ToUTF8(const A_UTF16Char* utf16String);

std::vector<A_UTF16Char> convertUTF8ToUTF16(const std::string& utf8String);

AEGP_ProjBitDepth ConvertToProjBitDepth(const std::string& bitDepthStr);



enum LayerFlag {
    VIDEO_ACTIVE = 0x00000001,
    AUDIO_ACTIVE = 0x00000002,
    EFFECTS_ACTIVE = 0x00000004,
    MOTION_BLUR = 0x00000008,
    FRAME_BLENDING = 0x00000010,
    LOCKED = 0x00000020,
    SHY = 0x00000040,
    COLLAPSE = 0x00000080,
    AUTO_ORIENT_ROTATION = 0x00000100,
    ADJUSTMENT_LAYER = 0x00000200,
    TIME_REMAPPING = 0x00000400,
    LAYER_IS_3D = 0x00000800,
    LOOK_AT_CAMERA = 0x00001000,
    LOOK_AT_POI = 0x00002000,
    SOLO = 0x00004000,
    MARKERS_LOCKED = 0x00008000,
    NULL_LAYER = 0x00010000,
    HIDE_LOCKED_MASKS = 0x00020000,
    GUIDE_LAYER = 0x00040000,
    ADVANCED_FRAME_BLENDING = 0x00080000,
    SUBLAYERS_RENDER_SEPARATELY = 0x00100000,
    ENVIRONMENT_LAYER = 0x00200000
};
