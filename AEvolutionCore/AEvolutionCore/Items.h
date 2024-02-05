#pragma once
#include "include/Core.h"
#include "include/MessageQueue.h"

AEvolution_API ItemH getActiveItem();

AEvolution_API std::string getItemType(ItemH item);

AEvolution_API std::string getItemName(ItemH item);

AEvolution_API void setItemName(ItemH item, const std::string& name);

AEvolution_API float getItemDuration(ItemH item);

AEvolution_API float getItemCurrentTime(ItemH item);

AEvolution_API dimensionsH getItemDimensions(ItemH item);

AEvolution_API float getItemPixelAspectRatio(ItemH item);

AEvolution_API void deleteItem(ItemH item);

AEvolution_API std::string getItemComment(ItemH item);

AEvolution_API void setItemComment(ItemH item, const std::string& comment);

//AEGP_LabelID getItemLabel(ItemH item);

//void setItemLabel(ItemH item, AEGP_LabelID label);

//AEGP_ItemViewP getItemMRUView(ItemH item);

AEvolution_API float getUniqueItemID(ItemH item);

AEvolution_API ItemH createFolderItem(const std::string& name, ItemH parentFolder);

AEvolution_API ItemH getFirstProjItem(ProjectH project);

AEvolution_API ItemH getNextProjItem(ProjectH project, ItemH currentItem);

AEvolution_API bool isItemSelected(ItemH item);

AEvolution_API void selectItem(ItemH item, bool select, bool deselectOthers);

AEvolution_API float getItemFlags(ItemH item);

AEvolution_API float getCompItemCurrentTime(ItemH item, float frameRate);

AEvolution_API void setCompItemCurrentTime(ItemH item, float time, float frameRate);

AEvolution_API void setItemUseProxy(ItemH item, bool useProxy);

AEvolution_API ItemH getItemParentFolder(ItemH item);

AEvolution_API void setItemParentFolder(ItemH item, ItemH parentFolder);











