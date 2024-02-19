#pragma once
#include "../MessageMain.h"

class GetFirstProjItemResp : public Response {
public:
	AE_Item itemH; //What will be contained in the response
	GetFirstProjItemResp() = default;
	GetFirstProjItemResp(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetFirstProjItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class GetNextProjItemResp : public Response {
public:
	AE_Item itemH;
	GetNextProjItemResp() = default;
	GetNextProjItemResp(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetNextProjItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class GetActiveItemResp : public Response {
public:
	AE_Item itemH;
	GetActiveItemResp() = default;
	GetActiveItemResp(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetActiveItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class IsItemSelectedResp : public Response {
public:
	bool selectedPB;
	IsItemSelectedResp() = default;
	IsItemSelectedResp(bool selectedPB, std::string error) : selectedPB(selectedPB), Response(CommandID::IsItemSelected, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& selectedPB;
	}
};

class SelectItemResp : public Response {
public:
	SelectItemResp() = default;
	SelectItemResp(std::string error) : Response(CommandID::SelectItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemTypeResp : public Response {
public:
	AEGP_ItemType item_type;
	GetItemTypeResp() = default;
	GetItemTypeResp(AEGP_ItemType item_type, std::string error) : item_type(item_type), Response(CommandID::GetItemType, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_type;
	}
};


class GetItemNameResp : public Response {
public:
	std::string name;
	GetItemNameResp() = default;
	GetItemNameResp(std::string name, std::string error) : name(name), Response(CommandID::GetItemName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& name;
	}
};

class SetItemNameResp : public Response {
public:
	SetItemNameResp() = default;
	SetItemNameResp(std::string error) : Response(CommandID::SetItemName, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemIDResp : public Response {
public:
	A_long item_idPL;
	GetItemIDResp() = default;
	GetItemIDResp(A_long item_idPL, std::string error) : item_idPL(item_idPL), Response(CommandID::GetItemID, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_idPL;
	}
};

class GetItemFlagsResp : public Response {
public:
	AEGP_ItemFlags item_flagsP;
	GetItemFlagsResp() = default;
	GetItemFlagsResp(AEGP_ItemFlags item_flagsP, std::string error) : item_flagsP(item_flagsP), Response(CommandID::GetItemFlags, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_flagsP;
	}
};

class SetItemUseProxyResp : public Response {
public:
	SetItemUseProxyResp() = default;
	SetItemUseProxyResp(std::string error) : Response(CommandID::SetItemUseProxy, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemParentFolderResp : public Response {
public:
	AE_Item parent_itemPH;
	GetItemParentFolderResp() = default;
	GetItemParentFolderResp(AEGP_ItemH parent_itemPH, std::string error) : parent_itemPH(AE_Item(parent_itemPH)), Response(CommandID::GetItemParentFolder, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& parent_itemPH;
	}
};

class SetItemParentFolderResp : public Response {
public:
	SetItemParentFolderResp() = default;
	SetItemParentFolderResp(std::string error) : Response(CommandID::SetItemParentFolder, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemDurationResp : public Response {
public:
	A_Time durationPT;
	GetItemDurationResp() = default;
	GetItemDurationResp(A_Time durationPT, std::string error) : durationPT(durationPT), Response(CommandID::GetItemDuration, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& durationPT;
	}
};

class GetItemCurrentTimeResp : public Response {
public:
	A_Time curr_timePT;
	GetItemCurrentTimeResp() = default;
	GetItemCurrentTimeResp(A_Time curr_timePT, std::string error) : curr_timePT(curr_timePT), Response(CommandID::GetItemCurrentTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& curr_timePT;
	}
};

class GetItemDimensionsResp : public Response {
public:
	A_long widthPL;
	A_long heightPL;
	GetItemDimensionsResp() = default;
	GetItemDimensionsResp(A_long widthPL, A_long heightPL, std::string error) : widthPL(widthPL), heightPL(heightPL), Response(CommandID::GetItemDimensions, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& widthPL;
		ar& heightPL;
	}
};

class GetItemPixelAspectRatioResp : public Response {
public:
	A_Ratio ratioPRt;
	GetItemPixelAspectRatioResp() = default;
	GetItemPixelAspectRatioResp(A_Ratio ratioPRt, std::string error) : ratioPRt(ratioPRt), Response(CommandID::GetItemPixelAspectRatio, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& ratioPRt;
	}
};

class DeleteItemResp : public Response {
public:
	DeleteItemResp() = default;
	DeleteItemResp(std::string error) : Response(CommandID::DeleteItem, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CreateNewFolderResp : public Response {
public:
	AE_Item new_folderPH;
	CreateNewFolderResp() = default;
	CreateNewFolderResp(AEGP_ItemH new_folderPH, std::string error) : new_folderPH(AE_Item(new_folderPH)), Response(CommandID::CreateNewFolder, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_folderPH;
	}
};

class SetItemCurrentTimeResp : public Response {
public:
	SetItemCurrentTimeResp() = default;
	SetItemCurrentTimeResp(std::string error) : Response(CommandID::SetItemCurrentTime, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemCommentLengthResp : public Response {
public:
	A_u_long buf_sizePLu;
	GetItemCommentLengthResp() = default;
	GetItemCommentLengthResp(A_u_long buf_sizePLu, std::string error) : buf_sizePLu(buf_sizePLu), Response(CommandID::GetItemCommentLength, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& buf_sizePLu;
	}
};

class GetItemCommentResp : public Response {
public:
	std::string unicode_namePH;
	GetItemCommentResp() = default;
	GetItemCommentResp(std::string unicode_namePH, std::string error) : unicode_namePH(unicode_namePH), Response(CommandID::GetItemComment, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& unicode_namePH;
	}
};

class SetItemCommentResp : public Response {
public:
	SetItemCommentResp() = default;
	SetItemCommentResp(std::string error) : Response(CommandID::SetItemComment, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class GetItemLabelResp : public Response {
public:
	AEGP_LabelID labelP;
	GetItemLabelResp() = default;
	GetItemLabelResp(AEGP_LabelID labelP, std::string error) : labelP(labelP), Response(CommandID::GetItemLabel, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& labelP;
	}
};

class SetItemLabelResp : public Response {
public:
	SetItemLabelResp() = default;
	SetItemLabelResp(std::string error) : Response(CommandID::SetItemLabel, error) {};
	template<class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};
