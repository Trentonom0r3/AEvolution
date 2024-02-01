#pragma once
#include "../include/Core.h"

int GetLayerNumEffects(LayerH layerH);

EffectRefH GetLayerEffectByIndex(LayerH layerH, int effect_indexL);

int GetInstalledKeyFromLayerEffect(EffectRefH effect_refH);

float GetEffectFlags(EffectRefH effect_refH);

void SetEffectFlags(EffectRefH effect_refH, float mask, float effect_flags);

void ReorderEffect(EffectRefH effect_refH, int effect_indexL);

void EffectCallGeneric(EffectRefH effectH, void* extraPV);

void DisposeEffect(EffectRefH effectH);

EffectRefH ApplyEffect(LayerH layerH, int installed_key);

void DeleteLayerEffect(EffectRefH effect_refH);

int GetNumInstalledEffects();

int GetNextInstalledEffect(int key);

void GetEffectName(int installed_key, std::string nameZ);

std::string GetEffectMatchName(int installed_keyZ);

void GetEffectCategory(int installed_key, std::string categoryZ);

EffectRefH DuplicateEffect(EffectRefH orig_effect_refH);

int NumEffectMask(EffectRefH effect_refH);

int GetEffectMaskID(EffectRefH effect_refH, int mask_indexL);

StreamRefH AddEffectMask(EffectRefH effect_refH, int id_val);

void RemoveEffectMask(EffectRefH effect_refH, int id_val);

StreamRefH SetEffectMask(EffectRefH effect_refH, int mask_indexL, int id_val);



