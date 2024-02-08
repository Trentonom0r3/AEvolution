#pragma once
#include "MessageQueue.h"
#include "Item.h"

class FootageItem : public Item {
public:
	using Item::Item;

	virtual ~FootageItem() {}
	static FootageItem create(std::string name, ItemH parent = getProjectRootFolder());

};