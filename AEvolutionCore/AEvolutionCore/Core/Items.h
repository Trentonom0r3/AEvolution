#pragma once
#include "../include/Core.h"

ItemH getActiveItem();

std::string getItemType(ItemH item);

std::string getItemName(ItemH item);

void setItemName(ItemH item, const std::string& name);

float getItemDuration(ItemH item);

float getItemCurrentTime(ItemH item);

using dimensions = std::tuple<float, float>;
using colors = std::tuple<float, float, float, float>;

dimensions getItemDimensions(ItemH item);

float getItemPixelAspectRatio(ItemH item);

void deleteItem(ItemH item);

std::string getItemComment(ItemH item);

void setItemComment(ItemH item, const std::string& comment);

//AEGP_LabelID getItemLabel(ItemH item);

//void setItemLabel(ItemH item, AEGP_LabelID label);

//AEGP_ItemViewP getItemMRUView(ItemH item);

float getUniqueItemID(ItemH item);

ItemH createFolderItem(const std::string& name, ItemH parentFolder);

ItemH getFirstProjItem(ProjectH project);

ItemH getNextProjItem(ProjectH project, ItemH currentItem);

bool isItemSelected(ItemH item);

void selectItem(ItemH item, bool select, bool deselectOthers);

float getItemFlags(ItemH item);

float getCompItemCurrentTime(ItemH item, float frameRate);

void setCompItemCurrentTime(ItemH item, float time, float frameRate);

void setItemUseProxy(ItemH item, bool useProxy);

ItemH getItemParentFolder(ItemH item);

void setItemParentFolder(ItemH item, ItemH parentFolder);

ItemH createFolderItem(const std::string& name, ItemH parentFolder);










