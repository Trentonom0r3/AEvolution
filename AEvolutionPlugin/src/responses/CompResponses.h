#pragma once
#include "../MessageMain.h"

class GetCompFromItemResp : public Response {
public:
	AE_Comp compH; //What will be contained in the response
	GetCompFromItemResp() = default;
	GetCompFromItemResp(AEGP_CompH compH, std::string error) : compH(AE_Comp(compH)), Response(CommandID::GetCompFromItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& compH;
	}
};

class GetItemFromCompResp : public Response {
public:
	AE_Item itemH; //What will be contained in the response
	GetItemFromCompResp() = default;
	GetItemFromCompResp(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetItemFromComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class GetCompDownsampleFactorResp : public Response {
public:
	AEGP_DownsampleFactor dsfP; //What will be contained in the response
	GetCompDownsampleFactorResp() = default;
	GetCompDownsampleFactorResp(AEGP_DownsampleFactor dsfP, std::string error) : dsfP(dsfP), Response(CommandID::GetCompDownsampleFactor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& dsfP;
	}
};

class SetCompDownsampleFactorResp : public Response {
public:
	SetCompDownsampleFactorResp() = default;
	SetCompDownsampleFactorResp(std::string error) : Response(CommandID::SetCompDownsampleFactor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompBGColorResp : public Response {
public:
	AEGP_ColorVal bg_colorP; //What will be contained in the response
	GetCompBGColorResp() = default;
	GetCompBGColorResp(AEGP_ColorVal bg_colorP, std::string error) : bg_colorP(bg_colorP), Response(CommandID::GetCompBGColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& bg_colorP;
	}
};

class SetCompBGColorResp : public Response {
public:
	SetCompBGColorResp() = default;
	SetCompBGColorResp(std::string error) : Response(CommandID::SetCompBGColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompFlagsResp : public Response {
public:
	AEGP_CompFlags flags; //What will be contained in the response
	GetCompFlagsResp() = default;
	GetCompFlagsResp(AEGP_CompFlags flags, std::string error) : flags(flags), Response(CommandID::GetCompFlags, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& flags;
	}
};

class GetShowLayerNameOrSourceNameResp : public Response {
public:
	A_Boolean layer_names_shownPB; //What will be contained in the response
	GetShowLayerNameOrSourceNameResp() = default;
	GetShowLayerNameOrSourceNameResp(A_Boolean layer_names_shownPB, std::string error) : layer_names_shownPB(layer_names_shownPB), Response(CommandID::GetShowLayerNameOrSourceName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& layer_names_shownPB;
	}
};

class SetShowLayerNameOrSourceNameResp : public Response {
public:
	SetShowLayerNameOrSourceNameResp() = default;
	SetShowLayerNameOrSourceNameResp(std::string error) : Response(CommandID::SetShowLayerNameOrSourceName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetShowBlendModesResp : public Response {
public:
	A_Boolean blend_modes_shownPB; //What will be contained in the response
	GetShowBlendModesResp() = default;
	GetShowBlendModesResp(A_Boolean blend_modes_shownPB, std::string error) : blend_modes_shownPB(blend_modes_shownPB), Response(CommandID::GetShowBlendModes, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& blend_modes_shownPB;
	}
};

class SetShowBlendModesResp : public Response {
public:
	SetShowBlendModesResp() = default;
	SetShowBlendModesResp(std::string error) : Response(CommandID::SetShowBlendModes, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompFramerateResp : public Response {
public:
	A_FpLong fpsPF; //What will be contained in the response
	GetCompFramerateResp() = default;
	GetCompFramerateResp(A_FpLong fpsPF, std::string error) : fpsPF(fpsPF), Response(CommandID::GetCompFramerate, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& fpsPF;
	}
};

class SetCompFramerateResp : public Response {
public:
	SetCompFramerateResp() = default;
	SetCompFramerateResp(std::string error) : Response(CommandID::SetCompFramerate, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompShutterAnglePhaseResp : public Response {
public:
	A_Ratio angle;
	A_Ratio phase;
	GetCompShutterAnglePhaseResp() = default;
	GetCompShutterAnglePhaseResp(A_Ratio angle, A_Ratio phase, std::string error) : angle(angle), phase(phase), Response(CommandID::GetCompShutterAnglePhase, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& angle;
		ar& phase;
	}
};

class GetCompShutterFrameRangeResp : public Response {
public:
	A_Time comp_timeP;
	GetCompShutterFrameRangeResp() = default;
	GetCompShutterFrameRangeResp(A_Time comp_timeP, std::string error) : comp_timeP(comp_timeP), Response(CommandID::GetCompShutterFrameRange, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& comp_timeP;
	}
};

class GetCompSuggestedMotionBlurSamplesResp : public Response {
public:
	A_long samplesPL;
	GetCompSuggestedMotionBlurSamplesResp() = default;
	GetCompSuggestedMotionBlurSamplesResp(A_long samplesPL, std::string error) : samplesPL(samplesPL), Response(CommandID::GetCompSuggestedMotionBlurSamples, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& samplesPL;
	}
};

class SetCompSuggestedMotionBlurSamplesResp : public Response {
public:
	SetCompSuggestedMotionBlurSamplesResp() = default;
	SetCompSuggestedMotionBlurSamplesResp(std::string error) : Response(CommandID::SetCompSuggestedMotionBlurSamples, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompMotionBlurAdaptiveSampleLimitResp : public Response {
public:
	A_long samplesPL;
	GetCompMotionBlurAdaptiveSampleLimitResp() = default;
	GetCompMotionBlurAdaptiveSampleLimitResp(A_long samplesPL, std::string error) : samplesPL(samplesPL), Response(CommandID::GetCompMotionBlurAdaptiveSampleLimit, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& samplesPL;
	}
};

class SetCompMotionBlurAdaptiveSampleLimitResp : public Response {
public:
	SetCompMotionBlurAdaptiveSampleLimitResp() = default;
	SetCompMotionBlurAdaptiveSampleLimitResp(std::string error) : Response(CommandID::SetCompMotionBlurAdaptiveSampleLimit, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetCompWorkAreaStartResp : public Response {
public:
	A_Time startPT;
	GetCompWorkAreaStartResp() = default;
	GetCompWorkAreaStartResp(A_Time startPT, std::string error) : startPT(startPT), Response(CommandID::GetCompWorkAreaStart, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& startPT;
	}
};

class GetCompWorkAreaDurationResp : public Response {
public:
	A_Time durationPT;
	GetCompWorkAreaDurationResp() = default;
	GetCompWorkAreaDurationResp(A_Time durationPT, std::string error) : durationPT(durationPT), Response(CommandID::GetCompWorkAreaDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& durationPT;
	}
};

class SetCompWorkAreaStartAndDurationResp : public Response {
public:
	SetCompWorkAreaStartAndDurationResp() = default;
	SetCompWorkAreaStartAndDurationResp(std::string error) : Response(CommandID::SetCompWorkAreaStartAndDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CreateSolidInCompResp : public Response {
public:
	AE_Layer new_solidPH;
	CreateSolidInCompResp() = default;
	CreateSolidInCompResp(AEGP_LayerH new_solidPH, std::string error) : new_solidPH(AE_Layer(new_solidPH)), Response(CommandID::CreateSolidInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_solidPH;
	}
};

class CreateCameraInCompResp : public Response {
public:
	AE_Layer new_cameraPH;
	CreateCameraInCompResp() = default;
	CreateCameraInCompResp(AEGP_LayerH new_cameraPH, std::string error) : new_cameraPH(AE_Layer(new_cameraPH)), Response(CommandID::CreateCameraInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_cameraPH;
	}
};

class CreateLightInCompResp : public Response {
public:
	AE_Layer new_lightPH;
	CreateLightInCompResp() = default;
	CreateLightInCompResp(AEGP_LayerH new_lightPH, std::string error) : new_lightPH(AE_Layer(new_lightPH)), Response(CommandID::CreateLightInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_lightPH;
	}
};

class CreateCompResp : public Response {
public:
	AE_Comp new_compPH;
	CreateCompResp() = default;
	CreateCompResp(AEGP_CompH new_compPH, std::string error) : new_compPH(AE_Comp(new_compPH)), Response(CommandID::CreateComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_compPH;
	}
};

class GetCompDisplayStartTimeResp : public Response {
public:
	A_Time start_timePT;
	GetCompDisplayStartTimeResp() = default;
	GetCompDisplayStartTimeResp(A_Time start_timePT, std::string error) : start_timePT(start_timePT), Response(CommandID::GetCompDisplayStartTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& start_timePT;
	}
};

class SetCompDisplayStartTimeResp : public Response {
public:
	SetCompDisplayStartTimeResp() = default;
	SetCompDisplayStartTimeResp(std::string error) : Response(CommandID::SetCompDisplayStartTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class SetCompDurationResp : public Response {
public:
	SetCompDurationResp() = default;
	SetCompDurationResp(std::string error) : Response(CommandID::SetCompDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CreateNullInCompResp : public Response {
public:
	AE_Layer new_null_solidPH;
	CreateNullInCompResp() = default;
	CreateNullInCompResp(AEGP_LayerH new_null_solidPH, std::string error) : new_null_solidPH(AE_Layer(new_null_solidPH)), Response(CommandID::CreateNullInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_null_solidPH;
	}
};

class SetCompPixelAspectRatioResp : public Response {
public:
	SetCompPixelAspectRatioResp() = default;
	SetCompPixelAspectRatioResp(std::string error) : Response(CommandID::SetCompPixelAspectRatio, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CreateTextLayerInCompResp : public Response {
public:
	AE_Layer new_text_lyrPH;
	CreateTextLayerInCompResp() = default;
	CreateTextLayerInCompResp(AEGP_LayerH new_text_lyrPH, std::string error) : new_text_lyrPH(AE_Layer(new_text_lyrPH)), Response(CommandID::CreateTextLayerInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_text_lyrPH;
	}
};

class CreateBoxTextLayerInCompResp : public Response {
public:
	AE_Layer new_text_layerPH;
	CreateBoxTextLayerInCompResp() = default;
	CreateBoxTextLayerInCompResp(AEGP_LayerH new_text_layerPH, std::string error) : new_text_layerPH(AE_Layer(new_text_layerPH)), Response(CommandID::CreateBoxTextLayerInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_text_layerPH;
	}
};

class SetCompDimensionsResp : public Response {
public:
	SetCompDimensionsResp() = default;
	SetCompDimensionsResp(std::string error) : Response(CommandID::SetCompDimensions, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class DuplicateCompResp : public Response {
public:
	AE_Comp new_compPH;
	DuplicateCompResp() = default;
	DuplicateCompResp(AEGP_CompH new_compPH, std::string error) : new_compPH(AE_Comp(new_compPH)), Response(CommandID::DuplicateComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_compPH;
	}
};

class GetCompFrameDurationResp : public Response {
public:
	A_Time timeP;
	GetCompFrameDurationResp() = default;
	GetCompFrameDurationResp(A_Time timeP, std::string error) : timeP(timeP), Response(CommandID::GetCompFrameDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& timeP;
	}
};

class GetMostRecentlyUsedCompResp : public Response {
public:
	AE_Comp compPH;
	GetMostRecentlyUsedCompResp() = default;
	GetMostRecentlyUsedCompResp(AEGP_CompH compPH, std::string error) : compPH(AE_Comp(compPH)), Response(CommandID::GetMostRecentlyUsedComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& compPH;
	}
};

class CreateVectorLayerInCompResp : public Response {
public:
	AE_Layer new_vec_layerPH;
	CreateVectorLayerInCompResp() = default;
	CreateVectorLayerInCompResp(AEGP_LayerH new_vec_layerPH, std::string error) : new_vec_layerPH(AE_Layer(new_vec_layerPH)), Response(CommandID::CreateVectorLayerInComp, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_vec_layerPH;
	}
};

class GetNewCompMarkerStreamResp : public Response {
public:
	AE_StreamRef streamPH;
	GetNewCompMarkerStreamResp() = default;
	GetNewCompMarkerStreamResp(AEGP_StreamRefH streamPH, std::string error) : streamPH(AE_StreamRef(streamPH)), Response(CommandID::GetNewCompMarkerStream, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& streamPH;
	}
};

class GetCompDisplayDropFrameResp : public Response {
public:
	A_Boolean dropFramePB;
	GetCompDisplayDropFrameResp() = default;
	GetCompDisplayDropFrameResp(A_Boolean dropFramePB, std::string error) : dropFramePB(dropFramePB), Response(CommandID::GetCompDisplayDropFrame, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& dropFramePB;
	}
};

class SetCompDisplayDropFrameResp : public Response {
public:
	SetCompDisplayDropFrameResp() = default;
	SetCompDisplayDropFrameResp(std::string error) : Response(CommandID::SetCompDisplayDropFrame, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};



