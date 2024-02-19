#pragma once
#include "../MessageMain.h"
#include "../responses/LayerResponses.h"

class GetCompNumLayersCmd : public Command {
public:
	AE_Comp comp;
	GetCompNumLayersCmd() : Command(CommandID::GetCompNumLayers) {}
	GetCompNumLayersCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompNumLayers) {}
	GetCompNumLayersCmd(wComp comp) : comp(comp.comp), Command(CommandID::GetCompNumLayers) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompLayerByIndexCmd : public Command {
public:
	AE_Comp comp;
	A_long layer_index;
	GetCompLayerByIndexCmd() : Command(CommandID::GetCompLayerByIndex) {}
	GetCompLayerByIndexCmd(AE_Comp comp, A_long layer_index) : comp(comp), layer_index(layer_index), Command(CommandID::GetCompLayerByIndex) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& layer_index;
	}
};

class GetActiveLayerCmd : public Command {
public:
	GetActiveLayerCmd() : Command(CommandID::GetActiveLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
	}
};

class GetLayerIndexCmd : public Command {
public:
	AE_Layer layer;
	GetLayerIndexCmd() : Command(CommandID::GetLayerIndex) {}
	GetLayerIndexCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerIndex) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerSourceItemCmd : public Command {
public:
	AE_Layer layer;
	GetLayerSourceItemCmd() : Command(CommandID::GetLayerSourceItem) {}
	GetLayerSourceItemCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerSourceItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerSourceItemIDCmd : public Command {
public:
	AE_Layer layer;
	GetLayerSourceItemIDCmd() : Command(CommandID::GetLayerSourceItemID) {}
	GetLayerSourceItemIDCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerSourceItemID) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerParentCompCmd : public Command {
public:
	AE_Layer layer;
	GetLayerParentCompCmd() : Command(CommandID::GetLayerParentComp) {}
	GetLayerParentCompCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerParentComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerNameCmd : public Command {
public:
	AE_Layer layer;
	GetLayerNameCmd() : Command(CommandID::GetLayerName) {}
	GetLayerNameCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerName) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerQualityCmd : public Command {
public:
	AE_Layer layer;
	GetLayerQualityCmd() : Command(CommandID::GetLayerQuality) {}
	GetLayerQualityCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerQuality) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerQualityCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LayerQuality quality;
	SetLayerQualityCmd() : Command(CommandID::SetLayerQuality) {}
	SetLayerQualityCmd(AE_Layer layer, AEGP_LayerQuality quality) : layer(layer), quality(quality), Command(CommandID::SetLayerQuality) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& quality;
	}
};

class GetLayerFlagsCmd : public Command {
public:
	AE_Layer layer;
	GetLayerFlagsCmd() : Command(CommandID::GetLayerFlags) {}
	GetLayerFlagsCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerFlags) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerFlagCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LayerFlags flags;
	A_Boolean value;
	SetLayerFlagCmd() : Command(CommandID::SetLayerFlags) {}
	SetLayerFlagCmd(AE_Layer layer, AEGP_LayerFlags flags, A_Boolean value) : layer(layer), flags(flags), value(value), Command(CommandID::SetLayerFlags) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& flags;
		ar& value;
	}
};

class IsLayerVideoReallyOnCmd : public Command {
public:
	AE_Layer layer;
	IsLayerVideoReallyOnCmd() : Command(CommandID::IsLayerVideoReallyOn) {}
	IsLayerVideoReallyOnCmd(AE_Layer layer) : layer(layer), Command(CommandID::IsLayerVideoReallyOn) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class IsLayerAudioReallyOnCmd : public Command {
public:
	AE_Layer layer;
	IsLayerAudioReallyOnCmd() : Command(CommandID::IsLayerAudioReallyOn) {}
	IsLayerAudioReallyOnCmd(AE_Layer layer) : layer(layer), Command(CommandID::IsLayerAudioReallyOn) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerCurrentTimeCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LTimeMode time_mode;
	GetLayerCurrentTimeCmd() : Command(CommandID::GetLayerCurrentTime) {}
	GetLayerCurrentTimeCmd(AE_Layer layer, AEGP_LTimeMode time_mode) : layer(layer), time_mode(time_mode), Command(CommandID::GetLayerCurrentTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& time_mode;
	}
};

class GetLayerInPointCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LTimeMode time_mode;
	GetLayerInPointCmd() : Command(CommandID::GetLayerInPoint) {}
	GetLayerInPointCmd(AE_Layer layer, AEGP_LTimeMode time_mode) : layer(layer), time_mode(time_mode), Command(CommandID::GetLayerInPoint) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& time_mode;
	}
};

class GetLayerDurationCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LTimeMode time_mode;
	GetLayerDurationCmd() : Command(CommandID::GetLayerDuration) {}
	GetLayerDurationCmd(AE_Layer layer, AEGP_LTimeMode time_mode) : layer(layer), time_mode(time_mode), Command(CommandID::GetLayerDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& time_mode;
	}
};

class SetLayerInPointAndDurationCmd : public Command {
public:
AE_Layer layer;
	AEGP_LTimeMode time_mode;
	A_Time in_point;
	A_Time duration;
	SetLayerInPointAndDurationCmd() : Command(CommandID::SetLayerInPointAndDuration) {}
	SetLayerInPointAndDurationCmd(AE_Layer layer, AEGP_LTimeMode time_mode, A_Time in_point, A_Time duration) : layer(layer), time_mode(time_mode), in_point(in_point), duration(duration), Command(CommandID::SetLayerInPointAndDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& time_mode;
		ar& in_point;
		ar& duration;
	}
};

class GetLayerOffsetCmd : public Command {
public:
	AE_Layer layer;
	GetLayerOffsetCmd() : Command(CommandID::GetLayerOffset) {}
	GetLayerOffsetCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerOffset) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerOffsetCmd : public Command {
public:
	AE_Layer layer;
	A_Time offset;
	SetLayerOffsetCmd() : Command(CommandID::SetLayerOffset) {}
	SetLayerOffsetCmd(AE_Layer layer, A_Time offset) : layer(layer), offset(offset), Command(CommandID::SetLayerOffset) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& offset;
	}
};

class GetLayerStretchCmd : public Command {
public:
	AE_Layer layer;
	GetLayerStretchCmd() : Command(CommandID::GetLayerStretch) {}
	GetLayerStretchCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerStretch) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerStretchCmd : public Command {
public:
	AE_Layer layer;
	A_Ratio stretch;
	SetLayerStretchCmd() : Command(CommandID::SetLayerStretch) {}
	SetLayerStretchCmd(AE_Layer layer, A_Ratio stretch) : layer(layer), stretch(stretch), Command(CommandID::SetLayerStretch) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& stretch;
	}
};

class GetLayerTransferModeCmd : public Command {
public:
	AE_Layer layer;
	GetLayerTransferModeCmd() : Command(CommandID::GetLayerTransferMode) {}
	GetLayerTransferModeCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerTransferMode) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerTransferModeCmd : public Command {
public:
AE_Layer layer;
	AEGP_LayerTransferMode mode;
	SetLayerTransferModeCmd() : Command(CommandID::SetLayerTransferMode) {}
	SetLayerTransferModeCmd(AE_Layer layer, AEGP_LayerTransferMode mode) : layer(layer), mode(mode), Command(CommandID::SetLayerTransferMode) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& mode;
	}
};

class IsAddLayerValidCmd : public Command {
public:
	AE_Item item_to_add;
	AE_Comp into_comp;
	IsAddLayerValidCmd() : Command(CommandID::IsAddLayerValid) {}
	IsAddLayerValidCmd(AE_Item item_to_add, AE_Comp into_comp) : item_to_add(item_to_add), into_comp(into_comp), Command(CommandID::IsAddLayerValid) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item_to_add;
		ar& into_comp;
	}
};

class AddLayerCmd : public Command {
public:
	AE_Item item_to_add;
	AE_Comp into_comp;
	AddLayerCmd() : Command(CommandID::AddLayer) {}
	AddLayerCmd(AE_Item item_to_add, AE_Comp into_comp) : item_to_add(item_to_add), into_comp(into_comp), Command(CommandID::AddLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item_to_add;
		ar& into_comp;
	}
};

class ReorderLayerCmd : public Command {
public:
	AE_Layer layer;
	A_long layer_index;
	ReorderLayerCmd() : Command(CommandID::ReorderLayer) {}
	ReorderLayerCmd(AE_Layer layer, A_long layer_index) : layer(layer), layer_index(layer_index), Command(CommandID::ReorderLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& layer_index;
	}
};

class GetLayerMaskedBoundsCmd : public Command {
public:
	AE_Layer layer;
	A_Time comp_time;
	AEGP_LTimeMode time_mode;
	GetLayerMaskedBoundsCmd() : Command(CommandID::GetLayerMaskedBounds) {}
	GetLayerMaskedBoundsCmd(AE_Layer layer, A_Time comp_time, AEGP_LTimeMode timeMode) : layer(layer), comp_time(comp_time), time_mode(timeMode), Command(CommandID::GetLayerMaskedBounds) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& comp_time;
		ar& time_mode;
	}
};

class GetLayerObjectTypeCmd : public Command {
public:
	AE_Layer layer;
	GetLayerObjectTypeCmd() : Command(CommandID::GetLayerObjectType) {}
	GetLayerObjectTypeCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerObjectType) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class IsLayer3DCmd : public Command {
public:
	AE_Layer layer;
	IsLayer3DCmd() : Command(CommandID::IsLayer3D) {}
	IsLayer3DCmd(AE_Layer layer) : layer(layer), Command(CommandID::IsLayer3D) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class IsLayer2DCmd : public Command {
public:
	AE_Layer layer;
	IsLayer2DCmd() : Command(CommandID::IsLayer2D) {}
	IsLayer2DCmd(AE_Layer layer) : layer(layer), Command(CommandID::IsLayer2D) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class IsVideoActiveCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LTimeMode time_mode;
	A_Time comp_time;
	IsVideoActiveCmd() : Command(CommandID::IsVideoActive) {}
	IsVideoActiveCmd(AE_Layer layer, AEGP_LTimeMode time_mode, A_Time comp_time) : layer(layer), time_mode(time_mode), comp_time(comp_time), Command(CommandID::IsVideoActive) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& time_mode;
		ar& comp_time;
	}
};

class IsLayerUsedAsTrackMatteCmd : public Command {
public:
	AE_Layer layer;
	A_Boolean fill_must_be_active;
	IsLayerUsedAsTrackMatteCmd() : Command(CommandID::IsLayerUsedAsTrackMatte) {}
	IsLayerUsedAsTrackMatteCmd(AE_Layer layer, A_Boolean fill_must_be_active) : layer(layer), fill_must_be_active(fill_must_be_active), Command(CommandID::IsLayerUsedAsTrackMatte) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& fill_must_be_active;
	}
};

class DoesLayerHaveTrackMatteCmd : public Command {
public:
	AE_Layer layer;
	DoesLayerHaveTrackMatteCmd() : Command(CommandID::DoesLayerHaveTrackMatte) {}
	DoesLayerHaveTrackMatteCmd(AE_Layer layer) : layer(layer), Command(CommandID::DoesLayerHaveTrackMatte) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class ConvertCompToLayerTimeCmd : public Command {
public:
	AE_Layer layer;
	A_Time comp_time;
	ConvertCompToLayerTimeCmd() : Command(CommandID::ConvertCompToLayerTime) {}
	ConvertCompToLayerTimeCmd(AE_Layer layer, A_Time comp_time) : layer(layer), comp_time(comp_time), Command(CommandID::ConvertCompToLayerTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& comp_time;
	}
};

class ConvertLayerToCompTime : public Command {
public:
	AE_Layer layer;
	A_Time layer_time;
	A_Time comp_time;
	ConvertLayerToCompTime() : Command(CommandID::ConvertLayerToCompTime) {}
	ConvertLayerToCompTime(AE_Layer layer, A_Time layer_time, A_Time comp_time) : layer(layer), layer_time(layer_time), comp_time(comp_time), Command(CommandID::ConvertLayerToCompTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& layer_time;
		ar& comp_time;
	}
};

class GetLayerDancingRandValueCmd : public Command {
public:
	AE_Layer layer;
	A_Time comp_time;
	GetLayerDancingRandValueCmd() : Command(CommandID::GetLayerDancingRandValue) {}
	GetLayerDancingRandValueCmd(AE_Layer layer, A_Time comp_time) : layer(layer), comp_time(comp_time), Command(CommandID::GetLayerDancingRandValue) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& comp_time;
	}
};

class GetLayerIDCmd : public Command {
public:
	AE_Layer layer;
	GetLayerIDCmd() : Command(CommandID::GetLayerID) {}
	GetLayerIDCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerID) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class GetLayerToWorldXformCmd : public Command {
public:
	AE_Layer layer;
	A_Time comp_time;
	GetLayerToWorldXformCmd() : Command(CommandID::GetLayerToWorldXform) {}
	GetLayerToWorldXformCmd(AE_Layer layer, A_Time comp_time) : layer(layer), comp_time(comp_time), Command(CommandID::GetLayerToWorldXform) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& comp_time;
	}
};

class GetLayerToWorldXformFromViewCmd : public Command {
public:
	AE_Layer layer;
	A_Time view_time;
	A_Time comp_time;
	GetLayerToWorldXformFromViewCmd() : Command(CommandID::GetLayerToWorldXformFromView) {}
	GetLayerToWorldXformFromViewCmd(AE_Layer layer, A_Time view_time, A_Time comp_time) : layer(layer), view_time(view_time), comp_time(comp_time), Command(CommandID::GetLayerToWorldXformFromView) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& view_time;
		ar& comp_time;
	}
};

class SetLayerNameCmd : public Command {
public:
	AE_Layer layer;
	std::string new_name;
	SetLayerNameCmd() : Command(CommandID::SetLayerName) {}
	SetLayerNameCmd(AE_Layer layer, std::string new_name) : layer(layer), new_name(new_name), Command(CommandID::SetLayerName) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& new_name;
	}
};

class GetLayerParentCmd : public Command {
public:
	AE_Layer layer;
	GetLayerParentCmd() : Command(CommandID::GetLayerParent) {}
	GetLayerParentCmd(AE_Layer layer) : layer(layer), Command(CommandID::GetLayerParent) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class SetLayerParentCmd : public Command {
public:
	AE_Layer layer;
	AE_Layer parent_layer;
	SetLayerParentCmd() : Command(CommandID::SetLayerParent) {}
	SetLayerParentCmd(AE_Layer layer, AE_Layer parent_layer) : layer(layer), parent_layer(parent_layer), Command(CommandID::SetLayerParent) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& parent_layer;
	}
};

class DeleteLayerCmd : public Command {
public:
	AE_Layer layer;
	DeleteLayerCmd() : Command(CommandID::DeleteLayer) {}
	DeleteLayerCmd(AE_Layer layer) : layer(layer), Command(CommandID::DeleteLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};

class DuplicateLayerCmd : public Command {
public:
	AE_Layer orig_layer;
	AE_Layer dupe_layer;
	DuplicateLayerCmd() : Command(CommandID::DuplicateLayer) {}
	DuplicateLayerCmd(AE_Layer orig_layer, AE_Layer dupe_layer) : orig_layer(orig_layer), dupe_layer(dupe_layer), Command(CommandID::DuplicateLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& orig_layer;
		ar& dupe_layer;
	}
};

class GetLayerFromLayerIDCmd : public Command {
public:
	AE_Comp parent_comp;
	AEGP_LayerIDVal id;
	GetLayerFromLayerIDCmd() : Command(CommandID::GetLayerFromLayerID) {}
	GetLayerFromLayerIDCmd(AE_Comp parent_comp, AEGP_LayerIDVal id) : parent_comp(parent_comp), id(id), Command(CommandID::GetLayerFromLayerID) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& id;
		ar& layer;
	}
};

class GetLayerLabelCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LabelID label;
	GetLayerLabelCmd() : Command(CommandID::GetLayerLabel) {}
	GetLayerLabelCmd(AE_Layer layer, AEGP_LabelID label) : layer(layer), label(label), Command(CommandID::GetLayerLabel) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& label;
	}
};

class SetLayerLabelCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LabelID label;
	SetLayerLabelCmd() : Command(CommandID::SetLayerLabel) {}
	SetLayerLabelCmd(AE_Layer layer, AEGP_LabelID label) : layer(layer), label(label), Command(CommandID::SetLayerLabel) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& label;
	}
};

class GetLayerSamplingQualityCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LayerSamplingQuality label;
	GetLayerSamplingQualityCmd() : Command(CommandID::GetLayerSamplingQuality) {}
	GetLayerSamplingQualityCmd(AE_Layer layer, AEGP_LayerSamplingQuality label) : layer(layer), label(label), Command(CommandID::GetLayerSamplingQuality) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& label;
	}
};

class SetLayerSamplingQualityCmd : public Command {
public:
	AE_Layer layer;
	AEGP_LayerSamplingQuality label;
	SetLayerSamplingQualityCmd() : Command(CommandID::SetLayerSamplingQuality) {}
	SetLayerSamplingQualityCmd(AE_Layer layer, AEGP_LayerSamplingQuality label) : layer(layer), label(label), Command(CommandID::SetLayerSamplingQuality) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& label;
	}
};

class GetTrackMatteLayerCmd : public Command {
public:
	AE_Layer layer;
	AE_Layer track_matte_layer;
	GetTrackMatteLayerCmd() : Command(CommandID::GetTrackMatteLayer) {}
	GetTrackMatteLayerCmd(AE_Layer layer, AE_Layer track_matte_layer) : layer(layer), track_matte_layer(track_matte_layer), Command(CommandID::GetTrackMatteLayer) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& track_matte_layer;
	}
};

class SetTrackMatteCmd : public Command {
public:
	AE_Layer layer;
	AE_Layer track_matte_layer;
	AEGP_TrackMatte track_matte_type;
	SetTrackMatteCmd() : Command(CommandID::SetTrackMatte) {}
	SetTrackMatteCmd(AE_Layer layer, AE_Layer track_matte_layer, AEGP_TrackMatte track_matte_type) : layer(layer), track_matte_layer(track_matte_layer), track_matte_type(track_matte_type), Command(CommandID::SetTrackMatte) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
		ar& track_matte_layer;
		ar& track_matte_type;
	}
};

class RemoveTrackMatteCmd : public Command {
public:
	AE_Layer layer;
	RemoveTrackMatteCmd() : Command(CommandID::RemoveTrackMatte) {}
	RemoveTrackMatteCmd(AE_Layer layer) : layer(layer), Command(CommandID::RemoveTrackMatte) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& layer;
	}
};
