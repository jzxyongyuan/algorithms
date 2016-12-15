
cc_binary (
    name = "test_dart",
    srcs = ["example/test_dart.cpp"],

    copts = [ "-Iexternal/log/src",
              "-I./"],

    deps = ["//:algorithm"],
)

cc_binary (
    name = "test_stack",
    srcs = ["example/test_stack.cpp"],

    copts = [ "-Iexternal/log/src",
              "-I./"],

    deps = ["//:algorithm"],
)

cc_library (
    name = "algorithm",

    srcs = glob(
        ["tree/*.cpp", "stack/*.cpp"]),

    hdrs = glob (
        ["tree/*.h", "stack/*.h"]),

    deps = [ "@log//:log" ],

    copts = [ "-Iexternal/log/src" ],

    visibility = ["//visibility:public"],
)
