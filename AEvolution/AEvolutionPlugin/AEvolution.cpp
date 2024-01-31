#include "AEvolution.h"
#include "SessionManager.h"

static AEGP_PluginID		AEvolution = 6969L;
static A_long				S_idle_count = 0L;
static SPBasicSuite* sP = NULL;


static A_Err
DeathHook(
	AEGP_GlobalRefcon	plugin_refconP,
	AEGP_DeathRefcon	refconP)
{
	A_Err	err = A_Err_NONE;

	SessionManager::GetInstance().cleanAll(); //The only thing we need to clean is the SessionManager, because it's a singleton

	return err;
}

static A_Err 
IdleHook(AEGP_GlobalRefcon plugin_refconP, AEGP_IdleRefcon refconP, A_long* max_sleepPL) 
{
	A_Err err = A_Err_NONE;

	auto message = MessageQueue::getInstance().dequeue(); // Get the next message in the queue

	if (message != nullptr) { // If there is a message, execute it
		message->execute(); 
		return err; // Return, so we don't increment the idle count
	}

	return err;
}

A_Err
EntryPointFunc(
	struct SPBasicSuite* pica_basicP,		/* >> */
	A_long				 	major_versionL,		/* >> */
	A_long					minor_versionL,		/* >> */
	AEGP_PluginID			aegp_plugin_id,		/* >> */
	AEGP_GlobalRefcon* global_refconV)	/* << */
{

	AEvolution = aegp_plugin_id;

	A_Err 					err = A_Err_NONE,
							err2 = A_Err_NONE;

	sP = pica_basicP;

	// Initialize the suite managers
	SuiteManager::GetInstance().InitializeSuiteHandler(sP);  // Initialize the suite handler, Singleton pattern

	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler(); // Get the suite handler

	SuiteManager::GetInstance().SetPluginID(&AEvolution); // Set the plugin ID

	SessionManager::GetInstance(); //start the SessionManager, so we can have IPC communication

	ERR(suites.RegisterSuite5()->AEGP_RegisterDeathHook(AEvolution, DeathHook, NULL));  // Register the death hook, for proper cleanup

	ERR(suites.RegisterSuite5()->AEGP_RegisterIdleHook(AEvolution, IdleHook, NULL)); // Register the idleHook, for IPC communication

	if (err) { // not !err, err!
		ERR2(suites.UtilitySuite3()->AEGP_ReportInfo(AEvolution, "AEvolution : Could not register command hook."));
	}

	return err;
}
