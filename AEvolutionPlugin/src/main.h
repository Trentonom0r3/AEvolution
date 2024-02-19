#pragma once
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
