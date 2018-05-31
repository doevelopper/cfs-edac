
add_library(edac.main
    cfs/edac/callstack/ABIDemangling
    cfs/edac/private/ErrorCodePrivate
    cfs/edac/ErrorHandler
    cfs/edac/ErrorOr
    cfs/edac/private/ErrorCodeTable
    cfs/edac/IsErrorActive
    cfs/edac/Exception
    cfs/edac/private/LoggerPrivate
    cfs/edac/Logger
)

target_link_libraries(edac.main
    PUBLIC
        LOG4CXX::LOG4CXX
)

option(EXCLUDE_DEPRECATED "Exclude deprecated parts of the library" TRUE)
if (EXCLUDE_DEPRECATED)
    set(NO_BUILD_DEPRECATED DEFINE_NO_DEPRECATED)
endif()

include(GenerateExportHeader)
generate_export_header(edac.main
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/Export.hpp"
    INCLUDE_GUARD_NAME CFS_EDAC_EXPORT_HPP
    # EXPORT_MACRO_NAME API_DECLS
    #BASE_NAME EDAC 
    #PREFIX_NAME EDAC_
    #STATIC_DEFINE BUILT_AS_STATIC
    DEPRECATED_MACRO_NAME CFS_EDAC_DEPRECATED
    ${NO_BUILD_DEPRECATED}
)

target_compile_options(edac.main 
    INTERFACE
        #-std=c++17
        $<$<CONFIG:Debug>:-g3 -O0 -fstack-protector>
        $<$<CONFIG:Release>:-g0 -O2>
    PUBLIC 
        $<$<COMPILE_LANGUAGE:CXX>: -W -Wall -Wextra -Weffc++ -Wpedantic -fmax-errors=5 -Werror=shadow -fdiagnostics-parseable-fixits>
        $<$<CONFIG:Debug>: -O0 -g -D_DEBUG -D_FORTIFY_SOURCE=2 -fno-strict-aliasing -fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-g0 -O2>
        $<$<CONFIG:Coverage>:-O0  -fprofile-arcs -ftest-coverage --coverage>
        $<$<CONFIG:Profile>:-fsanitize=memory -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer>
       
)

target_compile_features(edac.main
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

target_include_directories(edac.main
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

if(NOT TARGET EDAC-MAIN::EDAC-MAIN)
    add_library(EDAC-MAIN::EDAC-MAIN UNKNOWN IMPORTED)
    set_target_properties(EDAC-MAIN::EDAC-MAIN PROPERTIES
        # EXCLUDE_FROM_ALL 1
        INTERFACE_COMPILE_DEFINITIONS "${EDAC_MAIN_DEFINITIONS}"
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_INSTALL_LIBDIR}/edac.main.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/edac"
        INTERFACE_LINK_LIBRARIES "LOG4CXX::LOG4CXX"
    )
endif(NOT TARGET EDAC-MAIN::EDAC-MAIN)


