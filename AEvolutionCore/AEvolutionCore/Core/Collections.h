#pragma once
#include "../include/Core.h"

Collection2H newCollection();

void disposeCollection(Collection2H collection);

int getCollectionNumItems(Collection2H collection);

CollectionItemH getCollectionItemByIndex(Collection2H collection, int index);

void collectionPushBack(Collection2H collection, CollectionItemH item);

void collectionErase(Collection2H collection, int index_first, int index_last);



