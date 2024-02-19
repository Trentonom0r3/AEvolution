#pragma once
#include "../MessageMain.h"
#include "../responses/ItemResponses.h"

class GetFirstProjItemCmd : public Command {
public:
	AE_Project project; //AEGP_ProjectH, in a wrapper. In command, member variables are the args for the command,
	GetFirstProjItemCmd() : Command(CommandID::GetFirstProjItem) {}
	GetFirstProjItemCmd(AEGP_ProjectH project) : project(AE_Project(project)), Command(CommandID::GetFirstProjItem) {}
	GetFirstProjItemCmd(AE_Project project) : project(project), Command(CommandID::GetFirstProjItem) {}

    void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& project;
	}
};

class GetNextProjItemCmd : public Command {
public:
	AE_Project project; //AEGP_ProjectH, in a wrapper. In command, member variables are the args for the command,
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetNextProjItemCmd() : Command(CommandID::GetNextProjItem) {}
	GetNextProjItemCmd(AEGP_ProjectH project, AEGP_ItemH item) : project(AE_Project(project)), item(AE_Item(item)), Command(CommandID::GetNextProjItem) {}
	GetNextProjItemCmd(AE_Project project, AE_Item item) : project(project), item(item), Command(CommandID::GetNextProjItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& project;
		ar& item;
	}
};

class GetActiveItemCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetActiveItemCmd() : Command(CommandID::GetActiveItem) {}
	GetActiveItemCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetActiveItem) {}
	GetActiveItemCmd(AE_Item item) : item(item), Command(CommandID::GetActiveItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class IsItemSelectedCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	IsItemSelectedCmd() : Command(CommandID::IsItemSelected) {}
	IsItemSelectedCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::IsItemSelected) {}
	IsItemSelectedCmd(AE_Item item) : item(item), Command(CommandID::IsItemSelected) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SelectItemCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean selectB;
	A_Boolean deselect_othersB;
	SelectItemCmd() : Command(CommandID::SelectItem) {}
	SelectItemCmd(AEGP_ItemH item, A_Boolean selectB, A_Boolean deselect_othersB) : item(AE_Item(item)), selectB(selectB), deselect_othersB(deselect_othersB), Command(CommandID::SelectItem) {}
	SelectItemCmd(AE_Item item, A_Boolean selectB, A_Boolean deselect_othersB) : item(item), selectB(selectB), deselect_othersB(deselect_othersB), Command(CommandID::SelectItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& selectB;
		ar& deselect_othersB;
	}
};

class GetItemTypeCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemTypeCmd() : Command(CommandID::GetItemType) {}
	GetItemTypeCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemType) {}
	GetItemTypeCmd(AE_Item item) : item(item), Command(CommandID::GetItemType) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemNameCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemNameCmd() : Command(CommandID::GetItemName) {}
	GetItemNameCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemName) {}
	GetItemNameCmd(AE_Item item) : item(item), Command(CommandID::GetItemName) {}
	
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SetItemNameCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	std::string nameZ;
	SetItemNameCmd() : Command(CommandID::SetItemName) {}
	SetItemNameCmd(AEGP_ItemH item, std::string nameZ) : item(AE_Item(item)), nameZ(nameZ), Command(CommandID::SetItemName) {}
	SetItemNameCmd(AE_Item item, std::string nameZ) : item(item), nameZ(nameZ), Command(CommandID::SetItemName) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& nameZ;
	}
};

class GetItemIDCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemIDCmd() : Command(CommandID::GetItemID) {}
	GetItemIDCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemID) {}
	GetItemIDCmd(AE_Item item) : item(item), Command(CommandID::GetItemID) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemFlagsCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemFlagsCmd() : Command(CommandID::GetItemFlags) {}
	GetItemFlagsCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemFlags) {}
	GetItemFlagsCmd(AE_Item item) : item(item), Command(CommandID::GetItemFlags) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SetItemUseProxyCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	A_Boolean use_proxyB;
	SetItemUseProxyCmd() : Command(CommandID::SetItemUseProxy) {}
	SetItemUseProxyCmd(AEGP_ItemH item, A_Boolean use_proxyB) : item(AE_Item(item)), use_proxyB(use_proxyB), Command(CommandID::SetItemUseProxy) {}
	SetItemUseProxyCmd(AE_Item item, A_Boolean use_proxyB) : item(item), use_proxyB(use_proxyB), Command(CommandID::SetItemUseProxy) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& use_proxyB;
	}
};

class GetItemParentFolderCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemParentFolderCmd() : Command(CommandID::GetItemParentFolder) {}
	GetItemParentFolderCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemParentFolder) {}
	GetItemParentFolderCmd(AE_Item item) : item(item), Command(CommandID::GetItemParentFolder) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SetItemParentFolderCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	AE_Item parent_folder; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	SetItemParentFolderCmd() : Command(CommandID::SetItemParentFolder) {}
	SetItemParentFolderCmd(AEGP_ItemH item, AEGP_ItemH parent_folder) : item(AE_Item(item)), parent_folder(AE_Item(parent_folder)), Command(CommandID::SetItemParentFolder) {}
	SetItemParentFolderCmd(AE_Item item, AE_Item parent_folder) : item(item), parent_folder(parent_folder), Command(CommandID::SetItemParentFolder) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& parent_folder;
	}
};

class GetItemDurationCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemDurationCmd() : Command(CommandID::GetItemDuration) {}
	GetItemDurationCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemDuration) {}
	GetItemDurationCmd(AE_Item item) : item(item), Command(CommandID::GetItemDuration) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemCurrentTimeCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemCurrentTimeCmd() : Command(CommandID::GetItemCurrentTime) {}
	GetItemCurrentTimeCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemCurrentTime) {}
	GetItemCurrentTimeCmd(AE_Item item) : item(item), Command(CommandID::GetItemCurrentTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemDimensionsCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemDimensionsCmd() : Command(CommandID::GetItemDimensions) {}
	GetItemDimensionsCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemDimensions) {}
	GetItemDimensionsCmd(AE_Item item) : item(item), Command(CommandID::GetItemDimensions) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class GetItemPixelAspectRatioCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemPixelAspectRatioCmd() : Command(CommandID::GetItemPixelAspectRatio) {}
	GetItemPixelAspectRatioCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemPixelAspectRatio) {}
	GetItemPixelAspectRatioCmd(AE_Item item) : item(item), Command(CommandID::GetItemPixelAspectRatio) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class DeleteItemCmd : public Command {
public:
AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	DeleteItemCmd() : Command(CommandID::DeleteItem) {}
	DeleteItemCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::DeleteItem) {}
	DeleteItemCmd(AE_Item item) : item(item), Command(CommandID::DeleteItem) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class CreateNewFolderCmd : public Command {
public:
	AE_Item parent_folder; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	std::string nameZ;
	CreateNewFolderCmd() : Command(CommandID::CreateNewFolder) {}
	CreateNewFolderCmd(AEGP_ItemH parent_folder, std::string nameZ) : parent_folder(AE_Item(parent_folder)), nameZ(nameZ), Command(CommandID::CreateNewFolder) {}
	CreateNewFolderCmd(AE_Item parent_folder, std::string nameZ) : parent_folder(parent_folder), nameZ(nameZ), Command(CommandID::CreateNewFolder) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& parent_folder;
		ar& nameZ;
	}
};

class SetItemCurrentTimeCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	A_Time new_timePT;
	SetItemCurrentTimeCmd() : Command(CommandID::SetItemCurrentTime) {}
	SetItemCurrentTimeCmd(AEGP_ItemH item, A_Time new_timePT) : item(AE_Item(item)), new_timePT(new_timePT), Command(CommandID::SetItemCurrentTime) {}
	SetItemCurrentTimeCmd(AE_Item item, A_Time new_timePT) : item(item), new_timePT(new_timePT), Command(CommandID::SetItemCurrentTime) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& new_timePT;
	}
};

class GetItemCommentCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemCommentCmd() : Command(CommandID::GetItemComment) {}
	GetItemCommentCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemComment) {}
	GetItemCommentCmd(AE_Item item) : item(item), Command(CommandID::GetItemComment) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SetItemCommentCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	std::string commentZ;
	SetItemCommentCmd() : Command(CommandID::SetItemComment) {}
	SetItemCommentCmd(AEGP_ItemH item, std::string commentZ) : item(AE_Item(item)), commentZ(commentZ), Command(CommandID::SetItemComment) {}
	SetItemCommentCmd(AE_Item item, std::string commentZ) : item(item), commentZ(commentZ), Command(CommandID::SetItemComment) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& commentZ;
	}
};

class GetItemLabelCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	GetItemLabelCmd() : Command(CommandID::GetItemLabel) {}
	GetItemLabelCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::GetItemLabel) {}
	GetItemLabelCmd(AE_Item item) : item(item), Command(CommandID::GetItemLabel) {}

	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class SetItemLabelCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	AEGP_LabelID label;
	SetItemLabelCmd() : Command(CommandID::SetItemLabel) {}
	SetItemLabelCmd(AEGP_ItemH item, AEGP_LabelID label) : item(AE_Item(item)), label(label), Command(CommandID::SetItemLabel) {}
	SetItemLabelCmd(AE_Item item, AEGP_LabelID label) : item(item), label(label), Command(CommandID::SetItemLabel) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& label;
	}
};
