#pragma once
#include "../CommandFactory.h"
#include "../SessionManager.h"

class NewCollection : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_Collection2H collectionH;
		A_Err err = A_Err_NONE;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_PluginID* plugin_id = SuiteManager::GetInstance().GetPluginID();
		Collection2H collection;
		ERR(suites.CollectionSuite2()->AEGP_NewCollection(*plugin_id, &collectionH));
		if (collectionH) {
			collection = Collection2H(createUUID());
			SessionManager::GetInstance().addSession(collectionH, collection.getSessionID());
		}
		baseobj base = boost::make_shared<Collection2H>(collection);
		Result<baseobj> result(base, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};

REGISTER_COMMAND(CommandID::NewCollection, NewCollection);

/*
Result<Collection2H> NewCollection() {
	Command cmd(CommandID::NewCollection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Collection2H> result = boost::get<Result<Collection2H>>(res.args[0]);
	return result;
}
*/

class DisposeCollection : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Collection2H collection = *boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[0]));
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));

		ERR(suites.CollectionSuite2()->AEGP_DisposeCollection(collectionH));
		baseobj base = boost::make_shared<null>();
		Result<baseobj> result(base, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::DisposeCollection, DisposeCollection);

/*
Result<null> DisposeCollection(Collection2H collection) {
	Command cmd(CommandID::DisposeCollection);
	cmd.args.push_back(collection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}
*/

class GetCollectionNumItems : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_u_long num_items = 0;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		Collection2H collection = *boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[0]));
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));

		ERR(suites.CollectionSuite2()->AEGP_GetCollectionNumItems(collectionH, &num_items));

		Result<int> result(static_cast<int>(num_items), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCollectionNumItems, GetCollectionNumItems);

/*
Result<int> GetCollectionNumItems(Collection2H collection) {
	Command cmd(CommandID::GetCollectionNumItems);
	cmd.args.push_back(collection);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<int> result = boost::get<Result<int>>(res.args[0]);
	return result;
}
*/

class GetCollectionItemByIndex : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		//get the args from the command
		auto collection = boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[0]));
		int index = boost::get<int>(cmd.args[1]);

		//initialize the AE SDK objects that will be used
		A_Err err = A_Err_NONE;
		AEGP_LayerH layerH;
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection->getSessionID()));
		AEGP_CollectionItemV2 itemH;
		AEGP_LayerCollectionItem layerItem;
		AEGP_MaskCollectionItem maskItem;
		AEGP_EffectCollectionItem effectItem;
		AEGP_StreamCollectionItem streamItem;
		AEGP_KeyframeCollectionItem keyframeItem;
		AEGP_MaskVertexCollectionItem maskVertexItem;

		//layer stream items
		AEGP_LayerStreamCollectionItem layerStreamItem;
		AEGP_MaskStreamCollectionItem maskStreamItem;
		AEGP_EffectStreamCollectionItem effectStreamItem;

		//proxy objects
		Layer layerProxy;
		LayerCollectionItem layerCollectionItem;
		MaskCollectionItem maskCollectionItem;
		EffectCollectionItem effectCollectionItem;
		StreamCollectionItem streamCollectionItem;
		KeyframeCollectionItem keyframeCollectionItem;
		MaskVertexCollectionItem maskVertexCollectionItem;

		//stream items
		LayerStreamCollectionItem layerStreamCollectionItem;
		MaskStreamCollectionItem maskStreamCollectionItem;
		EffectStreamCollectionItem effectStreamCollectionItem;

		CollectionItemV2 item;
		baseobj base;
		Result<baseobj> result;
		Response response;

		//IDs
		int MainID = createUUID(); //use this for the CollectionItemV2
		int ID2 = createUUID(); //use this for the CollectionItem's union type
		int ID3 = createUUID(); //use this for the union type's contents
		int ID4 = createUUID(); //if a stream type, use this on the lowest level
		int streamID = createUUID(); //use this for the StreamRef
		int layerID;

		ERR(suites.CollectionSuite2()->AEGP_GetCollectionItemByIndex(collectionH, index, &itemH));

		SessionManager::GetInstance().addSession(itemH.stream_refH, streamID);

		StreamRef stream = StreamRef(streamID);

		switch (itemH.type) {
			case AEGP_CollectionItemType_NONE:
				break;
			case AEGP_CollectionItemType_LAYER:
				layerItem = itemH.u.layer;
				layerH = layerItem.layerH;
				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
				layerProxy = Layer(layerID);
				layerCollectionItem = LayerCollectionItem(layerProxy, ID2);
				item = CollectionItemV2(AEGP_CollectionItemType_LAYER, layerCollectionItem, stream, MainID);
				base = boost::make_shared<CollectionItemV2>(item);
				result = Result<baseobj>(base, errToString(err));

				// For each case, add each "level" of the object to the session manager
				SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
				SessionManager::GetInstance().addSession(layerItem, ID2); //add the layer collection item to the session manager
				SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
				break;
			case AEGP_CollectionItemType_MASK:
				maskItem = itemH.u.mask;
				layerH = maskItem.layerH;
				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
				layerProxy = Layer(layerID);
				maskCollectionItem = MaskCollectionItem(layerProxy, maskItem.index, ID3);
				item = CollectionItemV2(AEGP_CollectionItemType_MASK, maskCollectionItem, stream, MainID);
				base = boost::make_shared<CollectionItemV2>(item);
				result = Result<baseobj>(base, errToString(err));

				// For each case, add each "level" of the object to the session manager
				SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
				SessionManager::GetInstance().addSession(maskItem, ID3); //add the mask collection item to the session manager
				SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager

				break;
			case AEGP_CollectionItemType_EFFECT:
				effectItem = itemH.u.effect;
				layerH = effectItem.layerH;
				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
				layerProxy = Layer(layerID);
				effectCollectionItem = EffectCollectionItem(layerProxy, effectItem.index, ID3);
				item = CollectionItemV2(AEGP_CollectionItemType_EFFECT, effectCollectionItem, stream, MainID);
				base = boost::make_shared<CollectionItemV2>(item);
				result = Result<baseobj>(base, errToString(err));

				// For each case, add each "level" of the object to the session manager
				SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
				SessionManager::GetInstance().addSession(effectItem, ID3); //add the effect collection item to the session manager
				SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
				break;
			case AEGP_CollectionItemType_STREAM:
				streamItem = itemH.u.stream;
				switch (streamItem.type) {
					case AEGP_StreamCollectionItemType_NONE:
						break;
					case AEGP_StreamCollectionItemType_LAYER:
						layerStreamItem = streamItem.u.layer_stream;
						layerH = layerStreamItem.layerH;
						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
						layerProxy = Layer(layerID);
						layerStreamCollectionItem = LayerStreamCollectionItem(layerProxy, layerStreamItem.layer_stream, ID3);
						streamCollectionItem = StreamCollectionItem(AEGP_StreamCollectionItemType_LAYER, layerStreamCollectionItem, ID2);
						item = CollectionItemV2(AEGP_CollectionItemType_STREAM, streamCollectionItem, stream, MainID);
						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(streamItem, ID2); //add the stream collection item to the session manager
						SessionManager::GetInstance().addSession(layerStreamItem, ID3); //add the layer stream collection item to the session manager
						SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
						break;
					case AEGP_StreamCollectionItemType_MASK:
						maskStreamItem = streamItem.u.mask_stream;
						maskItem = maskStreamItem.mask;
						layerH = maskItem.layerH;
						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
						layerProxy = Layer(layerID);
						maskCollectionItem = MaskCollectionItem(layerProxy, maskItem.index, ID3);
						maskStreamCollectionItem = MaskStreamCollectionItem(maskCollectionItem, maskStreamItem.mask_stream, ID4);
						streamCollectionItem = StreamCollectionItem(AEGP_StreamCollectionItemType_MASK, maskStreamCollectionItem, ID2);
						item = CollectionItemV2(AEGP_CollectionItemType_STREAM, streamCollectionItem, stream, MainID);
						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(streamItem, ID2); //add the stream collection item to the session manager
						SessionManager::GetInstance().addSession(maskStreamItem, ID4); //add the mask stream collection item to the session manager
						SessionManager::GetInstance().addSession(maskItem, ID3); //add the mask collection item to the session manager
						SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
						break;
					case AEGP_StreamCollectionItemType_EFFECT:
						effectStreamItem = streamItem.u.effect_stream;
						effectItem = effectStreamItem.effect;
						layerH = effectItem.layerH;
						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
						layerProxy = Layer(layerID);
						effectCollectionItem = EffectCollectionItem(layerProxy, effectItem.index, ID3);
						effectStreamCollectionItem = EffectStreamCollectionItem(effectCollectionItem, effectStreamItem.param_index, ID4);
						streamCollectionItem = StreamCollectionItem(AEGP_StreamCollectionItemType_EFFECT, effectStreamCollectionItem, ID2);
						item = CollectionItemV2(AEGP_CollectionItemType_STREAM, streamCollectionItem, stream, MainID);
						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(streamItem, ID2); //add the stream collection item to the session manager
						SessionManager::GetInstance().addSession(effectStreamItem, ID4); //add the effect stream collection item to the session manager
						SessionManager::GetInstance().addSession(effectItem, ID3); //add the effect collection item to the session manager
						SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
						break;
					case AEGP_StreamCollectionItemType_END:
						break;
				}
				break;
			case AEGP_CollectionItemType_KEYFRAME:
				keyframeItem = itemH.u.keyframe;
				streamItem = keyframeItem.stream_coll;
				switch (streamItem.type) {
					case AEGP_StreamCollectionItemType_NONE:
						break;
					case AEGP_StreamCollectionItemType_LAYER:
						layerStreamItem = streamItem.u.layer_stream;
						layerH = layerStreamItem.layerH;
						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
						layerProxy = Layer(layerID);
						layerStreamCollectionItem = LayerStreamCollectionItem(layerProxy, layerStreamItem.layer_stream, ID3);
						streamCollectionItem = StreamCollectionItem(AEGP_StreamCollectionItemType_LAYER, layerStreamCollectionItem, ID2);
						item = CollectionItemV2(AEGP_CollectionItemType_STREAM, streamCollectionItem, stream, MainID);
						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(streamItem, ID2); //add the stream collection item to the session manager
						SessionManager::GetInstance().addSession(layerStreamItem, ID3); //add the layer stream collection item to the session manager
						SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
						break;
					case AEGP_CollectionItemType_MASK_VERTEX:
						maskVertexItem = itemH.u.mask_vertex;
						maskItem = maskVertexItem.mask_sel;
						layerH = maskItem.layerH;
						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &layerID));
						layerProxy = Layer(layerID);
						maskCollectionItem = MaskCollectionItem(layerProxy, maskItem.index, ID3);
						maskVertexCollectionItem = MaskVertexCollectionItem(maskCollectionItem, maskVertexItem.index, ID4);
						streamCollectionItem = StreamCollectionItem(AEGP_StreamCollectionItemType_MASK, maskStreamCollectionItem, ID2);
						item = CollectionItemV2(AEGP_CollectionItemType_STREAM, streamCollectionItem, stream, MainID);
						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(maskVertexItem, ID4); //add the mask vertex collection item to the session manager
						SessionManager::GetInstance().addSession(maskItem, ID3); //add the mask collection item to the session manager
						SessionManager::GetInstance().addSession(layerH, layerID); //add the layer handle to the session manager
						break;
					case AEGP_CollectionItemType_STREAMREF:
						item = CollectionItemV2(AEGP_CollectionItemType_STREAMREF, stream, MainID);

						base = boost::make_shared<CollectionItemV2>(item);
						result = Result<baseobj>(base, errToString(err));

						// For each case, add each "level" of the object to the session manager
						SessionManager::GetInstance().addSession(itemH, MainID); //add the item to the session manager
						SessionManager::GetInstance().addSession(itemH.stream_refH, streamID); //add the stream ref to the session manager
						break;
					}
		}
		response = Response(result);
		MessageQueueManager::getInstance().sendResponse(response);

	}
};
REGISTER_COMMAND(CommandID::GetCollectionItemByIndex, GetCollectionItemByIndex);

/*
Result<CollectionItemV2> GetCollectionItemByIndex(Collection2H collection, int index) {
	Command cmd(CommandID::GetCollectionItemByIndex);
	cmd.args.push_back(collection);
	cmd.args.push_back(index);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<CollectionItemV2> result = boost::get<Result<CollectionItemV2>>(res.args[0]);
	return result;
}
*/

class CollectionPushBack : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		auto collection = boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[0]));
		auto item = boost::dynamic_pointer_cast<CollectionItemV2>(boost::get<baseobj>(cmd.args[1]));
		StreamRef stream = item->streamRef;

		//What we know we have now
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection->getSessionID()));
		AEGP_StreamRefH streamH = std::get<AEGP_StreamRefH>(SessionManager::GetInstance().getSession(stream.getSessionID()));

		A_Err err = A_Err_NONE;
		AEGP_CollectionItemV2 itemH;
		AEGP_LayerCollectionItem layerItem;
		AEGP_MaskCollectionItem maskItem;
		AEGP_EffectCollectionItem effectItem;
		AEGP_StreamCollectionItem streamItem;
		AEGP_KeyframeCollectionItem keyframeItem;
		AEGP_MaskVertexCollectionItem maskVertexItem;

		//layer stream items
		AEGP_LayerStreamCollectionItem layerStreamItem;
		AEGP_MaskStreamCollectionItem maskStreamItem;
		AEGP_EffectStreamCollectionItem effectStreamItem;

		//proxy objects
		Layer layerProxy;
		LayerCollectionItem layerCollectionItem;
		MaskCollectionItem maskCollectionItem;
		EffectCollectionItem effectCollectionItem;
		StreamCollectionItem streamCollectionItem;
		KeyframeCollectionItem keyframeCollectionItem;
		MaskVertexCollectionItem maskVertexCollectionItem;

		//stream items
		LayerStreamCollectionItem layerStreamCollectionItem;
		MaskStreamCollectionItem maskStreamCollectionItem;
		EffectStreamCollectionItem effectStreamCollectionItem;

		Result<baseobj> nullResponse;
		Response response;

		itemH.stream_refH = streamH;

	switch (item->type) {
		case AEGP_CollectionItemType_NONE:
			break;
		case AEGP_CollectionItemType_LAYER:
			itemH.type = AEGP_CollectionItemType_LAYER; //Set the Type, since we already know it's a layer
			//get proxy objects
			layerCollectionItem = boost::get<LayerCollectionItem>(item->u); //get the layer collection item
			layerProxy = layerCollectionItem.layer; //get the layer


			layerItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			itemH.u.layer = layerItem; //set the layer item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));

			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_MASK:
			itemH.type = AEGP_CollectionItemType_MASK;
			
			maskCollectionItem = boost::get<MaskCollectionItem>(item->u); //get the mask collection item
			layerProxy = maskCollectionItem.layer; //get the layer
			maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			maskItem.index = maskCollectionItem.index; //get the mask index
			itemH.u.mask = maskItem; //set the mask item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_EFFECT:
			itemH.type = AEGP_CollectionItemType_EFFECT;
			effectCollectionItem = boost::get<EffectCollectionItem>(item->u); //get the effect collection item
			layerProxy = effectCollectionItem.layer; //get the layer
			effectItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			effectItem.index = effectCollectionItem.index; //get the effect index
			itemH.u.effect = effectItem; //set the effect item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_STREAM:
			itemH.type = AEGP_CollectionItemType_STREAM;
			streamCollectionItem = boost::get<StreamCollectionItem>(item->u); //get the stream collection item
			switch (streamCollectionItem.type) {
				case AEGP_StreamCollectionItemType_NONE:
					break;
				case AEGP_StreamCollectionItemType_LAYER:
					layerStreamCollectionItem = boost::get<LayerStreamCollectionItem>(streamCollectionItem.u); //get the layer stream collection item
					layerProxy = layerStreamCollectionItem.layer; //get the layer
					layerStreamItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
					streamItem.u.layer_stream = layerStreamItem; //set the layer stream item
					break;
				case AEGP_StreamCollectionItemType_MASK:
					maskStreamCollectionItem = boost::get<MaskStreamCollectionItem>(streamCollectionItem.u); //get the mask stream collection item
					maskCollectionItem = maskStreamCollectionItem.mask;//maskcollectionItem, containing layer and index
					layerProxy = maskCollectionItem.layer; //get the layer
					maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
					maskItem.index = maskCollectionItem.index; //get the mask index
					maskStreamItem.mask = maskItem;
					maskStreamItem.mask_stream = maskStreamCollectionItem.maskStream;
					break;
				case AEGP_StreamCollectionItemType_EFFECT:
				effectStreamCollectionItem = boost::get<EffectStreamCollectionItem>(streamCollectionItem.u); //get the effect stream collection item
					effectCollectionItem = effectStreamCollectionItem.effect; //get the effect
					layerProxy = effectCollectionItem.layer; //get the layer
					effectItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
					effectItem.index = effectCollectionItem.index; //get the effect index
					effectStreamItem.effect = effectItem; //set the effect stream item
					effectStreamItem.param_index = effectStreamCollectionItem.param_index; //set the param index
					streamItem.u.effect_stream = effectStreamItem; //set the effect stream item
					break;
				case AEGP_StreamCollectionItemType_END:
				break;
			} 
			//end switch
			itemH.u.stream = streamItem; //set the stream item
			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_KEYFRAME:

			itemH.type = AEGP_CollectionItemType_KEYFRAME;
			keyframeCollectionItem = boost::get<KeyframeCollectionItem>(item->u); //get the keyframe collection item
			streamCollectionItem = keyframeCollectionItem.stream; //get the stream collection item

			switch (streamCollectionItem.type) {
					case AEGP_StreamCollectionItemType_NONE:
						break;
					case AEGP_StreamCollectionItemType_LAYER:
						layerStreamCollectionItem = boost::get<LayerStreamCollectionItem>(streamCollectionItem.u); //get the layer stream collection item
						layerProxy = layerStreamCollectionItem.layer; //get the layer
						layerStreamItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
						streamItem.u.layer_stream = layerStreamItem; //set the layer stream item
						break;
					case AEGP_StreamCollectionItemType_MASK:
						maskStreamCollectionItem = boost::get<MaskStreamCollectionItem>(streamCollectionItem.u); //get the mask stream collection item
						maskCollectionItem = maskStreamCollectionItem.mask; //get the mask
						layerProxy = maskCollectionItem.layer; //get the layer
						maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
						maskItem.index = maskCollectionItem.index; //get the mask index
						maskStreamItem.mask = maskItem; //set the mask item
						maskStreamItem.mask_stream = maskStreamCollectionItem.maskStream; //set the mask stream
						streamItem.u.mask_stream = maskStreamItem; //set the mask stream item
						break;
					case AEGP_StreamCollectionItemType_EFFECT:
						effectStreamCollectionItem = boost::get<EffectStreamCollectionItem>(streamCollectionItem.u); //get the effect stream collection item
						effectCollectionItem = effectStreamCollectionItem.effect; //get the effect
						layerProxy = effectCollectionItem.layer; //get the layer
						effectItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
						effectItem.index = effectCollectionItem.index; //get the effect index
						effectStreamItem.effect = effectItem; //set the effect stream item
						effectStreamItem.param_index = effectStreamCollectionItem.param_index; //set the param index
						streamItem.u.effect_stream = effectStreamItem; //set the effect stream item
						break;
					case AEGP_StreamCollectionItemType_END:
						break;
			}
			//end switch
			keyframeItem.stream_coll = streamItem; //set the stream collection item
			keyframeItem.index = keyframeCollectionItem.index; //set the keyframe index
			itemH.u.keyframe = keyframeItem; //set the keyframe item
			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_MASK_VERTEX:
			itemH.type = AEGP_CollectionItemType_MASK_VERTEX;
			maskVertexCollectionItem = boost::get<MaskVertexCollectionItem>(item->u); //get the mask vertex collection item
			maskCollectionItem = maskVertexCollectionItem.mask; //get the mask
			layerProxy = maskCollectionItem.layer; //get the layer
			maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			maskItem.index = maskCollectionItem.index; //set the mask index
			maskVertexItem.mask_sel = maskItem; //set the mask item
			maskVertexItem.index = maskVertexCollectionItem.index; //set the vertex index from the proxy object
			itemH.u.mask_vertex = maskVertexItem; //set the mask vertex item (of the real item)
			nullResponse = Result<baseobj>(boost::make_shared<null>(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_STREAMREF:
			itemH.type = AEGP_CollectionItemType_STREAMREF;
			itemH.stream_refH = streamH;
			break;
		}
		ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CollectionPushBack, CollectionPushBack);

/*
Result<null> CollectionPushBack(Collection2H collection, CollectionItemV2 item) {
	Command cmd(CommandID::CollectionPushBack);
	cmd.args.push_back(collection);
	cmd.args.push_back(item);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}
*/

class CollectionErase : public CommandBase {
public: 
using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		auto collection = boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[0]));
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection->getSessionID()));
		Range range = *boost::dynamic_pointer_cast<Range>(boost::get<baseobj>(cmd.args[1]));
		int index_first = static_cast<int>(range.minF);
		int index_last = static_cast<int>(range.maxF);

		ERR(suites.CollectionSuite2()->AEGP_CollectionErase(collectionH, index_first, index_last));

		boost::shared_ptr<Base> nullPtr = boost::make_shared<null>();

		Result<boost::shared_ptr<Base>> result(nullPtr, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CollectionErase, CollectionErase);

/*
Result<null> CollectionErase(Collection2H collection, Range range) {
	Command cmd(CommandID::CollectionErase);
	cmd.args.push_back(collection);
	cmd.args.push_back(range);
	Response res = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(res.args[0]);
	return result;
}
*/