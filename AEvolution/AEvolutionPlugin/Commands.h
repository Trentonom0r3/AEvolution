#pragma once
#include "PyUtils/MessageManager.h"
class SessionManager; // Forward declaration

class CommandBase {
public:
    CommandBase() = default;
    CommandBase(Command cmd) : cmd(cmd) {};
    virtual void execute() = 0;
    Command cmd;
};

class NewCollectionCommand : public CommandBase {
public:
    NewCollectionCommand() = default;

    NewCollectionCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DisposeCollectionCommand : public CommandBase {
public:
    DisposeCollectionCommand() = default;

    DisposeCollectionCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCollectionNumItemsCommand : public CommandBase {
public:
    GetCollectionNumItemsCommand() = default;

    GetCollectionNumItemsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCollectionItemByIndexCommand : public CommandBase {
public:
    GetCollectionItemByIndexCommand() = default;

    GetCollectionItemByIndexCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CollectionPushBackCommand : public CommandBase {
public:
    CollectionPushBackCommand() = default;

    CollectionPushBackCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CollectionEraseCommand : public CommandBase {
public:
    CollectionEraseCommand() = default;

    CollectionEraseCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class AddcompCommand : public CommandBase {
public:
    AddcompCommand() = default;

    AddcompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getCompFromItemCommand : public CommandBase {
public:
    getCompFromItemCommand() = default;

    getCompFromItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemFromCompCommand : public CommandBase {
public:
    GetItemFromCompCommand() = default;

    GetItemFromCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompDownsampleFactorCommand : public CommandBase {
public:
    GetCompDownsampleFactorCommand() = default;

    GetCompDownsampleFactorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompDownsampleFactorCommand : public CommandBase {
public:
    SetCompDownsampleFactorCommand() = default;

    SetCompDownsampleFactorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompBGColorCommand : public CommandBase {
public:
    GetCompBGColorCommand() = default;

    GetCompBGColorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompBGColorCommand : public CommandBase {
public:
    SetCompBGColorCommand() = default;

    SetCompBGColorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompFlagsCommand : public CommandBase {
public:
    GetCompFlagsCommand() = default;

    GetCompFlagsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetShowLayerNameOrSourceNameCommand : public CommandBase {
public:
    GetShowLayerNameOrSourceNameCommand() = default;

    GetShowLayerNameOrSourceNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetShowLayerNameOrSourceNameCommand : public CommandBase {
public:
    SetShowLayerNameOrSourceNameCommand() = default;

    SetShowLayerNameOrSourceNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetShowBlendModesCommand : public CommandBase {
public:
    GetShowBlendModesCommand() = default;

    GetShowBlendModesCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetShowBlendModesCommand : public CommandBase {
public:
    SetShowBlendModesCommand() = default;

    SetShowBlendModesCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompFramerateCommand : public CommandBase {
public:
    GetCompFramerateCommand() = default;

    GetCompFramerateCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompFramerateCommand : public CommandBase {
public:
    SetCompFramerateCommand() = default;

    SetCompFramerateCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompShutterAnglePhaseCommand : public CommandBase {
public:
    GetCompShutterAnglePhaseCommand() = default;

    GetCompShutterAnglePhaseCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompSuggestedMotionBlurSamplesCommand : public CommandBase {
public:
    SetCompSuggestedMotionBlurSamplesCommand() = default;

    SetCompSuggestedMotionBlurSamplesCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompWorkAreaStartCommand : public CommandBase {
public:
    GetCompWorkAreaStartCommand() = default;

    GetCompWorkAreaStartCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompWorkAreaDurationCommand : public CommandBase {
public:
    GetCompWorkAreaDurationCommand() = default;

    GetCompWorkAreaDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompWorkAreaStartAndDurationCommand : public CommandBase {
public:
    SetCompWorkAreaStartAndDurationCommand() = default;

    SetCompWorkAreaStartAndDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateSolidInCompCommand : public CommandBase {
public:
    CreateSolidInCompCommand() = default;

    CreateSolidInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateCameraInCompCommand : public CommandBase {
public:
    CreateCameraInCompCommand() = default;

    CreateCameraInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateLightInCompCommand : public CommandBase {
public:
    CreateLightInCompCommand() = default;

    CreateLightInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetNewCollectionFromCompSelectionCommand : public CommandBase {
public:
    GetNewCollectionFromCompSelectionCommand() = default;

    GetNewCollectionFromCompSelectionCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetSelectionCommand : public CommandBase {
public:
    SetSelectionCommand() = default;

    SetSelectionCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompDisplayStartTimeCommand : public CommandBase {
public:
    GetCompDisplayStartTimeCommand() = default;

    GetCompDisplayStartTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompDisplayStartTimeCommand : public CommandBase {
public:
    SetCompDisplayStartTimeCommand() = default;

    SetCompDisplayStartTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompDurationCommand : public CommandBase {
public:
    SetCompDurationCommand() = default;

    SetCompDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateNullInCompCommand : public CommandBase {
public:
    CreateNullInCompCommand() = default;

    CreateNullInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompPixelAspectRatioCommand : public CommandBase {
public:
    SetCompPixelAspectRatioCommand() = default;

    SetCompPixelAspectRatioCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateTextLayerInCompCommand : public CommandBase {
public:
    CreateTextLayerInCompCommand() = default;

    CreateTextLayerInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateBoxTextLayerInCompCommand : public CommandBase {
public:
    CreateBoxTextLayerInCompCommand() = default;

    CreateBoxTextLayerInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompDimensionsCommand : public CommandBase {
public:
    SetCompDimensionsCommand() = default;

    SetCompDimensionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DuplicateCompCommand : public CommandBase {
public:
    DuplicateCompCommand() = default;

    DuplicateCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompFrameDurationCommand : public CommandBase {
public:
    GetCompFrameDurationCommand() = default;

    GetCompFrameDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetMostRecentlyUsedCompCommand : public CommandBase {
public:
    GetMostRecentlyUsedCompCommand() = default;

    GetMostRecentlyUsedCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class CreateVectorLayerInCompCommand : public CommandBase {
public:
    CreateVectorLayerInCompCommand() = default;

    CreateVectorLayerInCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetNewCompMarkerStreamCommand : public CommandBase {
public:
    GetNewCompMarkerStreamCommand() = default;

    GetNewCompMarkerStreamCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompDisplayDropFrameCommand : public CommandBase {
public:
    GetCompDisplayDropFrameCommand() = default;

    GetCompDisplayDropFrameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompDisplayDropFrameCommand : public CommandBase {
public:
    SetCompDisplayDropFrameCommand() = default;

    SetCompDisplayDropFrameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ReorderCompSelectionCommand : public CommandBase {
public:
    ReorderCompSelectionCommand() = default;

    ReorderCompSelectionCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerNumEffectsCommand : public CommandBase {
public:
    GetLayerNumEffectsCommand() = default;

    GetLayerNumEffectsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerEffectByIndexCommand : public CommandBase {
public:
    GetLayerEffectByIndexCommand() = default;

    GetLayerEffectByIndexCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetInstalledKeyFromLayerEffectCommand : public CommandBase {
public:
    GetInstalledKeyFromLayerEffectCommand() = default;

    GetInstalledKeyFromLayerEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectParamUnionByIndexCommand : public CommandBase {
public:
    GetEffectParamUnionByIndexCommand() = default;

    GetEffectParamUnionByIndexCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectFlagsCommand : public CommandBase {
public:
    GetEffectFlagsCommand() = default;

    GetEffectFlagsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetEffectFlagsCommand : public CommandBase {
public:
    SetEffectFlagsCommand() = default;

    SetEffectFlagsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ReorderEffectCommand : public CommandBase {
public:
    ReorderEffectCommand() = default;

    ReorderEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class EffectCallGenericCommand : public CommandBase {
public:
    EffectCallGenericCommand() = default;

    EffectCallGenericCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DisposeEffectCommand : public CommandBase {
public:
    DisposeEffectCommand() = default;

    DisposeEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ApplyEffectCommand : public CommandBase {
public:
    ApplyEffectCommand() = default;

    ApplyEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DeleteLayerEffectCommand : public CommandBase {
public:
    DeleteLayerEffectCommand() = default;

    DeleteLayerEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetNumInstalledEffectsCommand : public CommandBase {
public:
    GetNumInstalledEffectsCommand() = default;

    GetNumInstalledEffectsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetNextInstalledEffectCommand : public CommandBase {
public:
    GetNextInstalledEffectCommand() = default;

    GetNextInstalledEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectNameCommand : public CommandBase {
public:
    GetEffectNameCommand() = default;

    GetEffectNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectMatchNameCommand : public CommandBase {
public:
    GetEffectMatchNameCommand() = default;

    GetEffectMatchNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectCategoryCommand : public CommandBase {
public:
    GetEffectCategoryCommand() = default;

    GetEffectCategoryCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DuplicateEffectCommand : public CommandBase {
public:
    DuplicateEffectCommand() = default;

    DuplicateEffectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NumEffectMaskCommand : public CommandBase {
public:
    NumEffectMaskCommand() = default;

    NumEffectMaskCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetEffectMaskIDCommand : public CommandBase {
public:
    GetEffectMaskIDCommand() = default;

    GetEffectMaskIDCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class AddEffectMaskCommand : public CommandBase {
public:
    AddEffectMaskCommand() = default;

    AddEffectMaskCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class RemoveEffectMaskCommand : public CommandBase {
public:
    RemoveEffectMaskCommand() = default;

    RemoveEffectMaskCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetEffectMaskCommand : public CommandBase {
public:
    SetEffectMaskCommand() = default;

    SetEffectMaskCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class createFootageCommand : public CommandBase {
public:
    createFootageCommand() = default;

    createFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class disposeFootageCommand : public CommandBase {
public:
    disposeFootageCommand() = default;

    disposeFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class addFootageToProjectCommand : public CommandBase {
public:
    addFootageToProjectCommand() = default;

    addFootageToProjectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemSolidColorCommand : public CommandBase {
public:
    GetItemSolidColorCommand() = default;

    GetItemSolidColorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetSolidColorCommand : public CommandBase {
public:
    SetSolidColorCommand() = default;

    SetSolidColorCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetSolidDimensionsCommand : public CommandBase {
public:
    SetSolidDimensionsCommand() = default;

    SetSolidDimensionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetMainFootageFromItemCommand : public CommandBase {
public:
    GetMainFootageFromItemCommand() = default;

    GetMainFootageFromItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetProxyFootageFromItemCommand : public CommandBase {
public:
    GetProxyFootageFromItemCommand() = default;

    GetProxyFootageFromItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageNumFilesCommand : public CommandBase {
public:
    GetFootageNumFilesCommand() = default;

    GetFootageNumFilesCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootagePathCommand : public CommandBase {
public:
    GetFootagePathCommand() = default;

    GetFootagePathCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageSignatureCommand : public CommandBase {
public:
    GetFootageSignatureCommand() = default;

    GetFootageSignatureCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemProxyFootageCommand : public CommandBase {
public:
    SetItemProxyFootageCommand() = default;

    SetItemProxyFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ReplaceItemMainFootageCommand : public CommandBase {
public:
    ReplaceItemMainFootageCommand() = default;

    ReplaceItemMainFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetFootageInterpretationCommand : public CommandBase {
public:
    SetFootageInterpretationCommand() = default;

    SetFootageInterpretationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageInterpretationCommand : public CommandBase {
public:
    GetFootageInterpretationCommand() = default;

    GetFootageInterpretationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageLayerKeyCommand : public CommandBase {
public:
    GetFootageLayerKeyCommand() = default;

    GetFootageLayerKeyCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NewPlaceholderFootageCommand : public CommandBase {
public:
    NewPlaceholderFootageCommand() = default;

    NewPlaceholderFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NewPlaceholderFootageWithPathCommand : public CommandBase {
public:
    NewPlaceholderFootageWithPathCommand() = default;

    NewPlaceholderFootageWithPathCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NewSolidFootageCommand : public CommandBase {
public:
    NewSolidFootageCommand() = default;

    NewSolidFootageCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageSoundDataFormatCommand : public CommandBase {
public:
    GetFootageSoundDataFormatCommand() = default;

    GetFootageSoundDataFormatCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFootageSequenceImportOptionsCommand : public CommandBase {
public:
    GetFootageSequenceImportOptionsCommand() = default;

    GetFootageSequenceImportOptionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getActiveItemCommand : public CommandBase {
public:
    getActiveItemCommand() = default;

    getActiveItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getItemTypeCommand : public CommandBase {
public:
    getItemTypeCommand() = default;

    getItemTypeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getUniqueItemIDCommand : public CommandBase {
public:
    getUniqueItemIDCommand() = default;

    getUniqueItemIDCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class createFolderItemCommand : public CommandBase {
public:
    createFolderItemCommand() = default;

    createFolderItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetFirstProjItemCommand : public CommandBase {
public:
    GetFirstProjItemCommand() = default;

    GetFirstProjItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetNextProjItemCommand : public CommandBase {
public:
    GetNextProjItemCommand() = default;

    GetNextProjItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsItemSelectedCommand : public CommandBase {
public:
    IsItemSelectedCommand() = default;

    IsItemSelectedCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SelectItemCommand : public CommandBase {
public:
    SelectItemCommand() = default;

    SelectItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemFlagsCommand : public CommandBase {
public:
    GetItemFlagsCommand() = default;

    GetItemFlagsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetCompItemCurrentTimeCommand : public CommandBase {
public:
    GetCompItemCurrentTimeCommand() = default;

    GetCompItemCurrentTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetCompItemCurrentTimeCommand : public CommandBase {
public:
    SetCompItemCurrentTimeCommand() = default;

    SetCompItemCurrentTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemUseProxyCommand : public CommandBase {
public:
    SetItemUseProxyCommand() = default;

    SetItemUseProxyCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemParentFolderCommand : public CommandBase {
public:
    GetItemParentFolderCommand() = default;

    GetItemParentFolderCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemParentFolderCommand : public CommandBase {
public:
    SetItemParentFolderCommand() = default;

    SetItemParentFolderCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemDurationCommand : public CommandBase {
public:
    GetItemDurationCommand() = default;

    GetItemDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemCurrentTimeCommand : public CommandBase {
public:
    GetItemCurrentTimeCommand() = default;

    GetItemCurrentTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemDimensionsCommand : public CommandBase {
public:
    GetItemDimensionsCommand() = default;

    GetItemDimensionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemPixelAspectRatioCommand : public CommandBase {
public:
    GetItemPixelAspectRatioCommand() = default;

    GetItemPixelAspectRatioCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DeleteItemCommand : public CommandBase {
public:
    DeleteItemCommand() = default;

    DeleteItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemCurrentTimeCommand : public CommandBase {
public:
    SetItemCurrentTimeCommand() = default;

    SetItemCurrentTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemCommentCommand : public CommandBase {
public:
    GetItemCommentCommand() = default;

    GetItemCommentCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemCommentCommand : public CommandBase {
public:
    SetItemCommentCommand() = default;

    SetItemCommentCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemLabelCommand : public CommandBase {
public:
    GetItemLabelCommand() = default;

    GetItemLabelCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetItemLabelCommand : public CommandBase {
public:
    SetItemLabelCommand() = default;

    SetItemLabelCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetItemMRUViewCommand : public CommandBase {
public:
    GetItemMRUViewCommand() = default;

    GetItemMRUViewCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getNumLayersCommand : public CommandBase {
public:
    getNumLayersCommand() = default;

    getNumLayersCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getLayerIndexCommand : public CommandBase {
public:
    getLayerIndexCommand() = default;

    getLayerIndexCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getLayerNameCommand : public CommandBase {
public:
    getLayerNameCommand() = default;

    getLayerNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getLayerSourceNameCommand : public CommandBase {
public:
    getLayerSourceNameCommand() = default;

    getLayerSourceNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class setLayerNameCommand : public CommandBase {
public:
    setLayerNameCommand() = default;

    setLayerNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ActiveLayerCommand : public CommandBase {
public:
    ActiveLayerCommand() = default;

    ActiveLayerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getLayerFromCompCommand : public CommandBase {
public:
    getLayerFromCompCommand() = default;

    getLayerFromCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class changeLayerIndexCommand : public CommandBase {
public:
    changeLayerIndexCommand() = default;

    changeLayerIndexCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class isAddLayerValidCommand : public CommandBase {
public:
    isAddLayerValidCommand() = default;

    isAddLayerValidCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class AddLayerCommand : public CommandBase {
public:
    AddLayerCommand() = default;

    AddLayerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getLayerSourceItemCommand : public CommandBase {
public:
    getLayerSourceItemCommand() = default;

    getLayerSourceItemCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerSourceItemIDCommand : public CommandBase {
public:
    GetLayerSourceItemIDCommand() = default;

    GetLayerSourceItemIDCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerParentCompCommand : public CommandBase {
public:
    GetLayerParentCompCommand() = default;

    GetLayerParentCompCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerQualityCommand : public CommandBase {
public:
    GetLayerQualityCommand() = default;

    GetLayerQualityCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerQualityCommand : public CommandBase {
public:
    SetLayerQualityCommand() = default;

    SetLayerQualityCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerFlagsCommand : public CommandBase {
public:
    GetLayerFlagsCommand() = default;

    GetLayerFlagsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerFlagCommand : public CommandBase {
public:
    SetLayerFlagCommand() = default;

    SetLayerFlagCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsLayerVideoReallyOnCommand : public CommandBase {
public:
    IsLayerVideoReallyOnCommand() = default;

    IsLayerVideoReallyOnCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsLayerAudioReallyOnCommand : public CommandBase {
public:
    IsLayerAudioReallyOnCommand() = default;

    IsLayerAudioReallyOnCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerCurrentTimeCommand : public CommandBase {
public:
    GetLayerCurrentTimeCommand() = default;

    GetLayerCurrentTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerInPointCommand : public CommandBase {
public:
    GetLayerInPointCommand() = default;

    GetLayerInPointCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerDurationCommand : public CommandBase {
public:
    GetLayerDurationCommand() = default;

    GetLayerDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerInPointAndDurationCommand : public CommandBase {
public:
    SetLayerInPointAndDurationCommand() = default;

    SetLayerInPointAndDurationCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerOffsetCommand : public CommandBase {
public:
    GetLayerOffsetCommand() = default;

    GetLayerOffsetCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerOffsetCommand : public CommandBase {
public:
    SetLayerOffsetCommand() = default;

    SetLayerOffsetCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerStretchCommand : public CommandBase {
public:
    GetLayerStretchCommand() = default;

    GetLayerStretchCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerStretchCommand : public CommandBase {
public:
    SetLayerStretchCommand() = default;

    SetLayerStretchCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerTransferModeCommand : public CommandBase {
public:
    GetLayerTransferModeCommand() = default;

    GetLayerTransferModeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerTransferModeCommand : public CommandBase {
public:
    SetLayerTransferModeCommand() = default;

    SetLayerTransferModeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerMaskedBoundsCommand : public CommandBase {
public:
    GetLayerMaskedBoundsCommand() = default;

    GetLayerMaskedBoundsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerObjectTypeCommand : public CommandBase {
public:
    GetLayerObjectTypeCommand() = default;

    GetLayerObjectTypeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsLayer3DCommand : public CommandBase {
public:
    IsLayer3DCommand() = default;

    IsLayer3DCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsLayer2DCommand : public CommandBase {
public:
    IsLayer2DCommand() = default;

    IsLayer2DCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsVideoActiveCommand : public CommandBase {
public:
    IsVideoActiveCommand() = default;

    IsVideoActiveCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsLayerUsedAsTrackMatteCommand : public CommandBase {
public:
    IsLayerUsedAsTrackMatteCommand() = default;

    IsLayerUsedAsTrackMatteCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DoesLayerHaveTrackMatteCommand : public CommandBase {
public:
    DoesLayerHaveTrackMatteCommand() = default;

    DoesLayerHaveTrackMatteCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ConvertCompToLayerTimeCommand : public CommandBase {
public:
    ConvertCompToLayerTimeCommand() = default;

    ConvertCompToLayerTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class ConvertLayerToCompTimeCommand : public CommandBase {
public:
    ConvertLayerToCompTimeCommand() = default;

    ConvertLayerToCompTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerDancingRandValueCommand : public CommandBase {
public:
    GetLayerDancingRandValueCommand() = default;

    GetLayerDancingRandValueCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerIDCommand : public CommandBase {
public:
    GetLayerIDCommand() = default;

    GetLayerIDCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerFromLayerIDCommand : public CommandBase {
public:
    GetLayerFromLayerIDCommand() = default;

    GetLayerFromLayerIDCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerLabelCommand : public CommandBase {
public:
    GetLayerLabelCommand() = default;

    GetLayerLabelCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerLabelCommand : public CommandBase {
public:
    SetLayerLabelCommand() = default;

    SetLayerLabelCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerSamplingQualityCommand : public CommandBase {
public:
    GetLayerSamplingQualityCommand() = default;

    GetLayerSamplingQualityCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerSamplingQualityCommand : public CommandBase {
public:
    SetLayerSamplingQualityCommand() = default;

    SetLayerSamplingQualityCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetTrackMatteLayerCommand : public CommandBase {
public:
    GetTrackMatteLayerCommand() = default;

    GetTrackMatteLayerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetTrackMatteCommand : public CommandBase {
public:
    SetTrackMatteCommand() = default;

    SetTrackMatteCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class RemoveTrackMatteCommand : public CommandBase {
public:
    RemoveTrackMatteCommand() = default;

    RemoveTrackMatteCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DeleteLayerCommand : public CommandBase {
public:
    DeleteLayerCommand() = default;

    DeleteLayerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DuplicateLayerCommand : public CommandBase {
public:
    DuplicateLayerCommand() = default;

    DuplicateLayerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetLayerParentCommand : public CommandBase {
public:
    GetLayerParentCommand() = default;

    GetLayerParentCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetLayerParentCommand : public CommandBase {
public:
    SetLayerParentCommand() = default;

    SetLayerParentCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NewMarkerCommand : public CommandBase {
public:
    NewMarkerCommand() = default;

    NewMarkerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DisposeMarkerCommand : public CommandBase {
public:
    DisposeMarkerCommand() = default;

    DisposeMarkerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class DuplicateMarkerCommand : public CommandBase {
public:
    DuplicateMarkerCommand() = default;

    DuplicateMarkerCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class setPanelTitleCommand : public CommandBase {
public:
    setPanelTitleCommand() = default;

    setPanelTitleCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class togglePanelVisibilityCommand : public CommandBase {
public:
    togglePanelVisibilityCommand() = default;

    togglePanelVisibilityCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class isPanelShownCommand : public CommandBase {
public:
    isPanelShownCommand() = default;

    isPanelShownCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getProjectCommand : public CommandBase {
public:
    getProjectCommand() = default;

    getProjectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class executecmdCommand : public CommandBase {
public:
    executecmdCommand() = default;

    executecmdCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetProjectNameCommand : public CommandBase {
public:
    GetProjectNameCommand() = default;

    GetProjectNameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetProjectPathCommand : public CommandBase {
public:
    GetProjectPathCommand() = default;

    GetProjectPathCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SaveProjectToPathCommand : public CommandBase {
public:
    SaveProjectToPathCommand() = default;

    SaveProjectToPathCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetProjectTimeDisplayCommand : public CommandBase {
public:
    GetProjectTimeDisplayCommand() = default;

    GetProjectTimeDisplayCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetProjectTimeDisplay2Command : public CommandBase {
public:
    SetProjectTimeDisplay2Command() = default;

    SetProjectTimeDisplay2Command(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class IsProjectDirtyCommand : public CommandBase {
public:
    IsProjectDirtyCommand() = default;

    IsProjectDirtyCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SaveProjectAsCommand : public CommandBase {
public:
    SaveProjectAsCommand() = default;

    SaveProjectAsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class NewProjectCommand : public CommandBase {
public:
    NewProjectCommand() = default;

    NewProjectCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class OpenProjectFromPathCommand : public CommandBase {
public:
    OpenProjectFromPathCommand() = default;

    OpenProjectFromPathCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class GetProjectBitDepthCommand : public CommandBase {
public:
    GetProjectBitDepthCommand() = default;

    GetProjectBitDepthCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class SetProjectBitDepthCommand : public CommandBase {
public:
    SetProjectBitDepthCommand() = default;

    SetProjectBitDepthCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getProjectRootFolderCommand : public CommandBase {
public:
    getProjectRootFolderCommand() = default;

    getProjectRootFolderCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getRenderOptionsCommand : public CommandBase {
public:
    getRenderOptionsCommand() = default;

    getRenderOptionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class setTimeCommand : public CommandBase {
public:
    setTimeCommand() = default;

    setTimeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getWorldTypeCommand : public CommandBase {
public:
    getWorldTypeCommand() = default;

    getWorldTypeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class disposeRenderOptionsCommand : public CommandBase {
public:
    disposeRenderOptionsCommand() = default;

    disposeRenderOptionsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class renderAndCheckoutFrameCommand : public CommandBase {
public:
    renderAndCheckoutFrameCommand() = default;

    renderAndCheckoutFrameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getReceiptWorldCommand : public CommandBase {
public:
    getReceiptWorldCommand() = default;

    getReceiptWorldCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class checkinFrameCommand : public CommandBase {
public:
    checkinFrameCommand() = default;

    checkinFrameCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class StartUndoGroupCommand : public CommandBase {
public:
    StartUndoGroupCommand() = default;

    StartUndoGroupCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class EndUndoGroupCommand : public CommandBase {
public:
    EndUndoGroupCommand() = default;

    EndUndoGroupCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getPluginPathsCommand : public CommandBase {
public:
    getPluginPathsCommand() = default;

    getPluginPathsCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};
class getBaseAddr8Command : public CommandBase {
public:
    getBaseAddr8Command() = default;

    getBaseAddr8Command(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};

class getSizeCommand : public CommandBase {
public:
    getSizeCommand() = default;

    getSizeCommand(Command cmd) : CommandBase(cmd) {

    };
    void execute() override;
};

class ReportInfoCommand : public CommandBase {
public:
    ReportInfoCommand() = default;

	ReportInfoCommand(Command cmd) : CommandBase(cmd) {

	};
	void execute() override;
};

class getItemNameCommand : public CommandBase {
public:
	getItemNameCommand() = default;

	getItemNameCommand(Command cmd) : CommandBase(cmd) {

	};
	void execute() override;
};

class CommandFactory {
public:
    CommandFactory() {
        // Register commands
        commands["NewCollection"] = [](const Command& cmd) { return std::make_unique<NewCollectionCommand>(cmd); };
        commands["DisposeCollection"] = [](const Command& cmd) { return std::make_unique<DisposeCollectionCommand>(cmd); };
        commands["GetCollectionNumItems"] = [](const Command& cmd) { return std::make_unique<GetCollectionNumItemsCommand>(cmd); };
        commands["GetCollectionItemByIndex"] = [](const Command& cmd) { return std::make_unique<GetCollectionItemByIndexCommand>(cmd); };
        commands["CollectionPushBack"] = [](const Command& cmd) { return std::make_unique<CollectionPushBackCommand>(cmd); };
        commands["CollectionErase"] = [](const Command& cmd) { return std::make_unique<CollectionEraseCommand>(cmd); };
        commands["Addcomp"] = [](const Command& cmd) { return std::make_unique<AddcompCommand>(cmd); };
        commands["GetCompFromItem"] = [](const Command& cmd) { return std::make_unique<getCompFromItemCommand>(cmd); };
        commands["GetItemFromComp"] = [](const Command& cmd) { return std::make_unique<GetItemFromCompCommand>(cmd); };
        commands["GetCompDownsampleFactor"] = [](const Command& cmd) { return std::make_unique<GetCompDownsampleFactorCommand>(cmd); };
        commands["SetCompDownsampleFactor"] = [](const Command& cmd) { return std::make_unique<SetCompDownsampleFactorCommand>(cmd); };
        commands["GetCompBGColor"] = [](const Command& cmd) { return std::make_unique<GetCompBGColorCommand>(cmd); };
        commands["SetCompBGColor"] = [](const Command& cmd) { return std::make_unique<SetCompBGColorCommand>(cmd); };
        commands["GetCompFlags"] = [](const Command& cmd) { return std::make_unique<GetCompFlagsCommand>(cmd); };
        commands["getItemName"] = [](const Command& cmd) { return std::make_unique<getItemNameCommand>(cmd); };
        commands["GetShowLayerNameOrSourceName"] = [](const Command& cmd) { return std::make_unique<GetShowLayerNameOrSourceNameCommand>(cmd); };
        commands["SetShowLayerNameOrSourceName"] = [](const Command& cmd) { return std::make_unique<SetShowLayerNameOrSourceNameCommand>(cmd); };
        commands["GetShowBlendModes"] = [](const Command& cmd) { return std::make_unique<GetShowBlendModesCommand>(cmd); };
        commands["SetShowBlendModes"] = [](const Command& cmd) { return std::make_unique<SetShowBlendModesCommand>(cmd); };
        commands["GetCompFramerate"] = [](const Command& cmd) { return std::make_unique<GetCompFramerateCommand>(cmd); };
        commands["SetCompFramerate"] = [](const Command& cmd) { return std::make_unique<SetCompFramerateCommand>(cmd); };
        commands["GetCompShutterAnglePhase"] = [](const Command& cmd) { return std::make_unique<GetCompShutterAnglePhaseCommand>(cmd); };
        commands["SetCompSuggestedMotionBlurSamples"] = [](const Command& cmd) { return std::make_unique<SetCompSuggestedMotionBlurSamplesCommand>(cmd); };
        commands["GetCompWorkAreaStart"] = [](const Command& cmd) { return std::make_unique<GetCompWorkAreaStartCommand>(cmd); };
        commands["GetCompWorkAreaDuration"] = [](const Command& cmd) { return std::make_unique<GetCompWorkAreaDurationCommand>(cmd); };
        commands["SetCompWorkAreaStartAndDuration"] = [](const Command& cmd) { return std::make_unique<SetCompWorkAreaStartAndDurationCommand>(cmd); };
        commands["CreateSolidInComp"] = [](const Command& cmd) { return std::make_unique<CreateSolidInCompCommand>(cmd); };
        commands["CreateCameraInComp"] = [](const Command& cmd) { return std::make_unique<CreateCameraInCompCommand>(cmd); };
        commands["CreateLightInComp"] = [](const Command& cmd) { return std::make_unique<CreateLightInCompCommand>(cmd); };
        commands["GetNewCollectionFromCompSelection"] = [](const Command& cmd) { return std::make_unique<GetNewCollectionFromCompSelectionCommand>(cmd); };
        commands["SetSelection"] = [](const Command& cmd) { return std::make_unique<SetSelectionCommand>(cmd); };
        commands["GetCompDisplayStartTime"] = [](const Command& cmd) { return std::make_unique<GetCompDisplayStartTimeCommand>(cmd); };
        commands["SetCompDisplayStartTime"] = [](const Command& cmd) { return std::make_unique<SetCompDisplayStartTimeCommand>(cmd); };
        commands["SetCompDuration"] = [](const Command& cmd) { return std::make_unique<SetCompDurationCommand>(cmd); };
        commands["CreateNullInComp"] = [](const Command& cmd) { return std::make_unique<CreateNullInCompCommand>(cmd); };
        commands["SetCompPixelAspectRatio"] = [](const Command& cmd) { return std::make_unique<SetCompPixelAspectRatioCommand>(cmd); };
        commands["CreateTextLayerInComp"] = [](const Command& cmd) { return std::make_unique<CreateTextLayerInCompCommand>(cmd); };
        commands["CreateBoxTextLayerInComp"] = [](const Command& cmd) { return std::make_unique<CreateBoxTextLayerInCompCommand>(cmd); };
        commands["SetCompDimensions"] = [](const Command& cmd) { return std::make_unique<SetCompDimensionsCommand>(cmd); };
        commands["DuplicateComp"] = [](const Command& cmd) { return std::make_unique<DuplicateCompCommand>(cmd); };
        commands["GetCompFrameDuration"] = [](const Command& cmd) { return std::make_unique<GetCompFrameDurationCommand>(cmd); };
        commands["GetMostRecentlyUsedComp"] = [](const Command& cmd) { return std::make_unique<GetMostRecentlyUsedCompCommand>(cmd); };
        commands["CreateVectorLayerInComp"] = [](const Command& cmd) { return std::make_unique<CreateVectorLayerInCompCommand>(cmd); };
        commands["GetNewCompMarkerStream"] = [](const Command& cmd) { return std::make_unique<GetNewCompMarkerStreamCommand>(cmd); };
        commands["GetCompDisplayDropFrame"] = [](const Command& cmd) { return std::make_unique<GetCompDisplayDropFrameCommand>(cmd); };
        commands["SetCompDisplayDropFrame"] = [](const Command& cmd) { return std::make_unique<SetCompDisplayDropFrameCommand>(cmd); };
        commands["ReorderCompSelection"] = [](const Command& cmd) { return std::make_unique<ReorderCompSelectionCommand>(cmd); };
        commands["GetLayerNumEffects"] = [](const Command& cmd) { return std::make_unique<GetLayerNumEffectsCommand>(cmd); };
        commands["GetLayerEffectByIndex"] = [](const Command& cmd) { return std::make_unique<GetLayerEffectByIndexCommand>(cmd); };
        commands["GetInstalledKeyFromLayerEffect"] = [](const Command& cmd) { return std::make_unique<GetInstalledKeyFromLayerEffectCommand>(cmd); };
        commands["GetEffectParamUnionByIndex"] = [](const Command& cmd) { return std::make_unique<GetEffectParamUnionByIndexCommand>(cmd); };
        commands["GetEffectFlags"] = [](const Command& cmd) { return std::make_unique<GetEffectFlagsCommand>(cmd); };
        commands["SetEffectFlags"] = [](const Command& cmd) { return std::make_unique<SetEffectFlagsCommand>(cmd); };
        commands["ReorderEffect"] = [](const Command& cmd) { return std::make_unique<ReorderEffectCommand>(cmd); };
        commands["EffectCallGeneric"] = [](const Command& cmd) { return std::make_unique<EffectCallGenericCommand>(cmd); };
        commands["DisposeEffect"] = [](const Command& cmd) { return std::make_unique<DisposeEffectCommand>(cmd); };
        commands["ApplyEffect"] = [](const Command& cmd) { return std::make_unique<ApplyEffectCommand>(cmd); };
        commands["DeleteLayerEffect"] = [](const Command& cmd) { return std::make_unique<DeleteLayerEffectCommand>(cmd); };
        commands["GetNumInstalledEffects"] = [](const Command& cmd) { return std::make_unique<GetNumInstalledEffectsCommand>(cmd); };
        commands["GetNextInstalledEffect"] = [](const Command& cmd) { return std::make_unique<GetNextInstalledEffectCommand>(cmd); };
        commands["GetEffectName"] = [](const Command& cmd) { return std::make_unique<GetEffectNameCommand>(cmd); };
        commands["GetEffectMatchName"] = [](const Command& cmd) { return std::make_unique<GetEffectMatchNameCommand>(cmd); };
        commands["GetEffectCategory"] = [](const Command& cmd) { return std::make_unique<GetEffectCategoryCommand>(cmd); };
        commands["DuplicateEffect"] = [](const Command& cmd) { return std::make_unique<DuplicateEffectCommand>(cmd); };
        commands["NumEffectMask"] = [](const Command& cmd) { return std::make_unique<NumEffectMaskCommand>(cmd); };
        commands["GetEffectMaskID"] = [](const Command& cmd) { return std::make_unique<GetEffectMaskIDCommand>(cmd); };
        commands["AddEffectMask"] = [](const Command& cmd) { return std::make_unique<AddEffectMaskCommand>(cmd); };
        commands["RemoveEffectMask"] = [](const Command& cmd) { return std::make_unique<RemoveEffectMaskCommand>(cmd); };
        commands["SetEffectMask"] = [](const Command& cmd) { return std::make_unique<SetEffectMaskCommand>(cmd); };
        commands["createFootage"] = [](const Command& cmd) { return std::make_unique<createFootageCommand>(cmd); };
        commands["disposeFootage"] = [](const Command& cmd) { return std::make_unique<disposeFootageCommand>(cmd); };
        commands["addFootageToProject"] = [](const Command& cmd) { return std::make_unique<addFootageToProjectCommand>(cmd); };
        commands["GetItemSolidColor"] = [](const Command& cmd) { return std::make_unique<GetItemSolidColorCommand>(cmd); };
        commands["SetSolidColor"] = [](const Command& cmd) { return std::make_unique<SetSolidColorCommand>(cmd); };
        commands["SetSolidDimensions"] = [](const Command& cmd) { return std::make_unique<SetSolidDimensionsCommand>(cmd); };
        commands["GetMainFootageFromItem"] = [](const Command& cmd) { return std::make_unique<GetMainFootageFromItemCommand>(cmd); };
        commands["GetProxyFootageFromItem"] = [](const Command& cmd) { return std::make_unique<GetProxyFootageFromItemCommand>(cmd); };
        commands["GetFootageNumFiles"] = [](const Command& cmd) { return std::make_unique<GetFootageNumFilesCommand>(cmd); };
        commands["GetFootagePath"] = [](const Command& cmd) { return std::make_unique<GetFootagePathCommand>(cmd); };
        commands["GetFootageSignature"] = [](const Command& cmd) { return std::make_unique<GetFootageSignatureCommand>(cmd); };
        commands["SetItemProxyFootage"] = [](const Command& cmd) { return std::make_unique<SetItemProxyFootageCommand>(cmd); };
        commands["ReplaceItemMainFootage"] = [](const Command& cmd) { return std::make_unique<ReplaceItemMainFootageCommand>(cmd); };
        commands["SetFootageInterpretation"] = [](const Command& cmd) { return std::make_unique<SetFootageInterpretationCommand>(cmd); };
        commands["GetFootageInterpretation"] = [](const Command& cmd) { return std::make_unique<GetFootageInterpretationCommand>(cmd); };
        commands["GetFootageLayerKey"] = [](const Command& cmd) { return std::make_unique<GetFootageLayerKeyCommand>(cmd); };
        commands["NewPlaceholderFootage"] = [](const Command& cmd) { return std::make_unique<NewPlaceholderFootageCommand>(cmd); };
        commands["NewPlaceholderFootageWithPath"] = [](const Command& cmd) { return std::make_unique<NewPlaceholderFootageWithPathCommand>(cmd); };
        commands["NewSolidFootage"] = [](const Command& cmd) { return std::make_unique<NewSolidFootageCommand>(cmd); };
        commands["GetFootageSoundDataFormat"] = [](const Command& cmd) { return std::make_unique<GetFootageSoundDataFormatCommand>(cmd); };
        commands["GetFootageSequenceImportOptions"] = [](const Command& cmd) { return std::make_unique<GetFootageSequenceImportOptionsCommand>(cmd); };
        commands["getActiveItem"] = [](const Command& cmd) { return std::make_unique<getActiveItemCommand>(cmd); };
        commands["getItemType"] = [](const Command& cmd) { return std::make_unique<getItemTypeCommand>(cmd); };
        commands["getUniqueItemID"] = [](const Command& cmd) { return std::make_unique<getUniqueItemIDCommand>(cmd); };
        commands["createFolderItem"] = [](const Command& cmd) { return std::make_unique<createFolderItemCommand>(cmd); };
        commands["GetFirstProjItem"] = [](const Command& cmd) { return std::make_unique<GetFirstProjItemCommand>(cmd); };
        commands["GetNextProjItem"] = [](const Command& cmd) { return std::make_unique<GetNextProjItemCommand>(cmd); };
        commands["IsItemSelected"] = [](const Command& cmd) { return std::make_unique<IsItemSelectedCommand>(cmd); };
        commands["SelectItem"] = [](const Command& cmd) { return std::make_unique<SelectItemCommand>(cmd); };
        commands["GetItemFlags"] = [](const Command& cmd) { return std::make_unique<GetItemFlagsCommand>(cmd); };
        commands["GetCompItemCurrentTime"] = [](const Command& cmd) { return std::make_unique<GetCompItemCurrentTimeCommand>(cmd); };
        commands["SetCompItemCurrentTime"] = [](const Command& cmd) { return std::make_unique<SetCompItemCurrentTimeCommand>(cmd); };
        commands["SetItemUseProxy"] = [](const Command& cmd) { return std::make_unique<SetItemUseProxyCommand>(cmd); };
        commands["GetItemParentFolder"] = [](const Command& cmd) { return std::make_unique<GetItemParentFolderCommand>(cmd); };
        commands["SetItemParentFolder"] = [](const Command& cmd) { return std::make_unique<SetItemParentFolderCommand>(cmd); };
        commands["GetItemDuration"] = [](const Command& cmd) { return std::make_unique<GetItemDurationCommand>(cmd); };
        commands["GetItemCurrentTime"] = [](const Command& cmd) { return std::make_unique<GetItemCurrentTimeCommand>(cmd); };
        commands["GetItemDimensions"] = [](const Command& cmd) { return std::make_unique<GetItemDimensionsCommand>(cmd); };
        commands["GetItemPixelAspectRatio"] = [](const Command& cmd) { return std::make_unique<GetItemPixelAspectRatioCommand>(cmd); };
        commands["DeleteItem"] = [](const Command& cmd) { return std::make_unique<DeleteItemCommand>(cmd); };
        commands["SetItemCurrentTime"] = [](const Command& cmd) { return std::make_unique<SetItemCurrentTimeCommand>(cmd); };
        commands["GetItemComment"] = [](const Command& cmd) { return std::make_unique<GetItemCommentCommand>(cmd); };
        commands["SetItemComment"] = [](const Command& cmd) { return std::make_unique<SetItemCommentCommand>(cmd); };
        commands["GetItemLabel"] = [](const Command& cmd) { return std::make_unique<GetItemLabelCommand>(cmd); };
        commands["SetItemLabel"] = [](const Command& cmd) { return std::make_unique<SetItemLabelCommand>(cmd); };
        commands["GetItemMRUView"] = [](const Command& cmd) { return std::make_unique<GetItemMRUViewCommand>(cmd); };
        commands["getNumLayers"] = [](const Command& cmd) { return std::make_unique<getNumLayersCommand>(cmd); };
        commands["getLayerIndex"] = [](const Command& cmd) { return std::make_unique<getLayerIndexCommand>(cmd); };
        commands["getLayerName"] = [](const Command& cmd) { return std::make_unique<getLayerNameCommand>(cmd); };
        commands["getLayerSourceName"] = [](const Command& cmd) { return std::make_unique<getLayerSourceNameCommand>(cmd); };
        commands["setLayerName"] = [](const Command& cmd) { return std::make_unique<setLayerNameCommand>(cmd); };
        commands["ActiveLayer"] = [](const Command& cmd) { return std::make_unique<ActiveLayerCommand>(cmd); };
        commands["getLayerFromComp"] = [](const Command& cmd) { return std::make_unique<getLayerFromCompCommand>(cmd); };
        commands["changeLayerIndex"] = [](const Command& cmd) { return std::make_unique<changeLayerIndexCommand>(cmd); };
        commands["isAddLayerValid"] = [](const Command& cmd) { return std::make_unique<isAddLayerValidCommand>(cmd); };
        commands["AddLayer"] = [](const Command& cmd) { return std::make_unique<AddLayerCommand>(cmd); };
        commands["getLayerSourceItem"] = [](const Command& cmd) { return std::make_unique<getLayerSourceItemCommand>(cmd); };
        commands["GetLayerSourceItemID"] = [](const Command& cmd) { return std::make_unique<GetLayerSourceItemIDCommand>(cmd); };
        commands["GetLayerParentComp"] = [](const Command& cmd) { return std::make_unique<GetLayerParentCompCommand>(cmd); };
        commands["GetLayerQuality"] = [](const Command& cmd) { return std::make_unique<GetLayerQualityCommand>(cmd); };
        commands["SetLayerQuality"] = [](const Command& cmd) { return std::make_unique<SetLayerQualityCommand>(cmd); };
        commands["GetLayerFlags"] = [](const Command& cmd) { return std::make_unique<GetLayerFlagsCommand>(cmd); };
        commands["SetLayerFlag"] = [](const Command& cmd) { return std::make_unique<SetLayerFlagCommand>(cmd); };
        commands["IsLayerVideoReallyOn"] = [](const Command& cmd) { return std::make_unique<IsLayerVideoReallyOnCommand>(cmd); };
        commands["IsLayerAudioReallyOn"] = [](const Command& cmd) { return std::make_unique<IsLayerAudioReallyOnCommand>(cmd); };
        commands["GetLayerCurrentTime"] = [](const Command& cmd) { return std::make_unique<GetLayerCurrentTimeCommand>(cmd); };
        commands["GetLayerInPoint"] = [](const Command& cmd) { return std::make_unique<GetLayerInPointCommand>(cmd); };
        commands["GetLayerDuration"] = [](const Command& cmd) { return std::make_unique<GetLayerDurationCommand>(cmd); };
        commands["SetLayerInPointAndDuration"] = [](const Command& cmd) { return std::make_unique<SetLayerInPointAndDurationCommand>(cmd); };
        commands["GetLayerOffset"] = [](const Command& cmd) { return std::make_unique<GetLayerOffsetCommand>(cmd); };
        commands["SetLayerOffset"] = [](const Command& cmd) { return std::make_unique<SetLayerOffsetCommand>(cmd); };
        commands["GetLayerStretch"] = [](const Command& cmd) { return std::make_unique<GetLayerStretchCommand>(cmd); };
        commands["SetLayerStretch"] = [](const Command& cmd) { return std::make_unique<SetLayerStretchCommand>(cmd); };
        commands["GetLayerTransferMode"] = [](const Command& cmd) { return std::make_unique<GetLayerTransferModeCommand>(cmd); };
        commands["SetLayerTransferMode"] = [](const Command& cmd) { return std::make_unique<SetLayerTransferModeCommand>(cmd); };
        commands["GetLayerMaskedBounds"] = [](const Command& cmd) { return std::make_unique<GetLayerMaskedBoundsCommand>(cmd); };
        commands["GetLayerObjectType"] = [](const Command& cmd) { return std::make_unique<GetLayerObjectTypeCommand>(cmd); };
        commands["IsLayer3D"] = [](const Command& cmd) { return std::make_unique<IsLayer3DCommand>(cmd); };
        commands["IsLayer2D"] = [](const Command& cmd) { return std::make_unique<IsLayer2DCommand>(cmd); };
        commands["IsVideoActive"] = [](const Command& cmd) { return std::make_unique<IsVideoActiveCommand>(cmd); };
        commands["IsLayerUsedAsTrackMatte"] = [](const Command& cmd) { return std::make_unique<IsLayerUsedAsTrackMatteCommand>(cmd); };
        commands["DoesLayerHaveTrackMatte"] = [](const Command& cmd) { return std::make_unique<DoesLayerHaveTrackMatteCommand>(cmd); };
        commands["ConvertCompToLayerTime"] = [](const Command& cmd) { return std::make_unique<ConvertCompToLayerTimeCommand>(cmd); };
        commands["ConvertLayerToCompTime"] = [](const Command& cmd) { return std::make_unique<ConvertLayerToCompTimeCommand>(cmd); };
        commands["GetLayerDancingRandValue"] = [](const Command& cmd) { return std::make_unique<GetLayerDancingRandValueCommand>(cmd); };
        commands["GetLayerID"] = [](const Command& cmd) { return std::make_unique<GetLayerIDCommand>(cmd); };
        commands["GetLayerFromLayerID"] = [](const Command& cmd) { return std::make_unique<GetLayerFromLayerIDCommand>(cmd); };
        commands["GetLayerLabel"] = [](const Command& cmd) { return std::make_unique<GetLayerLabelCommand>(cmd); };
        commands["SetLayerLabel"] = [](const Command& cmd) { return std::make_unique<SetLayerLabelCommand>(cmd); };
        commands["GetLayerSamplingQuality"] = [](const Command& cmd) { return std::make_unique<GetLayerSamplingQualityCommand>(cmd); };
        commands["SetLayerSamplingQuality"] = [](const Command& cmd) { return std::make_unique<SetLayerSamplingQualityCommand>(cmd); };
        commands["GetTrackMatteLayer"] = [](const Command& cmd) { return std::make_unique<GetTrackMatteLayerCommand>(cmd); };
        commands["SetTrackMatte"] = [](const Command& cmd) { return std::make_unique<SetTrackMatteCommand>(cmd); };
        commands["RemoveTrackMatte"] = [](const Command& cmd) { return std::make_unique<RemoveTrackMatteCommand>(cmd); };
        commands["DeleteLayer"] = [](const Command& cmd) { return std::make_unique<DeleteLayerCommand>(cmd); };
        commands["DuplicateLayer"] = [](const Command& cmd) { return std::make_unique<DuplicateLayerCommand>(cmd); };
        commands["GetLayerParent"] = [](const Command& cmd) { return std::make_unique<GetLayerParentCommand>(cmd); };
        commands["SetLayerParent"] = [](const Command& cmd) { return std::make_unique<SetLayerParentCommand>(cmd); };
        commands["NewMarker"] = [](const Command& cmd) { return std::make_unique<NewMarkerCommand>(cmd); };
        commands["DisposeMarker"] = [](const Command& cmd) { return std::make_unique<DisposeMarkerCommand>(cmd); };
        commands["DuplicateMarker"] = [](const Command& cmd) { return std::make_unique<DuplicateMarkerCommand>(cmd); };
        commands["setPanelTitle"] = [](const Command& cmd) { return std::make_unique<setPanelTitleCommand>(cmd); };
        commands["togglePanelVisibility"] = [](const Command& cmd) { return std::make_unique<togglePanelVisibilityCommand>(cmd); };
        commands["isPanelShown"] = [](const Command& cmd) { return std::make_unique<isPanelShownCommand>(cmd); };
        commands["getProject"] = [](const Command& cmd) { return std::make_unique<getProjectCommand>(cmd); };
        commands["executeCommand"] = [](const Command& cmd) { return std::make_unique<executecmdCommand>(cmd); };
        commands["GetProjectName"] = [](const Command& cmd) { return std::make_unique<GetProjectNameCommand>(cmd); };
        commands["GetProjectPath"] = [](const Command& cmd) { return std::make_unique<GetProjectPathCommand>(cmd); };
        commands["SaveProjectToPath"] = [](const Command& cmd) { return std::make_unique<SaveProjectToPathCommand>(cmd); };
        commands["GetProjectTimeDisplay"] = [](const Command& cmd) { return std::make_unique<GetProjectTimeDisplayCommand>(cmd); };
        commands["SetProjectTimeDisplay2"] = [](const Command& cmd) { return std::make_unique<SetProjectTimeDisplay2Command>(cmd); };
        commands["IsProjectDirty"] = [](const Command& cmd) { return std::make_unique<IsProjectDirtyCommand>(cmd); };
        commands["SaveProjectAs"] = [](const Command& cmd) { return std::make_unique<SaveProjectAsCommand>(cmd); };
        commands["NewProject"] = [](const Command& cmd) { return std::make_unique<NewProjectCommand>(cmd); };
        commands["OpenProjectFromPath"] = [](const Command& cmd) { return std::make_unique<OpenProjectFromPathCommand>(cmd); };
        commands["GetProjectBitDepth"] = [](const Command& cmd) { return std::make_unique<GetProjectBitDepthCommand>(cmd); };
        commands["SetProjectBitDepth"] = [](const Command& cmd) { return std::make_unique<SetProjectBitDepthCommand>(cmd); };
        commands["getProjectRootFolder"] = [](const Command& cmd) { return std::make_unique<getProjectRootFolderCommand>(cmd); };
        commands["getRenderOptions"] = [](const Command& cmd) { return std::make_unique<getRenderOptionsCommand>(cmd); };
        commands["setTime"] = [](const Command& cmd) { return std::make_unique<setTimeCommand>(cmd); };
        commands["getWorldType"] = [](const Command& cmd) { return std::make_unique<getWorldTypeCommand>(cmd); };
        commands["disposeRenderOptions"] = [](const Command& cmd) { return std::make_unique<disposeRenderOptionsCommand>(cmd); };
        commands["renderAndCheckoutFrame"] = [](const Command& cmd) { return std::make_unique<renderAndCheckoutFrameCommand>(cmd); };
        commands["getReceiptWorld"] = [](const Command& cmd) { return std::make_unique<getReceiptWorldCommand>(cmd); };
        commands["checkinFrame"] = [](const Command& cmd) { return std::make_unique<checkinFrameCommand>(cmd); };
        commands["StartUndoGroup"] = [](const Command& cmd) { return std::make_unique<StartUndoGroupCommand>(cmd); };
        commands["EndUndoGroup"] = [](const Command& cmd) { return std::make_unique<EndUndoGroupCommand>(cmd); };
        commands["getPluginPaths"] = [](const Command& cmd) { return std::make_unique<getPluginPathsCommand>(cmd); };
        commands["getBaseAddr8"] = [](const Command& cmd) { return std::make_unique<getBaseAddr8Command>(cmd); };
        commands["getSize"] = [](const Command& cmd) { return std::make_unique<getSizeCommand>(cmd); };
        commands["ReportInfo"] = [](const Command& cmd) { return std::make_unique<ReportInfoCommand>(cmd); };
        //
    }

    std::unique_ptr<CommandBase> createCommand(const std::string& commandName, const Command& cmd) {
        auto it = commands.find(commandName);
        if (it != commands.end()) {
            return it->second(cmd); // Call the factory function with Command object
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<CommandBase>(const Command&)>> commands;
};