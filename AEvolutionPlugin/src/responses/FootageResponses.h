#pragma once
#include "../MessageMain.h"

class GetMainFootageFromItemResp : public Response {
public:
	AE_Footage footageH; //What will be contained in the response
    GetMainFootageFromItemResp() = default;
    GetMainFootageFromItemResp(AEGP_FootageH footageH, std::string error) : footageH(AE_Footage(footageH)), Response(CommandID::GetMainFootageFromItem, error) {};
    template<class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& footageH;
    }
};

class GetProxyFootageFromItemResp : public Response {
public:
	AE_Footage proxy_ftgH; //What will be contained in the response
	GetProxyFootageFromItemResp() = default;
	GetProxyFootageFromItemResp(AEGP_FootageH proxy_ftgH, std::string error) : proxy_ftgH(AE_Footage(proxy_ftgH)), Response(CommandID::GetProxyFootageFromItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& proxy_ftgH;
	}
};

class GetFootageNumFilesResp : public Response {
public:
	A_long num_filesPL0;
	A_long files_per_frmPL0;
	GetFootageNumFilesResp() = default;
	GetFootageNumFilesResp(A_long num_filesPL0, A_long files_per_frmPL0, std::string error) : num_filesPL0(num_filesPL0), files_per_frmPL0(files_per_frmPL0), Response(CommandID::GetFootageNumFiles, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& num_filesPL0;
	    ar& files_per_frmPL0;
	}
};

class GetFootagePathResp : public Response {
public:
	A_long frame_numL;
	A_long file_indexL;
	std::string unicode_pathPH;
	GetFootagePathResp() = default;
	GetFootagePathResp(A_long frame_numL, A_long file_indexL, std::string unicode_pathPH, std::string error) : frame_numL(frame_numL), file_indexL(file_indexL), unicode_pathPH(unicode_pathPH), Response(CommandID::GetFootagePath, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& frame_numL;
	    ar& file_indexL;
	    ar& unicode_pathPH;
	}
};

class GetFootageSignatureResp : public Response {
public:
	AEGP_FootageSignature sigP;
	GetFootageSignatureResp() = default;
	GetFootageSignatureResp(AEGP_FootageSignature sigP, std::string error) : sigP(sigP), Response(CommandID::GetFootageSignature, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& sigP;
	}
};

class NewFootageResp : public Response {
public:
	AE_Footage footageH;
	NewFootageResp() = default;
	NewFootageResp(AEGP_FootageH footageH, std::string error) : footageH(AE_Footage(footageH)), Response(CommandID::NewFootage, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& footageH;
	}
};

class AddFootageToProjectResp : public Response {
public:
	AE_Item add_itemPH0;
	AddFootageToProjectResp() = default;
	AddFootageToProjectResp(AEGP_ItemH add_itemPH0, std::string error) : add_itemPH0(AE_Item(add_itemPH0)), Response(CommandID::AddFootageToProject, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& add_itemPH0;
	}
};

class SetItemProxyFootageResp : public Response {
public:
	SetItemProxyFootageResp() = default;
	SetItemProxyFootageResp(std::string error) : Response(CommandID::SetItemProxyFootage, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class ReplaceItemMainFootageResp : public Response {
public:
	ReplaceItemMainFootageResp() = default;
	ReplaceItemMainFootageResp(std::string error) : Response(CommandID::ReplaceItemMainFootage, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class DisposeFootageResp : public Response {
public:
	DisposeFootageResp() = default;
	DisposeFootageResp(std::string error) : Response(CommandID::DisposeFootage, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetFootageInterpretationResp : public Response {
public:
	AEGP_FootageInterp interpP;
	GetFootageInterpretationResp() = default;
	GetFootageInterpretationResp(AEGP_FootageInterp interpP, std::string error) : interpP(interpP), Response(CommandID::GetFootageInterpretation, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& interpP;
	}
};

class SetFootageInterpretationResp : public Response {
public:
	SetFootageInterpretationResp() = default;
	SetFootageInterpretationResp(std::string error) : Response(CommandID::SetFootageInterpretation, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetFootageLayerKeyResp : public Response {
public:
	AEGP_FootageLayerKey layerKeyP;
	GetFootageLayerKeyResp() = default;
	GetFootageLayerKeyResp(AEGP_FootageLayerKey layerKeyP, std::string error) : layerKeyP(layerKeyP), Response(CommandID::GetFootageLayerKey, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& layerKeyP;
	}
};

class NewPlaceholderFootageWithPathResp : public Response {
public:
	AE_Footage footagePH;
	NewPlaceholderFootageWithPathResp() = default;
	NewPlaceholderFootageWithPathResp(AEGP_FootageH footagePH, std::string error) : footagePH(AE_Footage(footagePH)), Response(CommandID::NewPlaceholderFootageWithPath, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& footagePH;
	}
};

class NewSolidFootageResp : public Response {
public:
	AE_Footage footagePH;
	NewSolidFootageResp() = default;
	NewSolidFootageResp(AEGP_FootageH footagePH, std::string error) : footagePH(AE_Footage(footagePH)), Response(CommandID::NewSolidFootage, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& footagePH;
	}
};

class GetSolidFootageColorResp : public Response {
public:
	AEGP_ColorVal colorP;
	GetSolidFootageColorResp() = default;
	GetSolidFootageColorResp(AEGP_ColorVal colorP, std::string error) : colorP(colorP), Response(CommandID::GetSolidFootageColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& colorP;
	}
};

class SetSolidFootageColorResp : public Response {
public:
	SetSolidFootageColorResp() = default;
	SetSolidFootageColorResp(std::string error) : Response(CommandID::SetSolidFootageColor, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class SetSolidFootageDimensionsResp : public Response {
public:
	SetSolidFootageDimensionsResp() = default;
	SetSolidFootageDimensionsResp(std::string error) : Response(CommandID::SetSolidFootageDimensions, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetFootageSoundDataFormatResp : public Response {
public:
	AEGP_SoundDataFormat formatP;
	GetFootageSoundDataFormatResp() = default;
	GetFootageSoundDataFormatResp(AEGP_SoundDataFormat formatP, std::string error) : formatP(formatP), Response(CommandID::GetFootageSoundDataFormat, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& formatP;
	}
};

class GetFootageSequenceImportOptionsResp : public Response {
public:
	AEGP_FileSequenceImportOptions optionsP;
	GetFootageSequenceImportOptionsResp() = default;
	GetFootageSequenceImportOptionsResp(AEGP_FileSequenceImportOptions optionsP, std::string error) : optionsP(optionsP), Response(CommandID::GetFootageSequenceImportOptions, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Response>(*this);
	    ar& optionsP;
	}
};

