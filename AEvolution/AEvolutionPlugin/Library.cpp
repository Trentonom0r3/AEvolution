#include "Library.h"

//
std::string errToString(A_Err err) {
	switch (err) {
	case A_Err_NONE:
		return "None";
	case A_Err_GENERIC:
		return "Encounter a generic error";
	case A_Err_STRUCT:
		return "Encounter a struct error";
	case A_Err_PARAMETER:
		return "Encounter a parameter error";
	case A_Err_ALLOC:
		return "Encounter an allocation error";
	case A_Err_CONST_PROJECT_MODIFICATION:
		return "Encounter a constant project modification error";
	case A_Err_WRONG_THREAD:
		return "Encounter a wrong thread error";
	case A_Err_MISSING_SUITE:
		return "Encounter a missing suite error";
	case A_Err_NOT_IN_CACHE_OR_COMPUTE_PENDING:
		return "Encounter a not in cache or compute pending error";
	case A_Err_PROJECT_LOAD_FATAL:
		return "Encounter a project load fatal error";
	case A_Err_EFFECT_APPLY_FATAL:
		return "Encounter an effect apply fatal error";
	default:
		return "Unknown error";
	}
}
