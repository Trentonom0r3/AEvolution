cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(AEvolution CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME AEvolution)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../AEvolution.cpp"
    "../SessionManager.cpp"
)
source_group("" FILES ${no_group_source_files})

set(CoreLib
    "../CoreLib/App.cpp"
    "../CoreLib/App.h"
    "../CoreLib/ItemManager.cpp"
    "../CoreLib/ItemManager.h"
    "../CoreLib/Project.cpp"
    "../CoreLib/Project.h"
    "../Library.h"
)
source_group("CoreLib" FILES ${CoreLib})

set(CoreSDK
    "../CoreSDK/CollectionSuites.cpp"
    "../CoreSDK/CollectionSuites.h"
    "../CoreSDK/CompSuites.cpp"
    "../CoreSDK/CompSuites.h"
    "../CoreSDK/Core.cpp"
    "../CoreSDK/Core.h"
    "../CoreSDK/EffectSuites.cpp"
    "../CoreSDK/EffectSuites.h"
    "../CoreSDK/FootageSuites.cpp"
    "../CoreSDK/FootageSuites.h"
    "../CoreSDK/ItemSuites.cpp"
    "../CoreSDK/ItemSuites.h"
    "../CoreSDK/LayerSuites.cpp"
    "../CoreSDK/LayerSuites.h"
    "../CoreSDK/MarkerSuites.cpp"
    "../CoreSDK/MarkerSuites.h"
    "../CoreSDK/MessageQueue.h"
    "../CoreSDK/PanelSuites.cpp"
    "../CoreSDK/PanelSuites.h"
    "../CoreSDK/ProjectSuites.cpp"
    "../CoreSDK/ProjectSuites.h"
    "../CoreSDK/PT_Err.h"
    "../CoreSDK/RenderOptionsSuites.cpp"
    "../CoreSDK/RenderOptionsSuites.h"
    "../CoreSDK/RenderSuites.cpp"
    "../CoreSDK/RenderSuites.h"
    "../CoreSDK/SuiteManager.h"
    "../CoreSDK/TaskUtils.h"
    "../CoreSDK/UtilitySuites.cpp"
    "../CoreSDK/UtilitySuites.h"
    "../CoreSDK/Utils.h"
    "../CoreSDK/WorldSuites.cpp"
    "../CoreSDK/WorldSuites.h"
)
source_group("CoreSDK" FILES ${CoreSDK})

set(Headers
    "../AEvolution.h"
    "../Commands.h"
    "../SessionManager.h"
    "../UUID.hpp"
)
source_group("Headers" FILES ${Headers})

set(Headers__AE
    "../../../Headers/A.h"
    "../../../Headers/AE_AdvEffectSuites.h"
    "../../../Headers/AE_Effect.h"
    "../../../Headers/AE_EffectCB.h"
    "../../../Headers/AE_EffectCBSuites.h"
    "../../../Headers/AE_EffectSuites.h"
    "../../../Headers/AE_EffectSuitesHelper.h"
    "../../../Headers/AE_EffectUI.h"
    "../../../Headers/AE_GeneralPlug.h"
    "../../../Headers/AE_GeneralPlugOld.h"
    "../../../Headers/AE_Hook.h"
    "../../../Headers/AE_IO.h"
    "../../../Headers/AE_Macros.h"
    "../../../Headers/FIEL_Public.h"
    "../../../Headers/PF_Masks.h"
    "../../../Headers/PR_Public.h"
    "../../../Util/AEGP_SuiteHandler.h"
    "../../../Util/entry.h"
    "../../../Util/String_Utils.h"
)
source_group("Headers\\AE" FILES ${Headers__AE})

set(PyUtils
    "../PyUtils/MessageManager.h"
)
source_group("PyUtils" FILES ${PyUtils})

set(Resources
    "../AEvolution_PiPL.r"
)
source_group("Resources" FILES ${Resources})

set(Supporting_Code
    "../../../Util/AEGP_SuiteHandler.cpp"
    "../../../Util/MissingSuiteError.cpp"
)
source_group("Supporting Code" FILES ${Supporting_Code})

set(ALL_FILES
    ${no_group_source_files}
    ${CoreLib}
    ${CoreSDK}
    ${Headers}
    ${Headers__AE}
    ${PyUtils}
    ${Resources}
    ${Supporting_Code}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AEvolution)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "debug${TARGET_NAME}$ENV{TargetExt}"
    TARGET_NAME_RELEASE "release${TARGET_NAME}$ENV{TargetExt}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "C:/Users/tjerf/source/repos/AEvolution/dist/debugdist"
    OUTPUT_DIRECTORY_RELEASE "C:/Users/tjerf/source/repos/AEvolution/dist/releasedist"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DEBUG   "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE "${TARGET_NAME}"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PDB_OUTPUT_DIRECTORY         "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../Headers/Win"
    ">"
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../Headers/adobesdk"
    ">"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../vcpkg/installed/x64-windows-static/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Headers;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Headers/SP;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Util;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Resources"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "MSWindows;"
    "WIN32;"
    "_WINDOWS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            /O2
        >
        /std:c++17;
        /W3;
        /WX-;
        /Zi;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL
        >
        /NOLOGO;
        /MACHINE:X64;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_atomic-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_chrono-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_container-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_context-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_contract-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_coroutine-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_date_time-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_exception-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_fiber-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_filesystem-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_graph-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_iostreams-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_json-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_locale-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_log_setup-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_log-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_c99f-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_c99l-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_c99-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_tr1f-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_tr1l-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_math_tr1-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_nowide-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_program_options-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_random-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_regex-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_serialization-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_stacktrace_noop-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_stacktrace_windbg_cached-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_stacktrace_windbg-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_system-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_thread-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_timer-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_type_erasure-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_unit_test_framework-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_url-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_wave-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_wserialization-vc140-mt-gd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\bz2d.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\libexpatdMT.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\lzma.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\zlibd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\zstd.lib""
    ">"
    "$<$<CONFIG:Release>:"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_unit_test_framework-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_stacktrace_windbg_cached-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_stacktrace_windbg-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_stacktrace_noop-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_program_options-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_type_erasure-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\libexpatMT.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_nowide-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_log_setup-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_log-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_locale-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_json-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_iostreams-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\zstd.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\zlib.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\lzma.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\bz2.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_graph-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_fiber-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_c99f-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_c99l-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_c99-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_tr1f-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_tr1l-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_math_tr1-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_contract-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_random-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_filesystem-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_coroutine-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_context-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_serialization-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_wserialization-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_thread-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_date_time-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_container-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_chrono-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_system-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_atomic-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_exception-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_regex-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_wave-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_url-vc140-mt.lib";"
        ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_timer-vc140-mt.lib""
    ">"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:"
        "C:/Users/tjerf/vcpkg/installed/x64-windows-static/debug/lib"
    ">"
    "$<$<CONFIG:Release>:"
        "C:/Users/tjerf/vcpkg/installed/x64-windows-static/lib"
    ">"
)

