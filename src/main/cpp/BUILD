
package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@rules_pkg//:pkg.bzl", "pkg_tar", "pkg_deb")

cc_library(

    name = "cfs-edac-main",

    srcs = [
        "cfs/edar/LoggingServicePrivate.cpp",
        "cfs/edar/LoggingService.cpp",
    ],

    hdrs = [
        "cfs/edar/LoggingServicePrivate.hpp",
        "cfs/edar/LoggingService.hpp",
        "cfs/utils/PimplPtr.hpp",
        "cfs/utils/PimplPtr.inl",
        "cfs/utils/SharedPimplPtr.hpp",
        "cfs/utils/SharedPimplPtr.inl",
    ],

    copts = [
        "-std=c++17",
        "-DLOG_LEVEL=1",
        "-lapr-1",
        "-laprutil-1",
        "-llog4cxx",
		"-D_REENTRANT",
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

