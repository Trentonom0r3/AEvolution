#pragma once
#include "include/Core.h"
#include "include/MessageQueue.h"
/*
CompH compH= RAIIResult<AEGP_CompH>;
Result<AEGP_CompH> comp = compH->getResult()
*/
//define AEvolution_API for everything

AEvolution_API CompH addComp(const std::string& name, dimensionsH dimensions, float frameRate, float duration, float pixelAspectRatio, ItemH parentFolder);

AEvolution_API CompH GetCompFromItem(ItemH itemH);

AEvolution_API ItemH GetItemFromComp(CompH compH);

AEvolution_API std::pair<int, int> GetCompDownsampleFactor(CompH compH);

AEvolution_API void SetCompDownsampleFactor(CompH compH, std::pair<int, int> factor);

AEvolution_API colorH GetCompBGColor(CompH compH);

AEvolution_API void SetCompBGColor(CompH compH, colorH color);

AEvolution_API float getCompFlags(CompH compH);

AEvolution_API bool getShowLayerNameOrSourceName(CompH compH);

AEvolution_API void setShowLayerNameOrSourceName(CompH compH, bool showLayerNames);

AEvolution_API bool getShowBlendModes(CompH compH);

AEvolution_API void setShowBlendModes(CompH compH, bool showBlendModes);

AEvolution_API float getCompFramerate(CompH compH);

AEvolution_API void setCompFramerate(CompH compH, float fps);

AEvolution_API std::pair<float, float> getCompShutterAnglePhase(CompH compH);

AEvolution_API void setCompSuggestedMotionBlurSamples(CompH compH, int samples);

AEvolution_API float getCompWorkAreaStart(CompH compH);

AEvolution_API float getCompWorkAreaDuration(CompH compH);

AEvolution_API void setCompWorkAreaStartAndDuration(CompH compH, float start, float dur);

AEvolution_API LayerH createSolidInComp(const std::string& name, dimensionsH dimensions, colorH color, CompH parentCompH, float dur);

AEvolution_API LayerH createCameraInComp(const std::string& name, dimensionsH position, CompH parentCompH);

AEvolution_API LayerH createLightInComp(const std::string& name, dimensionsH position, CompH parentCompH);

//AEvolution_API std::vector<LayerH> getNewCollectionFromCompSelection(CompH compH);

//AEvolution_API void setSelection(CompH compH, Collection2H collectionH);

AEvolution_API float getCompDisplayStartTime(CompH compH);

AEvolution_API void setCompDisplayStartTime(CompH compH, float startTimeInSeconds);

AEvolution_API void setCompDuration(CompH compH, float durationInSeconds);

AEvolution_API LayerH createNullInComp(const std::string& name, CompH parentCompH, float dur);

AEvolution_API void setCompPixelAspectRatio(CompH compH, float pixelAspect);

AEvolution_API CompH duplicateComp(CompH compH);

AEvolution_API float getCompFrameDuration(CompH compH);

AEvolution_API CompH getMostRecentlyUsedComp();

AEvolution_API LayerH createVectorLayerInComp(CompH parentCompH);

AEvolution_API StreamRefH getNewCompMarkerStream(CompH parentCompH);

AEvolution_API bool getCompDisplayDropFrame(CompH compH);

AEvolution_API void setCompDisplayDropFrame(CompH compH, bool dropFrame);

AEvolution_API void reorderCompSelection(CompH compH, int index);


