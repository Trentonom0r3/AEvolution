#pragma once
#include "MessageQueue.h"

class Item; // Forward declaration

class Project {
public:
	Project() {
		this->projectH = getProject();
	};

	std::string name();

	std::string path();

	void saveToPath(std::string path);

	bool isDirty();

	void saveAs(std::string path);

	std::string bitDepth();

	void setBitDepth(std::string bitDepth);

	std::unique_ptr<Item> GetActiveItem();
protected:
	ProjectH projectH;

};
