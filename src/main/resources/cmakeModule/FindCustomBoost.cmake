# - Locate Boost library
# Defines:
#
#  BOOST_FOUND
#  BOOST_INCLUDE_DIR
#  BOOST_INCLUDE_DIRS (not cached)
#  BOOST_LIBRARY
#  BOOST_LIBRARIES (not cached)

find_path(BOOST_INCLUDE_DIR boost/asio.hpp
    HINTS ${CMAKE_INSTALL_INCLUDEDIR} 
    NO_DEFAULT_PATH
)

#macro(bulked_find_boost_bibraries)
list(APPEND commonBoostLibs 
        "atomic"
        "chrono"
        "context"
        "date_time"
        "exception"
        "filesystem"
        "iostreams"
        "timer"
        "thread"
        "system"
        "regex"
        "program_options"
        "math_tr1f"
        "math_tr1l"
        "math_tr1"
)

if(NOT TARGET Boost::chrono)
    add_library(Boost::chrono UNKNOWN IMPORTED)
    set_target_properties(Boost::chrono PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_chrono.a"
    )
endif()

if(NOT TARGET Boost::atomic)
    add_library(Boost::atomic UNKNOWN IMPORTED)
    set_target_properties(Boost::atomic PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_atomic.a"
    )
endif()

if(NOT TARGET Boost::date_time)
    add_library(Boost::date_time UNKNOWN IMPORTED)
    set_target_properties(Boost::date_time PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_date_time.a"
   )
endif()

if(NOT TARGET Boost::regex)
    add_library(Boost::regex UNKNOWN IMPORTED)
    set_target_properties(Boost::regex PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_regex.a"
    )
endif()

if(NOT TARGET Boost::system)
   add_library(Boost::system UNKNOWN IMPORTED)
   set_target_properties(Boost::system PROPERTIES
       IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
       IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_system.a"
   )
endif()

if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem UNKNOWN IMPORTED)
    set_target_properties(Boost::filesystem PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_filesystem.a"
        INTERFACE_LINK_LIBRARIES Boost::system
    )
endif()

if(NOT TARGET Boost::random)
    add_library(Boost::random UNKNOWN IMPORTED)
    set_target_properties(Boost::random PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_random.a"
    )
endif()

if(NOT TARGET Boost::thread)
    add_library(Boost::thread UNKNOWN IMPORTED)
    set_target_properties(Boost::thread PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_thread.a"
        INTERFACE_LINK_LIBRARIES Boost::chrono Boost::date_time Boost::regex
)
endif()

if(NOT TARGET Boost::program_options)
     add_library(Boost::program_options UNKNOWN IMPORTED)
     set_target_properties(Boost::program_options PROPERTIES
         IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
         IMPORTED_LOCATION "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libboost_program_options.a"
     )
endif()

if(NOT TARGET Boost::Boost)
    add_library(Boost::Boost UNKNOWN IMPORTED)
    set_target_properties(Boost::Boost PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        INTERFACE_LINK_LIBRARIES "Boost::chrono;Boost::date_time;Boost::regex;Boost::system;Boost::program_options"
   )
endif()



#    foreach(LIBRARY_NAME ${commonBoostLibs})

    #    message(STATUS "Searching ${LIBRARY_NAME}")

    #        find_library(BOOST_LIBRARY NAMES boost_${LIBRARY_NAME}.a libboost_${LIBRARY_NAME}.a
    #             HINTS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    #        )
    #         message(STATUS "Found ${BOOST_LIBRARY}")

#        if(NOT TARGET Boost::${LIBRARY_NAME})
#            add_library(Boost::${LIBRARY_NAME} UNKNOWN IMPORTED)
#            set_target_properties(Boost::${LIBRARY_NAME} PROPERTIES
#                 IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
#                 IMPORTED_LOCATION "${BOOST_LIBRARY}"
#            )
#        endif()

	#    list(APPEND  BOOST_LIBRARIES Boost::${LIBRARY_NAME})
#       set(BOOST_INCLUDE_DIRS ${BOOST_INCLUDE_DIR})
#    endforeach()

    #    set(BOOST_INCLUDE_DIRS ${BOOST_INCLUDE_DIR})

    #    if(NOT TARGET Boost::boost)
    #    add_library(Boost::boost UNKOWN IMPORTED)
    #   set_target_properties(Boost::boost PROPERTIES
    #           IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
       #IMPORTED_LOCATION "${BOOST_LIBRARY}"
       #       INTERFACE_INCLUDE_DIRECTORIES  "${BOOST_INCLUDE_DIR}"
       #       )
       #    endif(NOT TARGET Boost::boost)

#endmacro(bulked_find_boost_bibraries)

# handle the QUIETLY and REQUIRED arguments and set BOOST_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BOOST DEFAULT_MSG BOOST_INCLUDE_DIR ) #BOOST_LIBRARIES)
mark_as_advanced(BOOST_FOUND BOOST_INCLUDE_DIR )# BOOST_LIBRARIES)

if(BOOST_INCLUDE_DIR)
    set(Boost_FOUND ON )
endif(BOOST_INCLUDE_DIR)

