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
    GetItemFlags,
    GetItemCommentLength,

    // Project Suites
    GetNumProjects, 
    GetProjectByIndex,
    GetProjectName,
    GetProjectPath,
    GetProjectRootFolder,
    SaveProjectToPath,
    GetProjectTimeDisplay,
    SetProjectTimeDisplay,
    ProjectIsDirty,
    SaveProjectAs,
    NewProject,
    OpenProjectFromPath,
    GetProjectBitDepth,
    SetProjectBitDepth,

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
    GetLastErrorMessage,

    //Collection Suites
    NewCollection,
    DisposeCollection,
    GetCollectionNumItems,
    GetCollectionItemByIndex,
    CollectionPushBack,
    CollectionErase,

    //Comp Suite
    GetCompFromItem,
    GetItemFromComp,
    GetCompDownsampleFactor,
    SetCompDownsampleFactor,
    GetCompBGColor,
    SetCompBGColor,
    GetCompFlags,
    SetCompFlags,
    GetShowLayerNameOrSourceName,
    SetShowLayerNameOrSourceName,
    GetShowBlendModes,
    SetShowBlendModes,
    GetCompFramerate,
    SetCompFramerate,
    GetCompShutterAnglePhase,
    GetCompShutterFrameRange,
    GetCompSuggestedMotionBlurSamples,
    SetCompSuggestedMotionBlurSamples,
    GetCompMotionBlurAdaptiveSampleLimit,
    SetCompMotionBlurAdaptiveSampleLimit,
    GetCompWorkAreaStart,
    GetCompWorkAreaDuration,
    SetCompWorkAreaStartAndDuration,
    CreateSolidInComp,
    CreateCameraInComp,
    CreateLightInComp,
    CreateComp,
    GetNewCollectionFromCompSelection,
    SetSelection,
    GetCompDisplayStartTime,
    SetCompDisplayStartTime,
    SetCompDuration,
    CreateNullInComp,
    SetCompPixelAspectRatio,
    CreateTextLayerInComp,
    CreateBoxTextLayerInComp,
    SetCompDimensions,
    DuplicateComp,
    GetCompFrameDuration,
    GetMostRecentlyUsedComp,
    CreateVectorLayerInComp,
    GetNewCompMarkerStream,
    GetCompDisplayDropFrame,
    SetCompDisplayDropFrame,

    //Footage Suite
    GetMainFootageFromItem,
    GetProxyFootageFromItem,
    GetFootageNumFiles,
    GetFootagePath,
    GetFootageSignature,
    NewFootage,
    AddFootageToProject,
    SetItemProxyFootage,
    ReplaceItemMainFootage,
    DisposeFootage,
    GetFootageLayerKey,
    NewPlaceholderFootageWithPath,
    NewSolidFootage,
    GetSolidFootageColor,
    SetSolidFootageColor,
    SetSolidFootageDimensions,
    GetFootageSoundDataFormat,
    GetFootageSequenceImportOptions,
    GetFootageInterpretation,
    SetFootageInterpretation,
    NewSequence,

    // Layer Suites
    GetCompNumLayers,
    GetCompLayerByIndex,
    GetActiveLayer,
    GetLayerIndex,
    GetLayerSourceItem,
    GetLayerSourceItemID,
    GetLayerParentComp,
    GetLayerName,
    GetLayerQuality,
    SetLayerQuality,
    GetLayerFlags,
    SetLayerFlags,
    SetLayerInPointAndDuration,
    IsLayerVideoReallyOn,
    IsLayerAudioReallyOn,
    GetLayerCurrentTime,
    GetLayerInPoint,
    GetLayerDuration,
    GetLayerOffset,
    SetLayerOffset,
    GetLayerStretch,
    SetLayerStretch,
    GetLayerTransferMode,
    SetLayerTransferMode,
    IsAddLayerValid,
    AddLayer,
    ReorderLayer,
    GetLayerMaskedBounds,
    GetLayerObjectType,
    IsLayer3D,
    IsLayer2D,
    IsVideoActive,
    IsLayerUsedAsTrackMatte,
    DoesLayerHaveTrackMatte,
    ConvertCompToLayerTime,
    ConvertLayerToCompTime,
    GetLayerDancingRandValue,
    GetLayerID,
    GetLayerToWorldXform,
    GetLayerToWorldXformFromView,
    SetLayerName,
    GetLayerParent,
    SetLayerParent,
    DeleteLayer,
    DuplicateLayer,
    GetLayerFromLayerID,
    GetLayerLabel,
    SetLayerLabel,
    GetLayerSamplingQuality,
    SetLayerSamplingQuality,
    GetTrackMatteLayer,
    SetTrackMatte,
    RemoveTrackMatte,




};

// Serialization for CommandID
namespace boost {
    namespace serialization {

        template<class Archive>
        inline void serialize(Archive& ar, CommandID& commandID, const unsigned int version) {
            // Cast enum class to its underlying type for serialization
            typename std::underlying_type<CommandID>::type value = static_cast<typename std::underlying_type<CommandID>::type>(commandID);
            ar& value;
            // Cast back to enum class after deserialization
            commandID = static_cast<CommandID>(value);
        }

    } // namespace serialization
} // namespace boost

#endif // AENUMS_H