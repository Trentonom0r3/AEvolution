#pragma once
#include "..\CoreSDK\Core.h"

Result<PF_Pixel8*> getBaseAddr8(Result<AEGP_WorldH> frameH);

Result<size> getSize(Result<AEGP_WorldH> frameH);