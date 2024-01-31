#pragma once
#include "MessageQueue.h"
//forward declarations
class AEvolution_API Item;
class AEvolution_API Layer;
class AEvolution_API LayerCollection;
class AEvolution_API CompItem;
class AEvolution_API FootageItem;
class AEvolution_API FolderItem;

enum AEvolution_API LayerFlag {
    VIDEO_ACTIVE = 0x00000001,
    AUDIO_ACTIVE = 0x00000002,
    EFFECTS_ACTIVE = 0x00000004,
    MOTION_BLUR = 0x00000008,
    FRAME_BLENDING = 0x00000010,
    LOCKED = 0x00000020,
    SHY = 0x00000040,
    COLLAPSE = 0x00000080,
    AUTO_ORIENT_ROTATION = 0x00000100,
    ADJUSTMENT_LAYER = 0x00000200,
    TIME_REMAPPING = 0x00000400,
    LAYER_IS_3D = 0x00000800,
    LOOK_AT_CAMERA = 0x00001000,
    LOOK_AT_POI = 0x00002000,
    SOLO = 0x00004000,
    MARKERS_LOCKED = 0x00008000,
    NULL_LAYER = 0x00010000,
    HIDE_LOCKED_MASKS = 0x00020000,
    GUIDE_LAYER = 0x00040000,
    ADVANCED_FRAME_BLENDING = 0x00080000,
    SUBLAYERS_RENDER_SEPARATELY = 0x00100000,
    ENVIRONMENT_LAYER = 0x00200000
};


enum AEvolution_API qualityOptions {
    BEST,
    DRAFT,
    WIREFRAME,
    NONE
};

class AEvolution_API Layer {
public:
    explicit Layer(const std::string sessionID) : sessionID(sessionID) {};

    std::string GetLayerName();
    std::string GetSourceName();
    void SetLayerName(std::string name);
    int index();
    void changeIndex(int index);
    std::shared_ptr<FootageItem> duplicate();
    float layerTime(); //gets the current time in layer time 
    float layerCompTime(); //gets the current time in comp time
    float inPoint(); //gets the in point in layer time
    float compInPoint(); //gets the in point in comp time
    float duration(); //gets the duration in layer time
    float compDuration(); //gets the duration in comp time
    std::string getQuality();
    void setQuality(int quality);
    void deleteLayer(); //deletes the layer
    float getOffset();
    void setOffset(float offset);
    void setFlag(LayerFlag flag, bool value);
    bool getFlag(LayerFlag flag);
    std::string getLayerSessionID();
    std::shared_ptr<Item> getSource();
protected:
    std::string sessionID;
    int index_;
    std::string name_;
    std::string sourceName_;
};

//PyCore.h"
class AEvolution_API Item {
public:
    explicit Item(const std::string& sessionID) : sessionID(sessionID) {}
    virtual ~Item() = default;

    std::string getName();
    void setName(std::string name);
    float getWidth();
    float getHeight();
    std::string name;
    float getDuration();
    float getCurrentTime();
    void setCurrentTime(float time);
    void deleteItem();
    std::string getItemHandle();
    bool isSelected();
    void setSelected(bool select);
    std::string sessionID;
protected:

};


class AEvolution_API FootageItem : public Item, public std::enable_shared_from_this<FootageItem> {
public:
    // Constructors and Destructors
    explicit FootageItem(const std::string& itemHandle) : Item(itemHandle) {}
    virtual ~FootageItem() = default;

    static std::shared_ptr<FootageItem> createNew(std::string name, std::string path = NULL, int index = -1);
    std::string getPath();
    void replaceWithNewSource(std::string name, std::string path);
};
class AEvolution_API LayerCollection {
public:
    explicit LayerCollection(const std::string& compHandle, std::vector<std::shared_ptr<Layer>> layers)
        : compHandle_(compHandle), layers_(std::move(layers)) {}
    LayerCollection(const std::string& compHandle) : compHandle_(compHandle) {
        layers_ = LayerCollection::getAllLayers();
    }
    auto begin() const { return layers_.cbegin(); }
    auto end() const { return layers_.cend(); }
    std::size_t size() const {
        return layers_.size();
    }

    std::shared_ptr<Layer>& operator[](std::size_t index) {
        if (index >= layers_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return layers_[index];
    }

    const std::shared_ptr<Layer>& operator[](std::size_t index) const {
        if (index >= layers_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return layers_[index];
    }

    // Iterator-related methods
    auto begin() { return layers_.begin(); }
    auto end() { return layers_.end(); }

    std::shared_ptr<Layer> addLayerToCollection(Item itemHandle, int index = -1);
    void removeLayerFromCollection(Layer layerHandle);
    void RemoveLayerByIndex(int index);

    std::vector<std::shared_ptr<Layer>> getAllLayers();

    std::string getCompName();

protected:
    std::string compHandle_;
    std::vector<std::shared_ptr<Layer>> layers_;
};


//TODO: Figure out how to turn "item" into a factory class AEvolution_API, but still access things the same way.
class AEvolution_API CompItem : public Item {
public:
    explicit CompItem(const std::string& itemHandle) : Item(itemHandle) {}
    virtual ~CompItem() = default;

    std::shared_ptr<LayerCollection> getLayers();
    int NumLayers();
    float getCurrentTime();
    void setCurrentTime(float time);
    void addLayer(std::string name, std::string path = NULL, int index = -1);
    float getFrameRate();
    void setFrameRate(float frameRate);
    float getDuration();
    void setDuration(float duration);
    void setWidth(float width);
    void setHeight(float height);
    std::shared_ptr<Layer> newSolid(std::string name, float width, float height, float red, float green, float blue, float alpha,
        float duration);
    std::shared_ptr<LayerCollection> getSelectedLayers();
    // Static factory method to create a new CompItem
    static std::shared_ptr<CompItem> CreateNew(std::string name, float width, float height, float frameRate, float duration, float aspectRatio);

};

class AEvolution_API ItemCollection {
public:
    explicit ItemCollection(const std::string& itemHandle) : sessionID(itemHandle) {
        items_ = ItemCollection::getItems();
    }

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

    std::vector<std::shared_ptr<Item>> remove(std::shared_ptr<Item> item);

private:
    std::string sessionID;
    std::vector<std::shared_ptr<Item>> items_;
};

class AEvolution_API FolderItem : public Item {
public:
    // Constructors and Destructors
    explicit FolderItem(const std::string& itemHandle) : Item(itemHandle) {}
    virtual ~FolderItem() = default;

    static std::shared_ptr<FolderItem> createNew(std::string name);

    std::shared_ptr<ItemCollection> ChildItems(); //std::shared_ptr<ItemCollection> ChildItems();
};
/* COpy ProjectCollection over, change to ItemCollection, pass in itemHandle to get childItems,*/
class AEvolution_API SolidItem : public FootageItem {
public:
    // Constructors and Destructors
    explicit SolidItem(const std::string& itemHandle) : FootageItem(itemHandle) {}
    virtual ~SolidItem() = default;

    static std::shared_ptr<SolidItem> createNew(std::string name, std::tuple<float, float> dimensions,
        std::tuple<float, float, float, float> rgba, float duration, int index);

    std::vector<float> GetSolidColor(); //TODO
    void SetSolidColor(float red, float green, float blue, float alpha);  //TODO
    void SetSolidDimensions(float width, float height);  //TODO
};

class AEvolution_API AdjustmentLayer : public Layer {
public:
    explicit AdjustmentLayer(const std::string& layerHandle) : Layer(layerHandle) {}
    virtual ~AdjustmentLayer() = default;

    static std::shared_ptr<AdjustmentLayer> createNew(std::shared_ptr<CompItem> compH, std::string name = "Adjustment Layer");
};