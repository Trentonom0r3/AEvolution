#pragma once
#include "../include/Core.h"


Result<AEGP_FrameReceiptH> renderAndCheckoutFrame(Result<AEGP_RenderOptionsH> roH);

Result<AEGP_WorldH> getReceiptWorld(Result<AEGP_FrameReceiptH> receiptH);

Result<void> checkinFrame(Result<AEGP_FrameReceiptH> receiptH);
