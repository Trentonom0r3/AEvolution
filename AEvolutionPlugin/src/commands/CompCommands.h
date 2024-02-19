#pragma once
#include "../MessageMain.h"
#include "../responses/CompResponses.h"

class GetCompFromItemCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetCompFromItemCmd() : Command(CommandID::GetCompFromItem) {}
	GetCompFromItemCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetCompFromItem) {}
    GetCompFromItemCmd(AE_Item item) : item(item), Command(CommandID::GetCompFromItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemFromCompCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetItemFromCompCmd() : Command(CommandID::GetItemFromComp) {}
	GetItemFromCompCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetItemFromComp) {}
	GetItemFromCompCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetItemFromComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompDownsampleFactorCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompDownsampleFactorCmd() : Command(CommandID::GetCompDownsampleFactor) {}
	GetCompDownsampleFactorCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompDownsampleFactor) {}
	GetCompDownsampleFactorCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompDownsampleFactor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompDownsampleFactorCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	AEGP_DownsampleFactor dsf;
	SetCompDownsampleFactorCmd() : Command(CommandID::SetCompDownsampleFactor) {}
	SetCompDownsampleFactorCmd(AEGP_CompH comp, AEGP_DownsampleFactor dsf) : comp(AE_Comp(comp)), dsf(dsf), Command(CommandID::SetCompDownsampleFactor) {}
	SetCompDownsampleFactorCmd(AE_Comp comp, AEGP_DownsampleFactor dsf) : comp(comp), dsf(dsf), Command(CommandID::SetCompDownsampleFactor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& dsf;
	}
};

class GetCompBGColorCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompBGColorCmd() : Command(CommandID::GetCompBGColor) {}
	GetCompBGColorCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompBGColor) {}
	GetCompBGColorCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompBGColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompBGColorCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	AEGP_ColorVal bg_color;
	SetCompBGColorCmd() : Command(CommandID::SetCompBGColor) {}
	SetCompBGColorCmd(AEGP_CompH comp, AEGP_ColorVal bg_color) : comp(AE_Comp(comp)), bg_color(bg_color), Command(CommandID::SetCompBGColor) {}
	SetCompBGColorCmd(AE_Comp comp, AEGP_ColorVal bg_color) : comp(comp), bg_color(bg_color), Command(CommandID::SetCompBGColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& bg_color;
	}
};

class GetCompFlagsCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompFlagsCmd() : Command(CommandID::GetCompFlags) {}
	GetCompFlagsCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompFlags) {}
	GetCompFlagsCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompFlags) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetShowLayerNameOrSourceNameCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetShowLayerNameOrSourceNameCmd() : Command(CommandID::GetShowLayerNameOrSourceName) {}
	GetShowLayerNameOrSourceNameCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetShowLayerNameOrSourceName) {}
	GetShowLayerNameOrSourceNameCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetShowLayerNameOrSourceName) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetShowLayerNameOrSourceNameCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean layer_names_shown;
	SetShowLayerNameOrSourceNameCmd() : Command(CommandID::SetShowLayerNameOrSourceName) {}
	SetShowLayerNameOrSourceNameCmd(AEGP_CompH comp, A_Boolean layer_names_shown) : comp(AE_Comp(comp)), layer_names_shown(layer_names_shown), Command(CommandID::SetShowLayerNameOrSourceName) {}
	SetShowLayerNameOrSourceNameCmd(AE_Comp comp, A_Boolean layer_names_shown) : comp(comp), layer_names_shown(layer_names_shown), Command(CommandID::SetShowLayerNameOrSourceName) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& layer_names_shown;
	}
};

class GetShowBlendModesCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetShowBlendModesCmd() : Command(CommandID::GetShowBlendModes) {}
	GetShowBlendModesCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetShowBlendModes) {}
	GetShowBlendModesCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetShowBlendModes) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetShowBlendModesCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean show_blend_modes;
	SetShowBlendModesCmd() : Command(CommandID::SetShowBlendModes) {}
	SetShowBlendModesCmd(AEGP_CompH comp, A_Boolean show_blend_modes) : comp(AE_Comp(comp)), show_blend_modes(show_blend_modes), Command(CommandID::SetShowBlendModes) {}
	SetShowBlendModesCmd(AE_Comp comp, A_Boolean show_blend_modes) : comp(comp), show_blend_modes(show_blend_modes), Command(CommandID::SetShowBlendModes) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& show_blend_modes;
	}
};

class GetCompFramerateCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompFramerateCmd() : Command(CommandID::GetCompFramerate) {}
	GetCompFramerateCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompFramerate) {}
	GetCompFramerateCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompFramerate) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompFramerateCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_FpLong fps;
	SetCompFramerateCmd() : Command(CommandID::SetCompFramerate) {}
	SetCompFramerateCmd(AEGP_CompH comp, A_FpLong fps) : comp(AE_Comp(comp)), fps(fps), Command(CommandID::SetCompFramerate) {}
	SetCompFramerateCmd(AE_Comp comp, A_FpLong fps) : comp(comp), fps(fps), Command(CommandID::SetCompFramerate) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& fps;
	}
};

class GetCompShutterAnglePhaseCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompShutterAnglePhaseCmd() : Command(CommandID::GetCompShutterAnglePhase) {}
	GetCompShutterAnglePhaseCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompShutterAnglePhase) {}
	GetCompShutterAnglePhaseCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompShutterAnglePhase) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompShutterFrameRangeCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompShutterFrameRangeCmd() : Command(CommandID::GetCompShutterFrameRange) {}
	GetCompShutterFrameRangeCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompShutterFrameRange) {}
	GetCompShutterFrameRangeCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompShutterFrameRange) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompSuggestedMotionBlurSamplesCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompSuggestedMotionBlurSamplesCmd() : Command(CommandID::GetCompSuggestedMotionBlurSamples) {}
	GetCompSuggestedMotionBlurSamplesCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompSuggestedMotionBlurSamples) {}
	GetCompSuggestedMotionBlurSamplesCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompSuggestedMotionBlurSamples) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompSuggestedMotionBlurSamplesCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_long samples;
	SetCompSuggestedMotionBlurSamplesCmd() : Command(CommandID::SetCompSuggestedMotionBlurSamples) {}
	SetCompSuggestedMotionBlurSamplesCmd(AEGP_CompH comp, A_long samples) : comp(AE_Comp(comp)), samples(samples), Command(CommandID::SetCompSuggestedMotionBlurSamples) {}
	SetCompSuggestedMotionBlurSamplesCmd(AE_Comp comp, A_long samples) : comp(comp), samples(samples), Command(CommandID::SetCompSuggestedMotionBlurSamples) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& samples;
	}
};

class GetCompMotionBlurAdaptiveSampleLimitCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompMotionBlurAdaptiveSampleLimitCmd() : Command(CommandID::GetCompMotionBlurAdaptiveSampleLimit) {}
	GetCompMotionBlurAdaptiveSampleLimitCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompMotionBlurAdaptiveSampleLimit) {}
	GetCompMotionBlurAdaptiveSampleLimitCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompMotionBlurAdaptiveSampleLimit) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompMotionBlurAdaptiveSampleLimitCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_long samples;
	SetCompMotionBlurAdaptiveSampleLimitCmd() : Command(CommandID::SetCompMotionBlurAdaptiveSampleLimit) {}
	SetCompMotionBlurAdaptiveSampleLimitCmd(AEGP_CompH comp, A_long samples) : comp(AE_Comp(comp)), samples(samples), Command(CommandID::SetCompMotionBlurAdaptiveSampleLimit) {}
	SetCompMotionBlurAdaptiveSampleLimitCmd(AE_Comp comp, A_long samples) : comp(comp), samples(samples), Command(CommandID::SetCompMotionBlurAdaptiveSampleLimit) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& samples;
	}
};

class GetCompWorkAreaStartCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompWorkAreaStartCmd() : Command(CommandID::GetCompWorkAreaStart) {}
	GetCompWorkAreaStartCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompWorkAreaStart) {}
	GetCompWorkAreaStartCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompWorkAreaStart) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompWorkAreaDurationCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompWorkAreaDurationCmd() : Command(CommandID::GetCompWorkAreaDuration) {}
	GetCompWorkAreaDurationCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompWorkAreaDuration) {}
	GetCompWorkAreaDurationCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompWorkAreaDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompWorkAreaStartAndDurationCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Time start;
	A_Time duration;
	SetCompWorkAreaStartAndDurationCmd() : Command(CommandID::SetCompWorkAreaStartAndDuration) {}
	SetCompWorkAreaStartAndDurationCmd(AEGP_CompH comp, A_Time start, A_Time duration) : comp(AE_Comp(comp)), start(start), duration(duration), Command(CommandID::SetCompWorkAreaStartAndDuration) {}
	SetCompWorkAreaStartAndDurationCmd(AE_Comp comp, A_Time start, A_Time duration) : comp(comp), start(start), duration(duration), Command(CommandID::SetCompWorkAreaStartAndDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& start;
		ar& duration;
	}
};

class CreateSolidInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	std::string utf_name;
	A_long width;
	A_long height;
	AEGP_ColorVal color;
	A_Time duration;
	CreateSolidInCompCmd() : Command(CommandID::CreateSolidInComp) {}
	CreateSolidInCompCmd(AEGP_CompH parent_comp, std::string utf_name, A_long width, A_long height, AEGP_ColorVal color, A_Time duration) : parent_comp(AE_Comp(parent_comp)), utf_name(utf_name), width(width), height(height), color(color), duration(duration), Command(CommandID::CreateSolidInComp) {}
	CreateSolidInCompCmd(AE_Comp parent_comp, std::string utf_name, A_long width, A_long height, AEGP_ColorVal color, A_Time duration) : parent_comp(parent_comp), utf_name(utf_name), width(width), height(height), color(color), duration(duration), Command(CommandID::CreateSolidInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& utf_name;
		ar& width;
		ar& height;
		ar& color;
		ar& duration;
	}
};

class CreateCameraInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	std::string utf_name;
	A_FloatPoint center_point;
	CreateCameraInCompCmd() : Command(CommandID::CreateCameraInComp) {}
	CreateCameraInCompCmd(AEGP_CompH parent_comp, std::string utf_name, A_FloatPoint center_point) : parent_comp(AE_Comp(parent_comp)), utf_name(utf_name), center_point(center_point), Command(CommandID::CreateCameraInComp) {}
	CreateCameraInCompCmd(AE_Comp parent_comp, std::string utf_name, A_FloatPoint center_point) : parent_comp(parent_comp), utf_name(utf_name), center_point(center_point), Command(CommandID::CreateCameraInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& utf_name;
		ar& center_point;
	}
};

class CreateLightInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	std::string utf_name;
	A_FloatPoint center_point;
	CreateLightInCompCmd() : Command(CommandID::CreateLightInComp) {}
	CreateLightInCompCmd(AEGP_CompH parent_comp, std::string utf_name, A_FloatPoint center_point) : parent_comp(AE_Comp(parent_comp)), utf_name(utf_name), center_point(center_point), Command(CommandID::CreateLightInComp) {}
	CreateLightInCompCmd(AE_Comp parent_comp, std::string utf_name, A_FloatPoint center_point) : parent_comp(parent_comp), utf_name(utf_name), center_point(center_point), Command(CommandID::CreateLightInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& utf_name;
		ar& center_point;
	}
};

class CreateCompCmd : public Command {
public:
	AE_Item parent_folder; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	std::string utf_name;
	A_long width;
	A_long height;
	A_Ratio pixel_aspect_ratio;
	A_Time duration;
	A_Ratio framerate;
	CreateCompCmd() : Command(CommandID::CreateComp) {}
	CreateCompCmd(AEGP_ItemH parent_folder, std::string utf_name, A_long width, A_long height, A_Ratio pixel_aspect_ratio, A_Time duration, A_Ratio framerate) : parent_folder(AE_Item(parent_folder)), utf_name(utf_name), width(width), height(height), pixel_aspect_ratio(pixel_aspect_ratio), duration(duration), framerate(framerate), Command(CommandID::CreateComp) {}
	CreateCompCmd(AE_Item parent_folder, std::string utf_name, A_long width, A_long height, A_Ratio pixel_aspect_ratio, A_Time duration, A_Ratio framerate) : parent_folder(parent_folder), utf_name(utf_name), width(width), height(height), pixel_aspect_ratio(pixel_aspect_ratio), duration(duration), framerate(framerate), Command(CommandID::CreateComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_folder;
		ar& utf_name;
		ar& width;
		ar& height;
		ar& pixel_aspect_ratio;
		ar& duration;
		ar& framerate;
	}
};

class GetCompDisplayStartTimeCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompDisplayStartTimeCmd() : Command(CommandID::GetCompDisplayStartTime) {}
	GetCompDisplayStartTimeCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompDisplayStartTime) {}
	GetCompDisplayStartTimeCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompDisplayStartTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompDisplayStartTimeCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Time start_time;
	SetCompDisplayStartTimeCmd() : Command(CommandID::SetCompDisplayStartTime) {}
	SetCompDisplayStartTimeCmd(AEGP_CompH comp, A_Time start_time) : comp(AE_Comp(comp)), start_time(start_time), Command(CommandID::SetCompDisplayStartTime) {}
	SetCompDisplayStartTimeCmd(AE_Comp comp, A_Time start_time) : comp(comp), start_time(start_time), Command(CommandID::SetCompDisplayStartTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& start_time;
	}
};

class SetCompDurationCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Time duration;
	SetCompDurationCmd() : Command(CommandID::SetCompDuration) {}
	SetCompDurationCmd(AEGP_CompH comp, A_Time duration) : comp(AE_Comp(comp)), duration(duration), Command(CommandID::SetCompDuration) {}
	SetCompDurationCmd(AE_Comp comp, A_Time duration) : comp(comp), duration(duration), Command(CommandID::SetCompDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& duration;
	}
};

class CreateNullInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	std::string utf_name;
	A_Time duration;
	CreateNullInCompCmd() : Command(CommandID::CreateNullInComp) {}
	CreateNullInCompCmd(AEGP_CompH parent_comp, std::string utf_name, A_Time duration) : parent_comp(AE_Comp(parent_comp)), utf_name(utf_name), duration(duration), Command(CommandID::CreateNullInComp) {}
	CreateNullInCompCmd(AE_Comp parent_comp, std::string utf_name, A_Time duration) : parent_comp(parent_comp), utf_name(utf_name), duration(duration), Command(CommandID::CreateNullInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& utf_name;
		ar& duration;
	}
};

class SetCompPixelAspectRatioCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Ratio par;
	SetCompPixelAspectRatioCmd() : Command(CommandID::SetCompPixelAspectRatio) {}
	SetCompPixelAspectRatioCmd(AEGP_CompH comp, A_Ratio par) : comp(AE_Comp(comp)), par(par), Command(CommandID::SetCompPixelAspectRatio) {}
	SetCompPixelAspectRatioCmd(AE_Comp comp, A_Ratio par) : comp(comp), par(par), Command(CommandID::SetCompPixelAspectRatio) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& par;
	}
};

class CreateTextLayerInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean select_new_layer;
	CreateTextLayerInCompCmd() : Command(CommandID::CreateTextLayerInComp) {}
	CreateTextLayerInCompCmd(AEGP_CompH parent_comp, A_Boolean select_new_layer) : parent_comp(AE_Comp(parent_comp)), select_new_layer(select_new_layer), Command(CommandID::CreateTextLayerInComp) {}
	CreateTextLayerInCompCmd(AE_Comp parent_comp, A_Boolean select_new_layer) : parent_comp(parent_comp), select_new_layer(select_new_layer), Command(CommandID::CreateTextLayerInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& select_new_layer;
	}
};

class CreateBoxTextLayerInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean select_new_layer;
	A_FloatPoint box_dimensions;
	CreateBoxTextLayerInCompCmd() : Command(CommandID::CreateBoxTextLayerInComp) {}
	CreateBoxTextLayerInCompCmd(AEGP_CompH parent_comp, A_Boolean select_new_layer, A_FloatPoint box_dimensions) : parent_comp(AE_Comp(parent_comp)), select_new_layer(select_new_layer), box_dimensions(box_dimensions), Command(CommandID::CreateBoxTextLayerInComp) {}
	CreateBoxTextLayerInCompCmd(AE_Comp parent_comp, A_Boolean select_new_layer, A_FloatPoint box_dimensions) : parent_comp(parent_comp), select_new_layer(select_new_layer), box_dimensions(box_dimensions), Command(CommandID::CreateBoxTextLayerInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
		ar& select_new_layer;
		ar& box_dimensions;
	}
};

class SetCompDimensionsCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_long width;
	A_long height;
	SetCompDimensionsCmd() : Command(CommandID::SetCompDimensions) {}
	SetCompDimensionsCmd(AEGP_CompH comp, A_long width, A_long height) : comp(AE_Comp(comp)), width(width), height(height), Command(CommandID::SetCompDimensions) {}
	SetCompDimensionsCmd(AE_Comp comp, A_long width, A_long height) : comp(comp), width(width), height(height), Command(CommandID::SetCompDimensions) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& width;
		ar& height;
	}
};

class DuplicateCompCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	DuplicateCompCmd() : Command(CommandID::DuplicateComp) {}
	DuplicateCompCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::DuplicateComp) {}
	DuplicateCompCmd(AE_Comp comp) : comp(comp), Command(CommandID::DuplicateComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetCompFrameDurationCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompFrameDurationCmd() : Command(CommandID::GetCompFrameDuration) {}
	GetCompFrameDurationCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompFrameDuration) {}
	GetCompFrameDurationCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompFrameDuration) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class GetMostRecentlyUsedCompCmd : public Command {
public:
	GetMostRecentlyUsedCompCmd() : Command(CommandID::GetMostRecentlyUsedComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
	}
};

class CreateVectorLayerInCompCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	CreateVectorLayerInCompCmd() : Command(CommandID::CreateVectorLayerInComp) {}
	CreateVectorLayerInCompCmd(AEGP_CompH parent_comp) : parent_comp(AE_Comp(parent_comp)), Command(CommandID::CreateVectorLayerInComp) {}
	CreateVectorLayerInCompCmd(AE_Comp parent_comp) : parent_comp(parent_comp), Command(CommandID::CreateVectorLayerInComp) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
	}
};

class GetNewCompMarkerStreamCmd : public Command {
public:
	AE_Comp parent_comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetNewCompMarkerStreamCmd() : Command(CommandID::GetNewCompMarkerStream) {}
	GetNewCompMarkerStreamCmd(AEGP_CompH parent_comp) : parent_comp(AE_Comp(parent_comp)), Command(CommandID::GetNewCompMarkerStream) {}
	GetNewCompMarkerStreamCmd(AE_Comp parent_comp) : parent_comp(parent_comp), Command(CommandID::GetNewCompMarkerStream) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_comp;
	}
};

class GetCompDisplayDropFrameCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	GetCompDisplayDropFrameCmd() : Command(CommandID::GetCompDisplayDropFrame) {}
	GetCompDisplayDropFrameCmd(AEGP_CompH comp) : comp(AE_Comp(comp)), Command(CommandID::GetCompDisplayDropFrame) {}
	GetCompDisplayDropFrameCmd(AE_Comp comp) : comp(comp), Command(CommandID::GetCompDisplayDropFrame) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
	}
};

class SetCompDisplayDropFrameCmd : public Command {
public:
	AE_Comp comp; //AEGP_CompH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean dropFrameB;
	SetCompDisplayDropFrameCmd() : Command(CommandID::SetCompDisplayDropFrame) {}
	SetCompDisplayDropFrameCmd(AEGP_CompH comp, A_Boolean dropFrameB) : comp(AE_Comp(comp)), dropFrameB(dropFrameB), Command(CommandID::SetCompDisplayDropFrame) {}
	SetCompDisplayDropFrameCmd(AE_Comp comp, A_Boolean dropFrameB) : comp(comp), dropFrameB(dropFrameB), Command(CommandID::SetCompDisplayDropFrame) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& comp;
		ar& dropFrameB;
	}
};