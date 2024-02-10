#pragma once
#include "MessageQueueManager.h"


Result<Item> GetFirstProjItem();

Result<Item> GetNextProjItem(Item item);

Result<Item> GetActiveItem();

Result<bool> IsItemSelected(Item item);

Result<bool> SelectItem(Item item, bool select, bool deselectOthers);

Result<AEGP_ItemType> GetItemType(Item item);

Result<std::string> GetItemName(Item item);

Result<null> SetItemName(Item item, std::string name);

Result<int> GetItemID(Item item);

Result<null> SetItemUseProxy(Item item, bool useProxy);

Result<Item> GetItemParentFolder(Item item);

Result<null> SetItemParentFolder(Item item, Item parentFolder);

Result<AETime> GetItemDuration(Item item);

Result<int> GetItemCurrentTime(Item item);

Result<Size> GetItemDimensions(Item item);

Result<double> GetItemPixelAspectRatio(Item item);

Result<null> DeleteItem(Item item);

Result<std::string> GetItemComment(Item item);

Result<Item> CreateNewFolder(std::string name, Item parentFolder);

Result<null> SetItemCurrentTime(Item item, AETime time);

Result<null> SetItemComment(Item item, std::string comment);

Result<AEGP_LabelID> GetItemLabel(Item item);

Result<null> SetItemLabel(Item item, AEGP_LabelID label);