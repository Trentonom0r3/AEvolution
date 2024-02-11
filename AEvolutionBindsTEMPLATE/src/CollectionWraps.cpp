#include "pch.h"
#include "CollectionWraps.h"

Result<Collection2H> NewCollection() {
	Command cmd(CommandID::NewCollection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Collection2H> result = boost::get<Result<Collection2H>>(res.args[0]);
	return result;
}

Result<null> DisposeCollection(Collection2H collection) {
	Command cmd(CommandID::DisposeCollection);
	cmd.args.push_back(collection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}

Result<int> GetCollectionNumItems(Collection2H collection) {
	Command cmd(CommandID::GetCollectionNumItems);
	cmd.args.push_back(collection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<int> result = boost::get<Result<int>>(res.args[0]);
	return result;
}

Result<CollectionItemV2> GetCollectionItemByIndex(Collection2H collection, int index) {
	Command cmd(CommandID::GetCollectionItemByIndex);
	cmd.args.push_back(collection);
	cmd.args.push_back(index);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<CollectionItemV2> result = boost::get<Result<CollectionItemV2>>(res.args[0]);
	return result;
}

Result<null> CollectionPushBack(Collection2H collection, CollectionItemV2 item) {
	Command cmd(CommandID::CollectionPushBack);
	cmd.args.push_back(collection);
	cmd.args.push_back(item);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}

Result<null> CollectionErase(Collection2H collection, Range range) {
	Command cmd(CommandID::CollectionErase);
	cmd.args.push_back(collection);
	cmd.args.push_back(range);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}

class Collection {
public:
	Collection2H collection;
	int collectionSize;
	Collection() {
		Result<Collection2H> result = NewCollection();
		if (result.error != "A_Err_NONE") {
			throw std::runtime_error(result.error);
		}
		collection = result.value;
	}

	Collection(Collection2H collection) : collection(collection) {
		collectionSize = GetCollectionNumItems(collection).value;
	}

	~Collection() {
		DisposeCollection(collection);
	}
	void push_back(CollectionItemV2 item) {
		CollectionPushBack(collection, item);
		collectionSize++;
	}
	void erase(Range range) {
		CollectionErase(collection, range);
		collectionSize -= range.index_lastL - range.index_firstL;
	}
	int size() const {
		Result<int> result = GetCollectionNumItems(collection);
		if (result.error != "A_Err_NONE") {
			throw std::runtime_error(result.error);
		}
		return result.value;
	}

	CollectionItemV2 operator[](int index) const {
		if (index < 0 || index >= collectionSize) {
			throw std::out_of_range("Index out of range");
		}
		Result<CollectionItemV2> result = GetCollectionItemByIndex(collection, index);
		if (result.error != "A_Err_NONE") {
			throw std::runtime_error(result.error);
		}
		return result.value;
	}

	auto begin() const {
		return boost::make_transform_iterator(boost::counting_iterator<int>(0), [this](int index) {
			return (*this)[index];
			});
	}

	auto end() const {
		return boost::make_transform_iterator(boost::counting_iterator<int>(size()), [this](int index) {
			return (*this)[index];
			});
	}
};

class LayerCollection : public Collection {
public:
	using Collection::Collection;

	void push_back(Layer layer) {
		StreamRef stream(createUUID()); //actually will use getstreamfromLayer.
		LayerCollectionItem layerItem(layer, createUUID());
		CollectionItemV2 item(AEGP_CollectionItemType_LAYER, layerItem, stream, createUUID());
		Collection::push_back(item);
	}

	Layer operator[](int index) {
		CollectionItemV2 item = Collection::operator[](index);
		LayerCollectionItem layerItem = boost::get<LayerCollectionItem>(item.u);
		return layerItem.layer;
	}

	void erase(Range range) {
		Collection::erase(range);
	}

	int size() {
		return Collection::size();
	}

};
