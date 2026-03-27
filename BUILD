load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "spa",
    srcs = ["spa.cc"],
    hdrs = ["spa.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "spa_test",
    srcs = ["spa_test.cc"],
    deps = [
        ":spa",
        "@com_google_googletest//:gtest_main",
    ],
)
