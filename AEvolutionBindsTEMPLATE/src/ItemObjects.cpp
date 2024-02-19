#include "pch.h"
#include "ItemObjects.h"
#include "LayerObject.h"

AEGP_ItemType wItem::itemType()
{
	CommandH cmd = boost::make_shared<GetItemTypeCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemTypeResp> resp = boost::dynamic_pointer_cast<GetItemTypeResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->item_type;
}

A_long wItem::itemID()
{
	CommandH cmd = boost::make_shared<GetItemIDCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemIDResp> resp = boost::dynamic_pointer_cast<GetItemIDResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->item_idPL;
}

A_long wItem::itemFlags()
{
	CommandH cmd = boost::make_shared<GetItemFlagsCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemFlagsResp> resp = boost::dynamic_pointer_cast<GetItemFlagsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->item_flagsP;
}

void wItem::setUseProxy(bool use_proxyB)
{
	CommandH cmd = boost::make_shared<SetItemUseProxyCmd>(item, use_proxyB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemUseProxyResp> resp = boost::dynamic_pointer_cast<SetItemUseProxyResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

std::tuple<A_long, A_long> wItem::itemDimensions()
{
	CommandH cmd = boost::make_shared<GetItemDimensionsCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemDimensionsResp> resp = boost::dynamic_pointer_cast<GetItemDimensionsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return std::make_tuple(resp->widthPL, resp->heightPL);
}

A_Ratio wItem::itemPixelAspectRatio()
{
	CommandH cmd = boost::make_shared<GetItemPixelAspectRatioCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemPixelAspectRatioResp> resp = boost::dynamic_pointer_cast<GetItemPixelAspectRatioResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->ratioPRt;
}

A_Time wItem::itemDuration()
{
	CommandH cmd = boost::make_shared<GetItemDurationCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemDurationResp> resp = boost::dynamic_pointer_cast<GetItemDurationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->durationPT;
}

void wItem::deleteItem()
{
	CommandH cmd = boost::make_shared<DeleteItemCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<DeleteItemResp> resp = boost::dynamic_pointer_cast<DeleteItemResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

A_Time wItem::itemCurrentTime()
{
	CommandH cmd = boost::make_shared<GetItemCurrentTimeCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemCurrentTimeResp> resp = boost::dynamic_pointer_cast<GetItemCurrentTimeResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->curr_timePT;
}

void wItem::setCurrentTime(A_Time new_timePT)
{
	CommandH cmd = boost::make_shared<SetItemCurrentTimeCmd>(item, new_timePT);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemCurrentTimeResp> resp = boost::dynamic_pointer_cast<SetItemCurrentTimeResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

std::string wItem::itemComment()
{
	CommandH cmd = boost::make_shared<GetItemCommentCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemCommentResp> resp = boost::dynamic_pointer_cast<GetItemCommentResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->unicode_namePH;
}

void wItem::setItemComment(const std::string &commentZ)
{
	CommandH cmd = boost::make_shared<SetItemCommentCmd>(item, commentZ);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemCommentResp> resp = boost::dynamic_pointer_cast<SetItemCommentResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

AEGP_LabelID wItem::itemLabel()
{
	CommandH cmd = boost::make_shared<GetItemLabelCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemLabelResp> resp = boost::dynamic_pointer_cast<GetItemLabelResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->labelP;
}

void wItem::setItemLabel(AEGP_LabelID label)
{
	CommandH cmd = boost::make_shared<SetItemLabelCmd>(item, label);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemLabelResp> resp = boost::dynamic_pointer_cast<SetItemLabelResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

wFolder wItem::parentFolder()
{
	CommandH cmd = boost::make_shared<GetItemParentFolderCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemParentFolderResp> resp = boost::dynamic_pointer_cast<GetItemParentFolderResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wFolder(resp->parent_itemPH);
}

void wItem::setParentFolder(wFolder parent_folder)
{
	CommandH cmd = boost::make_shared<SetItemParentFolderCmd>(item, parent_folder.item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemParentFolderResp> resp = boost::dynamic_pointer_cast<SetItemParentFolderResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

std::string wItem::itemName()
{
	CommandH cmd = boost::make_shared<GetItemNameCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetItemNameResp> resp = boost::dynamic_pointer_cast<GetItemNameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->name;
}

void wItem::setItemName(const std::string &nameZ)
{
	CommandH cmd = boost::make_shared<SetItemNameCmd>(item, nameZ);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemNameResp> resp = boost::dynamic_pointer_cast<SetItemNameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

bool wItem::isSelected()
{
	CommandH cmd = boost::make_shared<IsItemSelectedCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<IsItemSelectedResp> resp = boost::dynamic_pointer_cast<IsItemSelectedResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->selectedPB;
}

void wItem::select(bool selectB, bool deselect_othersB)
{
	CommandH cmd = boost::make_shared<SelectItemCmd>(item, selectB, deselect_othersB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SelectItemResp> resp = boost::dynamic_pointer_cast<SelectItemResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

AEGP_DownsampleFactor wComp::getDownsampleFactor()
{
	CommandH cmd = boost::make_shared<GetCompDownsampleFactorCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompDownsampleFactorResp> resp = boost::dynamic_pointer_cast<GetCompDownsampleFactorResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->dsfP;
}

void wComp::setDownsampleFactor(AEGP_DownsampleFactor factor)
{
	CommandH cmd = boost::make_shared<SetCompDownsampleFactorCmd>(comp, factor);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompDownsampleFactorResp> resp = boost::dynamic_pointer_cast<SetCompDownsampleFactorResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

AEGP_ColorVal wComp::getBGColor()
{
	CommandH cmd = boost::make_shared<GetCompBGColorCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompBGColorResp> resp = boost::dynamic_pointer_cast<GetCompBGColorResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->bg_colorP;
}

void wComp::setBGColor(AEGP_ColorVal color)
{
	CommandH cmd = boost::make_shared<SetCompBGColorCmd>(comp, color);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompBGColorResp> resp = boost::dynamic_pointer_cast<SetCompBGColorResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

AEGP_CompFlags wComp::getFlags()
{
	CommandH cmd = boost::make_shared<GetCompFlagsCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompFlagsResp> resp = boost::dynamic_pointer_cast<GetCompFlagsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->flags;
}

bool wComp::getShowLayerNameorSourceName()
{
	CommandH cmd = boost::make_shared<GetShowLayerNameOrSourceNameCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetShowLayerNameOrSourceNameResp> resp = boost::dynamic_pointer_cast<GetShowLayerNameOrSourceNameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->layer_names_shownPB;
}

void wComp::setShowLayerNameorSourceName(bool showLayerNameB)
{
	CommandH cmd = boost::make_shared<SetShowLayerNameOrSourceNameCmd>(comp, showLayerNameB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetShowLayerNameOrSourceNameResp> resp = boost::dynamic_pointer_cast<SetShowLayerNameOrSourceNameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

bool wComp::showBlendModes()
{
	CommandH cmd = boost::make_shared<GetShowBlendModesCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetShowBlendModesResp> resp = boost::dynamic_pointer_cast<GetShowBlendModesResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->blend_modes_shownPB;
}

void wComp::setShowBlendModes(bool showBlendModesB)
{
	CommandH cmd = boost::make_shared<SetShowBlendModesCmd>(comp, showBlendModesB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetShowBlendModesResp> resp = boost::dynamic_pointer_cast<SetShowBlendModesResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

A_FpLong wComp::getFrameRate()
{
	CommandH cmd = boost::make_shared<GetCompFramerateCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompFramerateResp> resp = boost::dynamic_pointer_cast<GetCompFramerateResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->fpsPF;
}

void wComp::setFrameRate(A_FpLong frameRate)
{
	CommandH cmd = boost::make_shared<SetCompFramerateCmd>(comp, frameRate);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompFramerateResp> resp = boost::dynamic_pointer_cast<SetCompFramerateResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

std::pair<A_Ratio, A_Ratio> wComp::shutterAnglePhase()
{
	CommandH cmd = boost::make_shared<GetCompShutterAnglePhaseCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompShutterAnglePhaseResp> resp = boost::dynamic_pointer_cast<GetCompShutterAnglePhaseResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return std::make_pair(resp->angle, resp->phase);
}

A_long wComp::motionBlurSamples()
{
	CommandH cmd = boost::make_shared<GetCompSuggestedMotionBlurSamplesCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompSuggestedMotionBlurSamplesResp> resp = boost::dynamic_pointer_cast<GetCompSuggestedMotionBlurSamplesResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->samplesPL;
}

void wComp::setMotionBlurSamples(A_long samplesL)
{
	CommandH cmd = boost::make_shared<SetCompSuggestedMotionBlurSamplesCmd>(comp, samplesL);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompSuggestedMotionBlurSamplesResp> resp = boost::dynamic_pointer_cast<SetCompSuggestedMotionBlurSamplesResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

A_long wComp::motionBlurAdaptiveSampleLimit()
{
	CommandH cmd = boost::make_shared<GetCompMotionBlurAdaptiveSampleLimitCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompMotionBlurAdaptiveSampleLimitResp> resp = boost::dynamic_pointer_cast<GetCompMotionBlurAdaptiveSampleLimitResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->samplesPL;
}

void wComp::setMotionBlurAdaptiveSampleLimit(A_long limitL)
{
	CommandH cmd = boost::make_shared<SetCompMotionBlurAdaptiveSampleLimitCmd>(comp, limitL);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompMotionBlurAdaptiveSampleLimitResp> resp = boost::dynamic_pointer_cast<SetCompMotionBlurAdaptiveSampleLimitResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wComp::setDisplayStartTime(A_Time time)
{
	CommandH cmd = boost::make_shared<SetCompDisplayStartTimeCmd>(comp, time);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompDisplayStartTimeResp> resp = boost::dynamic_pointer_cast<SetCompDisplayStartTimeResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wComp::setDisplayDropFrame(bool dropFrameB)
{ 
	CommandH cmd = boost::make_shared<SetCompDisplayDropFrameCmd>(comp, dropFrameB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompDisplayDropFrameResp> resp = boost::dynamic_pointer_cast<SetCompDisplayDropFrameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wComp::setDuration(A_Time duration)
{
	CommandH cmd = boost::make_shared<SetCompDurationCmd>(comp, duration);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompDurationResp> resp = boost::dynamic_pointer_cast<SetCompDurationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wComp::setPixelAspectRatio(A_Ratio pixelAspect)
{
	CommandH cmd = boost::make_shared<SetCompPixelAspectRatioCmd>(comp, pixelAspect);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompPixelAspectRatioResp> resp = boost::dynamic_pointer_cast<SetCompPixelAspectRatioResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wComp::setDimensions(A_long width, A_long height)
{
	CommandH cmd = boost::make_shared<SetCompDimensionsCmd>(comp, width, height);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetCompDimensionsResp> resp = boost::dynamic_pointer_cast<SetCompDimensionsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

A_Time wComp::getWorkAreaStart()
{
	CommandH cmd = boost::make_shared<GetCompWorkAreaStartCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompWorkAreaStartResp> resp = boost::dynamic_pointer_cast<GetCompWorkAreaStartResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->startPT;
}

A_Time wComp::getWorkAreaDuration()
{
	CommandH cmd = boost::make_shared<GetCompWorkAreaDurationCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompWorkAreaDurationResp> resp = boost::dynamic_pointer_cast<GetCompWorkAreaDurationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->durationPT;
}

A_Time wComp::displayStartTime()
{
	CommandH cmd = boost::make_shared<GetCompDisplayStartTimeCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompDisplayStartTimeResp> resp = boost::dynamic_pointer_cast<GetCompDisplayStartTimeResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->start_timePT;
}

bool wComp::displayDropFrame()
{
	CommandH cmd = boost::make_shared<GetCompDisplayDropFrameCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompDisplayDropFrameResp> resp = boost::dynamic_pointer_cast<GetCompDisplayDropFrameResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->dropFramePB;
}

A_Time wComp::frameDuration()
{
	CommandH cmd = boost::make_shared<GetCompFrameDurationCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompFrameDurationResp> resp = boost::dynamic_pointer_cast<GetCompFrameDurationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->timeP;
}

wComp wComp::newComp(std::string name, A_long width, A_long height, A_Ratio pixelAspect, A_Time duration, A_Ratio framerate, AE_Item parent)
{
	CommandH cmd = boost::make_shared<CreateCompCmd>(parent, name, width, height, pixelAspect, duration, framerate);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateCompResp> resp = boost::dynamic_pointer_cast<CreateCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wComp(resp->new_compPH);
}

wComp wComp::mostRecentlyUsed()
{
	CommandH cmd = boost::make_shared<GetMostRecentlyUsedCompCmd>();
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetMostRecentlyUsedCompResp> resp = boost::dynamic_pointer_cast<GetMostRecentlyUsedCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wComp(resp->compPH);
}

wComp wComp::duplicate()
{
	CommandH cmd = boost::make_shared<DuplicateCompCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<DuplicateCompResp> resp = boost::dynamic_pointer_cast<DuplicateCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wComp(resp->new_compPH);
}

A_long wComp::getNumLayers()
{
	CommandH cmd = boost::make_shared<GetCompNumLayersCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompNumLayersResp> resp = boost::dynamic_pointer_cast<GetCompNumLayersResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->num_layers;
}

bool wComp::isAddLayerValid(wItem item)
{
	CommandH cmd = boost::make_shared<IsAddLayerValidCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<IsAddLayerValidResp> resp = boost::dynamic_pointer_cast<IsAddLayerValidResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->valid;
}

wLayer wComp::addLayer(wItem item)
{
	CommandH cmd = boost::make_shared<AddLayerCmd>(item, comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<AddLayerResp> resp = boost::dynamic_pointer_cast<AddLayerResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->layer);
}

wLayer wComp::getLayerfromID(AEGP_LayerIDVal layerID)
{
	CommandH cmd = boost::make_shared<GetLayerFromLayerIDCmd>(comp, layerID);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetLayerFromLayerIDResp> resp = boost::dynamic_pointer_cast<GetLayerFromLayerIDResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->layer);
}

wLayer wComp::getLayerByIndex(A_long index)
{
	CommandH cmd = boost::make_shared<GetCompLayerByIndexCmd>(comp, index);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetCompLayerByIndexResp> resp = boost::dynamic_pointer_cast<GetCompLayerByIndexResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->layer);
}

wLayer wComp::getActiveLayer()
{
	CommandH cmd = boost::make_shared<GetActiveLayerCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetActiveLayerResp> resp = boost::dynamic_pointer_cast<GetActiveLayerResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->layer);
}

wLayer wComp::createSolid(std::string name, A_long width, A_long height, AEGP_ColorVal color, A_Time duration)
{
	CommandH cmd = boost::make_shared <CreateSolidInCompCmd> (comp, name, width, height, color, duration);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateSolidInCompResp> resp = boost::dynamic_pointer_cast<CreateSolidInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_solidPH);
}

wLayer wComp::createCamera(std::string name, A_FloatPoint center)
{
	CommandH cmd = boost::make_shared<CreateCameraInCompCmd>(comp, name, center);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateCameraInCompResp> resp = boost::dynamic_pointer_cast<CreateCameraInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_cameraPH);
}

wLayer wComp::createLight(std::string name, A_FloatPoint center)
{
	CommandH cmd = boost::make_shared<CreateLightInCompCmd>(comp, name, center);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateLightInCompResp> resp = boost::dynamic_pointer_cast<CreateLightInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_lightPH);
}

wLayer wComp::createNull(std::string name, A_Time duration)
{
	CommandH cmd = boost::make_shared<CreateNullInCompCmd>(comp, name, duration);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateNullInCompResp> resp = boost::dynamic_pointer_cast<CreateNullInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_null_solidPH);
}

wLayer wComp::createTextLayer(bool selectNew)
{
	CommandH cmd = boost::make_shared<CreateTextLayerInCompCmd>(comp, selectNew);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateTextLayerInCompResp> resp = boost::dynamic_pointer_cast<CreateTextLayerInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_text_lyrPH);
}

wLayer wComp::createBoxTextLayer(bool selectNew, A_FloatPoint dimensions)
{
	CommandH cmd = boost::make_shared<CreateBoxTextLayerInCompCmd>(comp, selectNew, dimensions);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateBoxTextLayerInCompResp> resp = boost::dynamic_pointer_cast<CreateBoxTextLayerInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_text_layerPH);
}

wLayer wComp::createVectorLayer()
{
	CommandH cmd = boost::make_shared<CreateVectorLayerInCompCmd>(comp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<CreateVectorLayerInCompResp> resp = boost::dynamic_pointer_cast<CreateVectorLayerInCompResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return wLayer(resp->new_vec_layerPH);
}

wFootage::wFootage(AE_Item item)
{
	this->item = item;
}

wFootage wFootage::newFootage(std::string name, std::string file_path, AEGP_InterpretationStyle interp, wFolder parent)
{
	CommandH cmd = boost::make_shared<NewFootageCmd>(name, file_path, interp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<NewFootageResp> resp = boost::dynamic_pointer_cast<NewFootageResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	CommandH cmd2 = boost::make_shared<AddFootageToProjectCmd>(resp->footageH, parent.item);
	auto result2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	boost::shared_ptr<AddFootageToProjectResp> resp2 = boost::dynamic_pointer_cast<AddFootageToProjectResp>(result2);
	if (resp2->error != "A_Err_NONE") {
		throw std::runtime_error(resp2->error);
	}
	return wFootage(resp2->add_itemPH0);
}

wFootage wFootage::newPlaceholderFootage(std::string name, std::string file_path, AEGP_InterpretationStyle interp, wFolder parent)
{
	CommandH cmd = boost::make_shared<NewPlaceholderFootageWithPathCmd>(name, file_path, interp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<NewPlaceholderFootageWithPathResp> resp = boost::dynamic_pointer_cast<NewPlaceholderFootageWithPathResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	CommandH cmd2 = boost::make_shared<AddFootageToProjectCmd>(resp->footagePH, parent.item);
	auto result2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	boost::shared_ptr<AddFootageToProjectResp> resp2 = boost::dynamic_pointer_cast<AddFootageToProjectResp>(result2);
	if (resp2->error != "A_Err_NONE") {
		throw std::runtime_error(resp2->error);
	}
	return wFootage(resp2->add_itemPH0);
}

wFootage wFootage::newSolidFootage(std::string name, A_long width, A_long height, AEGP_ColorVal color, wFolder parent)
{
	CommandH cmd = boost::make_shared<NewSolidFootageCmd>(name, width, height, color);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<NewSolidFootageResp> resp = boost::dynamic_pointer_cast<NewSolidFootageResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	CommandH cmd2 = boost::make_shared<AddFootageToProjectCmd>(resp->footagePH, parent.item);
	auto result2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	boost::shared_ptr<AddFootageToProjectResp> resp2 = boost::dynamic_pointer_cast<AddFootageToProjectResp>(result2);
	if (resp2->error != "A_Err_NONE") {
		throw std::runtime_error(resp2->error);
	}
	return wFootage(resp2->add_itemPH0);
}

AE_Footage wFootage::getProxyFootage()
{
	CommandH cmd = boost::make_shared<GetProxyFootageFromItemCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetProxyFootageFromItemResp> resp = boost::dynamic_pointer_cast<GetProxyFootageFromItemResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->proxy_ftgH;
}

std::pair<A_long, A_long> wFootage::footageNumFiles()
{
	CommandH cmd = boost::make_shared<GetFootageNumFilesCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageNumFilesResp> resp = boost::dynamic_pointer_cast<GetFootageNumFilesResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return std::make_pair(resp->num_filesPL0, resp->files_per_frmPL0);
}

std::string wFootage::footagePath(A_long frameNum, A_long fileIndex)
{
	CommandH cmd = boost::make_shared<GetFootagePathCmd>(item, frameNum, fileIndex);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootagePathResp> resp = boost::dynamic_pointer_cast<GetFootagePathResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->unicode_pathPH;
}

AEGP_FootageSignature wFootage::getFootageSignature()
{
	CommandH cmd = boost::make_shared<GetFootageSignatureCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageSignatureResp> resp = boost::dynamic_pointer_cast<GetFootageSignatureResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->sigP;
}

AEGP_FootageInterp wFootage::getInterpretation()
{
	CommandH cmd = boost::make_shared<GetFootageInterpretationCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageInterpretationResp> resp = boost::dynamic_pointer_cast<GetFootageInterpretationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->interpP;
}

AEGP_FootageLayerKey wFootage::getLayerKey()
{
	CommandH cmd = boost::make_shared<GetFootageLayerKeyCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageLayerKeyResp> resp = boost::dynamic_pointer_cast<GetFootageLayerKeyResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->layerKeyP;
}

AEGP_SoundDataFormat wFootage::getSoundDataFormat()
{
	CommandH cmd = boost::make_shared<GetFootageSoundDataFormatCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageSoundDataFormatResp> resp = boost::dynamic_pointer_cast<GetFootageSoundDataFormatResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->formatP;
}

AEGP_FileSequenceImportOptions wFootage::getSequenceImportOptions()
{
	CommandH cmd = boost::make_shared<GetFootageSequenceImportOptionsCmd>(item);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<GetFootageSequenceImportOptionsResp> resp = boost::dynamic_pointer_cast<GetFootageSequenceImportOptionsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	return resp->optionsP;
}

void wFootage::setSolidColor(AEGP_ColorVal color)
{
	CommandH cmd = boost::make_shared<SetSolidFootageColorCmd>(item, color);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetSolidFootageColorResp> resp = boost::dynamic_pointer_cast<SetSolidFootageColorResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wFootage::setSolidDimensions(A_long width, A_long height)
{
	CommandH cmd = boost::make_shared<SetSolidFootageDimensionsCmd>(item, width, height);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetSolidFootageDimensionsResp> resp = boost::dynamic_pointer_cast<SetSolidFootageDimensionsResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wFootage::setItemUseProxy(bool use_proxyB)
{
	CommandH cmd = boost::make_shared<SetItemUseProxyCmd>(item, use_proxyB);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetItemUseProxyResp> resp = boost::dynamic_pointer_cast<SetItemUseProxyResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}

void wFootage::replaceFootage(std::string path, AEGP_InterpretationStyle interp)
{
	CommandH cmd = boost::make_shared<NewFootageCmd>(path, interp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	auto resp = boost::dynamic_pointer_cast<NewFootageResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
	CommandH cmd2 = boost::make_shared<ReplaceItemMainFootageCmd>(resp->footageH, item);
	auto result2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	auto resp2 = boost::dynamic_pointer_cast<ReplaceItemMainFootageResp>(result2);
	if (resp2->error != "A_Err_NONE") {
		throw std::runtime_error(resp2->error);
	}
	CommandH cmd2 = boost::make_shared<DisposeFootageCmd>(resp->footageH);
	auto result2 = MessageQueueManager::getInstance().sendAndReceive(cmd2);
	if (resp2->error != "A_Err_NONE") {
		throw std::runtime_error(resp2->error);
	}
}

void wFootage::setInterpretation(AEGP_FootageInterp interp)
{
	CommandH cmd = boost::make_shared<SetFootageInterpretationCmd>(item, interp);
	auto result = MessageQueueManager::getInstance().sendAndReceive(cmd);
	boost::shared_ptr<SetFootageInterpretationResp> resp = boost::dynamic_pointer_cast<SetFootageInterpretationResp>(result);
	if (resp->error != "A_Err_NONE") {
		throw std::runtime_error(resp->error);
	}
}
