#pragma once
#ifdef AEvolution_EXPORTS
#define AEvolution_API __declspec(dllexport)
#else
#define AEvolution_API __declspec(dllimport)
#endif

#include "../../AEvolutionCore/AEvolutionCore/include/Utility.h"
#include "../../AEvolutionCore/AEvolutionCore/include/Core.h"
#include "../../AEvolutionCore/AEvolutionCore/include/UUID.hpp"