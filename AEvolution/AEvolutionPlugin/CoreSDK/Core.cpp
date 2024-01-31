#include "Core.h"
/*
 * File: Core.cpp
 * Description: This file contains the core logic wrappers for the After Effects SDK. It is designed to be simple and heavily abstracted for reusability.
 *
 * Guidelines for Contributors:
 * 1. Simplicity: Functions should be straightforward, performing a single task.
 * 2. Suite Access: Always access suites via `SuiteManager::GetInstance().GetSuiteHandler()`.
 * 3. Plugin ID: Retrieve the plugin ID using `SuiteManager::GetInstance().GetPluginID()`. Check for null pointers.
 * 4. Error Handling: Use the `Result<T>` class for returning both values and error codes.
 *	 `Result<void>` for functions that do not return a value.
 *	'Result<T>' is a template class that contains a value of type T and an error code of type A_Err.
 * 5. Abstraction: Maintain a high level of abstraction. Complex functionalities should be delegated to 'PyCore.cpp'.
 * 6. Reusability: Write reusable code. Many functions will be used in various combinations in 'PyCore.cpp'.
 * 7. Do not modify the standard set unless absolutely necessary.
 * 
 * Error Handling:
 * 1. Use the `Result<T>` class for returning both values and error codes.
 * `Result<void>` for functions that do not return a value.
 * 2. `Result<T>` is a template class that contains a value of type T and an error code of type A_Err.
 * 3. The `Result<T>` class is defined in 'Core.h'.
 * 4. The `Result<T>` class is used to return both values and error codes from functions.
 * 5. The `Result<T>` class is used to return error codes from functions that do not return a value.
 * 
 * See Existing code and header file for examples.
 *
 */

 // Convert seconds to A_Time considering the frame rate
A_Time ConvertFloatToATime(float seconds, float frameRate) {
	A_Time aTime;
	float timescale = frameRate * 100;  // Scale based on frame rate
	aTime.value = static_cast<A_long>(seconds * timescale);
	aTime.scale = static_cast<A_u_long>(timescale);
	return aTime;
}

float ConvertATimeToFloat(const A_Time& aTime, float frameRate) {
	if (aTime.scale == 0) {
		throw std::runtime_error("Scale cannot be zero in A_Time conversion.");
	}
	if (frameRate <= 0) {
		throw std::runtime_error("Frame rate must be positive in A_Time conversion.");
	}

	float timeInSeconds = static_cast<float>(aTime.value) / static_cast<float>(aTime.scale);
	return timeInSeconds * frameRate; // This will give you the frame number as a float
}

// Convert frame number to A_Time
A_Time ConvertFrameToATime(int frameNumber, float frameRate) {
	return ConvertFloatToATime(static_cast<float>(frameNumber) / frameRate, frameRate);
}


std::string convertUTF16ToUTF8(const A_UTF16Char* utf16String) {
	if (utf16String == nullptr) {
		return "";
	}

	// Convert the input UTF-16 string to std::wstring
	const wchar_t* wcharString = reinterpret_cast<const wchar_t*>(utf16String);
	std::wstring wideString(wcharString);

	// Use Boost to perform the conversion
	try {
		return boost::locale::conv::utf_to_utf<char>(wideString);
	}
	catch (const std::exception& e) {
		// Handle or log the conversion error
		return "";
	}
}

std::vector<A_UTF16Char> convertUTF8ToUTF16(const std::string& utf8String) {
	try {
		// Use Boost to perform the conversion
		std::wstring wideString = boost::locale::conv::utf_to_utf<wchar_t>(utf8String);

		// Convert the std::wstring to std::vector<A_UTF16Char>
		return std::vector<A_UTF16Char>(wideString.begin(), wideString.end());
	}
	catch (const std::exception& e) {
		// Handle or log the conversion error
		return std::vector<A_UTF16Char>();
	}
}

AEGP_ProjBitDepth ConvertToProjBitDepth(const std::string& bitDepthStr) {
	if (bitDepthStr == "8") return AEGP_ProjBitDepth_8;
	if (bitDepthStr == "16") return AEGP_ProjBitDepth_16;
	if (bitDepthStr == "32") return AEGP_ProjBitDepth_32;
	throw std::runtime_error("Invalid bit depth string: " + bitDepthStr);
}
