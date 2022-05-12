cmake_minimum_required(VERSION 3.11)
project(samples)

include_directories(
    ./
    utils
)

add_definitions(-g)

file(GLOB_RECURSE H_FILES utils/*h)

add_executable(sample_test samples/test.cpp ${H_FILES})

