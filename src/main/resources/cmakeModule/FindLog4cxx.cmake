
find_package(Apr)
find_package(APR-util)

if(APR_FOUND AND APRU_FOUND)

    find_library(LOG4CXX_LIBRARY 
        NAMES liblog4cxx.a 
        HINTS 
	    /usr/local/lib/ 
	    #/usr/lib/x86_64-linux-gnu
	    #${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    )

    find_path(LOG4CXX_INCLUDE_DIR 
        NAMES log4cxx/log4cxx.h
        HINTS 
	/usr/local/include
	#/usr/include 
	#${CMAKE_INSTALL_INCLUDEDIR}
   )

#   message(STATUS "LOG4CXX_LIBRARY ${LOG4CXX_LIBRARY}")
#   message(STATUS "LOG4CXX_INCLUDE_DIR ${LOG4CXX_INCLUDE_DIR}")

   include(FindPackageHandleStandardArgs)
   find_package_handle_standard_args(log4cxx
       REQUIRED_VARS LOG4CXX_LIBRARY  LOG4CXX_INCLUDE_DIR
   )
set(LOG4CXX_DEFINITIONS "HAVE_LOG4CXX")
   if(LOG4CXX_FOUND)

      set(LOG4CXX_LIBRARIES ${LOG4CXX_LIBRARY})
      set(LOG4CXX_INCLUDE_DIRS ${LOG4CXX_INCLUDE_DIR} ${APR_INCLUDES})

      if(NOT TARGET LOG4CXX::LOG4CXX)
          add_library(LOG4CXX::LOG4CXX UNKNOWN IMPORTED)
          set_target_properties(LOG4CXX::LOG4CXX PROPERTIES
	      INTERFACE_COMPILE_DEFINITIONS "${LOG4CXX_DEFINITIONS}"
              IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
              IMPORTED_LOCATION "${LOG4CXX_LIBRARY}"
	      INTERFACE_INCLUDE_DIRECTORIES "${LOG4CXX_INCLUDE_DIRS}"
	      INTERFACE_LINK_LIBRARIES ${APR_LIBRARY};${EXPAT_LIBRARY};${APRUTIL_LIBRARY})
      endif(NOT TARGET LOG4CXX::LOG4CXX)

   endif(LOG4CXX_FOUND)

   include(FindPackageHandleStandardArgs)
   find_package_handle_standard_args(LOG4CXX
         REQUIRED_VARS LOG4CXX_LIBRARY LOG4CXX_INCLUDE_DIR
	 #VERSION_VAR LOG4CXX_VERSION_STRING
    )

else (APR_FOUND AND APRU_FOUND)
    message(FATAL_ERROR "Could not find APR/Expat/APRu library")
endif(APR_FOUND AND APRU_FOUND)

mark_as_advanced(LOG4CXX_INCLUDE_DIR LOG4CXX_LIBRARY)

