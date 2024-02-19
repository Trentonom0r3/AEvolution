#include "LayerCommands.h"
#include "../MessageQueueManager.h"

void GetCompNumLayersCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long num_layers;
	ERR(suites.LayerSuite9()->AEGP_GetCompNumLayers(comp.handle, &num_layers));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompNumLayersResp>(num_layers, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetCompLayerByIndexCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layer;
	ERR(suites.LayerSuite9()->AEGP_GetCompLayerByIndex(comp.handle, layer_index, &layer));
	boost::shared_ptr<Response> resp = boost::make_shared<GetCompLayerByIndexResp>(layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetActiveLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layer;
	ERR(suites.LayerSuite9()->AEGP_GetActiveLayer(&layer));
	boost::shared_ptr<Response> resp = boost::make_shared<GetActiveLayerResp>(layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerIndexCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long index;
	ERR(suites.LayerSuite9()->AEGP_GetLayerIndex(layer.handle, &index));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerIndexResp>(index, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerSourceItemCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ItemH item;
	ERR(suites.LayerSuite9()->AEGP_GetLayerSourceItem(layer.handle, &item));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerSourceItemResp>(item, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerSourceItemIDCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long itemID;
	ERR(suites.LayerSuite9()->AEGP_GetLayerSourceItemID(layer.handle, &itemID));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerSourceItemIDResp>(itemID, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerParentCompCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_CompH comp;
	ERR(suites.LayerSuite9()->AEGP_GetLayerParentComp(layer.handle, &comp));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerParentCompResp>(comp, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}	

void GetLayerNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_PluginID* plugin_id = SuiteManager::GetInstance().GetPluginID();
	AEGP_MemHandle layer_name = NULL;
	AEGP_MemHandle source_name = NULL;
	A_UTF16Char* layerNameZ;
	A_UTF16Char* sourceNameZ;
	ERR(suites.LayerSuite9()->AEGP_GetLayerName(*plugin_id, layer.handle, &layer_name, &source_name));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(layer_name, reinterpret_cast<void**>(&layerNameZ)));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(source_name, reinterpret_cast<void**>(&sourceNameZ)));
	std::string layerName = convertUTF16ToUTF8(layerNameZ);
	std::string sourceName = convertUTF16ToUTF8(sourceNameZ);
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(layer_name));
	ERR(suites.MemorySuite1()->AEGP_UnlockMemHandle(source_name));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(layer_name));
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(source_name));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerNameResp>(layerName, sourceName, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerQualityCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerQuality quality;
	ERR(suites.LayerSuite9()->AEGP_GetLayerQuality(layer.handle, &quality));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerQualityResp>(quality, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerQualityCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerQuality(layer.handle, quality));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerQualityResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerFlagsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerFlags flags;
	ERR(suites.LayerSuite9()->AEGP_GetLayerFlags(layer.handle, &flags));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerFlagsResp>(flags, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerFlagCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerFlag(layer.handle, flags, value));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerFlagResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsLayerVideoReallyOnCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean on;
	ERR(suites.LayerSuite9()->AEGP_IsLayerVideoReallyOn(layer.handle, &on));
	boost::shared_ptr<Response> resp = boost::make_shared<IsLayerVideoReallyOnResp>(on, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsLayerAudioReallyOnCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean on;
	ERR(suites.LayerSuite9()->AEGP_IsLayerAudioReallyOn(layer.handle, &on));
	boost::shared_ptr<Response> resp = boost::make_shared<IsLayerAudioReallyOnResp>(on, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerCurrentTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time time;
	ERR(suites.LayerSuite9()->AEGP_GetLayerCurrentTime(layer.handle, time_mode, &time));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerCurrentTimeResp>(time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerInPointCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time time;
	ERR(suites.LayerSuite9()->AEGP_GetLayerInPoint(layer.handle, time_mode, &time));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerInPointResp>(time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time time;
	ERR(suites.LayerSuite9()->AEGP_GetLayerDuration(layer.handle, time_mode, &time));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerDurationResp>(time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerInPointAndDurationCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerInPointAndDuration(layer.handle, time_mode, &in_point, &duration));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerInPointAndDurationResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerOffsetCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time offset;
	ERR(suites.LayerSuite9()->AEGP_GetLayerOffset(layer.handle, &offset));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerOffsetResp>(offset, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerOffsetCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerOffset(layer.handle, &offset));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerOffsetResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerStretchCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Ratio stretch;
	ERR(suites.LayerSuite9()->AEGP_GetLayerStretch(layer.handle, &stretch));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerStretchResp>(stretch, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerStretchCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerStretch(layer.handle, &stretch));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerStretchResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerTransferModeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerTransferMode mode;
	ERR(suites.LayerSuite9()->AEGP_GetLayerTransferMode(layer.handle, &mode));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerTransferModeResp>(mode, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerTransferModeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerTransferMode(layer.handle, &mode));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerTransferModeResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsAddLayerValidCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean valid;
	ERR(suites.LayerSuite9()->AEGP_IsAddLayerValid(item_to_add.handle, into_comp.handle, &valid));
	boost::shared_ptr<Response> resp = boost::make_shared<IsAddLayerValidResp>(valid, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void AddLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH new_layer;
	ERR(suites.LayerSuite9()->AEGP_AddLayer(item_to_add.handle, into_comp.handle, &new_layer));
	boost::shared_ptr<Response> resp = boost::make_shared<AddLayerResp>(new_layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void ReorderLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_ReorderLayer(layer.handle, layer_index));
	boost::shared_ptr<Response> resp = boost::make_shared<ReorderLayerResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerMaskedBoundsCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_FloatRect bounds;
	ERR(suites.LayerSuite9()->AEGP_GetLayerMaskedBounds(layer.handle, time_mode, &comp_time, &bounds));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerMaskedBoundsResp>(bounds, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerObjectTypeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_ObjectType type;
	ERR(suites.LayerSuite9()->AEGP_GetLayerObjectType(layer.handle, &type));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerObjectTypeResp>(type, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsLayer3DCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean is_3d;
	ERR(suites.LayerSuite9()->AEGP_IsLayer3D(layer.handle, &is_3d));
	boost::shared_ptr<Response> resp = boost::make_shared<IsLayer3DResp>(is_3d, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsLayer2DCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean is_2d;
	ERR(suites.LayerSuite9()->AEGP_IsLayer2D(layer.handle, &is_2d));
	boost::shared_ptr<Response> resp = boost::make_shared<IsLayer2DResp>(is_2d, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsVideoActiveCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean is_active;
	ERR(suites.LayerSuite9()->AEGP_IsVideoActive(layer.handle, time_mode, &comp_time, &is_active));
	boost::shared_ptr<Response> resp = boost::make_shared<IsVideoActiveResp>(is_active, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void IsLayerUsedAsTrackMatteCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean is_used;
	ERR(suites.LayerSuite9()->AEGP_IsLayerUsedAsTrackMatte(layer.handle, fill_must_be_active, &is_used));
	boost::shared_ptr<Response> resp = boost::make_shared<IsLayerUsedAsTrackMatteResp>(is_used, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void DoesLayerHaveTrackMatteCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Boolean has_matte;
	ERR(suites.LayerSuite9()->AEGP_DoesLayerHaveTrackMatte(layer.handle, &has_matte));
	boost::shared_ptr<Response> resp = boost::make_shared<DoesLayerHaveTrackMatteResp>(has_matte, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void ConvertCompToLayerTimeCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time layer_time;
	ERR(suites.LayerSuite9()->AEGP_ConvertCompToLayerTime(layer.handle, &comp_time, &layer_time));
	boost::shared_ptr<Response> resp = boost::make_shared<ConvertCompToLayerTimeResp>(layer_time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void ConvertLayerToCompTime::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Time comp_time;
	ERR(suites.LayerSuite9()->AEGP_ConvertLayerToCompTime(layer.handle, &layer_time, &comp_time));
	boost::shared_ptr<Response> resp = boost::make_shared<ConvertLayerToCompTimeResp>(comp_time, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerDancingRandValueCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_long value;
	ERR(suites.LayerSuite9()->AEGP_GetLayerDancingRandValue(layer.handle, &comp_time, &value));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerDancingRandValueResp>(value, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerIDCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerIDVal id;
	ERR(suites.LayerSuite9()->AEGP_GetLayerID(layer.handle, &id));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerIDResp>(id, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerToWorldXformCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Matrix4 xform;
	ERR(suites.LayerSuite9()->AEGP_GetLayerToWorldXform(layer.handle, &comp_time, &xform));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerToWorldXformResp>(xform, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerToWorldXformFromViewCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	A_Matrix4 xform;
	ERR(suites.LayerSuite9()->AEGP_GetLayerToWorldXformFromView(layer.handle, &view_time, &comp_time, &xform));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerToWorldXformFromViewResp>(xform, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerNameCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	std::vector<A_UTF16Char> name = convertUTF8ToUTF16(new_name);
	ERR(suites.LayerSuite9()->AEGP_SetLayerName(layer.handle, name.data()));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerNameResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerParentCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH parent_layer;
	ERR(suites.LayerSuite9()->AEGP_GetLayerParent(layer.handle, &parent_layer));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerParentResp>(parent_layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerParentCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerParent(layer.handle, parent_layer.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerParentResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void DeleteLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_DeleteLayer(layer.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<DeleteLayerResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void DuplicateLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH dupe_layer;
	ERR(suites.LayerSuite9()->AEGP_DuplicateLayer(orig_layer.handle, &dupe_layer));
	boost::shared_ptr<Response> resp = boost::make_shared<DuplicateLayerResp>(dupe_layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerFromLayerIDCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH layer;
	ERR(suites.LayerSuite9()->AEGP_GetLayerFromLayerID(parent_comp.handle, id, &layer));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerFromLayerIDResp>(layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerLabelCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LabelID label;
	ERR(suites.LayerSuite9()->AEGP_GetLayerLabel(layer.handle, &label));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerLabelResp>(label, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerLabelCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerLabel(layer.handle, label));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerLabelResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetLayerSamplingQualityCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerSamplingQuality quality;
	ERR(suites.LayerSuite9()->AEGP_GetLayerSamplingQuality(layer.handle, &quality));
	boost::shared_ptr<Response> resp = boost::make_shared<GetLayerSamplingQualityResp>(quality, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetLayerSamplingQualityCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetLayerSamplingQuality(layer.handle, label));
	boost::shared_ptr<Response> resp = boost::make_shared<SetLayerSamplingQualityResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void GetTrackMatteLayerCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_LayerH track_matte_layer;
	ERR(suites.LayerSuite9()->AEGP_GetTrackMatteLayer(layer.handle, &track_matte_layer));
	boost::shared_ptr<Response> resp = boost::make_shared<GetTrackMatteLayerResp>(track_matte_layer, errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void SetTrackMatteCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_SetTrackMatte(layer.handle, track_matte_layer.handle, track_matte_type));
	boost::shared_ptr<Response> resp = boost::make_shared<SetTrackMatteResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}

void RemoveTrackMatteCmd::execute()
{
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
	ERR(suites.LayerSuite9()->AEGP_RemoveTrackMatte(layer.handle));
	boost::shared_ptr<Response> resp = boost::make_shared<RemoveTrackMatteResp>(errToString(err));
	MessageQueueManager::getInstance().sendResponse(resp);
}















