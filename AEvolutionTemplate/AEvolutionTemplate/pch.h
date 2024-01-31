// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.
#pragma once
#ifndef PCH_H
#define PCH_H


// add headers that you want to pre-compile here
#include "framework.h"
#include <filesystem>
// add headers that you want to pre-compile here
#include "framework.h"
#include <string>
#include <vector>
#include <map>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include "..\..\AEvolutionCore\AEvolutionCore\include\App.h"
#include "..\..\AEvolutionCore\AEvolutionCore\include\Project.h"
#include "..\..\AEvolutionCore\AEvolutionCore\include\ItemManager.h"
#include "..\..\AEvolutionCore\AEvolutionCore\include\MessageQueue.h"
#include "..\..\AEvolutionCore\AEvolutionCore\include\UUID.hpp"

#endif //PCH_H
