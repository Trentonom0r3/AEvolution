#pragma once
#include "include/Core.h"
#include "include/MessageQueue.h"

AEvolution_API int GetLayerNumEffects(LayerH layerH);

AEvolution_API EffectRefH GetLayerEffectByIndex(LayerH layerH, int effect_indexL);

AEvolution_API int GetInstalledKeyFromLayerEffect(EffectRefH effect_refH);

AEvolution_API float GetEffectFlags(EffectRefH effect_refH);

AEvolution_API void SetEffectFlags(EffectRefH effect_refH, float mask, float effect_flags);

AEvolution_API void ReorderEffect(EffectRefH effect_refH, int effect_indexL);

AEvolution_API void EffectCallGeneric(EffectRefH effectH, void* extraPV);

AEvolution_API void DisposeEffect(EffectRefH effectH);

AEvolution_API EffectRefH ApplyEffect(LayerH layerH, int installed_key);

AEvolution_API void DeleteLayerEffect(EffectRefH effect_refH);

AEvolution_API int GetNumInstalledEffects();

AEvolution_API int GetNextInstalledEffect(int key);

AEvolution_API void GetEffectName(int installed_key, std::string nameZ);

AEvolution_API std::string GetEffectMatchName(int installed_keyZ);

AEvolution_API void GetEffectCategory(int installed_key, std::string categoryZ);

AEvolution_API EffectRefH DuplicateEffect(EffectRefH orig_effect_refH);

AEvolution_API int NumEffectMask(EffectRefH effect_refH);

AEvolution_API int GetEffectMaskID(EffectRefH effect_refH, int mask_indexL);

AEvolution_API StreamRefH AddEffectMask(EffectRefH effect_refH, int id_val);

AEvolution_API void RemoveEffectMask(EffectRefH effect_refH, int id_val);

AEvolution_API StreamRefH SetEffectMask(EffectRefH effect_refH, int mask_indexL, int id_val);



