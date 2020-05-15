
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("@rules_pkg//:pkg.bzl", "pkg_tar", "pkg_deb")

licenses(["notice"])  # Apache License

cc_test(

    name = "cfs-edac-unit-test.bin",

    srcs = [
        "cfs/edac/unitTest.cpp",
        "cfs/edac/Test.cpp",
        "cfs/edac/Test.hpp",
		"cfs/edac/callstack/ABIDemanglingTest.cpp",
		"cfs/edac/callstack/ABIDemanglingTest.hpp",
        "cfs/edac/callstack/CallStackDataStructureTest.cpp",
        "cfs/edac/callstack/CallStackDataStructureTest.hpp",
        "cfs/edac/callstack/CallStackTest.cpp",
        "cfs/edac/callstack/CallStackTest.hpp",
        "cfs/edacl/errors/IOErrorTest.cpp",
        "cfs/edacl/errors/IOErrorTest.hpp",
        "cfs/edacl/errors/GenericErrorTest.cpp",
        "cfs/edacl/errors/GenericErrorTest.hpp",
        "cfs/edacl/errors/SystemErrorTest.cpp",
        "cfs/edacl/errors/SystemErrorTest.hpp",
        "cfs/edar/EventSystemTest.cpp",
        "cfs/edar/EventSystemTest.hpp",
        "cfs/edac/LocationTest.cpp",
        "cfs/edac/LocationTest.hpp",
        "cfs/edac/ExceptionTest.cpp",
        "cfs/edac/ExceptionTest.hpp",

    ],

    includes = [
        ".",
    ],

    copts = [
       "-std=c++17",
       "-DLOG_LEVEL=1",
       #"-lapr-1",
       #"-laprutil-1",
       #"-llog4cxx",
       #"-lgtest",
       "-D_REENTRANT",
       "-I/usr/local/include/",
    ],

    linkopts = [
       "-L/usr/local/lib",
       "-lapr-1",
       "-laprutil-1",
       "-llog4cxx",
       "-lgtest",
       "-lgmock",
     ],


    deps = [
        "//src/main/cpp:cfs-edac-main",
    ],

    data = [
        "//src/main/resources/configs:log4cxx.xml",
    ],
)

