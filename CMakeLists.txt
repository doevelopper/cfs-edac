#[[
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
#]]

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project (cfs.edac
    VERSION 0.0.0.1
    DESCRIPTION "Error Detection Correction Classification and reporting"
    HOMEPAGE_URL "https://exemple.com"
    LANGUAGES CXX
)


add_definitions(-DRELEASE_LEVEL="SNAPSHOOT") # SNAPSHOOT ,ALPHA , BETA , CANDIDATE , FINAL.
set(RELEASE_LEVEL "SNAPSHOOT")

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/src/main/resources/cmake"
    "${CMAKE_SOURCE_DIR}/src/main/resources/cmake/modules"
    "${CMAKE_SOURCE_DIR}/src/main/resources/cmake/toolChains"
    "${CMAKE_SOURCE_DIR}/src/main/resources/cmake/macros"
    "${CMAKE_SOURCE_DIR}/src/test/resources/cmake"
    "/usr/local/lib/cmake"
    "/usr/lib/cmake"
)

include(LSBInfo)
include(CompilerOption)
include(DefinePlatformSpecfic)
include(macros)
include(goals)
include(CodingStyle)
include(CPPCheck)
include(CpplintWrapper)
include(lizard)
include(GccCoverage)
include(CucumberCppConfig)
getGitInfo()
TODAY(APP_BUILD_DATE)
set(COPYRIGHT_YEAR ${APP_BUILD_DATE})

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
     message(FATAL_ERROR "Big endian isn't supported !!!")
endif(IS_BIG_ENDIAN)

include(ProcessorCount)
ProcessorCount(Ncpu)

find_package(Log4cxx)
find_package(GoogleTestFwk)
find_package(Doxygen
    #   REQUIRED  dot
   OPTIONAL_COMPONENTS mscgen dia dot
)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.69.0
    COMPONENTS
        thread system regex date_time program_options filesystem unit_test_framework
    REQUIRED
)

option(EXCLUDE_DEPRECATED "Exclude deprecated parts of the library" TRUE)

if (EXCLUDE_DEPRECATED)
    set(NO_BUILD_DEPRECATED DEFINE_NO_DEPRECATED)
endif()

include(GoogleTest) #gtest_discover_tests
include(CTest)
set (CMAKE_TEST_COMMAND ctest -V) # Work aroound do console output

get_property(cxx_known_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
get_property(c_known_features GLOBAL PROPERTY CMAKE_C_KNOWN_FEATURES)

include(WriteCompilerDetectionHeader)
write_compiler_detection_header(
    FILE ${CMAKE_INSTALL_INCLUDEDIR}/cfs/edac/CompilerDetection.hpp
    PREFIX CFS_EDAC
#   OUTPUT_FILES_VAR <output_files_var> OUTPUT_DIR <output_dir>
    COMPILERS GNU Clang
    FEATURES ${cxx_known_features}
    VERSION "${CMAKE_VERSION}"
    PROLOG "//<This is a custom prolog>"
    EPILOG "//<This is a custom epilog>"
#   ALLOW_UNKNOWN_COMPILERS
#   ALLOW_UNKNOWN_COMPILER_VERSIONS
)

configure_file("${PROJECT_SOURCE_DIR}/src/main/resources/configs/GitRevision.hpp.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/GitRevision.hpp"
               @ONLY)

configure_file("${PROJECT_SOURCE_DIR}/src/main/resources/configs/AppInfo.hpp.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/AppInfo.hpp"
                @ONLY)

configure_file("${PROJECT_SOURCE_DIR}/src/main/resources/configs/Version.hpp.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/Version.hpp"
                @ONLY)

configure_file("${PROJECT_SOURCE_DIR}/src/main/resources/configs/Version.cpp.in"
                "${CMAKE_CURRENT_BINARY_DIR}/cfs/edac/Version.cpp"
                @ONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_INSTALL_PREFIX}/cmake/cfs-osal-config-version.cmake
    COMPATIBILITY ExactVersion
)

#add_subdirectory (src/main/cpp)
#add_subdirectory (src/test/cpp)
#add_subdirectory (src/it)

