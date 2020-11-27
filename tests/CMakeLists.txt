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
