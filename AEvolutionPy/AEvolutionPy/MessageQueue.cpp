#include "pch.h"
#include "MessageQueue.h"


ItemType checkType(ItemH itemH){
std::string itemType = getItemType(itemH);
std::cout << "Item type: " << itemType << std::endl;
if (itemType == "Folder") {
	std::cout << "Folder" << std::endl;
	return ItemType::Folder;
}
else if (itemType == "Comp") {
	std::cout << "Comp" << std::endl;
	return ItemType::Comp;
}
else if (itemType == "Footage") {
	std::cout << "Footage" << std::endl;
	return ItemType::Footage;
}
else {
	throw std::invalid_argument("Invalid item type");
}
}