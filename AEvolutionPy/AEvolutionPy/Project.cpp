#include "pch.h"
#include "Base.h"

std::string Project::name() {
	std::string name = GetProjectName(this->projectH);
	return name;
}

std::string Project::path() {
	std::string path = GetProjectPath(this->projectH);
	return path;
}

void Project::saveToPath(std::string path) {
	SaveProjectToPath(this->projectH, path);
}

bool Project::isDirty() {
	bool dirty = IsProjectDirty(this->projectH);
	return dirty;
}

void Project::saveAs(std::string path) {
	SaveProjectAs(this->projectH, path);
}

std::string Project::bitDepth() {
	std::string bitDepth = GetProjectBitDepth(this->projectH);
	return bitDepth;
}

void Project::setBitDepth(std::string bitDepth) {
	SetProjectBitDepth(this->projectH, bitDepth);
}

std::unique_ptr<Item> Project::GetActiveItem() {
    ItemH itemH = getActiveItem();
    ItemType type = checkType(itemH);
    std::cout << "Item type: " << type << std::endl;
    if (type == ItemType::Folder) {
        std::cout << "Returning Folder" << std::endl;
        return std::make_unique<FolderItem>(itemH);
    }
    else if (type == ItemType::Comp) {
        std::cout << "Returning Comp" << std::endl;
        return std::make_unique<CompItem>(itemH);
    }
    else if (type == ItemType::Footage) {
        std::cout << "Returning Footage" << std::endl;
        return std::make_unique<FootageItem>(itemH);
    }
    else {
        std::cout << "Returning Item" << std::endl;
        return std::make_unique<Item>(itemH);
    }
}


