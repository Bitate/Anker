include_directories(${CMAKE_SOURCE_DIR}/include)

set(all_header_files
    ../include/Anker.hpp
    ../include/httplib.h
    ../include/Window.hpp
)

set(all_source_files
    Anker.cpp
    Window.cpp
)

add_library(Anker STATIC
    ${all_header_files}
    ${all_source_files}
)

target_link_libraries(Anker  
    jsoncpp_static
    Qt${QT_VERSION_MAJOR}::Widgets
)
