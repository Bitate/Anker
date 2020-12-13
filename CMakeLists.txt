cmake_minimum_required(VERSION 3.8)

set(this Anker)

project(${this} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Use tis command to force google test to link dynamically
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(jsoncpp-1.9.4)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(googletest)

add_executable(main_exec
    main.cpp
    main.qrc
)
target_link_libraries(main_exec
    Anker
)
