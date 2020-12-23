include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(all_header_files
    ../include/httplib.h
    ../include/Anker.hpp
    ../include/MainWindow.hpp
)

set(all_source_files
    Anker.cpp
    MainWindow.cpp
)

add_library(Anker STATIC
    ${all_header_files}
    ${all_source_files}
)

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

target_link_libraries(Anker
    jsoncpp_static
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
)

