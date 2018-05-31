
add_library(edac.test
   #edac/GoogleTestCustomEventListener
   cfs/edac/Test
   cfs/edac/ErrorCodePrivateTest
   cfs/edac/callstack/ABIDemanglingTest
)

target_include_directories(edac.test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/edac>
        $<INSTALL_INTERFACE:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/edac>
)

target_link_libraries(edac.test 
	PUBLIC #EDAC-MAIN::EDAC-MAIN 
	edac.main
)
add_executable(edac.test.bin
    #cfs/edac/ErrorCodePrivateTest
    cfs/edac/unitTest
)

target_link_libraries (edac.test.bin
    PUBLIC
        edac.test
	LOG4CXX::LOG4CXX
	#${APR_LIBRARY}
	#${EXPAT_LIBRARY}
	#	${APRUTIL_LIBRARY}
	GTest::Main
	GMock::GMock
	#LOG4CXX::LOG4CXX
)

#gtest_discover_tests(cppbdd101.edac.test.bin
#    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#    TEST_PREFIX "EDAC:-: "
#    TEST_SUFFIX ----
#    PROPERTIES LABELS EDAC TEST
#    DISCOVERY_TIMEOUT 10
#    EXTRA_ARGS --iterration 1 --outputpath ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} --module edac.test
#)
