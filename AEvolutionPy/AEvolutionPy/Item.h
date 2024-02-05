#pragma once
#include "MessageQueue.h"

class FolderItem;

class Item {
public:
	virtual ~Item() {}

	Item(ItemH itemH) : itemH(itemH) {}

	Item(const Item& item) : itemH(item.itemH) {}

	std::string name();

	void setName(std::string name);

	float duration();

	float currentTime();

	dimensionsH getDimensions();

	std::string getComment();

	void setComment(std::string comment);

	bool isSelected();

	void setSelected(bool selected);

	float currentTimeInComp();

	void setCurrentTimeInComp(float time);

	void setProxy(bool useProxy);

	FolderItem getParent();

	void setParent(FolderItem parent);

	ItemH getItemH();

	void deleteItem();
protected:
	ItemH itemH;

};
