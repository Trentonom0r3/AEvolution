#pragma once
#include "MessageQueue.h"
#include "Item.h"

class LayerCollection;
class Layer;

class CompItem : public Item {
public:
	using Item::Item;
	virtual ~CompItem() {}

	LayerCollection getLayers();

	static CompItem create(std::string name, dimensionsH dimensions, ItemH parent);

	float getFrameRate();

	void setFrameRate(float frameRate);

	float getWorkAreaStart();

	float getWorkAreaDuration();

	void setWorkAreaStart(float start);

	void setWorkAreaDuration(float duration);

	Layer createSolid(std::string name, dimensionsH dimensions, std::string color, float duration, float frameRate, ItemH parent);

	Layer createCamera(std::string name, dimensionsH position, ItemH parent);

	Layer createLight(std::string name, dimensionsH position, ItemH parent);

	Layer createNull(std::string name, dimensionsH position, ItemH parent);

	Layer createVectorLayerInComp();

	float getDisplayStartTime();

	void setDisplayStartTime(float startTimeInSeconds);

	void setDuration(float duration);

	CompItem duplicate();

	float frameDuration();

	CompItem recentlyUsed();

	bool getDisplayDropFrame();

	void setDisplayDropFrame(bool dropFrame);

	void reorderComp(int index);

protected:
	CompH compH;
};