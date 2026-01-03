load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "sample",
    srcs = ["main.cc"],
    data = [
        "sample.txt",
    ],
    deps = ["@abseil-cpp//absl/container:flat_hash_set"],
)

cc_binary(
    name = "actual",
    srcs = ["main.cc"],
    data = [
        "actual.txt",
    ],
    deps = ["@abseil-cpp//absl/container:flat_hash_set"],
)
