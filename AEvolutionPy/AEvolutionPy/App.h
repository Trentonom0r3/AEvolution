#pragma once
#include "MessageQueue.h"

class Project;

class App {
public:
	App() {};

	void reportInfo(std::string info);

	std::string path();

	Project getProject();

};
