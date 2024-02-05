#pragma once
#include "../include/Core.h"
#include "../include/MessageQueue.h"


AEvolution_API int getNumLayers(CompH  compH);

AEvolution_API int getLayerIndex(LayerH layerH);

AEvolution_API std::string getLayerName(LayerH layerH);

AEvolution_API std::string getLayerSourceName(LayerH layerH);

AEvolution_API void setLayerName(LayerH layerH, const std::string& name);

AEvolution_API LayerH ActiveLayer();

AEvolution_API LayerH getLayerFromComp(CompH  compH, int index);

AEvolution_API void changeLayerIndex(LayerH layerH, int index);

AEvolution_API bool isAddLayerValid(AEvolution_API ItemH itemH, CompH  compH);

AEvolution_API LayerH AddLayer(AEvolution_API ItemH itemH, CompH  compH);

AEvolution_API ItemH getLayerSourceItem(LayerH layerH);

AEvolution_API int GetLayerSourceItemID(LayerH layerH);

AEvolution_API CompH GetLayerParentComp(LayerH layerH);

AEvolution_API std::string GetLayerQuality(LayerH layerH);

AEvolution_API void SetLayerQuality(LayerH layerH, int qualityint);

//gets flags for layer, any flags that are true are returned
//Result<AEGP_LayerFlags> GetLayerFlags(LayerH layerH); //DEAL WITH THIS LATER

// sets flag false or true given user input
//AEvolution_API void SetLayerFlag(LayerH layerH, LayerFlag flag, A_Boolean value);  //DEAL WITH THIS LATER

AEvolution_API bool IsLayerVideoReallyOn(LayerH layerH);

AEvolution_API bool IsLayerAudioReallyOn(LayerH layerH);

//AEvolution_API float GetLayerCurrentTime(LayerH layerH, AEGP_LTimeMode time_mode);

//AEvolution_API float GetLayerInPoint(LayerH layerH, AEGP_LTimeMode time_mode);

//AEvolution_API float GetLayerDuration(LayerH layerH, AEGP_LTimeMode time_mode);

//AEvolution_API void SetLayerInPointAndDuration(LayerH layerH, AEGP_LTimeMode time_mode, float in_point, float duration, float frameRate);

AEvolution_API float GetLayerOffset(LayerH layerH);

AEvolution_API void SetLayerOffset(LayerH layerH, float offsetH, float frameRate);

AEvolution_API float GetLayerStretch(LayerH layerH);

//AEvolution_API void SetLayerStretch(LayerH layerH, const A_Ratio& stretch); //deal with this later

//Result<AEGP_LayerTransferMode> GetLayerTransferMode(LayerH layerH);

//AEvolution_API void SetLayerTransferMode(LayerH layerH, const AEGP_LayerTransferMode mode);

//Result<A_FloatRect> GetLayerMaskedBounds(LayerH layerH, float intime, AEGP_LTimeMode comp_time, float frameRate);

//Result<AEGP_ObjectType> GetLayerObjectType(LayerH layerH);

AEvolution_API bool IsLayer3D(LayerH layerH);

AEvolution_API bool IsLayer2D(LayerH layerH);

//AEvolution_API bool IsVideoActive(LayerH layerH, AEGP_LTimeMode time_mode, float comp_timeH, float frameRate);

AEvolution_API bool IsLayerUsedAsTrackMatte(LayerH layerH, bool fill_must_be_active);

AEvolution_API bool DoesLayerHaveTrackMatte(LayerH layerH);

AEvolution_API float ConvertCompToLayerTime(LayerH layerH, float comp_time);

AEvolution_API float ConvertLayerToCompTime(LayerH layerH, float layer_time, float frameRate);

AEvolution_API float GetLayerDancingRandValue(LayerH layerH, float comp_time, float frameRate);

AEvolution_API int GetLayerID(LayerH layerH);

AEvolution_API LayerH GetLayerFromLayerID(AEvolution_API CompH parent_comp, int id);

//Result<AEGP_LabelID> GetLayerLabel(LayerH layerH);

//AEvolution_API void SetLayerLabel(LayerH layerH, AEGP_LabelID label);

//Result<AEGP_LayerSamplingQuality> GetLayerSamplingQuality(LayerH layerH);

//AEvolution_API void SetLayerSamplingQuality(LayerH layerH, AEGP_LayerSamplingQuality quality);

AEvolution_API LayerH GetTrackMatteLayer(LayerH layerH);

//AEvolution_API void SetTrackMatte(LayerH layerH, AEvolution_API LayerH track_matte_layer, AEGP_TrackMatte track_matte_type);

AEvolution_API void RemoveTrackMatte(LayerH layerH);

AEvolution_API void DeleteLayer(LayerH layerH);

AEvolution_API LayerH DuplicateLayer(LayerH layerH);

AEvolution_API LayerH GetLayerParent(LayerH layerH);

AEvolution_API void SetLayerParent(LayerH layerH, LayerH parent_layer);
