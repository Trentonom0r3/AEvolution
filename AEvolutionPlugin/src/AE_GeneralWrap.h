#pragma once
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "AE_GeneralPlug.h"
#include <type_traits>

/**
 * @file AE_GeneralWrap.h
 * @brief This Header file defines custom serialization logic for (almost) everything in AE_GeneralPlug.h.
 *
 * Detailed description of the file, including its purpose and how it fits into the larger project.
 * This can also include details about the classes, functions, and any specific algorithms implemented within.
 *
 * This file is part of the AEvolution project, to enhance and modernize AE's scripting abilities.
 * To do so, we have to define custom serialization logic for everything in the AE SDK. This being said, anything that is an 'opaque' handle
 * provide by AE (like AEGP_ItemH, AEGP_LayerH, AEGP_CompH, etc.) will be serialized as a uintptr_t, and deserialized into its proper type.
 * @NOTE This does not mean the object will be valid or useful outside of the AE context. It is there simply for ease of code maintenance.
 *
 * @author Trenton Flanagan @spigon/@trentonom0r3
 * @date 02/13/2024
 * @version 1.1.0
 * @section LICENSE
 * AEvolution is licensed under the AGPL 3.0 License.
 *
 * @section USAGE
 * There is no usage! This file is simply a helper for serialization.
 * That being said, do not alter anything in here!
 *
 *
 * @see `commands.h` for more on how things are used.
 */


 // Template wrapper struct for any AE handle type
template<typename HandleType>
struct AEHandleWrapper {
    HandleType handle; // Generic handle, can represent any AE handle type

    AEHandleWrapper() : handle(NULL) {} // Default constructor
    explicit AEHandleWrapper(HandleType h) : handle(h) {} // Constructor for initialization with a handle

    template<class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
        bool isNull = (handle == NULL);
        uintptr_t handleValue = 0;

        if (Archive::is_saving::value) {
            if (!isNull) {
                handleValue = reinterpret_cast<uintptr_t>(handle);
            }
            ar& BOOST_SERIALIZATION_NVP(isNull);
            ar& BOOST_SERIALIZATION_NVP(handleValue);
        }
        else {
            ar& BOOST_SERIALIZATION_NVP(isNull);
            ar& BOOST_SERIALIZATION_NVP(handleValue);
            if (!isNull) {
                handle = reinterpret_cast<HandleType>(handleValue);
            }
            else {
                handle = NULL; // Explicitly set to nullptr to avoid undefined behavior
            }
        }
    }
};

// 
using AE_Project = AEHandleWrapper<AEGP_ProjectH>; // Wrapper for AEGP_ProjectH
using AE_Item = AEHandleWrapper<AEGP_ItemH>; // Wrapper for AEGP_ItemH
using AE_Comp = AEHandleWrapper<AEGP_CompH>; // Wrapper for AEGP_CompH
using AE_Footage = AEHandleWrapper<AEGP_FootageH>; // Wrapper for AEGP_FootageH
using AE_Layer = AEHandleWrapper<AEGP_LayerH>; // Wrapper for AEGP_LayerH
using AE_EffectRef = AEHandleWrapper<AEGP_EffectRefH>; // Wrapper for AEGP_EffectRefH
using AE_MaskRef = AEHandleWrapper<AEGP_MaskRefH>; // Wrapper for AEGP_MaskRefH
using AE_StreamRef = AEHandleWrapper<AEGP_StreamRefH>; // Wrapper for AEGP_StreamRefH
/*
using AE_RenderLayerContext = AEHandleWrapper<AEGP_RenderLayerContextH>; // Wrapper for AEGP_RenderLayerContextH
using AE_PersistentBlob = AEHandleWrapper<AEGP_PersistentBlobH>; // Wrapper for AEGP_PersistentBlobH
using AE_MaskOutlineVal = AEHandleWrapper<AEGP_MaskOutlineValH>; // Wrapper for AEGP_MaskOutlineValH
using AE_SoundData = AEHandleWrapper<AEGP_SoundDataH>; // Wrapper for AEGP_SoundDataH
using AE_AddKeyframesInfo = AEHandleWrapper<AEGP_AddKeyframesInfoH>; // Wrapper for AEGP_AddKeyframesInfoH
using AE_RenderReceipt = AEHandleWrapper<AEGP_RenderReceiptH>; // Wrapper for AEGP_RenderReceiptH
using AE_World = AEHandleWrapper<AEGP_WorldH>; // Wrapper for AEGP_WorldH
using AE_RenderOptions = AEHandleWrapper<AEGP_RenderOptionsH>; // Wrapper for AEGP_RenderOptionsH
using AE_LayerRenderOptions = AEHandleWrapper<AEGP_LayerRenderOptionsH>; // Wrapper for AEGP_LayerRenderOptionsH
using AE_FrameReceipt = AEHandleWrapper<AEGP_FrameReceiptH>; // Wrapper for AEGP_FrameReceiptH
using AE_RQItemRef = AEHandleWrapper<AEGP_RQItemRefH>; // Wrapper for AEGP_RQItemRefH
using AE_OutputModuleRef = AEHandleWrapper<AEGP_OutputModuleRefH>; // Wrapper for AEGP_OutputModuleRefH
using AE_TextDocument = AEHandleWrapper<AEGP_TextDocumentH>; // Wrapper for AEGP_TextDocumentH
using AE_TextOutlines = AEHandleWrapper<AEGP_TextOutlinesH>; // Wrapper for AEGP_TextOutlinesH
using AE_PlatformWorld = AEHandleWrapper<AEGP_PlatformWorldH>; // Wrapper for AEGP_PlatformWorldH
using AE_ItemView = AEHandleWrapper<AEGP_ItemViewP>; // Wrapper for AEGP_ItemViewP
using AE_ColorProfile = AEHandleWrapper<AEGP_ColorProfileP>; // Wrapper for AEGP_ColorProfileP
using AE_ConstColorProfile = AEHandleWrapper<AEGP_ConstColorProfileP>; // Wrapper for AEGP_ConstColorProfileP
using AE_MarkerVal = AEHandleWrapper<AEGP_MarkerValP>; // Wrapper for AEGP_MarkerValP
using AE_ConstMarkerVal = AEHandleWrapper<AEGP_ConstMarkerValP>; // Wrapper for AEGP_ConstMarkerValP
*/

extern template struct AEHandleWrapper<AEGP_ItemH>;
extern template struct AEHandleWrapper<AEGP_LayerH>;
extern template struct AEHandleWrapper<AEGP_ProjectH>;
extern template struct AEHandleWrapper<AEGP_CompH>;
extern template struct AEHandleWrapper<AEGP_FootageH>;
extern template struct AEHandleWrapper<AEGP_EffectRefH>;
extern template struct AEHandleWrapper<AEGP_MaskRefH>;
extern template struct AEHandleWrapper<AEGP_StreamRefH>;


namespace boost {
    namespace serialization {
        // Serialization function for A_Time
        template<class Archive>
        inline void serialize(Archive& ar, A_Time& time, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(time.value);
            ar& BOOST_SERIALIZATION_NVP(time.scale);
        }

        // Serialization function for A_Ratio
        template<class Archive>
        inline void serialize(Archive& ar, A_Ratio& ratio, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(ratio.num);
            ar& BOOST_SERIALIZATION_NVP(ratio.den);
        }

        // Serialization function for A_FloatPoint
        template<class Archive>
        inline void serialize(Archive& ar, A_FloatPoint& point, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
        }

        // Serialization function for A_FloatPoint3
        template<class Archive>
        inline void serialize(Archive& ar, A_FloatPoint3& point, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
            ar& BOOST_SERIALIZATION_NVP(point.z);
        }

        // Serialization function for A_FloatRect
        template<class Archive>
        inline void serialize(Archive& ar, A_FloatRect& rect, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(rect.left);
            ar& BOOST_SERIALIZATION_NVP(rect.top);
            ar& BOOST_SERIALIZATION_NVP(rect.right);
            ar& BOOST_SERIALIZATION_NVP(rect.bottom);
        }

        // Serialization function for A_Matrix3
        template<class Archive>
        inline void serialize(Archive& ar, A_Matrix3& matrix, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][2]);
        }

        // Serialization function for A_Matrix4
        template<class Archive>
        inline void serialize(Archive& ar, A_Matrix4& matrix, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[0][3]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[1][3]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[2][3]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[3][0]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[3][1]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[3][2]);
            ar& BOOST_SERIALIZATION_NVP(matrix.mat[3][3]);
        }

        // Serialization function for A_LegacyRect
        template<class Archive>
        inline void serialize(Archive& ar, A_LegacyRect& rect, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(rect.top);
            ar& BOOST_SERIALIZATION_NVP(rect.left);
            ar& BOOST_SERIALIZATION_NVP(rect.bottom);
            ar& BOOST_SERIALIZATION_NVP(rect.right);
        }

        // Serialization function for A_LRect
        template<class Archive>
        inline void serialize(Archive& ar, A_LRect& rect, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(rect.left);
            ar& BOOST_SERIALIZATION_NVP(rect.top);
            ar& BOOST_SERIALIZATION_NVP(rect.right);
            ar& BOOST_SERIALIZATION_NVP(rect.bottom);
        }

        // Serialization function for A_LPoint
        template<class Archive>
        inline void serialize(Archive& ar, A_LPoint& point, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
        }

        // Serialization function for A_FloatPolar
        template<class Archive>
        inline void serialize(Archive& ar, A_FloatPolar& polar, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(polar.radius);
            ar& BOOST_SERIALIZATION_NVP(polar.angle);
        }

        // Serialization function for any enum type
        template<typename Archive, typename Enum>
        typename std::enable_if<std::is_enum<Enum>::value, void>::type
            serialize(Archive& ar, Enum& e, const unsigned int version) {
            auto val = static_cast<typename std::underlying_type<Enum>::type>(e);
            ar& BOOST_SERIALIZATION_NVP(val);
            e = static_cast<Enum>(val);
        }

        // Serialization function for AEGP_ColorVal
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_ColorVal& color, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(color.alphaF);
            ar& BOOST_SERIALIZATION_NVP(color.redF);
            ar& BOOST_SERIALIZATION_NVP(color.greenF);
            ar& BOOST_SERIALIZATION_NVP(color.blueF);
        }

        // Serialization function for AEGP_TimeDisplay2
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_TimeDisplay2& timeDisplay, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.time_display_type);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.timebaseC);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.non_drop_30B);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.frames_per_footC);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.starting_frameL);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.auto_timecode_baseB);
        }

        // Serialization function for AEGP_TimeDisplay3
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_TimeDisplay3& timeDisplay, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.display_mode);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.footage_display_mode);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.display_dropframeB);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.use_feet_framesB);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.timebaseC);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.frames_per_footC);
            ar& BOOST_SERIALIZATION_NVP(timeDisplay.frames_display_mode);
        }

        // Serialization function for AEGP_DownsampleFactor
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_DownsampleFactor& factor, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(factor.xS);
            ar& BOOST_SERIALIZATION_NVP(factor.yS);
        }

        // Serialization function for AEGP_LayerTransferMode
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_LayerTransferMode& mode, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(mode.mode);
            ar& BOOST_SERIALIZATION_NVP(mode.flags);
            ar& BOOST_SERIALIZATION_NVP(mode.track_matte);
        }

        // Serialization function for AEGP_TwoDVal
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_TwoDVal& val, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(val.x);
            ar& BOOST_SERIALIZATION_NVP(val.y);
        }

        // Serialization function for AEGP_ThreeDVal
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_ThreeDVal& val, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(val.x);
            ar& BOOST_SERIALIZATION_NVP(val.y);
            ar& BOOST_SERIALIZATION_NVP(val.z);
        }

        // Serialization function for AEGP_KeyframeEase
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_KeyframeEase& ease, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(ease.speedF);
            ar& BOOST_SERIALIZATION_NVP(ease.influenceF);
        }

        // Serialization function for AEGP_StreamValue2
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_StreamValue2& value, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(value.streamH);
            ar& BOOST_SERIALIZATION_NVP(value.val);
        }

        // Serialization function for AEGP_MaskFeather
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_MaskFeather& feather, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(feather.segment);
            ar& BOOST_SERIALIZATION_NVP(feather.segment_sF);
            ar& BOOST_SERIALIZATION_NVP(feather.radiusF);
            ar& BOOST_SERIALIZATION_NVP(feather.ui_corner_angleF);
            ar& BOOST_SERIALIZATION_NVP(feather.tensionF);
            ar& BOOST_SERIALIZATION_NVP(feather.interp);
            ar& BOOST_SERIALIZATION_NVP(feather.type);
        }

        // Serialization function for AEGP_AlphaLabel
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_AlphaLabel& label, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(label.flags);
            ar& BOOST_SERIALIZATION_NVP(label.redCu);
            ar& BOOST_SERIALIZATION_NVP(label.greenCu);
            ar& BOOST_SERIALIZATION_NVP(label.blueCu);
        }

        // Serialization function for AEGP_LoopBehavior
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_LoopBehavior& behavior, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(behavior.loops);
            ar& BOOST_SERIALIZATION_NVP(behavior.reserved);
        }

        // Serialization function for FIEL_Label
        template<class Archive>
        inline void serialize(Archive& ar, FIEL_Label& label, const unsigned int version) {
        ar& BOOST_SERIALIZATION_NVP(label.signature);
        ar& BOOST_SERIALIZATION_NVP(label.version);
        ar& BOOST_SERIALIZATION_NVP(label.type);
        ar& BOOST_SERIALIZATION_NVP(label.order);
        ar& BOOST_SERIALIZATION_NVP(label.reserved);
        }

        // Serialization function for AEGP_FootageInterp
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_FootageInterp& interp, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(interp.il);
            ar& BOOST_SERIALIZATION_NVP(interp.al);
            ar& BOOST_SERIALIZATION_NVP(interp.pd);
            ar& BOOST_SERIALIZATION_NVP(interp.loop);
            ar& BOOST_SERIALIZATION_NVP(interp.pix_aspect_ratio);
            ar& BOOST_SERIALIZATION_NVP(interp.native_fpsF);
            ar& BOOST_SERIALIZATION_NVP(interp.conform_fpsF);
            ar& BOOST_SERIALIZATION_NVP(interp.depthL);
            ar& BOOST_SERIALIZATION_NVP(interp.motion_dB);
        }

        // Serialization function for AEGP_FootageLayerKey
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_FootageLayerKey& key, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(key.layer_idL);
            ar& BOOST_SERIALIZATION_NVP(key.layer_indexL);
            ar& BOOST_SERIALIZATION_NVP(key.nameAC);
            ar& BOOST_SERIALIZATION_NVP(key.layer_draw_style);
        }

        // Serialization function for AEGP_FileSequenceImportOptions
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_FileSequenceImportOptions& options, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(options.all_in_folderB);
            ar& BOOST_SERIALIZATION_NVP(options.force_alphabeticalB);
            ar& BOOST_SERIALIZATION_NVP(options.start_frameL);
            ar& BOOST_SERIALIZATION_NVP(options.end_frameL);
        }

        // Serialization function for AEGP_SoundDataFormat
        template<class Archive>
        inline void serialize(Archive& ar, AEGP_SoundDataFormat& format, const unsigned int version) {
            ar& BOOST_SERIALIZATION_NVP(format.sample_rateF);
            ar& BOOST_SERIALIZATION_NVP(format.encoding);
            ar& BOOST_SERIALIZATION_NVP(format.bytes_per_sampleL);
            ar& BOOST_SERIALIZATION_NVP(format.num_channelsL);
        }



    } // namespace serialization
} // namespace boost

//base 
