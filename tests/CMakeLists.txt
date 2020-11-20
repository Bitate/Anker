add_executable(Anker_Test
    Anker_Test.cpp
)
target_link_libraries(Anker_Test
    Anker
    gtest_main
)

add_executable(Clipboard_Test
    Clipboard_Test.cpp
)
target_link_libraries(Clipboard_Test
    Anker
    gtest_main
)

add_executable(Media_Handler_Test
    Media_Handler_Test.cpp
)
target_link_libraries(Media_Handler_Test
    Anker
    gtest_main
)
