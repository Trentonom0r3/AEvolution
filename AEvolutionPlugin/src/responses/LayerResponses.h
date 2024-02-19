#pragma once
#include "../MessageMain.h"

class GetCompNumLayersResp : public Response {
public:
	A_long num_layers;
	GetCompNumLayersResp() = default;
	GetCompNumLayersResp(A_long num_layers, std::string error) : num_layers(num_layers), Response(CommandID::GetCompNumLayers, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& num_layers;
	}
};

class GetCompLayerByIndexResp : public Response {
public:
    AE_Layer layer;
    GetCompLayerByIndexResp() = default;
    GetCompLayerByIndexResp(AEGP_LayerH layerH, std::string error) : layer(AE_Layer(layerH)), Response(CommandID::GetCompLayerByIndex, error) {};
    template<class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& layer;
    }
};

class GetActiveLayerResp : public Response {
public:
	AE_Layer layer;
	GetActiveLayerResp() = default;
	GetActiveLayerResp(AEGP_LayerH layerH, std::string error) : layer(AE_Layer(layerH)), Response(CommandID::GetActiveLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& layer;
	}
};

class GetLayerIndexResp : public Response {
public:
	A_long layer_index;
	GetLayerIndexResp() = default;
	GetLayerIndexResp(A_long layer_index, std::string error) : layer_index(layer_index), Response(CommandID::GetLayerIndex, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& layer_index;
	}
};

class GetLayerSourceItemResp : public Response {
public:
	AE_Item source_item;
	GetLayerSourceItemResp() = default;
	GetLayerSourceItemResp(AEGP_ItemH itemH, std::string error) : source_item(AE_Item(itemH)), Response(CommandID::GetLayerSourceItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& source_item;
	}
};

class GetLayerSourceItemIDResp : public Response {
public:
	A_long source_id;
	GetLayerSourceItemIDResp() = default;
	GetLayerSourceItemIDResp(A_long source_id, std::string error) : source_id(source_id), Response(CommandID::GetLayerSourceItemID, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& source_id;
	}
};

class GetLayerParentCompResp : public Response {
public:
	AE_Comp comp;
	GetLayerParentCompResp() = default;
	GetLayerParentCompResp(AEGP_CompH compH, std::string error) : comp(AE_Comp(compH)), Response(CommandID::GetLayerParentComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& comp;
	}
};

class GetLayerNameResp : public Response {
public:
	std::string utf_layer_name;
	std::string utf_source_name;
	GetLayerNameResp() = default;
	GetLayerNameResp(std::string utf_layer_name, std::string utf_source_name, std::string error) : utf_layer_name(utf_layer_name), utf_source_name(utf_source_name), Response(CommandID::GetLayerName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& utf_layer_name;
		ar& utf_source_name;
	}
};

class GetLayerQualityResp : public Response {
public:
	AEGP_LayerQuality quality;
	GetLayerQualityResp() = default;
	GetLayerQualityResp(AEGP_LayerQuality quality, std::string error) : quality(quality), Response(CommandID::GetLayerQuality, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& quality;
	}
};

class SetLayerQualityResp : public Response {
public:
	SetLayerQualityResp() = default;
	SetLayerQualityResp(std::string error) : Response(CommandID::SetLayerQuality, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerFlagsResp : public Response {
public:
	AEGP_LayerFlags layer_flags;
	GetLayerFlagsResp() = default;
	GetLayerFlagsResp(AEGP_LayerFlags layer_flags, std::string error) : layer_flags(layer_flags), Response(CommandID::GetLayerFlags, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& layer_flags;
	}
};

class SetLayerFlagResp : public Response {
public:
	SetLayerFlagResp() = default;
	SetLayerFlagResp(std::string error) : Response(CommandID::SetLayerFlags, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class IsLayerVideoReallyOnResp : public Response {
public:
	A_Boolean on;
	IsLayerVideoReallyOnResp() = default;
	IsLayerVideoReallyOnResp(A_Boolean on, std::string error) : on(on), Response(CommandID::IsLayerVideoReallyOn, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& on;
	}
};

class IsLayerAudioReallyOnResp : public Response {
public:
	A_Boolean on;
	IsLayerAudioReallyOnResp() = default;
	IsLayerAudioReallyOnResp(A_Boolean on, std::string error) : on(on), Response(CommandID::IsLayerAudioReallyOn, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& on;
	}
};

class GetLayerCurrentTimeResp : public Response {
public:
	A_Time curr_time;
	GetLayerCurrentTimeResp() = default;
	GetLayerCurrentTimeResp(A_Time curr_time, std::string error) : curr_time(curr_time), Response(CommandID::GetLayerCurrentTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& curr_time;
	}
};

class GetLayerInPointResp : public Response {
public:
	A_Time in_point;
	GetLayerInPointResp() = default;
	GetLayerInPointResp(A_Time in_point, std::string error) : in_point(in_point), Response(CommandID::GetLayerInPoint, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& in_point;
	}
};

class GetLayerDurationResp : public Response {
public:
	A_Time duration;
	GetLayerDurationResp() = default;
	GetLayerDurationResp(A_Time duration, std::string error) : duration(duration), Response(CommandID::GetLayerDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& duration;
	}
};

class SetLayerInPointAndDurationResp : public Response {
public:
	SetLayerInPointAndDurationResp() = default;
	SetLayerInPointAndDurationResp(std::string error) : Response(CommandID::SetLayerInPointAndDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerOffsetResp : public Response {
public:
	A_Time offset;
	GetLayerOffsetResp() = default;
	GetLayerOffsetResp(A_Time offset, std::string error) : offset(offset), Response(CommandID::GetLayerOffset, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& offset;
	}
};

class SetLayerOffsetResp : public Response {
public:
	SetLayerOffsetResp() = default;
	SetLayerOffsetResp(std::string error) : Response(CommandID::SetLayerOffset, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerStretchResp : public Response {
public:
	A_Ratio stretch;
	GetLayerStretchResp() = default;
	GetLayerStretchResp(A_Ratio stretch, std::string error) : stretch(stretch), Response(CommandID::GetLayerStretch, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& stretch;
	}
};

class SetLayerStretchResp : public Response {
public:
	SetLayerStretchResp() = default;
	SetLayerStretchResp(std::string error) : Response(CommandID::SetLayerStretch, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerTransferModeResp : public Response {
public:
	AEGP_LayerTransferMode mode;
	GetLayerTransferModeResp() = default;
	GetLayerTransferModeResp(AEGP_LayerTransferMode mode, std::string error) : mode(mode), Response(CommandID::GetLayerTransferMode, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& mode;
	}
};

class SetLayerTransferModeResp : public Response {
public:
	SetLayerTransferModeResp() = default;
	SetLayerTransferModeResp(std::string error) : Response(CommandID::SetLayerTransferMode, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class IsAddLayerValidResp : public Response {
public:
	A_Boolean valid;
	IsAddLayerValidResp() = default;
	IsAddLayerValidResp(A_Boolean valid, std::string error) : valid(valid), Response(CommandID::IsAddLayerValid, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& valid;
	}
};

class AddLayerResp : public Response {
public:
	AE_Layer layer;
	AddLayerResp() = default;
	AddLayerResp(AEGP_LayerH added_layer, std::string error) : layer(AE_Layer(added_layer)), Response(CommandID::AddLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& layer;
	}
};

class ReorderLayerResp : public Response {
public:
	ReorderLayerResp() = default;
	ReorderLayerResp(std::string error) : Response(CommandID::ReorderLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerMaskedBoundsResp : public Response {
public:
	A_FloatRect bounds;
	A_Time time;
	GetLayerMaskedBoundsResp() = default;
	GetLayerMaskedBoundsResp(A_FloatRect bounds, std::string error) : bounds(bounds), Response(CommandID::GetLayerMaskedBounds, error) {};
	GetLayerMaskedBoundsResp(A_FloatRect bounds, A_Time time, std::string error) : bounds(bounds), time(time), Response(CommandID::GetLayerMaskedBounds, error) {};	
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& bounds;
	}
};

class GetLayerObjectTypeResp : public Response {
public:
	AEGP_ObjectType object_type;
	GetLayerObjectTypeResp() = default;
	GetLayerObjectTypeResp(AEGP_ObjectType object_type, std::string error) : object_type(object_type), Response(CommandID::GetLayerObjectType, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& object_type;
	}
};

class IsLayer3DResp : public Response {
public:
	A_Boolean is_3D;
	IsLayer3DResp() = default;
	IsLayer3DResp(A_Boolean is_3D, std::string error) : is_3D(is_3D), Response(CommandID::IsLayer3D, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_3D;
	}
};

class IsLayer2DResp : public Response {
public:
	A_Boolean is_2D;
	IsLayer2DResp() = default;
	IsLayer2DResp(A_Boolean is_2D, std::string error) : is_2D(is_2D), Response(CommandID::IsLayer2D, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_2D;
	}
};

class IsVideoActiveResp : public Response {
public:
	A_Boolean is_active;
	A_Time comp_time;
	IsVideoActiveResp() = default;
	IsVideoActiveResp(A_Boolean is_active, std::string error) : is_active(is_active), Response(CommandID::IsVideoActive, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_active;
	}
};

class IsLayerUsedAsTrackMatteResp : public Response {
public:
	A_Boolean is_track_matte;
	IsLayerUsedAsTrackMatteResp() = default;
	IsLayerUsedAsTrackMatteResp(A_Boolean is_track_matte, std::string error) : is_track_matte(is_track_matte), Response(CommandID::IsLayerUsedAsTrackMatte, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_track_matte;
	}
};

class DoesLayerHaveTrackMatteResp : public Response {
public:
	A_Boolean has_track_matte;
	DoesLayerHaveTrackMatteResp() = default;
	DoesLayerHaveTrackMatteResp(A_Boolean has_track_matte, std::string error) : has_track_matte(has_track_matte), Response(CommandID::DoesLayerHaveTrackMatte, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& has_track_matte;
	}
};

class ConvertCompToLayerTimeResp : public Response {
public:
	A_Time layer_time;
	ConvertCompToLayerTimeResp() = default;
	ConvertCompToLayerTimeResp(A_Time layer_time, std::string error) : layer_time(layer_time), Response(CommandID::ConvertCompToLayerTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& layer_time;
	}
};

class ConvertLayerToCompTimeResp : public Response {
public:
	A_Time comp_time;
	ConvertLayerToCompTimeResp() = default;
	ConvertLayerToCompTimeResp(A_Time comp_time, std::string error) : comp_time(comp_time), Response(CommandID::ConvertLayerToCompTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& comp_time;
	}
};

class GetLayerDancingRandValueResp : public Response {
public:
	A_long rand_value;
	GetLayerDancingRandValueResp() = default;
	GetLayerDancingRandValueResp(A_long rand_value, std::string error) : rand_value(rand_value), Response(CommandID::GetLayerDancingRandValue, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& rand_value;
	}
};

class GetLayerIDResp : public Response {
public:
	AEGP_LayerIDVal id_val;
	GetLayerIDResp() = default;
	GetLayerIDResp(AEGP_LayerIDVal id_val, std::string error) : id_val(id_val), Response(CommandID::GetLayerID, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& id_val;
	}
};

class GetLayerToWorldXformResp : public Response {
public:
	A_Matrix4 transform;
	GetLayerToWorldXformResp() = default;
	GetLayerToWorldXformResp(A_Matrix4 transform, std::string error) : transform(transform), Response(CommandID::GetLayerToWorldXform, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& transform;
	}
};

class GetLayerToWorldXformFromViewResp : public Response {
public:
	A_Matrix4 transform;
	GetLayerToWorldXformFromViewResp() = default;
	GetLayerToWorldXformFromViewResp(A_Matrix4 transform, std::string error) : transform(transform), Response(CommandID::GetLayerToWorldXformFromView, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& transform;
	}
};

class SetLayerNameResp : public Response {
public:
	SetLayerNameResp() = default;
	SetLayerNameResp(std::string error) : Response(CommandID::SetLayerName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerParentResp : public Response {
public:
	AE_Layer parent_layer;
	GetLayerParentResp() = default;
	GetLayerParentResp(AEGP_LayerH parent_layerH, std::string error) : parent_layer(AE_Layer(parent_layerH)), Response(CommandID::GetLayerParent, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& parent_layer;
	}
};

class SetLayerParentResp : public Response {
public:
	SetLayerParentResp() = default;
	SetLayerParentResp(std::string error) : Response(CommandID::SetLayerParent, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class DeleteLayerResp : public Response {
public:
	DeleteLayerResp() = default;
	DeleteLayerResp(std::string error) : Response(CommandID::DeleteLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class DuplicateLayerResp : public Response {
public:
	AE_Layer dupe_layer;
	DuplicateLayerResp() = default;
	DuplicateLayerResp(AEGP_LayerH dupe_layerH, std::string error) : dupe_layer(AE_Layer(dupe_layerH)), Response(CommandID::DuplicateLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& dupe_layer;
	}
};

class GetLayerFromLayerIDResp : public Response {
public:
	AE_Layer layer;
	GetLayerFromLayerIDResp() = default;
	GetLayerFromLayerIDResp(AEGP_LayerH layerH, std::string error) : layer(AE_Layer(layerH)), Response(CommandID::GetLayerFromLayerID, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& layer;
	}
};

class GetLayerLabelResp : public Response {
public:
	AEGP_LabelID label;
	GetLayerLabelResp() = default;
	GetLayerLabelResp(AEGP_LabelID label, std::string error) : label(label), Response(CommandID::GetLayerLabel, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& label;
	}
};

class SetLayerLabelResp : public Response {
public:
	SetLayerLabelResp() = default;
	SetLayerLabelResp(std::string error) : Response(CommandID::SetLayerLabel, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLayerSamplingQualityResp : public Response {
public:
	AEGP_LayerSamplingQuality label;
	GetLayerSamplingQualityResp() = default;
	GetLayerSamplingQualityResp(AEGP_LayerSamplingQuality label, std::string error) : label(label), Response(CommandID::GetLayerSamplingQuality, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& label;
	}
};

class SetLayerSamplingQualityResp : public Response {
public:
	SetLayerSamplingQualityResp() = default;
	SetLayerSamplingQualityResp(std::string error) : Response(CommandID::SetLayerSamplingQuality, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetTrackMatteLayerResp : public Response {
public:
	AE_Layer track_matte_layer;
	GetTrackMatteLayerResp() = default;
	GetTrackMatteLayerResp(AEGP_LayerH track_matte_layerH, std::string error) : track_matte_layer(AE_Layer(track_matte_layerH)), Response(CommandID::GetTrackMatteLayer, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& track_matte_layer;
	}
};

class SetTrackMatteResp : public Response {
public:
	SetTrackMatteResp() = default;
	SetTrackMatteResp(std::string error) : Response(CommandID::SetTrackMatte, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class RemoveTrackMatteResp : public Response {
public:
	RemoveTrackMatteResp() = default;
	RemoveTrackMatteResp(std::string error) : Response(CommandID::RemoveTrackMatte, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};