#pragma once
#include "../MessageMain.h"

class ReportInfoUnicodeResp : public Response {
public:
	ReportInfoUnicodeResp() = default;
	ReportInfoUnicodeResp(std::string error) : Response(CommandID::ReportInfoUnicode, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetDriverSpecVersionResp : public Response {
public:
	A_short major_version;
	A_short minor_version;
	GetDriverSpecVersionResp() = default;
	GetDriverSpecVersionResp(A_short major_version, A_short minor_version, std::string error) : major_version(major_version), minor_version(minor_version), Response(CommandID::GetDriverSpecVersion, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& major_version;
		ar& minor_version;
	}
};

class StartQuietErrorsResp : public Response {
public:
	StartQuietErrorsResp() = default;
	StartQuietErrorsResp(AEGP_ErrReportState state, std::string error) : state(state), Response(CommandID::StartQuietErrors, error) {};
	AEGP_ErrReportState state;
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class EndQuietErrorsResp : public Response {
public:
	EndQuietErrorsResp() = default;
	EndQuietErrorsResp(std::string error) : Response(CommandID::EndQuietErrors, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class StartUndoGroupResp : public Response {
public:
	StartUndoGroupResp() = default;
	StartUndoGroupResp(std::string error) : Response(CommandID::StartUndoGroup, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class EndUndoGroupResp : public Response {
public:
	EndUndoGroupResp() = default;
	EndUndoGroupResp(std::string error) : Response(CommandID::EndUndoGroup, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};


class ShowHideAllFloatersResp : public Response {
public:
	ShowHideAllFloatersResp() = default;
	ShowHideAllFloatersResp(std::string error) : Response(CommandID::ShowHideAllFloaters, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class PaintPalGetForeColorResp : public Response {
public:
	AEGP_ColorVal fore_color;
	PaintPalGetForeColorResp() = default;
	PaintPalGetForeColorResp(std::string error) : Response(CommandID::PaintPalGetForeColor, error) {};
	PaintPalGetForeColorResp(AEGP_ColorVal fore_color, std::string error) : fore_color(fore_color), Response(CommandID::PaintPalGetForeColor, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& fore_color;
	}
};

class PaintPalGetBackColorResp : public Response {
public:
	AEGP_ColorVal back_color;
	PaintPalGetBackColorResp() = default;
	PaintPalGetBackColorResp(std::string error) : Response(CommandID::PaintPalGetBackColor, error) {};
	PaintPalGetBackColorResp(AEGP_ColorVal back_color, std::string error) : back_color(back_color), Response(CommandID::PaintPalGetBackColor, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& back_color;
	}
};

class PaintPalSetForeColorResp : public Response {
public:
	PaintPalSetForeColorResp() = default;
	PaintPalSetForeColorResp(std::string error) : Response(CommandID::PaintPalSetForeColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class PaintPalSetBackColorResp : public Response {
public:
	PaintPalSetBackColorResp() = default;
	PaintPalSetBackColorResp(std::string error) : Response(CommandID::PaintPalSetBackColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CharPalGetFillColorResp : public Response {
public:
	A_Boolean is_fcolor_defined;
	AEGP_ColorVal fill_color;
	CharPalGetFillColorResp() = default;
	CharPalGetFillColorResp(std::string error) : Response(CommandID::CharPalGetFillColor, error) {};
	CharPalGetFillColorResp(A_Boolean is_fcolor_defined, AEGP_ColorVal fill_color, std::string error) : is_fcolor_defined(is_fcolor_defined), fill_color(fill_color), Response(CommandID::CharPalGetFillColor, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_fcolor_defined;
		ar& fill_color;
	}
};

class CharPalGetStrokeColorResp : public Response {
public:
	A_Boolean is_scolor_defined;
	AEGP_ColorVal stroke_color;
	CharPalGetStrokeColorResp() = default;
	CharPalGetStrokeColorResp(std::string error) : Response(CommandID::CharPalGetStrokeColor, error) {};
	CharPalGetStrokeColorResp(A_Boolean is_scolor_defined, AEGP_ColorVal stroke_color, std::string error) : is_scolor_defined(is_scolor_defined), stroke_color(stroke_color), Response(CommandID::CharPalGetStrokeColor, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_scolor_defined;
		ar& stroke_color;
	}
};

class CharPalSetFillColorResp : public Response {
public:
	CharPalSetFillColorResp() = default;
	CharPalSetFillColorResp(std::string error) : Response(CommandID::CharPalSetFillColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CharPalSetStrokeColorResp : public Response {
public:
	CharPalSetStrokeColorResp() = default;
	CharPalSetStrokeColorResp(std::string error) : Response(CommandID::CharPalSetStrokeColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CharPalIsFillColorUIFrontmostResp : public Response {
public:
	A_Boolean is_fcolor_selected;
	CharPalIsFillColorUIFrontmostResp() = default;
	CharPalIsFillColorUIFrontmostResp(std::string error) : Response(CommandID::CharPalIsFillColorUIFrontmost, error) {};
	CharPalIsFillColorUIFrontmostResp(A_Boolean is_fcolor_selected, std::string error) : is_fcolor_selected(is_fcolor_selected), Response(CommandID::CharPalIsFillColorUIFrontmost, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& is_fcolor_selected;
	}
};

class GetSuppressInteractiveUIResp : public Response {
public:
	A_Boolean ui_is_suppressed;
	GetSuppressInteractiveUIResp() = default;
	GetSuppressInteractiveUIResp(std::string error) : Response(CommandID::GetSuppressInteractiveUI, error) {};
	GetSuppressInteractiveUIResp(A_Boolean ui_is_suppressed, std::string error) : ui_is_suppressed(ui_is_suppressed), Response(CommandID::GetSuppressInteractiveUI, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& ui_is_suppressed;
	}
};

class WriteToOSConsoleResp : public Response {
public:
	WriteToOSConsoleResp() = default;
	WriteToOSConsoleResp(std::string error) : Response(CommandID::WriteToOSConsole, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class WriteToDebugLogResp : public Response {
public:
	WriteToDebugLogResp() = default;
	WriteToDebugLogResp(std::string error) : Response(CommandID::WriteToDebugLog, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetLastErrorMessageResp : public Response {
public:
	A_long buffer_size;
	A_char error_string;
	A_Err error_num;
	GetLastErrorMessageResp() = default;
	GetLastErrorMessageResp(std::string error) : Response(CommandID::GetLastErrorMessage, error) {};
	GetLastErrorMessageResp(A_long buffer_size, A_char error_string, A_Err error_num, std::string error) : buffer_size(buffer_size), error_string(error_string), error_num(error_num), Response(CommandID::GetLastErrorMessage, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& buffer_size;
		ar& error_string;
		ar& error_num;
	}
};

class UpdateFontListResp : public Response {
public:
	UpdateFontListResp() = default;
	UpdateFontListResp(std::string error) : Response(CommandID::UpdateFontList, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetPluginPathsResp : public Response {
public:
	std::string path;
	GetPluginPathsResp() = default;
	GetPluginPathsResp(std::string error) : Response(CommandID::GetPluginPaths, error) {};
	GetPluginPathsResp(std::string unicode_path, std::string error) : path(unicode_path), Response(CommandID::GetPluginPaths, error) {};

	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& path;
	}
};

