
add_library(cfs.edac.test
   cfs/edac/Test
   cfs/edac/ErrorCodePrivateTest
   #cfs/edac/namedType/NamedTypeTest
   cfs/edac/callstack/ABIDemanglingTest
)

target_include_directories(cfs.edac.test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

target_link_libraries(cfs.edac.test 
    PUBLIC 
        cfs.edac.main
        GMock::GMock
        GTest::GTest
)

add_executable(cfs.edac.test.bin
    cfs/edac/ErrorCodePrivateTest
    cfs/edac/unitTest
)

target_link_libraries (cfs.edac.test.bin
    PUBLIC
        cfs.edac.test
#        LOG4CXX::LOG4CXX
)

#gtest_discover_tests(cppbdd101.edac.test.bin
#    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#    TEST_PREFIX "EDAC:-: "
#    TEST_SUFFIX ----
#    PROPERTIES LABELS EDAC TEST
#    DISCOVERY_TIMEOUT 10
#    EXTRA_ARGS --iterration 1 --outputpath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --module edac.test
#)
