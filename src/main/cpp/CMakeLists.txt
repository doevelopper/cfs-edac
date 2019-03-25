
add_library(cfs.edac.main
#    cfs/edac/namedType/Crtp
#    cfs/edac/namedType/internal/NamedTypeInternal
#    cfs/edac/namedType/UnderlyingFunctionalities
#    cfs/edac/namedType/StrongType
#    cfs/edac/callstack/ABIDemangling
#    cfs/edac/private/ErrorCodePrivate
#    cfs/edac/ErrorHandler
#    cfs/edac/ErrorOr
#    cfs/edac/private/ErrorCodeTable
#    cfs/edac/IsErrorActive
    cfs/edac/Exception
#    cfs/edacl/Error
#    cfs/edac/internal/LoggerPrivate
#    cfs/edac/Logger
)

apply_style_targets_command (cfs.edac.main ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cfs.edac.main
    PUBLIC
        $<$<PLATFORM_ID:Linux>:rt>
        $<$<PLATFORM_ID:Linux>:pthread>
        LOG4CXX::LOG4CXX
)

option(EXCLUDE_DEPRECATED "Exclude deprecated parts of the library" TRUE)
if (EXCLUDE_DEPRECATED)
    set(NO_BUILD_DEPRECATED DEFINE_NO_DEPRECATED)
endif()

set_target_properties( cfs.edac.main PROPERTIES
    VERSION
        ${PROJECT_VERSION}
    SOVERSION
        "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

include(GenerateExportHeader)
generate_export_header(cfs.edac.main
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/Export.hpp"
    INCLUDE_GUARD_NAME CFS_EDAC_EXPORT_HPP
    # EXPORT_MACRO_NAME API_DECLS
    #BASE_NAME EDAC 
    #PREFIX_NAME EDAC_
    #STATIC_DEFINE BUILT_AS_STATIC
    DEPRECATED_MACRO_NAME CFS_EDAC_DEPRECATED
    ${NO_BUILD_DEPRECATED}
)

target_compile_definitions(cfs.edac.main
    PRIVATE
        "VERBOSITY=$<IF:$<BOOL:${VERBOSE}>,30,10>"
        $<$<OR:$<CONFIG:Release>,$<CONFIG:Debug>>: -DRELEASE_LEVEL="SNAPSHOOT"> # SNAPSHOOT ,ALPHA , BETA , CANDIDATE , FINAL.
        $<$<CXX_COMPILER_ID:GNU>: NOMINMAX>
        -D_GLIBCXX_SANITIZE_VECTOR

)

target_compile_options(cfs.edac.main
    INTERFACE
        $<$<CONFIG:Debug>:-g3 -O0 -fstack-protector>
        $<$<CONFIG:Release>:-g0 -O2>
        $<$<CXX_COMPILER_ID:GNU>:$<BUILD_INTERFACE:-Wall;-Wextra;-Wpedantic>>
    PUBLIC 
#        $<$<COMPILE_LANGUAGE:CXX>: -W -Wall -Wextra -Weffc++ -Wpedantic -fmax-errors=5 -Werror=reorder -Werror=shadow -fdiagnostics-parseable-fixits>
#        $<$<CONFIG:Debug>: -O0 -g -D_DEBUG -D_FORTIFY_SOURCE=2 -fno-strict-aliasing -fno-omit-frame-pointer>
#        $<$<CONFIG:Release>:-g0 -O2>
#        $<$<CONFIG:Coverage>:-O0 -fprofile-arcs -ftest-coverage --coverage>
#        $<$<CONFIG:Profile>:-fsanitize=memory -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer>

#        -m64
#        $<$<CXX_COMPILER_ID:GNU>: ${GNU_CXX_FLAGS} -U_FORTIFY_SOURCE -fsanitize-address-use-after-scope>
#        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: ${COMMON_CXX_FLAGS}>
#        $<IF:$<COMPILE_LANGUAGE:CXX>,-Wold-style-cast,>

#        $<$<CONFIG:Release>:${MY_RELEASE_OPTIONS}>
#        $<$<CONFIG:Release>:-ffunction-sections>
#        $<$<CONFIG:Release>:-fdata-sections>
#        $<$<CONFIG:Release>:-Wl,--gc-sections>

#        $<$<CONFIG:Debug>: ${MY_DEBUG_OPTIONS}>
#        $<$<CONFIG:Debug>: -O0>
#        $<$<CONFIG:Debug>: -ggdb3>
#        $<$<CONFIG:Debug>: -O0 -g -D_DEBUG -D_FORTIFY_SOURCE=2 -fno-strict-aliasing -fno-omit-frame-pointer>

#        $<IF:$<CONFIG:Debug>: helper_debug.cpp,helper_release.cpp>

#        $<$<OR:$<CONFIG:Release>,$<CONFIG:Profile>>: DISABLE_VAR>
#        $<$<CONFIG:Coverage>: -O0  -fprofile-arcs -ftest-coverage --coverage>

        $<$<CONFIG:Profile>: ${CHECK_MEMORY_FLAGS}>
       
)

target_compile_features(cfs.edac.main
    PUBLIC
        cxx_std_17
        cxx_strong_enums
        cxx_variadic_templates
        cxx_nullptr
        cxx_alias_templates
        cxx_auto_type
        cxx_constexpr
        cxx_defaulted_functions
        cxx_final
        cxx_lambdas
        cxx_noexcept
        cxx_nullptr
        cxx_rvalue_references
        cxx_thread_local
        cxx_variadic_templates
        cxx_override
    PRIVATE
        cxx_lambdas
        cxx_range_for
        $<$<CXX_COMPILER_ID:GNU>:cxx_attributes>
)

target_include_directories(cfs.edac.main
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

# Support find_package(<target> NO_MODULE).

#include(CMakePackageConfigHelpers)
#configure_package_config_file(cfs-edac-config.cmake.in cfs-edac-config.cmake
#    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cfs-edac-${MODULE_VERSION}
#    PATH_VARS 
#        INCLUDE_INSTALL_DIR 
#        SYSCONFIG_INSTALL_DIR
#)

#write_basic_package_version_file(${CMAKE_BINARY_DIR}/cfs-edac-config-version.cmake
#	VERSION ${MODULE_VERSION}
#	COMPATIBILITY ExactVersion
#)

#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cfs-edac-config.cmake 
#    ${CMAKE_CURRENT_BINARY_DIR}/cfs-edac-config-version.cmake
#    DESTINATION ${LIB_INSTALL_DIR}/cfs-edac/cmake 
#)

# To make the component usable not only from the install directory but also from the build directory
#export(
#    TARGETS .main.bin
#    FILE .main.bin-export.cmake
#)

#install (
#    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cfs/osal
#    DESTIATION ${CMAKE_INSTALL_INCLUDEDIR}
#    FILE_MATCHING PATTERN "*.hpp"
#)

#install( TARGETS
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    ARCHIVES DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

#install(
#    FILES
#        ${CMAKE_BINARY_DIR}/l101.main-config.cmake
#        ${CMAKE_BINARY_DIR}/l101.main-config-version.cmake
#    DESTINATION
#        ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}-${MODULE_VERSION}
#    COMPONENT
#        development
#)

#install(EXPORT .main
#	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}-${MODULE_VERSION}
#	NAMESPACE ${PROJECT_NAME}::
#	FILE l101.main-export.cmake
#	COMPONENT development
#)
