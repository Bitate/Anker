add_executable(Anker_Test
    Anker_Test.cpp
)
target_link_libraries(Anker_Test
    Anker
    gtest_main
    Qt::Gui
)


