
set(all_header_files
    ../include/Anker.hpp
    ../include/httplib.h
    ../include/Clipboard.hpp
    ../include/Media_Handler.hpp
    ../include/GUI.hpp
)

set(all_source_files
    Anker.cpp
    Clipboard.cpp
    Media_Handler.cpp
    GUI.cpp
)

add_library(Anker STATIC
    ${all_header_files}
    ${all_source_files}
)

target_link_libraries(Anker  
    jsoncpp_static
)

include_directories(${CMAKE_SOURCE_DIR}/include)
