#include "pch.h"
#include "include/MessageQueue.h"

std::string createUUID() {
	// Use the generate_uuid method from the UUID class
	std::string myUUID = CustomUUID::generate_uuid();
	return myUUID;
}