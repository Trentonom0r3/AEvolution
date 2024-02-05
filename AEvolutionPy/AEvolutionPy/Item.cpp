#include "pch.h"
#include "Item.h"

std::string Item::name() {
	std::string name = getItemName(this->itemH);
	return name;
}

void Item::setName(std::string name)
{
	setItemName(this->itemH, name);
}

float Item::duration()
{
	return 0.0f;
}

float Item::currentTime()
{
	return 0.0f;
}

dimensionsH Item::getDimensions()
{
	return dimensionsH();
}

std::string Item::getComment()
{
	return std::string();
}

void Item::setComment(std::string comment)
{
}

bool Item::isSelected()
{
	return false;
}

void Item::setSelected(bool selected)
{
}

float Item::currentTimeInComp()
{
	return 0.0f;
}

void Item::setCurrentTimeInComp(float time)
{
}

void Item::setProxy(bool useProxy)
{
}



ItemH Item::getItemH() {
	return itemH;
}

void Item::deleteItem()
{
}
