#include "pch.h"
#include "Layer.h"

std::string Layer::getName()
{
    return getLayerName(this->getLayer());
}

int Layer::LayerIndex()
{
    return getLayerIndex(this->getLayer());
}

void Layer::setLayerIndex(int index)
{
    changeLayerIndex(this->getLayer(), index);
}

std::string Layer::LayerName()
{
    return getLayerName(this->getLayer());
}

std::string Layer::LayerSourceName()
{
    return getLayerSourceName(this->getLayer());
}

void Layer::SetLayerName(std::string name)
{
    setLayerName(this->getLayer(), name);
}

bool Layer::isVideo()
{
    return IsLayerVideoReallyOn(this->getLayer());
}

bool Layer::isAudio()
{
    return IsLayerAudioReallyOn(this->getLayer());
}

float Layer::LayerOffset()
{
    return GetLayerOffset(this->getLayer());
}

void Layer::setLayerOffset(float offset)
{
    CompH comp = GetLayerParentComp(this->getLayer());
    float frameRate = getCompFramerate(comp);
    SetLayerOffset(this->getLayer(), offset, frameRate );
}

bool Layer::is2D()
{
    return IsLayer2D(this->getLayer());
}

bool Layer::is3D()
{
    return IsLayer3D(this->getLayer());
}

Layer Layer::LayerParent()
{
	return Layer(GetLayerParent(this->getLayer()));
}

void Layer::setParent(Layer parent)
{
	SetLayerParent(this->getLayer(), parent.getLayer());
}

Layer Layer::duplicate(Layer parent)
{
    return Layer(DuplicateLayer(this->getLayer()));
}

void Layer::deleteLayer()
{
    DeleteLayer(this->getLayer());
}
