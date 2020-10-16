include_directories(${CMAKE_SOURCE_DIR}/include)

set(all_header_files
    ../include/Anker.hpp
    ../include/Card.hpp
    ../include/httplib.h
)

set(all_source_files
    Anker.cpp
    Card.cpp
)

add_library(Anker STATIC
    ${all_header_files}
    ${all_source_files}
)
target_link_libraries(Anker
    jsoncpp_static
)
