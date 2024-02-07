#pragma once
#include "MessageQueue.h"
#include "Item.h"

class LayerCollection;
class Layer;

class CompItem : public Item {
public:
	using Item::Item;
	virtual ~CompItem() {}
	CompItem(CompH compH) : Item(GetItemFromComp(compH)), compH(compH) {}
	CompItem(ItemH itemH) : Item(itemH) {
		compH = GetCompFromItem(itemH);
	}
	CompItem(const CompItem& compItem) : Item(compItem.itemH), compH(compItem.compH) {}

	std::shared_ptr<LayerCollection> getLayers();

	static CompItem create(std::string name, std::tuple<float, float> dimensions, float frameRate, float duration, float pixelAspect);

	float getFrameRate();

	void setFrameRate(float frameRate);

	float WorkAreaStart();

	float WorkAreaDuration();

	void setWorkStart(float start);

	void setWorkDuration(float duration);

	Layer createSolid(std::string name, std::tuple<float, float> dimensions, std::tuple<float, float, float, float> color, float duration, float frameRate);

	Layer createCamera(std::string name, std::tuple<float, float> position);

	Layer createLight(std::string name, std::tuple<float, float> position);

	Layer createNull(std::string name, float duration);

	Layer createVector();

	float getDisplayStartTime();

	void setDisplayStartTime(float startTimeInSeconds);

	float getCurrentTime();

	void setCurrentTime(float time);

	void setDuration(float duration);

	CompItem duplicate();

	float frameDuration();

	CompItem recentlyUsed();

	void setDimensions(std::tuple<float, float> dimensions);

	bool getDisplayDropFrame();

	void setDisplayDropFrame(bool dropFrame);

	CompItem getSelf() {
		return *this;
	}
protected:
	CompH compH;

};