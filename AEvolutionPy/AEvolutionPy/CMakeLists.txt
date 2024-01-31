set(PROJECT_NAME AEvolutionPy)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "framework.h"
    "pch.h"
    "PyCore.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "pch.cpp"
    "PyCore.cpp"
    "Source.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AEvolutionPy)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "C:/Users/tjerf/source/repos/AEvolution/dist/debug"
        OUTPUT_DIRECTORY_RELEASE "C:/Users/tjerf/source/repos/AEvolution/dist/release"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebug
        >
        $<$<CONFIG:Release>:
            MultiThreaded
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../AEvolutionCore/AEvolutionCore/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../Program Files/Python312/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../vcpkg/installed/x64-windows-static/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "AEVOLUTIONPY_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "AEVOLUTIONPY_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /std:c++17;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_url-vc140-mt-gd.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_wave-vc140-mt-gd.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\boost_wserialization-vc140-mt-gd.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\bz2d.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\libexpatdMT.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\lzma.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\zlibd.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\debug\lib\zstd.lib";"
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
            ""C:\Program Files\Python312\libs\python3_d.lib";"
            ""C:\Users\tjerf\source\repos\AEvolution\dist\debug\AEvolutionCore.lib""
        ">"
        "$<$<CONFIG:Release>:"
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
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_timer-vc140-mt.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_unit_test_framework-vc140-mt.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_stacktrace_windbg_cached-vc140-mt.lib";"
            ""C:\Users\tjerf\vcpkg\installed\x64-windows-static\lib\boost_stacktrace_windbg-vc140-mt.lib";"
            ""C:\Program Files\Python312\libs\python3.lib";"
            ""C:\Users\tjerf\source\repos\AEvolution\dist\release\AEvolutionCore.lib""
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "C:/Users/tjerf/vcpkg/installed/x64-windows-static/debug/lib;"
            "C:/Users/tjerf/source/repos/AEvolution/dist/debug"
        ">"
        "$<$<CONFIG:Release>:"
            "C:/Users/tjerf/source/repos/AEvolution/dist/release;"
            "C:/Users/tjerf/vcpkg/installed/x64-windows-static/lib"
        ">"
        "C:/Program Files/Python312/libs"
    )
endif()

