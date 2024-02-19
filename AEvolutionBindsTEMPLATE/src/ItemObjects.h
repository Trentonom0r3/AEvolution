#pragma once

#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"
#include <string>
#include <memory>
#include <tuple>

// Forward declarations for class hierarchy
class wLayer;
class wFolder;

/**
 * @brief Base class for all items in the project, such as compositions, folders, and footage.
 */
class wItem {
public:
	// Constructors
	wItem() = default;
	explicit wItem(AE_Item item) : item(item) {}

	// Destructor
	virtual ~wItem() = default;

	// Item properties
	AE_Item item; // Contains a pointer to an After Effects item

	// Item behaviors
	AEGP_ItemType itemType();
	A_long itemID();
	A_long itemFlags();
	void setUseProxy(bool use_proxy);
	std::tuple<A_long, A_long> itemDimensions();
	A_Ratio itemPixelAspectRatio();
	A_Time itemDuration();
	void deleteItem();
	A_Time itemCurrentTime();
	void setCurrentTime(A_Time new_time);
	std::string itemComment();
	void setItemComment(const std::string& comment);
	AEGP_LabelID itemLabel();
	void setItemLabel(AEGP_LabelID label);
	wFolder parentFolder();
	void setParentFolder(wFolder parent_folder);
	std::string itemName();
	void setItemName(const std::string& name);
	bool isSelected();
	void select(bool select, bool deselect_others);
};


/**
 * @brief Represents a folder item, inheriting from wItem.
 */
class wFolder : public wItem {
public:
	using wItem::wItem; // Inherit constructors
	wFolder() = default;
	explicit wFolder(AE_Item folder) : wItem(folder) {}
};


//comp Item, can also be created from AE_Comp, or AE_Item
class wComp : public wItem {
public:
	using wItem::wItem;
	wComp() = default;
	wComp(AE_Comp comp) : comp(comp) {}

	wComp(AE_Item item) : wItem(item) {}

	AE_Comp comp;

	// Static methods
	static wComp newComp(std::string name, A_long width, A_long height, A_Ratio pixelAspect, A_Time duration, A_Ratio framerate, AE_Item parent);
	static wComp mostRecentlyUsed();

	// Methods
	wComp duplicate();

	// Layer Management
	A_long getNumLayers();
	bool isAddLayerValid(wItem item);
	wLayer addLayer(wItem item);
	wLayer getLayerfromID(AEGP_LayerIDVal layerID);
	wLayer getLayerByIndex(A_long index);
	wLayer getActiveLayer();
	wLayer createSolid(std::string name, A_long width, A_long height, AEGP_ColorVal color, A_Time duration);
	wLayer createCamera(std::string name, A_FloatPoint center);
	wLayer createLight(std::string name, A_FloatPoint center);
	wLayer createNull(std::string name, A_Time duration);
	wLayer createTextLayer(bool selectNew);
	wLayer createBoxTextLayer(bool selectNew, A_FloatPoint dimensions);
	wLayer createVectorLayer();

	// Getters (Paired, In Order)
	AEGP_DownsampleFactor getDownsampleFactor();
	AEGP_ColorVal getBGColor();
	bool getShowLayerNameorSourceName();
	bool showBlendModes();
	A_FpLong getFrameRate();
	std::pair<A_Ratio, A_Ratio> shutterAnglePhase();
	A_long motionBlurSamples();
	A_long motionBlurAdaptiveSampleLimit();
	A_Time getWorkAreaStart();
	A_Time getWorkAreaDuration();
	A_Time displayStartTime();
	bool displayDropFrame();

	// Getters (Pair from wItem)
	A_Time frameDuration();
	// GetNewCompMarkerStreamCmd::execute()

	// Setters (Paired, In Order)
	void setDownsampleFactor(AEGP_DownsampleFactor factor);
	void setBGColor(AEGP_ColorVal color);
	void setShowLayerNameorSourceName(bool showLayerNameB);
	void setShowBlendModes(bool showBlendModesB);
	void setFrameRate(A_FpLong frameRate);
	void setMotionBlurSamples(A_long samplesL);
	void setMotionBlurAdaptiveSampleLimit(A_long limitL);
	//void setWorkAreaStart(A_Time start);
	//void setWorkAreaDuration(A_Time duration);
	void setDisplayStartTime(A_Time time);
	void setDisplayDropFrame(bool dropFrameB);

	// Setters (Pair from wItem)
	void setDuration(A_Time duration);
	void setPixelAspectRatio(A_Ratio pixelAspect);
	void setDimensions(A_long width, A_long height);
	
	// Getters, Misc.
	AEGP_CompFlags getFlags();

};

//footage Item, can also be created from AE_Footage, or AE_Item
class wFootage : public wItem {
public:
	using wItem::wItem;
	wFootage() {};
	~wFootage() {};
	wFootage(AE_Item item);
	wFootage(AE_Footage footage);
	AE_Footage footage;
	AE_Item item;

	// Static methods
	static wFootage newFootage(std::string name, std::string file_path, AEGP_InterpretationStyle interp, wFolder parent);
	static wFootage newPlaceholderFootage(std::string name, std::string file_path, AEGP_InterpretationStyle interp, wFolder parent);
	static wFootage newSolidFootage(std::string name, A_long width, A_long height, AEGP_ColorVal color, wFolder parent);

	// Getter Methods (Mainly Info related)
	AE_Footage getProxyFootage();
	std::pair<A_long, A_long> footageNumFiles();
	std::string footagePath(A_long frameNum, A_long fileIndex);
	AEGP_FootageSignature getFootageSignature();
	AEGP_FootageInterp getInterpretation();
	AEGP_FootageLayerKey getLayerKey();
	AEGP_SoundDataFormat getSoundDataFormat();
	AEGP_FileSequenceImportOptions getSequenceImportOptions();

	// Setter Methods
	void setSolidColor(AEGP_ColorVal color);
	void setSolidDimensions(A_long width, A_long height);
	void setItemUseProxy(bool use_proxyB);
	void replaceFootage(std::string file_path, AEGP_InterpretationStyle interp);
	void setInterpretation(AEGP_FootageInterp interp);
};
