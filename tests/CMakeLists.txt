add_executable(Card_Test
    Card_Test.cpp
)
target_link_libraries(Card_Test
    Card
)

add_executable(Anker_Test
    Anker_Test.cpp
)
target_link_libraries(Anker_Test
    Anker
    gtest_main
)


