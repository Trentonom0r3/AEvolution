#pragma once
#include "../CommandFactory.h"
#include "../SessionManager.h"

class GetCompFromItem : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_CompH compH;

		auto item = boost::get<baseobj>(cmd.args[0]);
		Comp comp;
		int compID = createUUID();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_ItemH itemH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(item->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompFromItem(itemH, &compH));
		if (compH) {
			SessionManager::GetInstance().addSession(compH, compID);
			comp = Comp(compID);
		}
		Result<baseobj> result(boost::make_shared<Comp>(comp), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompFromItem, GetCompFromItem)

/*
Result<Comp> getCompFromItem(Item item) {
	Command cmd(CommandID::GetCompFromItem, { item });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Comp> result = boost::get<Result<Comp>>(response.result);
	return result;
}
*/

class GetItemFromComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_ItemH itemH;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		Item item;
		int itemID;
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetItemFromComp(compH, &itemH));
		if (itemH) {
			ERR(suites.ItemSuite9()->AEGP_GetItemID(itemH, &itemID));
			SessionManager::GetInstance().addSession(itemH, itemID);
			item = Item(itemID);
		}
		Result<baseobj> result(boost::make_shared<Item>(item), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetItemFromComp, GetItemFromComp)

/*
Result<Item> getItemFromComp(Comp comp) {
	Command cmd(CommandID::GetItemFromComp, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Item> result = boost::get<Result<Item>>(response.result);
	return result;
}
*/

class GetCompDownsampleFactor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_DownsampleFactor dsf;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompDownsampleFactor(compH, &dsf));
		DownsampleFactor downsampleFactor(dsf);
		Result<baseobj> result(boost::make_shared<DownsampleFactor>(downsampleFactor), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompDownsampleFactor, GetCompDownsampleFactor)

/*
Result<AEGP_DownsampleFactor> getCompDownsampleFactor(Comp comp) {
	Command cmd(CommandID::GetCompDownsampleFactor, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<AEGP_DownsampleFactor> result = boost::get<Result<AEGP_DownsampleFactor>>(response.result);
	return result;
}
*/

class SetCompDownsampleFactor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		DownsampleFactor dsf = *boost::dynamic_pointer_cast<DownsampleFactor>(boost::get<baseobj>(cmd.args[1]));
		AEGP_DownsampleFactor dsfH = dsf.toAEGP_DownsampleFactor();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompDownsampleFactor(compH, &dsfH));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));//////////////////////////////////////////////////////////////////////////////CONTINUE HERE
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompDownsampleFactor, SetCompDownsampleFactor)

/*
Result<null> setCompDownsampleFactor(Comp comp, AEGP_DownsampleFactor dsf) {
	Command cmd(CommandID::SetCompDownsampleFactor, { comp, dsf });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompBGColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_ColorVal bgColor;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompBGColor(compH, &bgColor));

		Color color(bgColor);
		Result<baseobj> result(boost::make_shared<Color>(color), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompBGColor, GetCompBGColor)

/*
Result<Color> getCompBGColor(Comp comp) {
	Command cmd(CommandID::GetCompBGColor, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Color> result = boost::get<Result<Color>>(response.result);
	return result;
}
*/

class SetCompBGColor : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		Color bgColor = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[1]));
		AEGP_ColorVal bgColorVal = bgColor.toAEGP_ColorVal();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompBGColor(compH, &bgColorVal));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompBGColor, SetCompBGColor)

/*
Result<null> setCompBGColor(Comp comp, Color bgColor) {
	Command cmd(CommandID::SetCompBGColor, { comp, bgColor });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompFlags : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_CompFlags compFlags;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompFlags(compH, &compFlags));

		Result<AEGP_CompFlags> result(compFlags, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompFlags, GetCompFlags)

/*
Result<AEGP_CompFlags> getCompFlags(Comp comp) {
	Command cmd(CommandID::GetCompFlags, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<AEGP_CompFlags> result = boost::get<Result<AEGP_CompFlags>>(response.result);
	return result;
}
*/

class GetShowLayerNameOrSourceName : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Boolean layerNamesShown;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		/* << true if layer names, false if source names */

		ERR(suites.CompSuite11()->AEGP_GetShowLayerNameOrSourceName(compH, &layerNamesShown));

		Result<bool> result(static_cast<bool>(layerNamesShown), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetShowLayerNameOrSourceName, GetShowLayerNameOrSourceName)

/*
Result<bool> getShowLayerNameOrSourceName(Comp comp) {
	Command cmd(CommandID::GetShowLayerNameOrSourceName, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(response.result);
	return result;
}
*/

class SetShowLayerNameOrSourceName : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		bool layerNamesShown = boost::get<bool>(cmd.args[1]);
		A_Boolean layerNamesShownB = static_cast<A_Boolean>(layerNamesShown);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetShowLayerNameOrSourceName(compH, layerNamesShownB));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetShowLayerNameOrSourceName, SetShowLayerNameOrSourceName)

/*
Result<null> setShowLayerNameOrSourceName(Comp comp, bool layerNamesShown) {
	Command cmd(CommandID::SetShowLayerNameOrSourceName, { comp, layerNamesShown });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetShowBlendModes : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Boolean blendModesShown;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		/* << true if blend modes shown, false if hidden */

		ERR(suites.CompSuite11()->AEGP_GetShowBlendModes(compH, &blendModesShown));

		Result<bool> result(static_cast<bool>(blendModesShown), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetShowBlendModes, GetShowBlendModes)

/*
Result<bool> getShowBlendModes(Comp comp) {
	Command cmd(CommandID::GetShowBlendModes, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(response.result);
	return result;
}
*/

class SetShowBlendModes : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		bool blendModesShown = boost::get<bool>(cmd.args[1]);
		A_Boolean blendModesShownB = static_cast<A_Boolean>(blendModesShown);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetShowBlendModes(compH, blendModesShownB));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetShowBlendModes, SetShowBlendModes)

/*
Result<null> setShowBlendModes(Comp comp, bool blendModesShown) {
	Command cmd(CommandID::SetShowBlendModes, { comp, blendModesShown });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompFramerate : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_FpLong fps;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompFramerate(compH, &fps));

		Result<A_FpLong> result(fps, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompFramerate, GetCompFramerate)

/*
Result<A_FpLong> getCompFramerate(Comp comp) {
	Command cmd(CommandID::GetCompFramerate, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<A_FpLong> result = boost::get<Result<A_FpLong>>(response.result);
	return result;
}
*/

class SetCompFramerate : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		A_FpLong fps = boost::get<A_FpLong>(cmd.args[1]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompFrameRate(compH, &fps));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompFramerate, SetCompFramerate)

/*
* Result<null> setCompFramerate(Comp comp, A_FpLong fps) {
	Command cmd(CommandID::SetCompFramerate, { comp, fps });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompShutterAnglePhase : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Ratio angle;
		A_Ratio phase;
		double angleD;
		double phaseD;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompShutterAnglePhase(compH, &angle, &phase));

		angleD = RATIO2DOUBLE(angle);
		phaseD = RATIO2DOUBLE(phase);
		ShutterAnglePhase shutterAnglePhase(angleD, phaseD);
		Result<baseobj> result(boost::make_shared<ShutterAnglePhase>(shutterAnglePhase), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompShutterAnglePhase, GetCompShutterAnglePhase)

/*
Result<ShutterAnglePhase> getCompShutterAnglePhase(Comp comp) {
	Command cmd(CommandID::GetCompShutterAnglePhase, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<ShutterAnglePhase> result = boost::get<Result<ShutterAnglePhase>>(response.result);
	return result;
}
*/


class GetCompSuggestedMotionBlurSamples : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_long samples;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompSuggestedMotionBlurSamples(compH, &samples));

		Result<A_long> result(samples, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompSuggestedMotionBlurSamples, GetCompSuggestedMotionBlurSamples)

/*
Result<A_long> getCompSuggestedMotionBlurSamples(Comp comp) {
	Command cmd(CommandID::GetCompSuggestedMotionBlurSamples, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<A_long> result = boost::get<Result<A_long>>(response.result);
	return result;
}
*/

class SetCompSuggestedMotionBlurSamples : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		A_long samples = boost::get<A_long>(cmd.args[1]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompSuggestedMotionBlurSamples(compH, samples));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompSuggestedMotionBlurSamples, SetCompSuggestedMotionBlurSamples)

/*
Result<null> setCompSuggestedMotionBlurSamples(Comp comp, A_long samples) {
	Command cmd(CommandID::SetCompSuggestedMotionBlurSamples, { comp, samples });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompMotionBlurAdaptiveSampleLimit : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_long samples;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompMotionBlurAdaptiveSampleLimit(compH, &samples));

		Result<A_long> result(samples, errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompMotionBlurAdaptiveSampleLimit, GetCompMotionBlurAdaptiveSampleLimit)

/*
Result<A_long> getCompMotionBlurAdaptiveSampleLimit(Comp comp) {
	Command cmd(CommandID::GetCompMotionBlurAdaptiveSampleLimit, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<A_long> result = boost::get<Result<A_long>>(response.result);
	return result;
}
*/

class SetCompMotionBlurAdaptiveSampleLimit : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		A_long samples = boost::get<A_long>(cmd.args[1]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompMotionBlurAdaptiveSampleLimit(compH, samples));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompMotionBlurAdaptiveSampleLimit, SetCompMotionBlurAdaptiveSampleLimit)

/*
Result<null> setCompMotionBlurAdaptiveSampleLimit(Comp comp, A_long samples) {
	Command cmd(CommandID::SetCompMotionBlurAdaptiveSampleLimit, { comp, samples });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class GetCompWorkAreaStart : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Time start;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompWorkAreaStart(compH, &start));

		Time time(start);
		Result<baseobj> result(boost::make_shared<Time>(time), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompWorkAreaStart, GetCompWorkAreaStart)

/*
Result<Time> getCompWorkAreaStart(Comp comp) {
	Command cmd(CommandID::GetCompWorkAreaStart, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Time> result = boost::get<Result<Time>>(response.result);
	return result;
}
*/

class GetCompWorkAreaDuration : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Time duration;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_GetCompWorkAreaDuration(compH, &duration));

		Time time(duration);
		Result<baseobj> result(boost::make_shared<Time>(time), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompWorkAreaDuration, GetCompWorkAreaDuration)

/*
Result<Time> getCompWorkAreaDuration(Comp comp) {
	Command cmd(CommandID::GetCompWorkAreaDuration, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Time> result = boost::get<Result<Time>>(response.result);
	return result;
}
*/

class SetCompWorkAreaStartAndDuration : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		Time start = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[1]));
		Time duration = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[2]));
		A_Time startT = start.toA_Time();
		A_Time durationT = duration.toA_Time();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));

		ERR(suites.CompSuite11()->AEGP_SetCompWorkAreaStartAndDuration(compH, &startT, &durationT));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompWorkAreaStartAndDuration, SetCompWorkAreaStartAndDuration)

/*
Result<null> setCompWorkAreaStartAndDuration(Comp comp, Time start, Time duration) {
	Command cmd(CommandID::SetCompWorkAreaStartAndDuration, { comp, start, duration });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class CreateSolidInComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Size size = *boost::dynamic_pointer_cast<Size>(boost::get<baseobj>(cmd.args[2]));
		Color color = *boost::dynamic_pointer_cast<Color>(boost::get<baseobj>(cmd.args[3]));
		Time duration = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[4]));

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		A_long width = static_cast<A_long>(size.x);
		A_long height = static_cast<A_long>(size.y);
		AEGP_ColorVal pixelColor = color.toAEGP_ColorVal();
		A_Time durationT = duration.toA_Time();
		AEGP_LayerH solidH;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		AEGP_LayerIDVal layerID;


		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateSolidInComp(nameV.data(), width, height, &pixelColor, compH, &durationT, &solidH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(solidH, &layerID));

		Layer layer(layerID);
		SessionManager::GetInstance().addSession(solidH, layerID);
		Result<baseobj> result(boost::make_shared<Layer>(layer), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateSolidInComp, CreateSolidInComp)

/*
Result<Layer> createSolidInComp(Comp comp, std::string name, Size size, Color color, Time duration) {
	Command cmd(CommandID::CreateSolidInComp, { comp, name, size, color, duration });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class CreateCameraInComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Point centerPoint = *boost::dynamic_pointer_cast<Point>(boost::get<baseobj>(cmd.args[2]));

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH cameraH;
		AEGP_LayerIDVal layerID;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_FloatPoint centerPointF = centerPoint.toA_FloatPoint();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateCameraInComp(nameV.data(), centerPointF, compH, &cameraH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(cameraH, &layerID));

		Layer camera(layerID);

		SessionManager::GetInstance().addSession(cameraH, camera.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(camera), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateCameraInComp, CreateCameraInComp)

/*
Result<Layer> createCameraInComp(Comp comp, std::string name, Point centerPoint) {
	Command cmd(CommandID::CreateCameraInComp, { comp, name, centerPoint });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class CreateLightInComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Point centerPoint = *boost::dynamic_pointer_cast<Point>(boost::get<baseobj>(cmd.args[2]));

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH lightH;
		AEGP_LayerIDVal layerID;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_FloatPoint centerPointF = centerPoint.toA_FloatPoint();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateLightInComp(nameV.data(), centerPointF, compH, &lightH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(lightH, &layerID));

		Layer light(layerID);

		SessionManager::GetInstance().addSession(lightH, light.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(light), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateLightInComp, CreateLightInComp)

/*
Result<Layer> createLightInComp(Comp comp, std::string name, Point centerPoint) {
	Command cmd(CommandID::CreateLightInComp, { comp, name, centerPoint });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class CreateNullInComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Time time = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[2]));

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH nullH;
		AEGP_LayerIDVal layerID;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_Time timeT = time.toA_Time();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateNullInComp(nameV.data(), compH, &timeT, &nullH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(nullH, &layerID));

		Layer null(layerID);

		SessionManager::GetInstance().addSession(nullH, null.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(null), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateNullInComp, CreateNullInComp)

/*
Result<Layer> createNullInComp(Comp comp, std::string name, Point centerPoint) {
	Command cmd(CommandID::CreateNullInComp, { comp, name, centerPoint });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class CreateComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		//first, get the required args.
		auto parentFolder = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Size size = *boost::dynamic_pointer_cast<Size>(boost::get<baseobj>(cmd.args[2]));
		AspectRatio aspectRatio = *boost::dynamic_pointer_cast<AspectRatio>(boost::get<baseobj>(cmd.args[3]));
		Time duration = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[4]));
		Ratio fps = *boost::dynamic_pointer_cast<Ratio>(boost::get<baseobj>(cmd.args[5]));

		//define the AE SDK args
		A_Err err = A_Err_NONE;
		AEGP_ItemH parentFolderH;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_long width = static_cast<A_long>(size.x);
		A_long height = static_cast<A_long>(size.y);
		A_Ratio pixelAspectRatio = aspectRatio.toA_Ratio();
		A_Time durationT = duration.toA_Time();
        A_Ratio fpsR = fps.toA_Ratio();
		AEGP_CompH compH;
		int compID = createUUID();

		if (!parentFolder->isValid()) {
			parentFolderH = nullptr;
		}
		else {
			parentFolderH = std::get<AEGP_ItemH>(SessionManager::GetInstance().getSession(parentFolder->getSessionID()));
		}

		//get the AE SDK suites
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

		ERR(suites.CompSuite11()->AEGP_CreateComp(parentFolderH, nameV.data(), width, height, &pixelAspectRatio, &durationT, &fpsR, &compH));
		//create a new comp object
		Comp comp(compID);
		//add the comp to the session manager
		SessionManager::GetInstance().addSession(compH, compID);
		//create a result object
		Result<baseobj> result(boost::make_shared<Comp>(comp), errToString(err));
		//create a response object
		Response response(result);
		//send the response
		MessageQueueManager::getInstance().sendResponse(response);

	}
};
REGISTER_COMMAND(CommandID::CreateComp, CreateComp)

/*
Result<Comp> createComp(Folder parentFolder, std::string name, Size size, AspectRatio aspectRatio, Time duration, Ratio fps) {
	Command cmd(CommandID::CreateComp, { parentFolder, name, size, aspectRatio, duration, fps });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Comp> result = boost::get<Result<Comp>>(response.result);
	return result;
}
*/

class GetCompDisplayStartTime : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		A_Time time;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		ERR(suites.CompSuite11()->AEGP_GetCompDisplayStartTime(compH, &time));

		Time displayStartTime(time);
		Result<baseobj> result(boost::make_shared<Time>(displayStartTime), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompDisplayStartTime, GetCompDisplayStartTime)

/*
Result<Time> getCompDisplayStartTime(Comp comp) {
	Command cmd(CommandID::GetCompDisplayStartTime, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Time> result = boost::get<Result<Time>>(response.result);
	return result;
}
*/

class SetCompDisplayStartTime : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		Time time = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[1]));
		A_Time timeT = time.toA_Time();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		ERR(suites.CompSuite11()->AEGP_SetCompDisplayStartTime(compH, &timeT));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompDisplayStartTime, SetCompDisplayStartTime)

/*
Result<null> setCompDisplayStartTime(Comp comp, Time time) {
	Command cmd(CommandID::SetCompDisplayStartTime, { comp, time });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class SetCompDuration : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		Time duration = *boost::dynamic_pointer_cast<Time>(boost::get<baseobj>(cmd.args[1]));
		A_Time durationT = duration.toA_Time();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		ERR(suites.CompSuite11()->AEGP_SetCompDuration(compH, &durationT));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompDuration, SetCompDuration)

/*
Result<null> setCompDuration(Comp comp, Time duration) {
	Command cmd(CommandID::SetCompDuration, { comp, duration });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class SetCompPixelAspectRatio : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;

		auto comp = boost::get<baseobj>(cmd.args[0]);
		AspectRatio aspectRatio = *boost::dynamic_pointer_cast<AspectRatio>(boost::get<baseobj>(cmd.args[1]));
		A_Ratio aspectRatioR = aspectRatio.toA_Ratio();
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		ERR(suites.CompSuite11()->AEGP_SetCompPixelAspectRatio(compH, &aspectRatioR));
		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompPixelAspectRatio, SetCompPixelAspectRatio)

/*
* Result<null> setCompPixelAspectRatio(Comp comp, AspectRatio aspectRatio) {
	Command cmd(CommandID::SetCompPixelAspectRatio, { comp, aspectRatio });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class CreateTextLayerInComp : public CommandBase {
public:
	using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		bool selectNewLayer = boost::get<bool>(cmd.args[2]);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH textLayerH;
		AEGP_LayerIDVal layerID;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_Boolean selectNewLayerB = static_cast<A_Boolean>(selectNewLayer);

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateTextLayerInComp(compH, selectNewLayerB, &textLayerH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(textLayerH, &layerID));

		Layer textLayer(layerID);

		SessionManager::GetInstance().addSession(textLayerH, textLayer.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(textLayer), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateTextLayerInComp, CreateTextLayerInComp)

/*
Result<Layer> createTextLayerInComp(Comp comp, std::string name, bool selectNewLayer) {
	Command cmd(CommandID::CreateTextLayerInComp, { comp, name, selectNewLayer });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class CreateBoxTextLayerInComp : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		std::string name = boost::get<std::string>(cmd.args[1]);
		Point boxDimensions = *boost::dynamic_pointer_cast<Point>(boost::get<baseobj>(cmd.args[2]));
		bool selectNewLayer = boost::get<bool>(cmd.args[3]);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH textLayerH;
		AEGP_LayerIDVal layerID;
		std::vector<A_UTF16Char> nameV = convertUTF8ToUTF16(name);
		A_FloatPoint boxDimensionsF = boxDimensions.toA_FloatPoint();
		A_Boolean selectNewLayerB = static_cast<A_Boolean>(selectNewLayer);

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateBoxTextLayerInComp(compH, selectNewLayerB, boxDimensionsF, &textLayerH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(textLayerH, &layerID));

		Layer textLayer(layerID);

		SessionManager::GetInstance().addSession(textLayerH, textLayer.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(textLayer), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateBoxTextLayerInComp, CreateBoxTextLayerInComp)

/*
Result<Layer> createBoxTextLayerInComp(Comp comp, std::string name, Point boxDimensions, bool selectNewLayer) {
	Command cmd(CommandID::CreateBoxTextLayerInComp, { comp, name, boxDimensions, selectNewLayer });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class SetCompDimensions : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		Size size = *boost::dynamic_pointer_cast<Size>(boost::get<baseobj>(cmd.args[1]));
		A_long width = static_cast<A_long>(size.x);
		A_long height = static_cast<A_long>(size.y);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_SetCompDimensions(compH, width, height));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompDimensions, SetCompDimensions)

/*
Result<null> setCompDimensions(Comp comp, Size size) {
	Command cmd(CommandID::SetCompDimensions, { comp, size });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

class DuplicateComp : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_CompH newCompH;
		int newCompID = createUUID();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_DuplicateComp(compH, &newCompH));

		Comp newComp(newCompID);
		SessionManager::GetInstance().addSession(newCompH, newCompID);
		Result<baseobj> result(boost::make_shared<Comp>(newComp), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::DuplicateComp, DuplicateComp)

/*
Result<Comp> duplicateComp(Comp comp) {
	Command cmd(CommandID::DuplicateComp, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Comp> result = boost::get<Result<Comp>>(response.result);
	return result;
}
*/

class GetCompFrameDuration : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		A_Time time;
		A_Err err = A_Err_NONE;

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_GetCompFrameDuration(compH, &time));

		Time frameDuration(time);
		Result<baseobj> result(boost::make_shared<Time>(frameDuration), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompFrameDuration, GetCompFrameDuration)

/*
Result<Time> getCompFrameDuration(Comp comp) {
	Command cmd(CommandID::GetCompFrameDuration, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Time> result = boost::get<Result<Time>>(response.result);
	return result;
}
*/

class GetMostRecentlyUsedComp : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_CompH compH;
		int compID = createUUID();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_GetMostRecentlyUsedComp(&compH));

		Comp comp(compID);
		SessionManager::GetInstance().addSession(compH, compID);
		Result<baseobj> result(boost::make_shared<Comp>(comp), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetMostRecentlyUsedComp, GetMostRecentlyUsedComp)

/*
Result<Comp> getMostRecentlyUsedComp() {
	Command cmd(CommandID::GetMostRecentlyUsedComp, {});
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Comp> result = boost::get<Result<Comp>>(response.result);
	return result;
}
*/

class CreateVectorLayerInComp : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;
		AEGP_LayerH vectorLayerH;
		AEGP_LayerIDVal layerID;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_CreateVectorLayerInComp(compH, &vectorLayerH));
		ERR(suites.LayerSuite9()->AEGP_GetLayerID(vectorLayerH, &layerID));

		Layer vectorLayer(layerID);

		SessionManager::GetInstance().addSession(vectorLayerH, vectorLayer.getSessionID());
		Result<baseobj> result(boost::make_shared<Layer>(vectorLayer), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::CreateVectorLayerInComp, CreateVectorLayerInComp)

/*
Result<Layer> createVectorLayerInComp(Comp comp) {
	Command cmd(CommandID::CreateVectorLayerInComp, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Layer> result = boost::get<Result<Layer>>(response.result);
	return result;
}
*/

class GetNewCompMarkerStream : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		A_Err err = A_Err_NONE;
		AEGP_StreamRefH streamH;
		int streamID = createUUID();

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_GetNewCompMarkerStream(0, nullptr, &streamH));

		StreamRef stream(streamID);
		SessionManager::GetInstance().addSession(streamH, streamID);
		Result<baseobj> result(boost::make_shared<StreamRef>(stream), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetNewCompMarkerStream, GetNewCompMarkerStream)

/*
Result<StreamRef> getNewCompMarkerStream() {
	Command cmd(CommandID::GetNewCompMarkerStream, {});
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<StreamRef> result = boost::get<Result<StreamRef>>(response.result);
	return result;
}
*/

class GetCompDisplayDropFrame : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		A_Boolean dropFrame;
		A_Err err = A_Err_NONE;

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_GetCompDisplayDropFrame(compH, &dropFrame));

		Result<bool> result(static_cast<bool>(dropFrame), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetCompDisplayDropFrame, GetCompDisplayDropFrame)

/*
Result<bool> getCompDisplayDropFrame(Comp comp) {
	Command cmd(CommandID::GetCompDisplayDropFrame, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<bool> result = boost::get<Result<bool>>(response.result);
	return result;
}
*/

class SetCompDisplayDropFrame : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		bool dropFrame = boost::get<bool>(cmd.args[1]);
		A_Boolean dropFrameB = static_cast<A_Boolean>(dropFrame);

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		A_Err err = A_Err_NONE;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_SetCompDisplayDropFrame(compH, dropFrameB));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetCompDisplayDropFrame, SetCompDisplayDropFrame)

/*
Result<null> setCompDisplayDropFrame(Comp comp, bool dropFrame) {
	Command cmd(CommandID::SetCompDisplayDropFrame, { comp, dropFrame });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.result);
	return result;
}
*/

/*	SPAPI A_Err	(*AEGP_GetNewCollectionFromCompSelection)(
						AEGP_PluginID		plugin_id,				/* >> 
	AEGP_CompH			compH,					/* >> 
	AEGP_Collection2H* collectionPH);			/* << /

	SPAPI A_Err(*AEGP_SetSelection)(
		AEGP_CompH			compH,					/* >> /
		AEGP_Collection2H	collectionH);			/* >> not adopted /
*/

class GetNewCollectionFromCompSelection : public CommandBase {
public:
using CommandBase::CommandBase;

	void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		AEGP_Collection2H collectionH;
		A_Err err = A_Err_NONE;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		ERR(suites.CompSuite11()->AEGP_GetNewCollectionFromCompSelection(0, compH, &collectionH));

		Collection2H collection(createUUID());
		SessionManager::GetInstance().addSession(collectionH, collection.getSessionID());
		Result<baseobj> result(boost::make_shared<Collection2H>(collection), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::GetNewCollectionFromCompSelection, GetNewCollectionFromCompSelection)

/*
Result<Collection2H> getNewCollectionFromCompSelection(Comp comp) {
	Command cmd(CommandID::GetNewCollectionFromCompSelection, { comp });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<Collection2H> result = boost::get<Result<Collection2H>>(response.result);
	return result;
}
*/

class SetSelection : public CommandBase {
public:
	using CommandBase::CommandBase;

void execute() override {
		auto comp = boost::get<baseobj>(cmd.args[0]);
		Collection2H collection = *boost::dynamic_pointer_cast<Collection2H>(boost::get<baseobj>(cmd.args[1]));

		AEGP_CompH compH = std::get<AEGP_CompH>(SessionManager::GetInstance().getSession(comp->getSessionID()));
		AEGP_Collection2H collectionH = std::get<AEGP_Collection2H>(SessionManager::GetInstance().getSession(collection.getSessionID()));
		A_Err err = A_Err_NONE;

		AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();
		ERR(suites.CompSuite11()->AEGP_SetSelection(compH, collectionH));

		Result<baseobj> result(boost::make_shared<null>(), errToString(err));
		Response response(result);
		MessageQueueManager::getInstance().sendResponse(response);
	}
};
REGISTER_COMMAND(CommandID::SetSelection, SetSelection)

/*
Result<null> setSelection(Comp comp, Collection2H collection) {
	Command cmd(CommandID::SetSelection, { comp, collection });
	Response response = MessageQueueManager::getInstance().sendAndReceive(cmd);
	Result<null> result = boost::get<Result<null>>(response.args[0]);
	return result;
}
*/
