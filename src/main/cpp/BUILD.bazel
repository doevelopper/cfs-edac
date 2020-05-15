
package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@rules_pkg//:pkg.bzl", "pkg_tar", "pkg_deb")

cc_library(

    name = "cfs-edac-main",

    srcs = [
        "cfs/edar/LoggingServicePrivate.cpp",
        "cfs/edar/LoggingService.cpp",
        "cfs/edar/EventSystem.cpp",
        "cfs/edac/callstack/ABIDemangling.cpp",
        "cfs/edac/callstack/CallStack.cpp",
        "cfs/edac/callstack/CallStackDataStructure.cpp",
		"cfs/edac/internal/Stack.cpp",
		"cfs/edac/internal/StackException.cpp",
        "cfs/edac/Location.cpp",
        "cfs/edac/Exception.cpp",
		"cfs/edac/IsErrorActive.cpp",
		"cfs/edacl/errors/SystemError.cpp",
		# "cfs/edacl/errors/FutureError.cpp",
		"cfs/edacl/errors/GenericError.cpp",
		# "cfs/edacl/errors/LowLevelApiError.cpp",
		"cfs/edacl/errors/IOError.cpp",
		# "cfs/edacl/errors/ErrorCode.cpp",
		#"cfs/edacl/internal/ErrorCodeTable.cpp",
		# "cfs/edacl/errors/ErrorCode.cpp",
		# "cfs/edacl/internal/ErrorCodePrivate.cpp",
    ],

    hdrs = [
        "cfs/edar/LoggingServicePrivate.hpp",
        "cfs/edar/LoggingService.hpp",
        "cfs/edar/EventSystem.hpp",
        "cfs/utils/PimplPtr.hpp",
        "cfs/utils/PimplPtr.inl",
        "cfs/utils/SharedPimplPtr.hpp",
        "cfs/utils/SharedPimplPtr.inl",
        "cfs/edac/callstack/ABIDemangling.hpp",
        "cfs/edac/callstack/CallStack.hpp",
        "cfs/edac/callstack/CallStackDataStructure.hpp",
		"cfs/edac/internal/Stack.hpp",
		"cfs/edac/internal/StackException.hpp",
        "cfs/edac/Location.hpp",
        "cfs/edac/Exception.hpp",
		"cfs/edac/IsErrorActive.hpp",
		"cfs/edac/ParameterSet.hpp",
		"cfs/edacl/errors/SystemError.hpp",
		# "cfs/edacl/errors/FutureError.hpp",
		"cfs/edacl/errors/GenericError.hpp",
		# "cfs/edacl/errors/LowLevelApiError.hpp",
		"cfs/edacl/errors/IOError.hpp",
        "cfs/utils/Singleton.hpp",
		# "cfs/edacl/errors/ErrorCode.hpp",
		# "cfs/edacl/internal/ErrorCodePrivate.hpp",
		#"cfs/edacl/internal/ErrorCodeTable.hpp",
		# "cfs/edacl/errors/ErrorCode.hpp",
    ],

    copts = [
        "-std=c++17",
        "-DLOG_LEVEL=1",
        "-lapr-1",
        "-laprutil-1",
        "-llog4cxx",
		"-D_REENTRANT",
		"-DEDAC_MAIN_EXPORT",
        "-DCFS_EDAC_MAIN_EXPORT",
        "-I/usr/local/include/",
    ],

    linkopts = [
        "-L/usr/local/lib",
		"-pthread",
        "-lapr-1",
        "-laprutil-1",
        "-llog4cxx",
	],

	includes = [
		".",
	],

    #visibility = ["//visibility:public"],
    #visibility = ["//main:__pkg__"],
)

cc_binary(
    name = "cfs-edac-main.bin",
    srcs = ["cfs/main.cpp"],
    copts = [
       "-std=c++17",
    ],

    deps = [
        ":cfs-edac-main",
    ],
)

pkg_tar(
    name = "cfs-edac-main-libs",
    strip_prefix = "/src/main/cpp",
    package_dir = "/opt/lib",
    srcs = ["//src/main/cpp:cfs-edac-main"],
    mode = "0755",
)

pkg_tar(
    name = "cfs-edac-main-hdrs-pkg",
#    testonly = True,
    srcs = glob([
        "**/*.hpp",
    ]),
    # extension = "tar.gz",
    package_dir = "/opt/include",
    strip_prefix = "/src/main/cpp",
    tags = ["manual"],
    visibility = ["//visibility:public"],
    mode = "0644",
)

pkg_tar(
    name = "cfs-edac-main-bin-pkg",
#    testonly = True,
    srcs = [
        # ":cfs-algo-main",
        ":cfs-edac-main.bin",
    ],
    # extension = "tar.gz",
    package_dir = "/opt/bin",
    strip_prefix = "/src/main/cpp",
    tags = ["manual"],
)

pkg_tar(
    name = "cfs-edac",
    extension = "tar.gz",
    deps = [
        ":cfs-edac-main-libs",
        ":cfs-edac-main-hdrs-pkg",
        ":cfs-edac-main-bin-pkg",
    ],
)

pkg_deb(
    name = "cfs-edac-main-deb-pkg",
    testonly = True,
    architecture = "amd64",
    data = ":cfs-edac",
    description = "Core Flight System Error Detector and Correction",
    homepage = "https://gitlab.com/doevelopper/cfs-edac",
    maintainer = "Adrien H.",
    package = "CFS EDAC",
    tags = ["manual"],
    version = "0.0.1",
    visibility = ["//visibility:public"],
)

