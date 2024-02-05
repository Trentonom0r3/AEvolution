#pragma once

#include "AEConfig.h"
#ifdef AE_OS_WIN
#include <windows.h>
#endif

#include <cstdlib>
//SDK HEADERS
#include "entry.h"
#include "AE_GeneralPlug.h"
#include "AEGP_SuiteHandler.h"
#include "AE_Macros.h"
#include "CoreSDK/SuiteManager.h"
#include "CoreSDK/MessageQueue.h"


//CUSTOM HEADERS
#define AEGP_MAX_STREAM_DIM 4

// This entry point is exported through the PiPL (.r file)
extern "C" DllExport AEGP_PluginInitFuncPrototype EntryPointFunc;
//define the Panelator UI class we'll be using globally, so it can be accessed from anywhere

//function to convert string into a Long
A_Err StringToLong(const A_char* string, A_long* value) {
	A_Err err = A_Err_NONE;
	A_long temp = 0;
	A_long sign = 1;
	A_long i = 0;
	if (string[0] == '-') {
		sign = -1;
		i++;
	}
	for (; string[i] != '\0'; ++i) {
		if (string[i] >= '0' && string[i] <= '9') {
			temp = temp * 10 + (string[i] - '0');
		}
		else {
			err = A_Err_GENERIC;
			break;
		}
	}
	//make sure value is all numbers, and not a negative sign
	if (err == A_Err_NONE) {
		*value = temp * sign;
	}

	return err;
}

