#include "pch.h"
#include "Comp.h"
#include "Collection.h"

std::shared_ptr<LayerCollection> CompItem::getLayers()
{
	auto layerCollection = std::make_shared<LayerCollection>(std::make_unique<CompItem>(*this));
	// Assuming you need to copy *this. If compH is the actual data needed, adjust accordingly.

	return layerCollection;
}

CompItem CompItem::create(std::string name, std::tuple<float, float> dimensions, float frameRate, float duration, float pixelAspect)
{
	dimensionsH dimensionsH(dimensions);
	ItemH parent = getProjectRootFolder();
	CompH comp = addComp(name, dimensionsH, frameRate, duration, pixelAspect, parent);
	return CompItem(comp);
}

float CompItem::getFrameRate()
{
	return getCompFramerate(this->compH);
}

void CompItem::setFrameRate(float frameRate)
{
	setCompFramerate(this->compH, frameRate);
}

float CompItem::WorkAreaStart()
{
	return getCompWorkAreaStart(this->compH);
}

float CompItem::WorkAreaDuration()
{
	return getCompWorkAreaDuration(this->compH);
}

void CompItem::setWorkStart(float start)
{
	setCompWorkAreaStartAndDuration(this->compH, start, WorkAreaDuration());
}

void CompItem::setWorkDuration(float duration)
{
	setCompWorkAreaStartAndDuration(this->compH, WorkAreaStart(), duration);
}

Layer CompItem::createSolid(std::string name, std::tuple<float, float> dimensions, std::tuple<float, float, float, float> color, float duration, float frameRate)
{
	dimensionsH dimensionsH(dimensions);
	colorH colorH(color);
	LayerH layer = createSolidInComp(name, dimensionsH, colorH, this->compH, duration);
	return Layer(layer);
}

Layer CompItem::createCamera(std::string name, std::tuple<float, float> position)
{
	dimensionsH positionH(position);	
	LayerH layer = createCameraInComp(name, positionH, this->compH);
	return Layer(layer);
}

Layer CompItem::createLight(std::string name, std::tuple<float, float> position)
{
	dimensionsH positionH(position);
	LayerH layer = createLightInComp(name, positionH, this->compH);
	return Layer(layer);
}

Layer CompItem::createNull(std::string name, float duration)
{
	LayerH layer = createNullInComp(name, this->compH, duration);
	return Layer(layer);
}

Layer CompItem::createVector()
{
	LayerH layer = createVectorLayerInComp(this->compH);
	return Layer(layer);
}

float CompItem::getDisplayStartTime()
{
	return getCompDisplayStartTime(this->compH);
}

void CompItem::setDisplayStartTime(float startTimeInSeconds)
{
	setCompDisplayStartTime(this->compH, startTimeInSeconds);
}

float CompItem::getCurrentTime()
{
	return getCompItemCurrentTime(this->getItemH(), 0); //FIX THIS
}

void CompItem::setCurrentTime(float time)
{
	setCompItemCurrentTime(this->getItemH(), time, 0); //FIX THIS
}

void CompItem::setDuration(float duration)
{
	setCompDuration(this->compH, duration);
}

CompItem CompItem::duplicate()
{
	CompH comp = duplicateComp(this->compH);
	return CompItem(comp);
}

float CompItem::frameDuration()
{
	return getCompFrameDuration(this->compH);
}

CompItem CompItem::recentlyUsed()
{
	CompH comp = getMostRecentlyUsedComp();
	return CompItem(comp);
}

void CompItem::setDimensions(std::tuple<float, float> dimensions)
{
	dimensionsH dimensionsH(dimensions);
	SetCompDimensions(this->compH, dimensionsH);
}

bool CompItem::getDisplayDropFrame()
{
	return getCompDisplayDropFrame(this->compH);
}

void CompItem::setDisplayDropFrame(bool dropFrame)
{
	setCompDisplayDropFrame(this->compH, dropFrame);
}
