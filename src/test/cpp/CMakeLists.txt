
add_executable(cfs.edac.test.bin
    cfs/edac/Test
    cfs/edac/unitTest
    cfs/edac/ExceptionTest
#    cfs/edac/ErrorCodePrivateTest
#    cfs/edac/ErrorCodePrivateTest
#    cfs/edac/namedType/NamedTypeTest
#    cfs/edac/callstack/ABIDemanglingTest
)

#add_library(cfs.edac.test
#    cfs/edac/unitTest
#)

apply_style_targets_command(cfs.edac.test.bin ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(cfs.edac.test.bin
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cfs/edac>
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/cfs/edac>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cfs/edac>
)

target_compile_definitions(cfs.edac.test.bin PUBLIC
    ${TEST_BUILD_OPTIONS}
#    $<$<OR:$<CONFIG:Release>,$<CONFIG:Profiling>>:DISABLE_CONF>
)

target_link_libraries(cfs.edac.test.bin
    PUBLIC
        cfs.edac.main
        GMock::GMock
        GTest::GTest
)


#target_link_libraries (cfs.edac.test.bin
#    PUBLIC
#        cfs.edac.test
#)

gtest_discover_tests(cfs.edac.test.bin
    TEST_PREFIX "CFS-EDAC:-: "
    TEST_SUFFIX ----
    PROPERTIES LABELS CFS_EDAC TEST
    DISCOVERY_TIMEOUT 10
    EXTRA_ARGS --iterration 1 --outputpath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --module edac.test
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
