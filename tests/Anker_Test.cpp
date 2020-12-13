#include "../include/Anker.hpp"
#include "../include/httplib.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(Anker_tests, create_and_delete_deck_test)
{
    Anker anker;

    std::string deck_name = "create_and_delete_deck_test";

    EXPECT_TRUE( anker.create_deck(deck_name) );
    
    EXPECT_TRUE( anker.has_deck(deck_name) );

    EXPECT_TRUE( anker.delete_deck(deck_name, true) );

    EXPECT_FALSE( anker.has_deck(deck_name) );
}


TEST(Anker_tests, add_new_card_test)
{
    Anker anker;

    // card info
    std::string deck_name = "add_new_card_test";
    std::string note_type = "basic";
    std::string front_content = "this is front";
    std::string back_content = "this is back";
    std::vector< std::string > tags = { "math","calculus" };
    bool allow_duplicate = true;

    EXPECT_TRUE( anker.create_deck(deck_name) );

    EXPECT_TRUE( anker.add_note(
            deck_name,
            note_type,
            front_content,
            back_content,
            tags,
            allow_duplicate
        ) 
    );

    EXPECT_TRUE( anker.delete_deck(deck_name, true) );
}