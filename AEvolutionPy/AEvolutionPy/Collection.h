#pragma once
#include "MessageQueue.h"
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>

class Item;
class Layer;

template<typename T>
class Collection {
public:

    explicit Collection(const std::string& handle) : handle_(handle) {
        items_ = initializeCollection();
    }

    // Move constructor
    Collection(Collection<T>&& other) noexcept : handle_(std::move(other.handle_)), items_(std::move(other.items_)) {}

    // Move assignment operator
    Collection& operator=(Collection<T>&& other) noexcept {
        if (this != &other) {
            handle_ = std::move(other.handle_);
            items_ = std::move(other.items_);
        }
        return *this;
    }

    // Delete copy constructor and copy assignment operator to prevent copying
    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;

    virtual ~Collection() {}

    virtual std::vector<std::unique_ptr<T>> initializeCollection() = 0;

    std::size_t size() const {
        return items_.size();
    }

    T& operator[](std::size_t index) {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items_[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items_[index];
    }

    auto begin() { return items_.begin(); }
    auto end() { return items_.end(); }
    auto begin() const { return items_.cbegin(); }
    auto end() const { return items_.cend(); }

    // Adjust append and remove to work with unique_ptr
    virtual void append(std::unique_ptr<T> item) = 0;
    virtual void remove(const T& item) = 0; // Removing may require different logic

    // Pop might need to return a unique_ptr as well
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
    std::string handle_;
};

class ItemCollection : public Collection<Item> {
public:
    using Collection::Collection; // Inherit constructor

protected:
    std::vector<std::unique_ptr<Item>> initializeCollection() override;

    void append(std::unique_ptr<Item> item) override;

    void remove(const Item& item) override;

    std::unique_ptr<Item> pop() override;
};


/*
class LayerCollection : public Collection<Layer> {
public:
    using Collection::Collection; // Inherit constructor

protected:
    std::vector<Layer> initializeCollection() override {
        // Logic to initialize LayerCollection
    }

    void append(const Layer& layer) override {
		// Custom append logic for LayerCollection
		items_.push_back(layer);
	}

    void remove(const Layer& layer) override {
		// Custom remove logic for LayerCollection
		// This assumes Layer has an appropriate operator== for comparison
		items_.erase(std::remove(items_.begin(), items_.end(), layer), items_.end());
	}
};
*/
