#pragma once
#include "MessageQueue.h"
#include "Item.h"

class ItemCollection;

class FolderItem : public Item {
public:
	using Item::Item;
	virtual ~FolderItem() {}
	ItemCollection getChildren();

	static FolderItem create(std::string name, ItemH parent);

};