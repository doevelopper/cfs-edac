
add_library(edac.test
   #edac/GoogleTestCustomEventListener
   cfs/edac/Test
)

target_include_directories(edac.test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

add_executable(edac.test.bin
    cfs/edac/ErrorCodePrivateTest
)

target_link_libraries (edac.test.bin
    PUBLIC
        edac.test
)

#gtest_discover_tests(cppbdd101.edac.test.bin
#    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#    TEST_PREFIX "EDAC:-: "
#    TEST_SUFFIX ----
#    PROPERTIES LABELS EDAC TEST
#    DISCOVERY_TIMEOUT 10
#    EXTRA_ARGS --iterration 1 --outputpath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --module edac.test
#)
