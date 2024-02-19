#pragma once
#include "../MessageMain.h"
#include "../responses/FootageResponses.h"

class GetMainFootageFromItemCmd : public Command {
public:
	AE_Item item;
	GetMainFootageFromItemCmd() : Command(CommandID::GetMainFootageFromItem) {}
	GetMainFootageFromItemCmd(AE_Item item) : item(item), Command(CommandID::GetMainFootageFromItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetProxyFootageFromItemCmd : public Command {
public:
	AE_Item item;
	GetProxyFootageFromItemCmd() : Command(CommandID::GetProxyFootageFromItem) {}
	GetProxyFootageFromItemCmd(AE_Item item) : item(item), Command(CommandID::GetProxyFootageFromItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetFootageNumFilesCmd : public Command {
public:
	AE_Footage footage;
	GetFootageNumFilesCmd() : Command(CommandID::GetFootageNumFiles) {}
	GetFootageNumFilesCmd(AE_Footage footage) : footage(footage), Command(CommandID::GetFootageNumFiles) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};

class GetFootagePathCmd : public Command {
public:
	AE_Footage footage;
	A_long frame_num;
	A_long file_index;
	GetFootagePathCmd() : Command(CommandID::GetFootagePath) {}
	GetFootagePathCmd(AE_Footage footage, A_long frame_num, A_long file_index) : footage(footage), frame_num(frame_num), file_index(file_index), Command(CommandID::GetFootagePath) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
		ar& frame_num;
		ar& file_index;
	}
};

class GetFootageSignatureCmd : public Command {
public:
	AE_Footage footage;
	GetFootageSignatureCmd() : Command(CommandID::GetFootageSignature) {}
	GetFootageSignatureCmd(AE_Footage footage) : footage(footage), Command(CommandID::GetFootageSignature) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};

class NewSequenceCmd : public Command {
public:
	std::string path;
	AEGP_FootageLayerKey layer_info;
	AEGP_FileSequenceImportOptions sequence_options;
	AEGP_InterpretationStyle interp_style;
	NewSequenceCmd() : Command(CommandID::NewFootage) {}
	NewSequenceCmd(std::string path, AEGP_FootageLayerKey layer_info, AEGP_FileSequenceImportOptions sequence_options, AEGP_InterpretationStyle interp_style) : path(path), layer_info(layer_info), sequence_options(sequence_options), interp_style(interp_style), Command(CommandID::NewSequence) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& path;
		ar& layer_info;
		ar& sequence_options;
		ar& interp_style;
	}
};

class NewFootageCmd : public Command {
public:
	std::string path;
	AEGP_InterpretationStyle interp_style;
	NewFootageCmd() : Command(CommandID::NewFootage) {}
	NewFootageCmd(std::string path) : path(path), Command(CommandID::NewFootage) {}
	NewFootageCmd(std::string path, AEGP_InterpretationStyle interp_style) : path(path), interp_style(interp_style), Command(CommandID::NewFootage) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& path;
		ar& interp_style;
	}
};

class AddFootageToProjectCmd : public Command {
public:
	AE_Footage footage;
	AE_Item folder;
	AddFootageToProjectCmd() : Command(CommandID::AddFootageToProject) {}
	AddFootageToProjectCmd(AE_Footage footage, AE_Item folder) : footage(footage), folder(folder), Command(CommandID::AddFootageToProject) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
		ar& folder;
	}
};

class SetItemProxyFootageCmd : public Command {
public:
	AE_Footage footage;
	AE_Item item;
	SetItemProxyFootageCmd() : Command(CommandID::SetItemProxyFootage) {}
	SetItemProxyFootageCmd(AE_Footage footage, AE_Item item) : footage(footage), item(item), Command(CommandID::SetItemProxyFootage) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
		ar& item;
	}
};

class ReplaceItemMainFootageCmd : public Command {
public:
	AE_Footage footage;
	AE_Item item;
	ReplaceItemMainFootageCmd() : Command(CommandID::ReplaceItemMainFootage) {}
	ReplaceItemMainFootageCmd(AE_Footage footage, AE_Item item) : footage(footage), item(item), Command(CommandID::ReplaceItemMainFootage) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
		ar& item;
	}
};

class DisposeFootageCmd : public Command {
public:
	AE_Footage footage;
	DisposeFootageCmd() : Command(CommandID::DisposeFootage) {}
	DisposeFootageCmd(AE_Footage footage) : footage(footage), Command(CommandID::DisposeFootage) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};

class GetFootageInterpretationCmd : public Command {
public:
	AE_Item item;
	A_Boolean proxy;
	GetFootageInterpretationCmd() : Command(CommandID::GetFootageInterpretation) {}
	GetFootageInterpretationCmd(AE_Item item, A_Boolean proxy) : item(item), proxy(proxy), Command(CommandID::GetFootageInterpretation) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& proxy;
	}
};

class SetFootageInterpretationCmd : public Command {
public:
	AE_Item item;
	A_Boolean proxy;
	AEGP_FootageInterp interp;
	SetFootageInterpretationCmd() : Command(CommandID::SetFootageInterpretation) {}
	SetFootageInterpretationCmd(AE_Item item, A_Boolean proxy, AEGP_FootageInterp interp) : item(item), proxy(proxy), interp(interp), Command(CommandID::SetFootageInterpretation) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& proxy;
		ar& interp;
	}
};

class GetFootageLayerKeyCmd : public Command {
public:
	AE_Footage footage;
	GetFootageLayerKeyCmd() : Command(CommandID::GetFootageLayerKey) {}
	GetFootageLayerKeyCmd(AE_Footage footage) : footage(footage), Command(CommandID::GetFootageLayerKey) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};


class NewPlaceholderFootageWithPathCmd : public Command {
public:
	std::string path;
	AEGP_Platform path_platform;
	AEIO_FileType file_type;
	A_long width;
	A_long height;
	A_Time duration;
	NewPlaceholderFootageWithPathCmd() : Command(CommandID::NewPlaceholderFootageWithPath) {}
	NewPlaceholderFootageWithPathCmd(std::string path, AEGP_Platform path_platform, AEIO_FileType file_type, A_long width, A_long height, A_Time duration) : path(path), path_platform(path_platform), file_type(file_type), width(width), height(height), duration(duration), Command(CommandID::NewPlaceholderFootageWithPath) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& path;
		ar& path_platform;
		ar& file_type;
		ar& width;
		ar& height;
		ar& duration;
	}
};

class NewSolidFootageCmd : public Command {
public:
	std::string name;
	A_long width;
	A_long height;
	AEGP_ColorVal color;
	NewSolidFootageCmd() : Command(CommandID::NewSolidFootage) {}
	NewSolidFootageCmd(std::string name, A_long width, A_long height, AEGP_ColorVal color) : name(name), width(width), height(height), color(color), Command(CommandID::NewSolidFootage) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& name;
		ar& width;
		ar& height;
		ar& color;
	}
};

class GetSolidFootageColorCmd : public Command {
public:
	AE_Item item;
	A_Boolean proxy;
	GetSolidFootageColorCmd() : Command(CommandID::GetSolidFootageColor) {}
	GetSolidFootageColorCmd(AE_Item item, A_Boolean proxy) : item(item), proxy(proxy), Command(CommandID::GetSolidFootageColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& proxy;
	}
};

class SetSolidFootageColorCmd : public Command {
public:
	AE_Item item;
	A_Boolean proxy;
	AEGP_ColorVal color;
	SetSolidFootageColorCmd() : Command(CommandID::SetSolidFootageColor) {}
	SetSolidFootageColorCmd(AE_Item item, A_Boolean proxy, AEGP_ColorVal color) : item(item), proxy(proxy), color(color), Command(CommandID::SetSolidFootageColor) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& proxy;
		ar& color;
	}
};

class SetSolidFootageDimensionsCmd : public Command {
public:
	AE_Item item;
	A_Boolean proxy;
	A_long width;
	A_long height;
	SetSolidFootageDimensionsCmd() : Command(CommandID::SetSolidFootageDimensions) {}
	SetSolidFootageDimensionsCmd(AE_Item item, A_Boolean proxy, A_long width, A_long height) : item(item), proxy(proxy), width(width), height(height), Command(CommandID::SetSolidFootageDimensions) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& proxy;
		ar& width;
		ar& height;
	}
};

class GetFootageSoundDataFormatCmd : public Command {
public:
	AE_Footage footage;
	GetFootageSoundDataFormatCmd() : Command(CommandID::GetFootageSoundDataFormat) {}
	GetFootageSoundDataFormatCmd(AE_Footage footage) : footage(footage), Command(CommandID::GetFootageSoundDataFormat) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};

class GetFootageSequenceImportOptionsCmd : public Command {
public:
	AE_Footage footage;
	GetFootageSequenceImportOptionsCmd() : Command(CommandID::GetFootageSequenceImportOptions) {}
	GetFootageSequenceImportOptionsCmd(AE_Footage footage) : footage(footage), Command(CommandID::GetFootageSequenceImportOptions) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& footage;
	}
};

