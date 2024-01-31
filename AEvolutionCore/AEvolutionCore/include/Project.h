#pragma once
#include "MessageQueue.h"
#include "ItemManager.h"



class AEvolution_API ProjectCollection {
public:
    explicit ProjectCollection(const std::string sessionID);
    std::vector<std::shared_ptr<Item>> getItems();

    std::size_t size() const {
        return items_.size();
    }

    std::shared_ptr<Item>& operator[](std::size_t index) {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items_[index];
    }

    const std::shared_ptr<Item>& operator[](std::size_t index) const {
        if (index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items_[index];
    }

    // Iterator-related methods
    auto begin() { return items_.begin(); }
    auto end() { return items_.end(); }
    auto begin() const { return items_.cbegin(); }
    auto end() const { return items_.cend(); }

    std::vector<std::shared_ptr<Item>> append(std::shared_ptr<Item> item);

    std::vector<std::shared_ptr<Item>> remove(std::shared_ptr<Item> item) {
        if (item == nullptr) {
            throw std::runtime_error("Item is null");
        }
        Item item2 = *item;
        item2.deleteItem();
        items_.erase(std::remove(items_.begin(), items_.end(), item), items_.end());
        return items_;
    }

private:
    std::string sessionID;
    std::vector<std::shared_ptr<Item>> items_;
};

//Project class AEvolution_API definition
class AEvolution_API Project {
public:
    Project() = default;  // Default constructor
    Project(std::string sessionID) : sessionID(sessionID) {}  // Default constructor

    std::shared_ptr<Item> ActiveItem();
    std::shared_ptr<Layer> GetActiveLayer();
    std::string getName();
    std::string getPath();
    void saveAs(std::string path);
    std::shared_ptr<ProjectCollection> ChildItems();
    std::shared_ptr<ProjectCollection> SelectedItems();
private:
    std::shared_ptr<Item> activeItem;
    std::string sessionID;
};


