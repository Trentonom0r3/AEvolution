#pragma once
#include "..\CoreSDK\Utils.h"
#include "../CoreSDK/TaskUtils.h"
/*
CompH compH= RAIIResult<AEGP_CompH>;
Result<AEGP_CompH> comp = compH->getResult()
*/

CompH addComp(const std::string& name, std::pair<int, int> dimensions, float frameRate, float duration, float pixelAspectRatio, ItemH parentFolder);

CompH GetCompFromItem(ItemH itemH);

ItemH GetItemFromComp(CompH compH);

std::pair<int, int> GetCompDownsampleFactor(CompH compH);

void SetCompDownsampleFactor(CompH compH, std::pair<int, int> factor);

std::tuple<float, float, float, float> GetCompBGColor(CompH compH);

void SetCompBGColor(CompH compH, std::tuple<float, float, float, float> color);

float getCompFlags(CompH compH);

bool getShowLayerNameOrSourceName(CompH compH);

void setShowLayerNameOrSourceName(CompH compH, bool showLayerNames);

bool getShowBlendModes(CompH compH);

void setShowBlendModes(CompH compH, bool showBlendModes);

float getCompFramerate(CompH compH);

void setCompFramerate(CompH compH, float fps);

std::pair<A_Ratio, A_Ratio> getCompShutterAnglePhase(CompH compH);

void setCompSuggestedMotionBlurSamples(CompH compH, int samples);

float getCompWorkAreaStart(CompH compH);

float getCompWorkAreaDuration(CompH compH);

void setCompWorkAreaStartAndDuration(CompH compH, float start, float dur);

LayerH createSolidInComp(const std::string& name, std::tuple<int, int> dimensions, std::tuple<float, float, float, float> color, CompH parentCompH, float dur);

LayerH createCameraInComp(const std::string& name, std::pair<float, float> position, CompH parentCompH);

LayerH createLightInComp(const std::string& name, std::pair<float, float> position, CompH parentCompH);

std::vector<LayerH> getNewCollectionFromCompSelection(CompH compH);

void setSelection(CompH compH, Collection2H collectionH);

float getCompDisplayStartTime(CompH compH);

void setCompDisplayStartTime(CompH compH, float startTimeInSeconds);

void setCompDuration(CompH compH, float durationInSeconds);

LayerH createNullInComp(const std::string& name, CompH parentCompH, float dur);

void setCompPixelAspectRatio(CompH compH, float pixelAspect);

CompH duplicateComp(CompH compH);

float getCompFrameDuration(CompH compH);

CompH getMostRecentlyUsedComp();

LayerH createVectorLayerInComp(CompH parentCompH);

StreamRefH getNewCompMarkerStream(CompH parentCompH);

bool getCompDisplayDropFrame(CompH compH);

void setCompDisplayDropFrame(CompH compH, bool dropFrame);

void reorderCompSelection(CompH compH, int index);


