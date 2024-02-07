#pragma once
#include "MessageQueue.h"

class Layer {
public:
	Layer(LayerH layer) : layer(layer) {}
	Layer(ItemH footageItem) : footageItem(footageItem) {}
	std::string getName();

	LayerH getLayer() { return layer; }

	ItemH getFootageItem() { return footageItem; }

	//getter and setter for layer index
	int LayerIndex();

	void setLayerIndex(int index);

	//getter and setter for layer name
	std::string LayerName();

	std::string LayerSourceName();

	void SetLayerName(std::string name);

	bool isVideo();
	bool isAudio();

	//getter and setter for layer offset
	float LayerOffset();

	void setLayerOffset(float offset);

	//is 2d/ is3d
	bool is2D();

	bool is3D();

	//getter and setter for layer parent
	Layer LayerParent();
	void setParent(Layer parent);

	Layer duplicate(Layer parent);

	void deleteLayer();


private:
	LayerH layer;
	ItemH footageItem;
};