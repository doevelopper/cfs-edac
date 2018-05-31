#       CMakeLists.txt
#
#               Copyright (c) 2014-2017 Nicolas J. FURY
#
#        Permission is hereby granted, free of charge, to any person obtaining
#        a copy of this software and associated documentation files (the
#        "Software"), to deal in the Software without restriction, including
#        without limitation the rights to use, copy, modify, merge, publish,
#        distribute, sublicense, and/or sell copies of the Software, and to
#        permit persons to whom the Software is furnished to do so, subject to
#        the following conditions:
#
#        The above copyright notice and this permission notice shall be
#        included in all copies or substantial portions of the Software.
#
#        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#        MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
#        LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#        OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#        WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

project (cfs-edac CXX)

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(${PROJECT_NAME}_MAJOR_VERSION       "1")
set(${PROJECT_NAME}_MINOR_VERSION       "0")
set(${PROJECT_NAME}_MICRO_VERSION       "0")
set(${PROJECT_NAME}_PATCH_VERSION       "-")
set(${PROJECT_NAME}_PATCH_LEVEL         "0")
set(${PROJECT_NAME}_REVISION_VERSION    "0")
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}" )
set("BUILD_SHARED_LIBS" OFF CACHE INTERNAL "If enabled, shared libs will be built by default, otherwise static libs")

add_definitions(-DRELEASE_LEVEL="SNAPSHOOT") # SNAPSHOOT ,ALPHA , BETA , CANDIDATE , FINAL.

if(NOT COMMON_MODULE_TOOLS)

    list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/src/main/resources/macros"
        "${CMAKE_SOURCE_DIR}/src/main/resources/cmakeModule"
    )

  if (NOT TARGET  LOG4CXX::LOG4CXX)
        find_package(Log4cxx REQUIRED)
  endif()

  if (NOT TARGET GTest::GTest AND NOT TARGET GMock::GMock)
        find_package(GoogleTestFwk REQUIRED)
  endif()

  
else(NOT COMMON_MODULE_TOOLS)
   massage(STATUS "${PROJECT_NAME} will use modules defined in main parent dir")
endif(NOT COMMON_MODULE_TOOLS)

#Work arorund. should be build as 3rd party dependencies
#include_directories(/home/happyman/cppbdd101/build/x86_64-Linux-GNU_GCC_7.2.0-DEBUG/include)
#link_directories(/home/happyman/cppbdd101/build/x86_64-Linux-GNU_GCC_7.2.0-DEBUG/lib)

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

if(IS_BIG_ENDIAN)
     message(FATAL_ERROR "Big endian isn't supported !!!")
endif(IS_BIG_ENDIAN)

include(ProcessorCount)
ProcessorCount(N)

include(Rules)
include(CompilerOption)

add_subdirectory (src/main/cpp)
#add_subdirectory (src/test/cpp)
#add_subdirectory (src/it)

