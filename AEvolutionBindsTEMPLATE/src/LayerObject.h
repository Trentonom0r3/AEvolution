#pragma once

#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"
#include <string>

// Forward declarations for referenced classes.
class wItem;
class wComp;
class wFootage;

/**
 * Represents a wrapper around an After Effects layer, providing easy access to layer properties
 * and functionalities.
 */
class wLayer {
public:
    // Constructors and Destructor
    wLayer() = default; // Default constructor
    explicit wLayer(AE_Layer layer) : layer(layer) {} // Initialize with AE_Layer
    ~wLayer() = default; // Default destructor

    // Properties
    AE_Layer layer;

    // Methods for accessing layer properties
    A_long getLayerIndex();
    wItem getLayerSource();
    A_long getSourceID();
    wComp parentComp();
    std::string layerName();
    AEGP_LayerQuality getLayerQuality();
    void setLayerQuality(AEGP_LayerQuality quality);
    AEGP_LayerFlags getLayerFlags(); 
    void setLayerFlags(AEGP_LayerFlags flags);
    bool isLayerVideoOn();
    bool isLayerAudioOn();
    A_Time currentTime();
    A_Time inPoint();
    A_Time duration();
    void setInPointAndDuration(A_Time inPoint, A_Time duration);
    A_Time offset();
    void setOffset(A_Time offset);
    A_Ratio layerStretch();
    void setLayerStretch(A_Ratio stretch);
    AEGP_LayerTransferMode getLayerTransferMode();
    void setLayerTransferMode(AEGP_LayerTransferMode transferMode);
    void reorderLayer(A_long newIndex);
    A_FloatRect getMaskedBounds(AEGP_LTimeMode timeMode, A_Time time);
    AEGP_ObjectType getObjectType();
    bool isLayer3D();
    bool isLayer2D();
    bool isVideoActive(AEGP_LTimeMode timeMode, A_Time time);
    bool isLayerUsedasTrackMatte(bool fill_must_be_active);
    bool doesLayerHaveTrackMatte();
    bool compTimeToLayerTime(A_Time compTime);
    A_long getLayerDancingRand(A_Time time);
    AEGP_LayerIDVal getLayerID();
    A_Matrix4 getLayerToWorldXForm(A_Time compTime);
    A_Matrix4 getLayerToWorldXFormAtTime(A_Time compTime, A_Time layerTime);
    void setLayerName(std::string name);
    wLayer getLayerParent();
    void setLayerParent(wLayer parentLayer);
    wLayer duplicateLayer();
    void deleteLayer();
    AEGP_LabelID getLayerLabel();
    void setLayerLabel(AEGP_LabelID label);
    AEGP_LayerSamplingQuality getLayerSamplingQuality();
    void setLayerSamplingQuality(AEGP_LayerSamplingQuality quality);
    wLayer getTrackMatteLayer();
    void setTrackMatteLayer(wLayer matteLayer, AEGP_TrackMatte trackMatteMode);
    void removeTrackMatte();
};
