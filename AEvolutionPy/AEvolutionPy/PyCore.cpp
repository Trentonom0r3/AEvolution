#include "pch.h"
#include "PyCore.h"

void UndoGroup::beginUndoGroup(const std::string& name)
{
	StartUndoGroup(name);
}

void UndoGroup::endUndoGroup()
{
	EndUndoGroup();
}
