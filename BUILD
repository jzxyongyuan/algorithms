
cc_binary (
    name = "test_dart",
    srcs = ["example/test_dart.cpp"],
    copts = [ "-I./" ],
    deps = ["//:algorithm"],
)

cc_binary (
    name = "test_stack",
    srcs = ["example/test_stack.cpp"],
    copts = [ "-I./" ],
    deps = ["//:algorithm"],
)

cc_library (
    name = "algorithm",

    srcs = glob(
        ["tree/*.cpp", "stack/*.cpp"]),

    hdrs = glob (
        ["tree/*.h", "stack/*.h"]),

    deps = [ "@log//:log" ],

    visibility = ["//visibility:public"],
)
