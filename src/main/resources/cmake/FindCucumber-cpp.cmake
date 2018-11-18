
#SET(ENV{Boost_DIR} "${CMAKE_INSTALL_LIBDIR}:${CMAKE_INSTALL_INCLUDEDIR}")
# export BOOST_ROOT="/home/happyman/cppbdd101/build/x86_64-Linux-GNU_GCC_7.2.0-DEBUG"

#if(DEFINED BOOST_ROOT)
#     message("...using Boots found in $ENV{BOOST_ROOT}")
#else()
#     message("BOOST_ROOT is not defined.  You must tell CMake where to find boost libraries ")
     # exit early 
#     return()
#endif()

message(STATUS "Searching for cucumber dependencies")

set(CUKE_BOOST_LIBS
    thread
    system
    regex
    date_time
    program_options
    asio
    assign
    filesystem
    multi_array
    signals
)

set(IT_TESTS_DEPENDENCIES
    ${CMAKE_THREAD_LIBS_INIT}
    Boost::asio
    Boost::assign
    Boost::date_time 
    Boost::filesystem
    Boost::multi_array 
    Boost::regex 
    Boost::program_options 
    Boost::system 
    Boost::thread 
    GTest::GTest
    GMock::GMock
    Benchmark::Benchmark
)

#add_definitions(-DBOOST_ROOT:PATH=${CMAKE_INSTALL_PREFIX}
#        -DBOOST_INCLUDEDIR:PATH=${CMAKE_INSTALL_INCLUDEDIR} 
#        -DBOOST_LIBRARYDIR:PATH=${CMAKE_INSTALL_LIBDIR}
#)

set(Boost_USE_STATIC_LIBS   ON CACHE BOOL "Link to Boost static libraries")
set(Boost_USE_MULTITHREADED ON CACHE BOOL "Multithreaded Boost libraries")
#set(Boost_NO_SYSTEM_PATHS TRUE)

#if(Boost_NO_SYSTEM_PATHS)
    #set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../3p/boost")
    #set(BOOST_ROOT ${CMAKE_INSTALL_PREFIX})
    #    set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)
    #    set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
    #    set(BOOST_LIBRARY_DIRS ${BOOST_ROOT}/lib)
    #    set(BOOST_LIBRARY_DIR ${BOOST_ROOT}/lib)
#endif (Boost_NO_SYSTEM_PATHS)

#message(STATUS "BOOST_ROOT ${BOOST_ROOT}")
#message(STATUS "BOOST_INCLUDE_DIRS ${BOOST_INCLUDE_DIRS}")
#message(STATUS "BOOST_LIBRARY_DIRS ${BOOST_LIBRARY_DIRS}")
#set(Boost_DIR           "${CMAKE_INSTALL_PREFIX}/lib")
#set(Boost_INCLUDE_DIR   "${CMAKE_INSTALL_PREFIX}/include/boost")

find_package(CustomBoost)

#find_package(boost COMPONENTS ${CUKE_BOOST_LIBS} REQUIRED 
#    HINTS  
#        ${CMAKE_INSTALL_INCLUDEDIR}
#        ${CMAKE_INSTALL_PREFIX}
#	${CMAKE_INSTALL_LIBDIR}
#	${CMAKE_INSTALL_PREFIX}/lib
#	${CMAKE_INSTALL_PREFIX}/include
# PATHS
# /home/happyman/cppbdd101/external/src/main/cpp/cppbdd101/external/boost/boost_1_66_0 
# /home/happyman/cppbdd101/external/src/main/cpp/cppbdd101/external/boost/boost_1_66_0/stage/lib 
# /home/happyman/cppbdd101/external/src/main/cpp/cppbdd101/external/boost/boost_1_66_0/boost 
# ${CMAKE_INSTALL_INCLUDEDIR} 
# ${CMAKE_INSTALL_LIBDIR}
# "${CMAKE_INSTALL_PREFIX}/lib"
# "${CMAKE_INSTALL_PREFIX}/include"
#    NO_CMAKE_SYSTEM_PATH
#    NO_DEFAULT_PATH
#)

#message(STATUS "${Boost_INCLUDE_DIRS} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY}")

#if(Boost_FOUND)
#message(STATUS "Boost is ${BOOST_ROOT}")
#   message(STATUS "Boost directories found at ${Boost_INCLUDE_DIRS}")
#   message(STATUS "Boost libraries found at ${Boost_LIBRARY_DIRS}")
#   message(STATUS "Boost component libraries to be linked are ${Boost_LIBRARIES}")
#   message(STATUS "Boost version found is ${Boost_VERSION}")

    find_path(CUCUMBER_INCLUDE_DIR cucumber-cpp/autodetect.hpp
        HINTS ${CMAKE_INSTALL_INCLUDEDIR}
    )

    list(APPEND CUCUMBER_NAMES cucumber-cpp libcucumber-cpp)
    list(APPEND CUCUMBER_NO_MAIN_NAMES cucumber-cpp-nomain libcucumber-cpp-nomain)

    #if(NOT CUCUMBER_LIBRARY)

        find_library(CUCUMBER_LIBRARY NAMES ${CUCUMBER_NAMES}
            HINTS ${CMAKE_INSTALL_LIBDIR}
        )

#       find_library(CUCUMBER_LIBRARY_DEBUG NAMES ${CUCUMBER_NAMES_DEBUG}
#          	HINTS ${CMAKE_INSTALL_LIBDIR}
#       )

        find_library(CUCUMBER_NO_MAIN_LIBRARY NAMES ${CUCUMBER_NO_MAIN_NAMES}
            HINTS ${CMAKE_INSTALL_LIBDIR}
        )

#        find_library(CUCUMBER_NO_MAIN_LIBRARY_DEBUG NAMES ${CUCUMBER_NO_MAIN_NAMES_DEBUG}
#            HINTS ${CMAKE_INSTALL_LIBDIR}
#        )


        find_program(CUCUMBER_BINARY NAMES cucumber)

	mark_as_advanced(CUCUMBER_LIBRARY CUCUMBER_NO_MAIN_LIBRARY CUCUMBER_BINARY) 

        if (CUCUMBER_LIBRARY AND CUCUMBER_INCLUDE_DIR)
            if(NOT TARGET CUCUMBER-CPP::CUCUMBER-CPP)
                add_library(CUCUMBER-CPP::CUCUMBER-CPP UNKNOWN IMPORTED)
                set_target_properties(CUCUMBER-CPP::CUCUMBER-CPP PROPERTIES
                ## INTERFACE_COMPILE_DEFINITIONS "${CUCUMBER_DEFINITIONS}"
                    INTERFACE_INCLUDE_DIRECTORIES "${CUCUMBER_INCLUDE_DIRS}"
		    INTERFACE_LINK_LIBRARIES  
		                "GTest::GTest;GMock::GMock;Boost::program_options;Boost::date_time;Boost::filesystem;Boost::regex;Boost::system;Boost::thread"
                    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		    IMPORTED_LOCATION "${CUCUMBER_LIBRARY}"
                )

            endif (NOT TARGET CUCUMBER-CPP::CUCUMBER-CPP)

	    if(NOT TARGET CUCUMBER_NO_MAIN_LIBRARY::CUCUMBER_NO_MAIN_LIBRARY)
	         add_library(CUCUMBER_NO_MAIN_LIBRARY::CUCUMBER_NO_MAIN_LIBRARY UNKNOWN IMPORTED)
	         set_target_properties(CUCUMBER_NO_MAIN_LIBRARY::CUCUMBER_NO_MAIN_LIBRARY PROPERTIES
                          ## INTERFACE_COMPILE_DEFINITIONS "${CUCUMBER_DEFINITIONS}"
		          INTERFACE_INCLUDE_DIRECTORIES "${CUCUMBER_INCLUDE_DIRS}"
			  ##INTERFACE_LINK_LIBRARIES Boost::Boost
			  IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
			  IMPORTED_LOCATION "${CUCUMBER_NO_MAIN_LIBRARY}"
			  )
		 endif (NOT TARGET CUCUMBER_NO_MAIN_LIBRARY::CUCUMBER_NO_MAIN_LIBRARY)
        endif(CUCUMBER_LIBRARY AND CUCUMBER_INCLUDE_DIR)

     #endif(NOT CUCUMBER_LIBRARY)

     include(FindPackageHandleStandardArgs)
     find_package_handle_standard_args(CUCUMBER-CPP
         REQUIRED_VARS CUCUMBER_LIBRARY CUCUMBER_NO_MAIN_LIBRARY CUCUMBER_INCLUDE_DIR
     )

     #message (STATUS "CUCUMBER_LIBRARY ${CUCUMBER_LIBRARY}")
     #message (STATUS "CUCUMBER_NO_MAIN_LIBRARY ${CUCUMBER_NO_MAIN_LIBRARY}")
     #message (STATUS "CUCUMBER_INCLUDE_DIR ${CUCUMBER_INCLUDE_DIR}")
     #mark_as_advanced(CUCUMBER_CUCUMBER_INCLUDE_DIR CUCUMBER_LIBRARY CUCUMBER_NO_MAIN_LIBRARY)

#else(Boost_FOUND)
#     message (WARNING "Boost library not found. Integration test not available")
#endif(Boost_FOUND)

