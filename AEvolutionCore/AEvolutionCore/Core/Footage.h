#pragma once

#include "../include/Core.h"


FootageH createFootage(const std::string& path);

void disposeFootage(FootageH footageH);

ItemH addFootageToProject(FootageH footageH, ItemH parentFolderH);

using colors = std::tuple<float, float, float, float>;

colors GetItemSolidColor(ItemH itemH, bool proxyB);

void SetSolidColor(ItemH itemH, bool proxyB, colors color);

using dimensions = std::tuple<float, float>;

dimensions GetSolidDimensions(ItemH itemH, bool proxyB);

void SetSolidDimensions(ItemH itemH, bool proxyB, dimensions dims);

FootageH GetMainFootageFromItem(ItemH itemH);

FootageH GetProxyFootageFromItem(ItemH itemH);

std::pair<int, int> GetFootageNumFiles(FootageH footageH);

std::string GetFootagePath(FootageH footageH, int frameNum, int fileIndex);

//FootageSignature GetFootageSignature(FootageH footageH);

void SetItemProxyFootage(FootageH footageH, ItemH itemH);

ItemH ReplaceItemMainFootage(FootageH footageH, ItemH itemH);

//void SetFootageInterpretation(ItemH itemH, bool proxyB, FootageInterp interpP);

//FootageInterp GetFootageInterpretation(ItemH itemH, bool proxyB);

//FootageLayerKey GetFootageLayerKey(FootageH footageH);

FootageH NewPlaceholderFootage(const std::string& name,
		float width, float height, float duration, float frameRate);

//FootageH NewPlaceholderFootageWithPath(const std::string& path, Platform path_platform, FileType file_type,
		//float width, float height, float duration, float frameRate);

FootageH NewSolidFootage(const std::string& name, float width, float height, colors color);

//SoundDataFormat GetFootageSoundDataFormat(FootageH footageH);

//FileSequenceImportOptions GetFootageSequenceImportOptions(FootageH footageH);



