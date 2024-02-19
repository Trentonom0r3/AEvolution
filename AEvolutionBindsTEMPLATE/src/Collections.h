#pragma once

#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"

class wLayer;
class wFolder;
class wComp;
class wItem;
/*
* Collection interface
* This is a generic interface for a collection of things.
*/
template<typename ItemType, typename U>
class Collection {
public:
    virtual ~Collection() = default;

    virtual std::size_t size() const = 0;
    virtual ItemType& operator[](std::size_t index) = 0;
    virtual const ItemType& operator[](std::size_t index) const = 0;
    virtual void append(const U& item) = 0;
    virtual void remove(std::size_t index) = 0;
    virtual std::vector<ItemType> getAllItems() const = 0;
};

class wLayerCollection : public Collection<wLayer, wItem> {
public:
    wLayerCollection(wComp comp);
    ~wLayerCollection() override = default;

    std::size_t size() const override; // Get the number of layers in the collection
    wLayer& operator[](std::size_t index) override; // Get a layer by index
    const wLayer& operator[](std::size_t index) const override; // Get a layer by index
    void append(const wItem& layer) override; // Add a layer to the collection
    void remove(std::size_t index) override; // Remove a layer from the collection
    std::vector<wLayer> getAllItems() const override; // Get all layers in the collection

private:
    wComp comp;
    std::vector<wLayer> layers;
};

class wItemCollection : public Collection<std::unique_ptr<wItem>, std::unique_ptr<wItem>> {
    public:
	wItemCollection(wFolder folder);
	~wItemCollection() override = default;

	std::size_t size() const override; // Get the number of items in the collection
    std::unique_ptr<wItem>& operator[](std::size_t index) override; // Get an item by index
	const std::unique_ptr<wItem>& operator[](std::size_t index) const override; // Get an item by index
	void append(const std::unique_ptr<wItem>& item) override; // Add an item to the collection
	void remove(std::size_t index) override; // Remove an item from the collection
	std::vector<std::unique_ptr<wItem>> getAllItems() const override; // Get all items in the collection

private:
    wFolder folder;
	std::vector<std::unique_ptr<wItem>> items;
};

using wProjectCollection = wItemCollection;