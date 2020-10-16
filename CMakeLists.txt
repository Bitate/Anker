cmake_minimum_required(VERSION 3.18)

set(this Anker)

project(${this})

enable_testing()

# Use tis command to force google test to link dynamically
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(jsoncpp-1.9.4)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(googletest)

