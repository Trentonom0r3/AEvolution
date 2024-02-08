
#include "AEvolution.h"

static AEGP_Command			S_AEvolution_cmd		=	0L;
static AEGP_PluginID		S_my_id				=	0L;
static A_long				S_idle_count		=	0L;
static SPBasicSuite			*sP					=	NULL;


static A_Err
DeathHook(
	AEGP_GlobalRefcon	plugin_refconP,
	AEGP_DeathRefcon	refconP)
{
	A_Err	err			= A_Err_NONE;
	AEGP_SuiteHandler	suites(sP);

	SessionManager::GetInstance().cleanAll();

	return err;
}

static	A_Err	
IdleHook(
	AEGP_GlobalRefcon	plugin_refconP,	
	AEGP_IdleRefcon		refconP,		
	A_long				*max_sleepPL)
{
	A_Err	err			= A_Err_NONE;

	if (SessionManager::GetInstance().areCommandsAvailable()) {
		auto command = SessionManager::GetInstance().popCommand();
		command->execute();
		return err;
	}

	return err;
}

A_Err
EntryPointFunc(
	struct SPBasicSuite		*pica_basicP,		/* >> */
	A_long				 	major_versionL,		/* >> */		
	A_long					minor_versionL,		/* >> */		
	AEGP_PluginID			aegp_plugin_id,		/* >> */
	AEGP_GlobalRefcon		*global_refconV)	/* << */
{
	S_my_id										= aegp_plugin_id;
	A_Err 					err 				= A_Err_NONE, 
							err2 				= A_Err_NONE;
	
	sP = pica_basicP;
	
	// Initialize the suite managers
	SuiteManager::GetInstance().InitializeSuiteHandler(sP);  // Initialize the suite handler, Singleton pattern
	SuiteManager::GetInstance().SetPluginID(&S_my_id);  // Set the plugin ID, Singleton pattern
	SessionManager::GetInstance();  // Initialize the session manager, Singleton pattern

	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();  // Get the suite handler, Singleton pattern

	ERR(suites.RegisterSuite5()->AEGP_RegisterDeathHook(	S_my_id, DeathHook,	NULL));

	ERR(suites.RegisterSuite5()->AEGP_RegisterIdleHook(S_my_id, IdleHook, NULL));

	if (err){ // not !err, err!
		ERR2(suites.UtilitySuite3()->AEGP_ReportInfo(S_my_id, "AEvolution : Could not register command hook."));
	}
	return err;
}
			  
			  
