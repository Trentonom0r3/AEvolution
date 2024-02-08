#include "pch.h"
#include "Item.h"
#include "Folder.h"

std::string Item::name() {
	std::string name = getItemName(this->itemH);
	return name;
}

float Item::getUUID()
{
	return getUniqueItemID(this->itemH);
}

void Item::setName(std::string name)
{
	SetItemName(this->itemH, name);
}

float Item::duration()
{
	return getItemDuration(this->itemH);
}

float Item::currentTime()
{
	return getItemCurrentTime(this->itemH);
}

std::tuple<float, float> Item::getDimensions()
{
	dimensionsH dimensions= getItemDimensions(this->itemH);
	return std::make_tuple(dimensions.width, dimensions.height);
}

std::string Item::getComment()
{
	return getItemComment(this->itemH);
}

void Item::setComment(std::string comment)
{
	setItemComment(this->itemH, comment);
}

bool Item::isSelected()
{
	return isItemSelected(this->itemH);
}

void Item::setSelected(bool selected)
{
	selectItem(this->itemH, selected, FALSE); //deselect others is false
}

/*

float Item::currentTimeInComp()
{

}

void Item::setCurrentTimeInComp(float time)
{
}

*/

void Item::setProxy(bool useProxy)
{
	setItemUseProxy(this->itemH, useProxy);
	proxyH = useProxy;
}

bool Item::getProxy()
{
	return proxyH;
}

FolderItem Item::getParent()
{
	ItemH parent = getItemParentFolder(this->itemH);
	return FolderItem(parent);
}

void Item::setParent(FolderItem parent)
{
	SetItemParentFolder(this->itemH, parent.getItemH());
}



ItemH Item::getItemH() {
	return itemH;
}

void Item::Delete()
{
	deleteItem(this->itemH);
}
