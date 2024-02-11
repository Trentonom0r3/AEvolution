#pragma once
#include "CommandFactory.h"
#include "SessionManager.h"

/*AEGP_CompSuite11¶
Function

Purpose

AEGP_GetCompFromItem

Retrieves the handle to the composition, given an item handle. Returns NULL if itemH is not an AEGP_CompH.

AEGP_GetCompFromItem(
  AEGP_ItemH  itemH,
  AEGP_CompH  *compPH);
AEGP_GetItemFromComp

Used to get the item handle, given a composition handle.

AEGP_GetItemFromComp(
  AEGP_CompH  compH,
  AEGP_ItemH  *itemPH);
AEGP_GetCompDownsampleFactor

Returns current downsample factor. Measured in pixels X by Y. Users can choose a custom downsample factor with independent X and Y.

AEGP_GetCompDownsampleFactor(
  AEGP_CompH             compH,
  AEGP_DownsampleFactor  *dsfP);
AEGP_SetCompDownsampleFactor

Sets the composition’s downsample factor.

AEGP_SetCompDownsampleFactor(
  AEGP_CompH             compH,
  AEGP_DownsampleFactor  *dsfP);
AEGP_GetCompBGColor

Returns the composition background color.

AEGP_GetCompBGColor(
  AEGP_CompH     compH,
  AEGP_ColorVal  *bg_colorP);
AEGP_SetCompBGColor

Sets a composition’s background color.

AEGP_SetCompBGColor(
  AEGP_CompH           compH,
  const AEGP_ColorVal  *bg_colorP);
AEGP_GetCompFlags

Returns composition flags, or’d together.

AEGP_GetCompFlags(
  AEGP_CompH      compH,
  AEGP_CompFlags  *AEGP_CompFlags);
AEGP_CompFlag_SHOW_ALL_SHY

AEGP_CompFlag_ENABLE_MOTION_BLUR

AEGP_CompFlag_ENABLE_TIME_FILTER

AEGP_CompFlag_GRID_TO_FRAME

AEGP_CompFlag_GRID_TO_FIELDS

AEGP_CompFlag_USE_LOCAL_DSF

AEGP_CompFlag_DRAFT_3D

AEGP_CompFlag_SHOW_GRAPH

AEGP_GetShowLayerNameOrSourceName

New in CC. Passes back true if the Comp’s timeline shows layer names, false if source names. This will open the comp as a side effect.

AEGP_GetShowLayerNameOrSourceName(
  AEGP_CompH  compH,
  A_Boolean   *layer_names_shownPB);
AEGP_SetShowLayerNameOrSourceName

New in CC. Pass in true to have the Comp’s timeline show layer names, false for source names. This will open the comp as a side effect.

AEGP_SetShowLayerNameOrSourceName(
  AEGP_CompH  compH,
  A_Boolean   *layer_names_shownPB);
AEGP_GetShowBlendModes

New in CC. Passes back true if the Comp’s timeline shows blend modes column, false if hidden. This will open the comp as a side effect.

AEGP_GetShowBlendModes(
  AEGP_CompH  compH,
  A_Boolean   *blend_modes_shownPB);
AEGP_SetShowBlendModes

New in CC. Pass in true to have the Comp’s timeline show the blend modes column, false to hide it. This will open the comp as a side effect.

AEGP_GetCompFlags(
  AEGP_CompH  compH,
  A_Boolean   show_blend_modesB);
AEGP_GetCompFramerate

Returns the composition’s frames per second.

AEGP_GetCompFramerate(
  AEGP_CompH  compH,
  A_FpLong    *fpsPF);
AEGP_SetCompFramerate

Sets the composition’s frames per second.

AEGP_SetCompFramerate(
  AEGP_CompH  compH,
  A_FpLong    *fpsPF);
AEGP_GetCompShutterAnglePhase

The composition shutter angle and phase.

AEGP_GetCompShutterAnglePhase(
  AEGP_CompH  compH,
  A_Ratio     *angle,
  A_Ratio     *phase);
AEGP_GetCompShutterFrameRange

The duration of the shutter frame, in seconds.

AEGP_GetCompShutterFrameRange(
  AEGP_CompH    compH,
  const A_Time  *comp_timeP);
AEGP_GetCompSuggestedMotionBlurSamples

Retrieves the number of motion blur samples After Effects will perform in the given composition.

AEGP_GetCompSuggestedMotionBlurSamples(
  AEGP_CompH  compH,
  A_long      *samplesPL)
AEGP_SetCompSuggestedMotionBlurSamples

Specifies the number of motion blur samples After Effects will perform in the given composition. Undoable.

AEGP_SetCompSuggestedMotionBlurSamples(
  AEGP_CompH  compH,
  A_long      samplesL);
AEGP_GetCompMotionBlurAdaptiveSampleLimit

New in CC. Retrieves the motion blur adaptive sample limit for the given composition. As of CC, a new comp defaults to 128.

AEGP_GetCompMotionBlurAdaptiveSampleLimit(
  AEGP_CompH  compH,
  A_long      *samplesPL)
AEGP_SetCompMotionBlurAdaptiveSampleLimit

New in CC. Specifies the motion blur adaptive sample limit for the given composition. As of CC, both the limit and the suggested values are clamped to [2,256] range and the limit value will not be allowed less than the suggested value.

Undoable.

AEGP_SetCompMotionBlurAdaptiveSampleLimit(
  AEGP_CompH  compH,
  A_long      samplesL);
AEGP_GetCompWorkAreaStart

Get the time where the current work area starts.

AEGP_GetCompWorkAreaStart(
  AEGP_CompH  compH,
  A_Time      *startPT);
AEGP_GetCompWorkAreaDuration

Get the duration of a composition’s current work area, in seconds.

AEGP_GetCompWorkAreaDuration(
  AEGP_CompH  compH,
  A_Time      *durationPT);
AEGP_SetCompWorkAreaStartAndDuration

Set the work area start and duration, in seconds. Undo-able. One call to this function is sufficient to set the layer’s in point and duration; it’s not necessary to call it twice, once for each timespace.

AEGP_SetCompWorkAreaStartAndDuration(
  AEGP_CompH    compH,
  const A_Time  *startPT)
  const A_Time  *durationPT);
AEGP_CreateSolidInComp

Creates a new solid with a specified width, height, color, and duration in the composition. Undo-able.

If you pass NULL for the duration, After Effects uses its preference for the duration of a new still. If you pass NULL, or an invalid time scale, duration is set to the length of the composition.

AEGP_CreateSolidInComp(
  const A_UTF16Char  *utf_nameZ,
  A_Long             widthL,
  A_Long             heightL,
  const PF_Pixel     *color,
  AEGP_CompH         parent_compH,
  const A_Time       *durationPT0,
  AEGP_LayerH        *new_solidPH);
AEGP_CreateCameraInComp

Creates and adds a camera to the specified composition. Once created, you can manipulate the camera’s parameter streams using the AEGP Stream Suite.

To specify a two-node camera, use AEGP_SetLayerFlag from AEGP_LayerSuite9 to set AEGP_LayerFlag_LOOK_AT_POI.

AEGP_CreateCameraInComp(
  const A_UTF16Char  *utf_nameZ,
  A_FloatPoint       center_point,
  AEGP_CompH         parent_compH,
  AEGP_LayerH        *new_cameraPH);
AEGP_CreateLightInComp

Creates and adds a light to the specified composition. Once created, you can manipulate the light’s parameter streams using the AEGP Stream Suite.

AEGP_CreateLightInComp(
  const A_UTF16Char  *utf_nameZ,
  A_FloatPoint       center_point,
  AEGP_CompH         parent_compH,
  AEGP_LayerH        *new_lightPH);
AEGP_CreateComp

Creates a new composition for the project. If you don’t provide a parent folder, the composition will be at the root level of the project. Undo-able.

AEGP_CreateComp(
  AEGP_ItemH         parent_folderHO,
  const A_UTF16Char  *utf_nameZ,
  A_Long             widthL,
  A_Long             heightL,
  const A_Ratio      *pixel_aspect_ratioPRt,
  const A_Time       *durationPT,
  const A_Ratio      *frameratePRt,
  AEGP_CompH         *new_compPH);
AEGP_GetNewCollectionFromCompSelection

Creates a new AEGP_Collection2H from the items selected in the given composition. The plug-in is responsible for disposing of the AEGP_Collection2H.

AEGP_GetNewCollectionFromCompSelection(
  AEGP_PluginID      plugin_id,
  AEGP_CompH         compH,
  AEGP_Collection2H  *collectionPH);
AEGP_SetSelection

Sets the selection within the given composition to the given AEGP_Collection2H. Will return an error if members of the AEGP_Collection2H are not available. Don’t assume that a composition hasn’t changed between operations; always use a fresh AEGP_Collection2H.

AEGP_SetSelection(
  AEGP_CompH         compH,
  AEGP_Collection2H  collectionH);
AEGP_GetCompDisplayStartTime

Gets the displayed start time of a composition.

AEGP_GetCompDisplayStartTime(
  AEGP_CompH    compH,
  const A_Time  *start_timePT);
AEGP_SetCompDisplayStartTime

Not undo-able. Sets the displayed start time of a composition (has no effect on the duration of the composition).

AEGP_SetCompDisplayStartTime(
  AEGP_CompH    compH,
  const A_Time  *start_timePT);
AEGP_SetCompDuration

Undoable. Sets the duration of the given composition.

AEGP_SetCompDuration(
  AEGP_CompH    compH,
  const A_Time  *durationPT);
AEGP_CreateNullInComp

Creates a “null object” in the composition (useful for translating projects from 3D applications into After Effects).

If you pass NULL for the duration, After Effects uses its preference for the duration of a new still. If you pass 0, or an invalid time scale, duration is set to the length of the composition.

AEGP_CreateNullInComp(
  const A_UTF16Char  *utf_nameZ,
  AEGP_CompH         parent_compH,
  const A_Time       *durationPT0,
  AEGP_LayerH        *new_null_solidPH);
AEGP_SetCompPixelAspectRatio

Sets the pixel aspect ratio of a composition.

AEGP_SetCompPixelAspectRatio(
  AEGP_CompH     compH,
  const A_Ratio  *parPRt);
AEGP_CreateTextLayerInComp

Updated in CS6. Creates a text layer in the composition, and returns its AEGP_LayerH.

AEGP_CreateTextLayerInComp(
  AEGP_CompH   parent_compH,
  A_Boolean    select_new_layerB,
  AEGP_LayerH  *new_text_lyrPH);
AEGP_CreateBoxTextLayerInComp

Updated in CS6. Creates a new box text layer, and returns its AEGP_LayerH.

AEGP_CreateBoxTextLayerInComp(
  AEGP_CompH    parent_compH,
  A_Boolean     select_new_layerB,
  A_FloatPoint  box_dimensions,
  AEGP_LayerH   *new_text_layerPH);
AEGP_SetCompDimensions

Sets the dimensions of the composition. Undoable.

AEGP_SetCompDimensions(
  AEGP_CompH  compH,
  A_long      widthL,
  A_long      heightL);
AEGP_DuplicateComp

Duplicates the composition. Undoable.

AEGP_DuplicateComp(
  AEGP_CompH  compH,
  AEGP_CompH  *new_compPH);
AEGP_GetCompFrameDuration

Retrieves the duration of a frame in a composition.

AEGP_GetCompFrameDuration(
  AEGP_CompH  compH,
  A_Time      *timeP);
AEGP_GetMostRecentlyUsedComp

Returns the most-recently-used composition.

AEGP_GetMostRecentlyUsedComp(
  AEGP_CompH  *compPH);
AEGP_CreateVectorLayerInComp

Creates and returns a handle to a new vector layer.

AEGP_CreateVectorLayerInComp(
  AEGP_CompH   parent_compH,
  AEGP_LayerH  *new_vec_layerPH);
AEGP_GetNewCompMarkerStream

Returns an AEGP_StreamRefH to the composition’s marker stream. Must be disposed by caller.

AEGP_GetNewCompMarkerStream(
  AEGP_PluginID    aegp_plugin_id,
  AEGP_CompH       parent_compH,
  AEGP_StreamRefH  *streamPH);
AEGP_GetCompDisplayDropFrame

Passes back a boolean that indicates whether the specified comp uses drop-frame timecode or not.

AEGP_GetCompDisplayDropFrame(
  AEGP_CompH  compH,
  A_Boolean   *dropFramePB);
AEGP_SetCompDisplayDropFrame

Sets the dropness of the timecode in the specified composition.

AEGP_SetCompDisplayDropFrame(
  AEGP_CompH  compH,
  A_Boolean   dropFrameB);
AEGP_ReorderCompSelection

Move the selection to a certain layer index. Use along with AEGP_SetSelection().

AEGP_SetCompDisplayDropFrame(
  AEGP_CompH  compH,
  A_long      index);
  */

