#pragma once
#include "MessageQueue.h"

class FolderItem;

class Item {
public:
	virtual ~Item() {}
	Item() : itemH(nullptr) {}

	Item(ItemH itemH) : itemH(itemH) {}

	Item(const Item& item) : itemH(item.itemH) {}

	std::string name();

	void setName(std::string name);

	float duration();

	float currentTime();

	std::tuple<float, float> getDimensions();

	std::string getComment();

	void setComment(std::string comment);

	bool isSelected();

	void setSelected(bool selected);

	//float currentTimeInComp();

	//void setCurrentTimeInComp(float time);

	void setProxy(bool useProxy);

	bool getProxy();

	FolderItem getParent();

	void setParent(FolderItem parent);

	ItemH getItemH();

	void Delete();
protected:
	ItemH itemH;
	bool proxyH;
};
