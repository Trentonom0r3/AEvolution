#pragma once
#include "MessageQueueManager.h"

Result<Collection2H> NewCollection();

Result<null> DisposeCollection(Collection2H collection);

Result<int> GetCollectionNumItems(Collection2H collection);

Result<CollectionItemV2> GetCollectionItemByIndex(Collection2H collection, int index);

Result<null> CollectionPushBack(Collection2H collection, CollectionItemV2 item);

Result<null> CollectionErase(Collection2H collection, Range range);