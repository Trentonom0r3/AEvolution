#include "CompCommands.h"
#include "../MessageQueueManager.h"

void GetCompFromItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_CompH compH;
	ERR(suites.CompSuite11()->AEGP_GetCompFromItem(item.handle, &compH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompFromItemResp>(compH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetItemFromCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH itemH;
	ERR(suites.CompSuite11()->AEGP_GetItemFromComp(comp.handle, &itemH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetItemFromCompResp>(itemH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompDownsampleFactorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_DownsampleFactor dsf;
	ERR(suites.CompSuite11()->AEGP_GetCompDownsampleFactor(comp.handle, &dsf));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompDownsampleFactorResp>(dsf, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompDownsampleFactorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompDownsampleFactor(comp.handle, &dsf));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompDownsampleFactorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompBGColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ColorVal bg_color;
	ERR(suites.CompSuite11()->AEGP_GetCompBGColor(comp.handle, &bg_color));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompBGColorResp>(bg_color, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompBGColorCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompBGColor(comp.handle, &bg_color));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompBGColorResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompFlagsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long flags;
	ERR(suites.CompSuite11()->AEGP_GetCompFlags(comp.handle, &flags));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompFlagsResp>(flags, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetShowLayerNameOrSourceNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean show;
	ERR(suites.CompSuite11()->AEGP_GetShowLayerNameOrSourceName(comp.handle, &show));
	boost::shared_ptr<Response> resp = boost::make_shared<GetShowLayerNameOrSourceNameResp>(show, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetShowLayerNameOrSourceNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetShowLayerNameOrSourceName(comp.handle, layer_names_shown));
	boost::shared_ptr<Response> resp = boost::make_shared<SetShowLayerNameOrSourceNameResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetShowBlendModesCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean show;
	ERR(suites.CompSuite11()->AEGP_GetShowBlendModes(comp.handle, &show));
	boost::shared_ptr<Response> resp = boost::make_shared<GetShowBlendModesResp>(show, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetShowBlendModesCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetShowBlendModes(comp.handle, show_blend_modes));
	boost::shared_ptr<Response> resp = boost::make_shared<SetShowBlendModesResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompFramerateCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_FpLong fps;
	ERR(suites.CompSuite11()->AEGP_GetCompFramerate(comp.handle, &fps));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompFramerateResp>(fps, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompFramerateCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompFrameRate(comp.handle, &fps));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompFramerateResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompShutterAnglePhaseCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Ratio angle;
	A_Ratio phase;
	ERR(suites.CompSuite11()->AEGP_GetCompShutterAnglePhase(comp.handle, &angle, &phase));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompShutterAnglePhaseResp>(angle, phase, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompShutterFrameRangeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time time;
	A_Time start;
	A_Time duration;
	ERR(suites.CompSuite11()->AEGP_GetCompShutterFrameRange(comp.handle, &time, &start, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompShutterFrameRangeResp>(duration, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompSuggestedMotionBlurSamplesCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long samples;
	ERR(suites.CompSuite11()->AEGP_GetCompSuggestedMotionBlurSamples(comp.handle, &samples));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompSuggestedMotionBlurSamplesResp>(samples, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompSuggestedMotionBlurSamplesCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompSuggestedMotionBlurSamples(comp.handle, samples));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompSuggestedMotionBlurSamplesResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompMotionBlurAdaptiveSampleLimitCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long samples;
	ERR(suites.CompSuite11()->AEGP_GetCompMotionBlurAdaptiveSampleLimit(comp.handle, &samples));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompMotionBlurAdaptiveSampleLimitResp>(samples, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompMotionBlurAdaptiveSampleLimitCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompMotionBlurAdaptiveSampleLimit(comp.handle, samples));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompMotionBlurAdaptiveSampleLimitResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompWorkAreaStartCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time start;
	ERR(suites.CompSuite11()->AEGP_GetCompWorkAreaStart(comp.handle, &start));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompWorkAreaStartResp>(start, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompWorkAreaDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time duration;
	ERR(suites.CompSuite11()->AEGP_GetCompWorkAreaDuration(comp.handle, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompWorkAreaDurationResp>(duration, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompWorkAreaStartAndDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompWorkAreaStartAndDuration(comp.handle, &start, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompWorkAreaStartAndDurationResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateSolidInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(utf_name);
	ERR(suites.CompSuite11()->AEGP_CreateSolidInComp(name.data(), width, height, &color, parent_comp.handle, &duration, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateSolidInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateCameraInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(utf_name);
	ERR(suites.CompSuite11()->AEGP_CreateCameraInComp(name.data(), center_point, parent_comp.handle, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateCameraInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateLightInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(utf_name);
	ERR(suites.CompSuite11()->AEGP_CreateLightInComp(name.data(), center_point, parent_comp.handle, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateLightInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_CompH compH;
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(utf_name);
	ERR(suites.CompSuite11()->AEGP_CreateComp(parent_folder.handle, name.data(), width, height, &pixel_aspect_ratio, &duration, &framerate, &compH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateCompResp>(compH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompDisplayStartTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time start_time;
	ERR(suites.CompSuite11()->AEGP_GetCompDisplayStartTime(comp.handle, &start_time));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompDisplayStartTimeResp>(start_time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompDisplayStartTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompDisplayStartTime(comp.handle, &start_time));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompDisplayStartTimeResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompDuration(comp.handle, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompDurationResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateNullInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(utf_name);
	ERR(suites.CompSuite11()->AEGP_CreateNullInComp(name.data(), parent_comp.handle, &duration, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateNullInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompPixelAspectRatioCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompPixelAspectRatio(comp.handle, &par));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompPixelAspectRatioResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateTextLayerInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	ERR(suites.CompSuite11()->AEGP_CreateTextLayerInComp(parent_comp.handle, select_new_layer, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateTextLayerInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateBoxTextLayerInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	ERR(suites.CompSuite11()->AEGP_CreateBoxTextLayerInComp(parent_comp.handle, select_new_layer, box_dimensions, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateBoxTextLayerInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompDimensionsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompDimensions(comp.handle, width, height));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompDimensionsResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void DuplicateCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_CompH compH;
	ERR(suites.CompSuite11()->AEGP_DuplicateComp(comp.handle, &compH));
	boost::shared_ptr<Response> resp = boost::make_shared<DuplicateCompResp>(compH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompFrameDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time duration;
	ERR(suites.CompSuite11()->AEGP_GetCompFrameDuration(comp.handle, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompFrameDurationResp>(duration, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetMostRecentlyUsedCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_CompH compH;
	ERR(suites.CompSuite11()->AEGP_GetMostRecentlyUsedComp(&compH));
	boost::shared_ptr<Response> resp = boost::make_shared<GetMostRecentlyUsedCompResp>(compH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void CreateVectorLayerInCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layerH;
	ERR(suites.CompSuite11()->AEGP_CreateVectorLayerInComp(parent_comp.handle, &layerH));
	boost::shared_ptr<Response> resp = boost::make_shared<CreateVectorLayerInCompResp>(layerH, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetNewCompMarkerStreamCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_StreamRefH marker;
	AEGP_PluginID* pluginID = SuiteManager::GetInstance().GetPluginID();
	ERR(suites.CompSuite11()->AEGP_GetNewCompMarkerStream(*pluginID, parent_comp.handle, &marker));
	boost::shared_ptr<Response> resp = boost::make_shared<GetNewCompMarkerStreamResp>(marker, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompDisplayDropFrameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean dropFrameB;
	ERR(suites.CompSuite11()->AEGP_GetCompDisplayDropFrame(comp.handle, &dropFrameB));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompDisplayDropFrameResp>(dropFrameB, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetCompDisplayDropFrameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.CompSuite11()->AEGP_SetCompDisplayDropFrame(comp.handle, dropFrameB));
	boost::shared_ptr<Response> resp = boost::make_shared<SetCompDisplayDropFrameResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}




















