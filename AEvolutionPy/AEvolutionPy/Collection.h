#pragma once
#include "MessageQueue.h"
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "Item.h"
#include "Comp.h"
#include "Folder.h"
#include "Layer.h"
template<typename T>
class Collection {
public:
    explicit Collection() {}

    // Utilizing rule of five for safe move semantics and deleting copy semantics
    Collection(Collection<T>&& other) noexcept = default;
    Collection& operator=(Collection<T>&& other) noexcept = default;
    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;
    virtual ~Collection() = default;

    // Initialize is a pure virtual function, enforcing derived classes to implement it
    virtual std::vector<std::unique_ptr<T>> initialize() = 0;

    std::size_t size() const {
        return items_.size();
    }

    T& operator[](std::size_t index) {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return *items_[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return *items_[index];
    }

    auto begin() { return items_.begin(); }
    auto end() { return items_.end(); }
    auto begin() const { return items_.cbegin(); }
    auto end() const { return items_.cend(); }

    virtual void append(std::unique_ptr<T> item) = 0;
    // Consideration for removal method needs careful handling of unique_ptr

    virtual std::unique_ptr<T> pop() {
        if (items_.empty()) {
            throw std::out_of_range("Collection is empty");
        }
        auto item = std::move(items_.back());
        items_.pop_back();
        return item;
    }

protected:
    std::vector<std::unique_ptr<T>> items_;
};

// Example derived class for ItemCollection
class ItemCollection : public Collection<Item> {
public:
    using Collection::Collection; // Inherit constructor
    explicit ItemCollection(std::unique_ptr<FolderItem> handle) : Collection() {
		items_ = initialize();
	}

    std::vector<std::unique_ptr<Item>> initialize() override {
        // Implementation of initializing items specific to ItemCollection
        return {};
    }

    void append(std::unique_ptr<Item> item) override {
        items_.push_back(std::move(item));
    }

    std::unique_ptr<Item> pop() override {
        if (items_.empty()) {
			throw std::out_of_range("Collection is empty");
		}
		auto item = std::move(items_.back());
		items_.pop_back();
		return item;
    }

private:
    std::unique_ptr<FolderItem> handle_;
};


// Example derived class for LayerCollection
class LayerCollection : public Collection<Layer> {
public:
using Collection::Collection; // Inherit constructor
	explicit LayerCollection(std::unique_ptr<CompItem> handle) : Collection() {
		items_ = initialize();
	}

    std::vector<std::unique_ptr<Layer>> initialize() override;

    void append(std::unique_ptr<Layer> item) override;

    std::unique_ptr<Layer> pop() override;

private:
    std::unique_ptr<CompItem> handle_;
};
