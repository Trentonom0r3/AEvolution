#pragma once
#include "../MessageMain.h"
#include "../responses/ItemResponses.h"

class GetFirstProjItemCmd : public Command {
public:
	AE_Project project; //AEGP_ProjectH, in a wrapper. In command, member variables are the args for the command,
	GetFirstProjItemCmd() : Command(CommandID::GetFirstProjItem) {}
	GetFirstProjItemCmd(AEGP_ProjectH project) : project(AE_Project(project)), Command(CommandID::GetFirstProjItem) {}

    void execute() override;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
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

	void execute() override;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
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

	void execute() override;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
	}
};

class IsItemSelectedCmd : public Command {
public:
	AE_Item item; //AEGP_ItemH, in a wrapper. In command, member variables are the args for the command,
	IsItemSelectedCmd() : Command(CommandID::IsItemSelected) {}
	IsItemSelectedCmd(AEGP_ItemH item) : item(AE_Item(item)), Command(CommandID::IsItemSelected) {}

	void execute() override;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
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

	void execute() override;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& item;
		ar& selectB;
		ar& deselect_othersB;
	}
};
/*AEGP_ItemSuite9¶
Function

Purpose

AEGP_GetFirstProjItem

Retrieves the first item in a given project.

AEGP_GetFirstProjItem(
  AEGP_ProjectH  projectH,
  AEGP_ItemH     *itemPH);
AEGP_GetNextProjItem

Retrieves the next project item; *next_itemPH will be NULL after the last item.

AEGP_GetNextProjItem(
  AEGP_ProjectH  projectH,
  AEGP_ItemH     itemH,
  AEGP_ItemH     *next_itemPH);
AEGP_GetActiveItem

If the Project window is active, the active item is the selected item (if only one item is selected). If a Composition, Timeline, or Footage window is active, returns the parent of the layer associated with the front-most tab in the window.

Returns NULL if no item is active.

AEGP_GetActiveItem(
  AEGP_ItemH  *itemPH,
AEGP_IsItemSelected

Returns true if the Project window is active and the item is selected.

AEGP_IsItemSelected(
  AEGP_ItemH  itemH,
  A_Boolean   *selectedPB)
AEGP_SelectItem

Toggles the selection state of the item, and (depending on deselect_othersB) can deselect other items. This call selects items in the Project panel.

To make selections in the Composition panel, use AEGP_SetSelection from AEGP_CompSuite11.

AEGP_SelectItem(
  AEGP_ItemH  itemH,
  A_Boolean   selectB,
  A_Boolean   deselect_othersB);
AEGP_GetItemType

Gets type of an item. Note: solids don’t appear in the project, but can be the source to a layer.

AEGP_GetItemType(
  AEGP_ItemH     itemH,
  AEGP_ItemType  *item_typeP);
Items are one of the following types:

AEGP_ItemType_NONE

AEGP_ItemType_FOLDER

AEGP_ItemType_COMP

AEGP_ItemType_SOLID

AEGP_ItemType_FOOTAGE

AEGP_GetTypeName

Get name of type. (name length up to AEGP_MAX_TYPE_NAME_LEN + 1).

AEGP_GetTypeName(
  AEGP_ItemType  item_type,
  A_char         *nameZ);
AEGP_GetItemName

Get item name. (name length has no limit). unicode_namePH points to A_UTF16Char (contains null terminated UTF16 string).

It must be disposed with AEGP_FreeMemHandle .

AEGP_GetItemName(
  AEGP_PluginID  pluginID,
  AEGP_ItemH     itemH,
  AEGP_MemHandle *unicode_namePH);
AEGP_SetItemName

Specifies the name of the AEGP_ItemH. (name length has no limit). Undoable.

AEGP_SetItemName(
  AEGP_ItemH         itemH,
  const A_UTF16Char  *nameZ);
AEGP_GetItemID

Returns the item’s unique ID, which persists across saves and loads of the project.

AEGP_GetItemID(
  AEGP_ItemH  itemH,
  A_long      *item_idPL);
AEGP_GetItemFlags

Get properties of an item.

AEGP_GetItemFlags(
  AEGP_ItemH      itemH,
  AEGP_ItemFlags  *item_flagsP);
Flag values (may be OR’d together):

AEGP_ItemFlag_MISSING

AEGP_ItemFlag_HAS_PROXY

AEGP_ItemFlag_USING_PROXY

AEGP_ItemFlag_MISSING_PROXY

AEGP_ItemFlag_HAS_VIDEO

AEGP_ItemFlag_HAS_AUDIO

AEGP_ItemFlag_STILL

AEGP_ItemFlag_HAS_ACTIVE_AUDIO

Unlike the HAS_AUDIO flag, this bit flag will set only if the comp has at least one layer where audio is actually on.

AEGP_SetItemUseProxy

Toggle item’s proxy usage. Undoable.

AEGP_SetItemUseProxy(
  AEGP_ItemH  itemH,
  A_Boolean   use_proxyB);
AEGP_GetItemParentFolder

Get folder containing item.

AEGP_GetItemParentFolder(
  AEGP_ItemH  itemH,
  AEGP_ItemH  *parent_itemPH);
AEGP_SetItemParentFolder

Sets an item’s parent folder. Undoable.

AEGP_SetItemParentFolder(
  AEGP_ItemH  itemH,
  AEGP_ItemH  parent_folderH);
AEGP_GetItemDuration

Get duration of item, in seconds.

AEGP_GetItemDuration(
  AEGP_ItemH  itemH,
  A_Time      *durationPT);
AEGP_GetItemCurrentTime

Get current time within item. Not updated while rendering.

AEGP_GetItemCurrentTime(
  AEGP_ItemH  itemH,
  A_long      *curr_timePT);
AEGP_GetItemDimensions

Get width and height of item.

AEGP_GetItemDimensions(
  AEGP_ItemH  itemH,
  A_long      *widthPL)
  A_long      *heightPL);
AEGP_GetItemPixelAspectRatio

Get the width of a pixel, assuming its height is 1.0, as numerator over denominator.

AEGP_GetItemPixelAspectRatio(
  AEGP_ItemH  itemH,
  A_Ratio     *ratioPRt);
AEGP_DeleteItem

Removes item from all compositions. Undo-able. Do not use the AEGP_ItemH after calling this function.

AEGP_DeleteItem(
  AEGP_ItemH  itemH);
AEGP_GetItemSolidColor

Removed in AEGP_ItemSuite4. See AEGP_GetSolidFootageColor from AEGP_FootageSuite5

Given a solid item, return its color.

AEGP_GetItemSolidColor(
  AEGP_ItemH  itemH,
  PF_Pixel    *PF_Pixel);
AEGP_SetSolidColor

Removed in AEGP_ItemSuite4. See AEGP_SetSolidFootageColor from AEGP_FootageSuite5.

Sets the color of an existing solid (error if itemH is not a solid).

AEGP_SetSolidColor(
  AEGP_ItemH     itemH,
  AEGP_ColorVal  color);
AEGP_SetSolidDimensions

Removed in AEGP_ItemSuite4. See AEGP_SetSolidFootageDimensions from AEGP_FootageSuite5.

Sets the dimensions of an existing solid (error if itemH is not a solid).

AEGP_SetSolidDimensions(
  AEGP_ItemH  itemH,
  A_short     widthS,
  A_short     heightS);
AEGP_CreateNewFolder

Creates a new folder in the project. The newly created folder is allocated and owned by After Effects.

Passing NULL for parent_folderH0 creates the folder at the project’s root.

AEGP_CreateNewFolder(
  const A_UTF16Char  *nameZ,
  AEGP_ProjectH      projH),
  AEGP_ItemH         parentH0),
  AEGP_ItemH         *new_folderPH);
AEGP_SetItemCurrentTime

Sets the current time within a given itemH.

AEGP_SetItemCurrentTime(
  AEGP_ItemH    itemH,
  const A_Time  *new_timePT);
AEGP_GetItemCommentLength

Removed in ItemSuite9. Retrieves the length (in characters) of the itemH's comment.

AEGP_GetItemCommentLength(
  AEGP_ItemH  itemH,
  A_u_long    *buf_sizePLu);
AEGP_GetItemComment

Updated to support Unicode in ItemSuite9, available in 14.1. Retrieves the itemH's comment.

AEGP_GetItemComment(
  AEGP_ItemH      itemH,
  AEGP_MemHandle  *unicode_namePH);
AEGP_SetItemComment

Updated to support Unicode in ItemSuite9, available in 14.1. Sets the itemH's comment.

AEGP_SetItemComment(
  AEGP_ItemH         itemH,
  const A_UTF16Char  *commentZ);
AEGP_GetItemLabel

Retrieves an item’s label.

AEGP_GetItemLabel(
  AEGP_ItemH    itemH,
  AEGP_LabelID  *labelP);
AEGP_SetItemLabel

Sets an item’s label.

AEGP_SetItemLabel(
  AEGP_ItemH    itemH,
  AEGP_LabelID  label);
AEGP_GetItemMRUView

Gets an item’s most recently used view. The view can be used with two calls in the AEGP_ColorSettingsSuite, to perform a color transform on a pixel buffer from working to view color space.

AEGP_GetItemMRUView(
  AEGP_ItemH      itemH,
  AEGP_ItemViewP  *mru_viewP);
  */