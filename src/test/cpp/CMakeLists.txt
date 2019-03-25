
add_library(cfs.edac.test
   cfs/edac/Test
)

apply_style_targets_command(cfs.edac.test ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(cfs.edac.test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

target_compile_definitions(cfs.edac.test PUBLIC
    ${TEST_BUILD_OPTIONS}
#    $<$<OR:$<CONFIG:Release>,$<CONFIG:Profiling>>:DISABLE_CONF>
)

target_link_libraries(cfs.edac.test 
    PUBLIC 
        cfs.edac.main
        GMock::GMock
        GTest::GTest
)

add_executable(cfs.edac.test.bin
    cfs/edac/unitTest
    cfs/edac/ExceptionTest
#    cfs/edac/ErrorCodePrivateTest
#    cfs/edac/ErrorCodePrivateTest
#    cfs/edac/namedType/NamedTypeTest
#    cfs/edac/callstack/ABIDemanglingTest
)

target_link_libraries (cfs.edac.test.bin
    PUBLIC
        cfs.edac.test
)

gtest_discover_tests(cfs.edac.test.bin
    TEST_PREFIX "CFS-EDAC:-: "
    TEST_SUFFIX ----
    PROPERTIES LABELS CFS_EDAC TEST
    DISCOVERY_TIMEOUT 10
    EXTRA_ARGS --iterration 1 --outputpath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --module edac.test
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
