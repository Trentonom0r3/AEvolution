#pragma once
#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"
#include <python.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>  // for the embedded interpreter
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/functional.h>

namespace py = pybind11;

using CommandH = boost::shared_ptr<Command>;
using ResponseH = boost::shared_ptr<Response>;

inline void GetActiveItemCmd::execute() {};
inline void GetItemTypeCmd::execute() {};

AE_Item getactiveitem() {
	CommandH cmd = boost::make_shared<GetActiveItemCmd>();
	ResponseH resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto respCast = boost::dynamic_pointer_cast<GetActiveItem>(resp);
	if (respCast) {
		return respCast->item;
	}
}

AEGP_ItemType getitemtype(AE_Item item) {
	try {
	CommandH cmd = boost::make_shared<GetItemTypeCmd>(item);
	ResponseH resp = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto respCast = boost::dynamic_pointer_cast<GetItemType>(resp);
	if (respCast) {
		return respCast->type;
	}
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
