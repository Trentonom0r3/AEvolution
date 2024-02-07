#pragma once

#include "include/Core.h"
#include "include/MessageQueue.h"


AEvolution_API FootageH createFootage(const std::string& path);

AEvolution_API void disposeFootage(FootageH footageH);

AEvolution_API ItemH addFootageToProject(FootageH footageH, ItemH parentFolderH);

AEvolution_API colorH GetItemSolidColor(ItemH itemH, bool proxyB);

AEvolution_API void SetSolidColor(ItemH itemH, bool proxyB, colorH color);

AEvolution_API dimensionsH GetSolidDimensions(ItemH itemH, bool proxyB);

AEvolution_API void SetSolidDimensions(ItemH itemH, bool proxyB, dimensionsH dims);

AEvolution_API FootageH GetMainFootageFromItem(ItemH itemH);

AEvolution_API FootageH GetProxyFootageFromItem(ItemH itemH);

AEvolution_API std::pair<int, int> GetFootageNumFiles(FootageH footageH);

AEvolution_API std::string GetFootagePath(FootageH footageH, int frameNum, int fileIndex);

//FootageSignature GetFootageSignature(FootageH footageH);

AEvolution_API void SetItemProxyFootage(FootageH footageH, ItemH itemH);

AEvolution_API ItemH ReplaceItemMainFootage(FootageH footageH, ItemH itemH);

//void SetFootageInterpretation(ItemH itemH, bool proxyB, FootageInterp interpP);

//FootageInterp GetFootageInterpretation(ItemH itemH, bool proxyB);

//FootageLayerKey GetFootageLayerKey(FootageH footageH);

AEvolution_API FootageH NewPlaceholderFootage(const std::string& name,
		dimensionsH dimensions, float duration, float frameRate);

//FootageH NewPlaceholderFootageWithPath(const std::string& path, Platform path_platform, FileType file_type,
		//float width, float height, float duration, float frameRate);

AEvolution_API FootageH NewSolidFootage(const std::string& name, float width, float height, colorH color);

//SoundDataFormat GetFootageSoundDataFormat(FootageH footageH);

//FileSequenceImportOptions GetFootageSequenceImportOptions(FootageH footageH);



