#pragma once
#include "../MessageMain.h"
/*struct Response {
    CommandID id;
    std::string error;
    // Default constructor
    Response() = default;
    virtual ~Response() = default;
    Response(CommandID id, std::string error) : id(id), error(error) {};
    //serialize method
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
    ar& id;
    }
};      // Response to be sent to the client
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Response)
*/

class FirstProjItem : public Response {
public:
	AE_Item itemH;
	FirstProjItem() = default;
	FirstProjItem(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetFirstProjItem, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class NextProjItem : public Response {
public:
	AE_Item itemH;
	NextProjItem() = default;
	NextProjItem(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetNextProjItem, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class ActiveItem : public Response {
public:
	AE_Item itemH;
	ActiveItem() = default;
	ActiveItem(AEGP_ItemH itemH, std::string error) : itemH(AE_Item(itemH)), Response(CommandID::GetActiveItem, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& itemH;
	}
};

class IsItemSelected : public Response {
public:
	bool selectedPB;
	IsItemSelected() = default;
	IsItemSelected(bool selectedPB, std::string error) : selectedPB(selectedPB), Response(CommandID::IsItemSelected, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& selectedPB;
	}
};

class SelectItem : public Response {
public:
	SelectItem() = default;
	SelectItem(std::string error) : Response(CommandID::SelectItem, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class ItemType : public Response {
public:
	AEGP_ItemType item_type;
	ItemType() = default;
	ItemType(AEGP_ItemType item_type, std::string error) : item_type(item_type), Response(CommandID::GetItemType, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_type;
	}
};


class ItemName : public Response {
public:
	std::string name;
	ItemName() = default;
	ItemName(std::string name, std::string error) : name(name), Response(CommandID::GetItemName, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& name;
	}
};

class ItemID : public Response {
public:
	A_long item_idPL;
	ItemID() = default;
	ItemID(A_long item_idPL, std::string error) : item_idPL(item_idPL), Response(CommandID::GetItemID, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_idPL;
	}
};

class ItemFlags : public Response {
public:
	AEGP_ItemFlags item_flagsP;
	ItemFlags() = default;
	ItemFlags(AEGP_ItemFlags item_flagsP, std::string error) : item_flagsP(item_flagsP), Response(CommandID::GetItemFlags, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& item_flagsP;
	}
};

class ItemUseProxy : public Response {
public:
	ItemUseProxy() = default;
	ItemUseProxy(std::string error) : Response(CommandID::SetItemUseProxy, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class ItemParentFolder : public Response {
public:
	AE_Item parent_itemPH;
	ItemParentFolder() = default;
	ItemParentFolder(AEGP_ItemH parent_itemPH, std::string error) : parent_itemPH(AE_Item(parent_itemPH)), Response(CommandID::GetItemParentFolder, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& parent_itemPH;
	}
};

class ItemDuration : public Response {
public:
	A_Time durationPT;
	ItemDuration() = default;
	ItemDuration(A_Time durationPT, std::string error) : durationPT(durationPT), Response(CommandID::GetItemDuration, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& durationPT;
	}
};

class ItemCurrentTime : public Response {
public:
	A_long curr_timePT;
	ItemCurrentTime() = default;
	ItemCurrentTime(A_long curr_timePT, std::string error) : curr_timePT(curr_timePT), Response(CommandID::GetItemCurrentTime, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& curr_timePT;
	}
};

class ItemDimensions : public Response {
public:
	A_long widthPL;
	A_long heightPL;
	ItemDimensions() = default;
	ItemDimensions(A_long widthPL, A_long heightPL, std::string error) : widthPL(widthPL), heightPL(heightPL), Response(CommandID::GetItemDimensions, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& widthPL;
		ar& heightPL;
	}
};

class ItemPixelAspectRatio : public Response {
public:
	A_Ratio ratioPRt;
	ItemPixelAspectRatio() = default;
	ItemPixelAspectRatio(A_Ratio ratioPRt, std::string error) : ratioPRt(ratioPRt), Response(CommandID::GetItemPixelAspectRatio, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& ratioPRt;
	}
};

class DeleteItem : public Response {
public:
	DeleteItem() = default;
	DeleteItem(std::string error) : Response(CommandID::DeleteItem, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
	}
};

class CreateNewFolder : public Response {
public:
	AE_Item new_folderPH;
	CreateNewFolder() = default;
	CreateNewFolder(AEGP_ItemH new_folderPH, std::string error) : new_folderPH(AE_Item(new_folderPH)), Response(CommandID::CreateNewFolder, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& new_folderPH;
	}
};

class ItemCommentLength : public Response {
public:
	A_u_long buf_sizePLu;
	ItemCommentLength() = default;
	ItemCommentLength(A_u_long buf_sizePLu, std::string error) : buf_sizePLu(buf_sizePLu), Response(CommandID::GetItemCommentLength, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& buf_sizePLu;
	}
};

class ItemComment : public Response {
public:
	std::string unicode_namePH;
	ItemComment() = default;
	ItemComment(std::string unicode_namePH, std::string error) : unicode_namePH(unicode_namePH), Response(CommandID::GetItemComment, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& unicode_namePH;
	}
};

class ItemLabel : public Response {
public:
	AEGP_LabelID labelP;
	ItemLabel() = default;
	ItemLabel(AEGP_LabelID labelP, std::string error) : labelP(labelP), Response(CommandID::GetItemLabel, error) {};
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Response>(*this);
		ar& labelP;
	}
};
