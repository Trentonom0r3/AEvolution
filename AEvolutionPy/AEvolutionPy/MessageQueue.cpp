#include "pch.h"
#include "MessageQueue.h"


ItemType checkType(ItemH itemH){

std::string itemType = getItemType(itemH);

if (itemType == "Folder") {
	return ItemType::Folder;
}
else if (itemType == "Comp") {
	return ItemType::Comp;
}
else if (itemType == "Footage") {
	return ItemType::Footage;
}
else {
	throw std::invalid_argument("Invalid item type");
}
}