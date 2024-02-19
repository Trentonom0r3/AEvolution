#pragma once
#include "../MessageMain.h"
#include "../responses/UtilityResponses.h"

class ReportInfoUnicodeCmd : public Command {
public:
    std::string info_string;
    ReportInfoUnicodeCmd() : Command(CommandID::ReportInfoUnicode) {}
    ReportInfoUnicodeCmd(std::string info_string) : info_string(info_string), Command(CommandID::ReportInfoUnicode) {}

    void execute() override;

    template <class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& info_string;
    }
};

class GetDriverSpecVersionCmd : public Command {
public:
	GetDriverSpecVersionCmd() : Command(CommandID::GetDriverSpecVersion) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class StartQuietErrorsCmd : public Command {
public:
	StartQuietErrorsCmd() : Command(CommandID::StartQuietErrors) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class EndQuietErrorsCmd : public Command {
public:
	EndQuietErrorsCmd() : Command(CommandID::EndQuietErrors) {}
	A_Boolean report;
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class StartUndoGroupCmd : public Command {
public:
	std::string undo_name;
	StartUndoGroupCmd() : Command(CommandID::StartUndoGroup) {}
	StartUndoGroupCmd(std::string undo_name) : undo_name(undo_name), Command(CommandID::StartUndoGroup) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& undo_name;
	}
};

class EndUndoGroupCmd : public Command {
public:
	EndUndoGroupCmd() : Command(CommandID::EndUndoGroup) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class ShowHideAllFloatersCmd : public Command {
public:
	bool include_tool_pal;
	ShowHideAllFloatersCmd() : Command(CommandID::ShowHideAllFloaters) {}
	ShowHideAllFloatersCmd(bool include_tool_pal) : include_tool_pal(include_tool_pal), Command(CommandID::ShowHideAllFloaters) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& include_tool_pal;
	}
};

class PaintPalGetForeColorCmd : public Command {
public:
	PaintPalGetForeColorCmd() : Command(CommandID::PaintPalGetForeColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class PaintPalGetBackColorCmd : public Command {
public:
	PaintPalGetBackColorCmd() : Command(CommandID::PaintPalGetBackColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class PaintPalSetForeColorCmd : public Command {
public:
	AEGP_ColorVal fore_color;
	PaintPalSetForeColorCmd() : Command(CommandID::PaintPalSetForeColor) {}
	PaintPalSetForeColorCmd(AEGP_ColorVal fore_color) : fore_color(fore_color), Command(CommandID::PaintPalSetForeColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& fore_color;
	}
};

class PaintPalSetBackColorCmd : public Command {
public:
	AEGP_ColorVal back_color;
	PaintPalSetBackColorCmd() : Command(CommandID::PaintPalSetBackColor) {}
	PaintPalSetBackColorCmd(AEGP_ColorVal back_color) : back_color(back_color), Command(CommandID::PaintPalSetBackColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& back_color;
	}
};

class CharPalGetFillColorCmd : public Command {
public:
	CharPalGetFillColorCmd() : Command(CommandID::CharPalGetFillColor) {}
	void execute() override;
	A_Boolean is_swatch;
	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
		ar& is_swatch;
	}
};

class CharPalGetStrokeColorCmd : public Command {
public:
	CharPalGetStrokeColorCmd() : Command(CommandID::CharPalGetStrokeColor) {}
	void execute() override;
	A_Boolean is_defined;
	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
		ar& is_defined;
	}
};

class CharPalSetFillColorCmd : public Command {
public:
	AEGP_ColorVal fill_color;
	CharPalSetFillColorCmd() : Command(CommandID::CharPalSetFillColor) {}
	CharPalSetFillColorCmd(AEGP_ColorVal fill_color) : fill_color(fill_color), Command(CommandID::CharPalSetFillColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& fill_color;
	}
};

class CharPalSetStrokeColorCmd : public Command {
public:
	AEGP_ColorVal stroke_color;
	CharPalSetStrokeColorCmd() : Command(CommandID::CharPalSetStrokeColor) {}
	CharPalSetStrokeColorCmd(AEGP_ColorVal stroke_color) : stroke_color(stroke_color), Command(CommandID::CharPalSetStrokeColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& stroke_color;
	}
};

class CharPalIsFillColorUIFrontmostCmd : public Command {
public:
	CharPalIsFillColorUIFrontmostCmd() : Command(CommandID::CharPalIsFillColorUIFrontmost) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class GetSuppressInteractiveUICmd : public Command {
public:
	GetSuppressInteractiveUICmd() : Command(CommandID::GetSuppressInteractiveUI) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
	}
};

class WriteToOSConsoleCmd : public Command {
public:
	std::string text;
	WriteToOSConsoleCmd() : Command(CommandID::WriteToOSConsole) {}
	WriteToOSConsoleCmd(std::string text) : text(text), Command(CommandID::WriteToOSConsole) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& text;
	}
};

class WriteToDebugLogCmd : public Command {
public:
	std::string subsystem;
	std::string event_type;
	std::string info;
	WriteToDebugLogCmd() : Command(CommandID::WriteToDebugLog) {}
	WriteToDebugLogCmd(std::string subsystem, std::string event_type, std::string info) : subsystem(subsystem), event_type(event_type), info(info), Command(CommandID::WriteToDebugLog) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& subsystem;
		ar& event_type;
		ar& info;
	}
};

class GetLastErrorMessageCmd : public Command {
public:
	A_long buffer_size;
	GetLastErrorMessageCmd() : Command(CommandID::GetLastErrorMessage) {}
	GetLastErrorMessageCmd(A_long buffer_size) : buffer_size(buffer_size), Command(CommandID::GetLastErrorMessage) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& buffer_size;
	}
};

class UpdateFontListCmd : public Command {
public:
	UpdateFontListCmd() : Command(CommandID::UpdateFontList) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
	}
};

class GetPluginPathsCmd : public Command {
public:
	AEGP_GetPathTypes path_type;
	GetPluginPathsCmd() : Command(CommandID::GetPluginPaths) {}
	GetPluginPathsCmd(AEGP_GetPathTypes path_type) : path_type(path_type), Command(CommandID::GetPluginPaths) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& path_type;
	}
};
