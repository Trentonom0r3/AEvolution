#include "pch.h"
#include "Folder.h"
#include "Collection.h"

std::shared_ptr<ItemCollection> FolderItem::getChildren()
{
	return std::make_shared<ItemCollection>(std::make_unique<FolderItem>(*this));
}

FolderItem FolderItem::create(std::string name, ItemH parent)
{
	ItemH itemH = createFolderItem(name, parent);
}
