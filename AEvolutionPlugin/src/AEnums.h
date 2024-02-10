#ifndef AENUMS_H
#define AENUMS_H
#include "main.h"


enum class CommandID : uint16_t {
    // Item Suites
    GetFirstProjItem = 0,
    GetNextProjItem,
    GetActiveItem,
    IsItemSelected,
    SelectItem,
    GetItemType,
    GetItemName,
    SetItemName,
    GetItemID,
    SetItemUseProxy,
    GetItemParentFolder,
    SetItemParentFolder,
    CreateNewFolder,
    GetItemDuration,
    GetItemCurrentTime,
    GetItemDimensions,
    GetItemPixelAspectRatio,
    DeleteItem,
    SetItemCurrentTime,
    GetItemComment,
    SetItemComment,
    GetItemLabel,
    SetItemLabel,
    // Utility Suites
    ReportInfoUnicode,
    GetDriverSpecVersion,
    StartQuietErrors,
    EndQuietErrors,
    StartUndoGroup,
    EndUndoGroup,
    GetMainHWND,
    ShowHideAllFloaters,
    PaintPalGetForeColor,
    PaintPalGetBackColor,
    PaintPalSetForeColor,
    PaintPalSetBackColor,
    CharPalGetFillColor,
    CharPalGetStrokeColor,
    CharPalSetFillColor,
    CharPalSetStrokeColor,
    CharPalIsFillColorUIFrontmost,
    GetSuppressInteractiveUI,
    WriteToOSConsole,
    WriteToDebugLog,
    HostIsActivated,
    GetPluginPlatformRef,
    UpdateFontList,
    GetPluginPaths,

    //Collection Suites
    NewCollection,
    DisposeCollection,
    GetCollectionNumItems,
    GetCollectionItemByIndex,
    CollectionPushBack,
    CollectionErase,
};

// Serialization for CommandID
namespace boost {
    namespace serialization {

        template<class Archive>
        void serialize(Archive& ar, CommandID& commandID, const unsigned int version) {
            // Cast enum class to its underlying type for serialization
            typename std::underlying_type<CommandID>::type value = static_cast<typename std::underlying_type<CommandID>::type>(commandID);
            ar& value;
            // Cast back to enum class after deserialization
            commandID = static_cast<CommandID>(value);
        }

    } // namespace serialization
} // namespace boost

#endif // AENUMS_H