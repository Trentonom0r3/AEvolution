#include "../src/commands/Items.h"
#include "MessageQueueManager.h"

void GetActiveItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH item;
	ERR(suites.ItemSuite6()->AEGP_GetActiveItem(&item));

	auto gai = boost::make_shared<GetActiveItem>(item, errToString(err)); // Correctly creating a shared_ptr to GAI
	MessageQueueManager::getInstance().sendResponse(gai);
}

void GetItemTypeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemType type;
	ERR(suites.ItemSuite6()->AEGP_GetItemType(item.handle, &type));

	auto git = boost::make_shared<GetItemType>(type, errToString(err));
	MessageQueueManager::getInstance().sendResponse(git);
}

BOOST_CLASS_EXPORT(GetActiveItem)
BOOST_CLASS_EXPORT(GetActiveItemCmd)
BOOST_CLASS_EXPORT(GetItemType)
BOOST_CLASS_EXPORT(GetItemTypeCmd)


