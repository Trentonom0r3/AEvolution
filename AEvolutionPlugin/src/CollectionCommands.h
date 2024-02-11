#pragma once
#include "CommandFactory.h"
#include "SessionManager.h"

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
		Result<Collection2H> result(collection, errToString(err));
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
		Collection2H collection = boost::get<Collection2H>(cmd.args[0]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));

		ERR(suites.CollectionSuite2()->AEGP_DisposeCollection(collectionH));

		Result<null> result(null(), errToString(err));
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
		Collection2H collection = boost::get<Collection2H>(cmd.args[0]);
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
		A_Err err = A_Err_NONE;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		Collection2H collection = boost::get<Collection2H>(cmd.args[0]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		A_u_long index = static_cast<A_u_long>(boost::get<int>(cmd.args[1]));

		//AE item
		AEGP_CollectionItemV2 item;

		//base item being returned
		CollectionItemV2 collectionItem;

		//items within the base item
		LayerCollectionItem layerCollectionItem;
		MaskCollectionItem maskCollectionItem;
		EffectCollectionItem effectCollectionItem;
		StreamCollectionItem streamCollectionItem;
		LayerStreamCollectionItem layerStreamItem;
		MaskStreamCollectionItem maskStreamItem;
		EffectStreamCollectionItem effectStreamItem;
		KeyframeCollectionItem keyframeCollectionItem;
		MaskVertexCollectionItem maskVertexCollectionItem;
		//layer within (most) returns
		Layer layerProxy;

		//create the UUIDs
		int collectionUUID = createUUID();
		int itemTypeUUID = createUUID();
		int streamRefUUID = createUUID();
		int streamItemUUID = createUUID();
		int streamItemTypeUUID = createUUID();
		int keyframeUUID = createUUID();
		int itemUUID;

		//create the response
		Response response;

		//create the result
		Result<CollectionItemV2> result;

		ERR(suites.CollectionSuite2()->AEGP_GetCollectionItemByIndex(collectionH, index, &item));

		//stream valid for all types, so we'll handle it first
		AEGP_StreamRefH stream = item.stream_refH;

		//add the stream to the session manager
		SessionManager::GetInstance().addSession(stream, streamRefUUID);

		//Create the proxy StreamRef
		StreamRef streamProxy = StreamRef(streamRefUUID);

		switch (item.type) {
			case AEGP_CollectionItemType_NONE:
				break;
			case AEGP_CollectionItemType_LAYER:
				// will return a Result<CollectionItemV2> with a CollectionItemV2 that contains a LayerCollectionItem that contains a Layer
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager
				AEGP_LayerCollectionItem layerItem = item.u.layer; // get the layer item
				AEGP_LayerH layerH = layerItem.layerH; // get the layer handle
				SessionManager::GetInstance().addSession(layerItem, itemTypeUUID); // add the layer handle to the session manager
				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));
				SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

				//create the proxy objects
				layerProxy = Layer(itemUUID);
				layerCollectionItem = LayerCollectionItem(layerProxy, itemTypeUUID);
				collectionItem = CollectionItemV2(item.type, layerCollectionItem, streamProxy, collectionUUID);

				result = Result<CollectionItemV2>(collectionItem, errToString(err));
				response = Response(result);
				MessageQueueManager::getInstance().sendResponse(response);
				break;
			case AEGP_CollectionItemType_MASK:
		// will return a Result<CollectionItemV2> with a CollectionItemV2 that contains a MaskCollectionItem that contains a Layer and a MaskIndex
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager

				AEGP_MaskCollectionItem maskItem = item.u.mask; // get the mask item
				AEGP_LayerH layerH = maskItem.layerH; // get the layer handle
				AEGP_MaskIndex maskIndex = maskItem.index; // get the mask index

				SessionManager::GetInstance().addSession(maskItem, itemTypeUUID); // add the mask item to the session manager

				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

				SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

				//create the proxy objects
				layerProxy = Layer(itemUUID);
				maskCollectionItem = MaskCollectionItem(layerProxy, maskIndex, itemTypeUUID);
				collectionItem = CollectionItemV2(item.type, maskCollectionItem, streamProxy, collectionUUID);

				//craft the result
				result = Result<CollectionItemV2>(collectionItem, errToString(err));

				//send the response
				response = Response(result);
				MessageQueueManager::getInstance().sendResponse(response);
				break;
			case AEGP_CollectionItemType_EFFECT:
// will return a Result<CollectionItemV2> with a CollectionItemV2 that contains a EffectCollectionItem that contains a Layer and a EffectIndex
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager

				AEGP_EffectCollectionItem effectItem = item.u.effect; // get the effect item
				AEGP_LayerH layerH = effectItem.layerH; // get the layer handle
				AEGP_EffectIndex effectIndex = effectItem.index; // get the effect index

				SessionManager::GetInstance().addSession(effectItem, itemTypeUUID); // add the effect item to the session manager

				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

				SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

				//create the proxy objects
				layerProxy = Layer(itemUUID);
				effectCollectionItem = EffectCollectionItem(layerProxy, effectIndex, itemTypeUUID);
				collectionItem = CollectionItemV2(item.type, effectCollectionItem, streamProxy, collectionUUID);

				//craft the result
				result = Result<CollectionItemV2>(collectionItem, errToString(err));

				//send the response
				response = Response(result);
				MessageQueueManager::getInstance().sendResponse(response);
				break;
			case AEGP_CollectionItemType_STREAM:
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager
				AEGP_StreamCollectionItem streamCollection = item.u.stream; // get the stream item
			switch (streamCollection.type) {
				case AEGP_StreamCollectionItemType_NONE:
					break;
				case AEGP_StreamCollectionItemType_LAYER:
					SessionManager::GetInstance().addSession(streamCollection, streamItemUUID); // add the stream item to the session manager

					AEGP_LayerStreamCollectionItem layerStream = streamCollection.u.layer_stream; // get the layer stream item
					AEGP_LayerH layerH = layerStream.layerH; // get the layer handle

					ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

					SessionManager::GetInstance().addSession(layerStream, streamItemTypeUUID); // add the layer stream item to the session manager)
					SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

					//create the proxy objects
					layerProxy = Layer(itemUUID);
					layerStreamItem = LayerStreamCollectionItem(layerProxy, layerStream.layer_stream, streamItemTypeUUID);
					streamCollectionItem = StreamCollectionItem(streamCollection.type, layerStreamItem, streamItemUUID);
					collectionItem = CollectionItemV2(item.type, streamCollectionItem, streamProxy, collectionUUID);

					//craft the result
					result = Result<CollectionItemV2>(collectionItem, errToString(err));

					//send the response
					response = Response(result);
					MessageQueueManager::getInstance().sendResponse(response);
					break;
				case AEGP_StreamCollectionItemType_MASK:
					SessionManager::GetInstance().addSession(streamCollection, itemTypeUUID); // add the stream item to the session manager

					AEGP_MaskStreamCollectionItem maskStream = streamCollection.u.mask_stream; // get the mask stream item
					AEGP_MaskCollectionItem maskItem = maskStream.mask; // get the mask item
					AEGP_LayerH layerH = maskItem.layerH; // get the layer handle
					AEGP_MaskIndex maskIndex = maskItem.index; // get the mask index

					SessionManager::GetInstance().addSession(maskStream, streamItemUUID); // add the mask stream item to the session manager
					SessionManager::GetInstance().addSession(maskItem, streamItemTypeUUID); // add the mask item to the session manager

					ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

					SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

					//create the proxy objects
					layerProxy = Layer(itemUUID);
					maskCollectionItem = MaskCollectionItem(layerProxy, maskIndex, streamItemTypeUUID);
					maskStreamItem = MaskStreamCollectionItem(maskCollectionItem, maskStream.mask_stream, streamItemUUID);
					streamCollectionItem = StreamCollectionItem(streamCollection.type, maskStreamItem, itemTypeUUID);
					collectionItem = CollectionItemV2(item.type, streamCollectionItem, streamProxy, collectionUUID);

					//craft the result
					result = Result<CollectionItemV2>(collectionItem, errToString(err));

					//send the response
					response = Response(result);
					MessageQueueManager::getInstance().sendResponse(response);
					break;
				case AEGP_StreamCollectionItemType_EFFECT:
					SessionManager::GetInstance().addSession(streamCollection, itemTypeUUID); // add the stream item to the session manager
						
					AEGP_EffectStreamCollectionItem effectStream = streamCollection.u.effect_stream; // get the effect stream item
					AEGP_EffectCollectionItem effectItem = effectStream.effect; // get the effect item
					AEGP_LayerH layerH = effectItem.layerH; // get the layer handle
					AEGP_EffectIndex effectIndex = effectItem.index; // get the effect index
					A_long param_index = effectStream.param_index; // get the param index

					SessionManager::GetInstance().addSession(effectStream, streamItemUUID); // add the effect stream item to the session manager
					SessionManager::GetInstance().addSession(effectItem, streamItemTypeUUID); // add the effect item to the session manager

					ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

					SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

					//create the proxy objects
					layerProxy = Layer(itemUUID);
					effectCollectionItem = EffectCollectionItem(layerProxy, effectIndex, streamItemTypeUUID);
					effectStreamItem = EffectStreamCollectionItem(effectCollectionItem, param_index, streamItemUUID);
					streamCollectionItem = StreamCollectionItem(streamCollection.type, effectStreamItem, itemTypeUUID);
					collectionItem = CollectionItemV2(item.type, streamCollectionItem, streamProxy, collectionUUID);

					//craft the result
					result = Result<CollectionItemV2>(collectionItem, errToString(err));

					//send the response
					response = Response(result);
					MessageQueueManager::getInstance().sendResponse(response);
					break;
				case AEGP_StreamCollectionItemType_END:
					break;
				}
				break;
			case AEGP_CollectionItemType_KEYFRAME:
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager
				AEGP_KeyframeCollectionItem keyframeItem = item.u.keyframe; // get the keyframe item
				AEGP_StreamCollectionItem streamCollection = keyframeItem.stream_coll; // get the stream item
				AEGP_KeyframeIndex keyframeIndex = keyframeItem.index; // get the keyframe index
				switch (streamCollection.type) {
					case AEGP_StreamCollectionItemType_NONE:
						break;
					case AEGP_StreamCollectionItemType_LAYER:
						SessionManager::GetInstance().addSession(keyframeItem, keyframeUUID);
						SessionManager::GetInstance().addSession(streamCollection, streamItemUUID); // add the stream item to the session manager

						AEGP_LayerStreamCollectionItem layerStream = streamCollection.u.layer_stream; // get the layer stream item
						AEGP_LayerH layerH = layerStream.layerH; // get the layer handle

						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

						SessionManager::GetInstance().addSession(layerStream, streamItemTypeUUID); // add the layer stream item to the session manager)
						SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

						//create the proxy objects
						layerProxy = Layer(itemUUID);
						layerStreamItem = LayerStreamCollectionItem(layerProxy, layerStream.layer_stream, streamItemTypeUUID);
						streamCollectionItem = StreamCollectionItem(streamCollection.type, layerStreamItem, streamItemUUID);
						keyframeCollectionItem = KeyframeCollectionItem(streamCollectionItem, keyframeIndex, keyframeUUID);
						collectionItem = CollectionItemV2(item.type, keyframeCollectionItem, streamProxy, collectionUUID);
						//craft the result
						result = Result<CollectionItemV2>(collectionItem, errToString(err));

						//send the response
						response = Response(result);
						MessageQueueManager::getInstance().sendResponse(response);
						break;
					case AEGP_StreamCollectionItemType_MASK:
						SessionManager::GetInstance().addSession(streamCollection, itemTypeUUID); // add the stream item to the session manager

						AEGP_MaskStreamCollectionItem maskStream = streamCollection.u.mask_stream; // get the mask stream item
						AEGP_MaskCollectionItem maskItem = maskStream.mask; // get the mask item
						AEGP_LayerH layerH = maskItem.layerH; // get the layer handle
						AEGP_MaskIndex maskIndex = maskItem.index; // get the mask index

						SessionManager::GetInstance().addSession(maskStream, streamItemUUID); // add the mask stream item to the session manager
						SessionManager::GetInstance().addSession(maskItem, streamItemTypeUUID); // add the mask item to the session manager

						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

						SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

						//create the proxy objects
						layerProxy = Layer(itemUUID);
						maskCollectionItem = MaskCollectionItem(layerProxy, maskIndex, streamItemTypeUUID);
						maskStreamItem = MaskStreamCollectionItem(maskCollectionItem, maskStream.mask_stream, streamItemUUID);
						streamCollectionItem = StreamCollectionItem(streamCollection.type, maskStreamItem, itemTypeUUID);
						keyframeCollectionItem = KeyframeCollectionItem(streamCollectionItem, keyframeIndex, keyframeUUID);
						collectionItem = CollectionItemV2(item.type, keyframeCollectionItem, streamProxy, collectionUUID);

						//craft the result
						result = Result<CollectionItemV2>(collectionItem, errToString(err));

						//send the response
						response = Response(result);
						MessageQueueManager::getInstance().sendResponse(response);
						break;
					case AEGP_StreamCollectionItemType_EFFECT:
						SessionManager::GetInstance().addSession(streamCollection, itemTypeUUID); // add the stream item to the session manager

						AEGP_EffectStreamCollectionItem effectStream = streamCollection.u.effect_stream; // get the effect stream item
						AEGP_EffectCollectionItem effectItem = effectStream.effect; // get the effect item
						AEGP_LayerH layerH = effectItem.layerH; // get the layer handle
						AEGP_EffectIndex effectIndex = effectItem.index; // get the effect index
						A_long param_index = effectStream.param_index; // get the param index

						SessionManager::GetInstance().addSession(effectStream, streamItemUUID); // add the effect stream item to the session manager
						SessionManager::GetInstance().addSession(effectItem, streamItemTypeUUID); // add the effect item to the session manager

						ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));

						SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

						//create the proxy objects
						layerProxy = Layer(itemUUID);
						effectCollectionItem = EffectCollectionItem(layerProxy, effectIndex, streamItemTypeUUID);
						effectStreamItem = EffectStreamCollectionItem(effectCollectionItem, param_index, streamItemUUID);
						streamCollectionItem = StreamCollectionItem(streamCollection.type, effectStreamItem, itemTypeUUID);
						keyframeCollectionItem = KeyframeCollectionItem(streamCollectionItem, keyframeIndex, keyframeUUID);
						collectionItem = CollectionItemV2(item.type, keyframeCollectionItem, streamProxy, collectionUUID);

						//craft the result
						result = Result<CollectionItemV2>(collectionItem, errToString(err));

						//send the response
						response = Response(result);
						MessageQueueManager::getInstance().sendResponse(response);
						break;
					case AEGP_StreamCollectionItemType_END:
						break;
				}
				break;
			case AEGP_CollectionItemType_MASK_VERTEX:
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager
				AEGP_MaskVertexCollectionItem maskVertexItem = item.u.mask_vertex; // get the mask vertex item
				AEGP_MaskCollectionItem maskItem = maskVertexItem.mask_sel; // get the mask item
				AEGP_VertexIndex vertexIndex = maskVertexItem.index; // get the vertex index
				SessionManager::GetInstance().addSession(maskVertexItem, itemTypeUUID); // add the mask vertex item to the session manager
				SessionManager::GetInstance().addSession(maskItem, streamItemUUID); // add the mask item to the session manager

				AEGP_LayerH layerH = maskItem.layerH; // get the layer handle
				AEGP_MaskIndex maskIndex = maskItem.index; // get the mask index
				ERR(suites.LayerSuite9()->AEGP_GetLayerID(layerH, &itemUUID));
				SessionManager::GetInstance().addSession(layerH, itemUUID); // add the layer handle to the session manager

				//create the proxy objects
				layerProxy = Layer(itemUUID);
				maskCollectionItem = MaskCollectionItem(layerProxy, maskIndex, streamItemUUID);
				maskVertexCollectionItem = MaskVertexCollectionItem(maskCollectionItem, vertexIndex, itemTypeUUID);
				collectionItem = CollectionItemV2(item.type, maskVertexCollectionItem, streamProxy, collectionUUID);

				//craft the result
				result = Result<CollectionItemV2>(collectionItem, errToString(err));

				//send the response
				response = Response(result);
				MessageQueueManager::getInstance().sendResponse(response);
				break;
			case AEGP_CollectionItemType_STREAMREF:
				SessionManager::GetInstance().addSession(item, collectionUUID); // add the CollectionItemV2 to the session manager
				AEGP_StreamRefH streamRef = item.stream_refH; // get the stream ref
				SessionManager::GetInstance().addSession(streamRef, itemTypeUUID); // add the stream ref to the session manager

				//create the proxy objects
				StreamRef streamRefProxy = StreamRef(itemTypeUUID);
				collectionItem = CollectionItemV2(item.type, streamRefProxy, collectionUUID);

				//craft the result
				result = Result<CollectionItemV2>(collectionItem, errToString(err));

				//send the response
				response = Response(result);
				MessageQueueManager::getInstance().sendResponse(response);
				break;	
		}

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

		Collection2H collection = boost::get<Collection2H>(cmd.args[0]);
		CollectionItemV2 item = boost::get<CollectionItemV2>(cmd.args[1]);
		StreamRef stream = item.streamRef;

		//What we know we have now
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		AEGP_StreamRefH streamH = std::get<AEGP_StreamRefH>(SessionManager::GetInstance().getSession(stream.getSessionID()));

		A_Err err = A_Err_NONE;
		AEGP_LayerH layerH;
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

		Result<null> nullResponse;
		Response response;

		itemH.stream_refH = streamH;

	switch (item.type) {
		case AEGP_CollectionItemType_NONE:
			break;
		case AEGP_CollectionItemType_LAYER:
			itemH.type = AEGP_CollectionItemType_LAYER; //Set the Type, since we already know it's a layer
			//get proxy objects
			layerCollectionItem = boost::get<LayerCollectionItem>(item.u); //get the layer collection item
			layerProxy = layerCollectionItem.layer; //get the layer


			layerItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			itemH.u.layer = layerItem; //set the layer item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));

			nullResponse = Result<null>(null(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_MASK:
			itemH.type = AEGP_CollectionItemType_MASK;
			
			maskCollectionItem = boost::get<MaskCollectionItem>(item.u); //get the mask collection item
			layerProxy = maskCollectionItem.layer; //get the layer
			maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			maskItem.index = maskCollectionItem.index; //get the mask index
			itemH.u.mask = maskItem; //set the mask item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<null>(null(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_EFFECT:
			itemH.type = AEGP_CollectionItemType_EFFECT;
			effectCollectionItem = boost::get<EffectCollectionItem>(item.u); //get the effect collection effectCollectionItem = boost::get<EffectCollectionItem>(item.u); //get the effect collection item
			layerProxy = effectCollectionItem.layer; //get the layer
			effectItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			effectItem.index = effectCollectionItem.index; //get the effect index
			itemH.u.effect = effectItem; //set the effect item

			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<null>(null(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_STREAM:
			itemH.type = AEGP_CollectionItemType_STREAM;
			streamCollectionItem = boost::get<StreamCollectionItem>(item.u); //get the stream collection item
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
			itemH.u.stream = streamItem; //set the stream item
			//push the item
			ERR(suites.CollectionSuite2()->AEGP_CollectionPushBack(collectionH, &itemH));
			nullResponse = Result<null>(null(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_KEYFRAME:

			itemH.type = AEGP_CollectionItemType_KEYFRAME;
			keyframeCollectionItem = boost::get<KeyframeCollectionItem>(item.u); //get the keyframe collection item
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
			nullResponse = Result<null>(null(), errToString(err));

			response = Response(nullResponse);
			break;
		case AEGP_CollectionItemType_MASK_VERTEX:
			itemH.type = AEGP_CollectionItemType_MASK_VERTEX;
			maskVertexCollectionItem = boost::get<MaskVertexCollectionItem>(item.u); //get the mask vertex collection item
			maskCollectionItem = maskVertexCollectionItem.mask; //get the mask
			layerProxy = maskCollectionItem.layer; //get the layer
			maskItem.layerH = std::get<AEGP_LayerH>(SessionManager::GetInstance().getSession(layerProxy.getSessionID())); //get the layer handle
			maskItem.index = maskCollectionItem.index; //set the mask index
			maskVertexItem.mask_sel = maskItem; //set the mask item
			maskVertexItem.index = maskVertexCollectionItem.index; //set the vertex index from the proxy object
			itemH.u.mask_vertex = maskVertexItem; //set the mask vertex item (of the real item)
			nullResponse = Result<null>(null(), errToString(err));

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
		Collection2H collection = boost::get<Collection2H>(cmd.args[0]);
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		Range range = boost::get<Range>(cmd.args[1]);
		int index_first = range.index_firstL;
		int index_last = range.index_lastL;

		ERR(suites.CollectionSuite2()->AEGP_CollectionErase(collectionH, index_first, index_last));

		Result<null> result(null(), errToString(err));
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