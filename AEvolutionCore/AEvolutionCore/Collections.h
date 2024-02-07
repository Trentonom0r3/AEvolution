#pragma once
#include "include/Core.h"
#include "include/MessageQueue.h"

AEvolution_API Collection2H newCollection();

AEvolution_API void disposeCollection(Collection2H collection);

AEvolution_API int getCollectionNumItems(Collection2H collection);

AEvolution_API CollectionItemH getCollectionItemByIndex(Collection2H collection, int index);

AEvolution_API void collectionPushBack(Collection2H collection, CollectionItemH item);

AEvolution_API void collectionErase(Collection2H collection, int index_first, int index_last);



