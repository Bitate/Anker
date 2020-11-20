cmake_minimum_required(VERSION 3.8)

set(this Anker)

project(${this} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Use tis command to force google test to link dynamically
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS
    Widgets
    Core
    Gui
    Quick

    REQUIRED
)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Widgets
    Core
    Gui
    Quick

    REQUIRED
)

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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Quick
)


