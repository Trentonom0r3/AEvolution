#include "pch.h"

Result<Item> GetFirstProjItem();

Result<Item> GetNextProjItem(Item item);

Result<Item> GetActiveItem();

Result<bool> IsItemSelected(Item item);

Result<bool> SelectItem(Item item, bool select, bool deselectOthers);

Result<ItemType> GetItemType(Item item);

Result<std::string> GetItemName(Item item);

Result<null> SetItemName(Item item, std::string name);

Result<int> GetItemID(Item item);

Result<null> SetItemUseProxy(Item item, bool useProxy);

Result<Item> GetItemParentFolder(Item item);

Result<null> SetItemParentFolder(Item item, Item parentFolder);

Result<AETime> GetItemDuration(Item item);

Result<int> GetItemCurrentTime(Item item);

Result<Size> GetItemDimensions(Item item);