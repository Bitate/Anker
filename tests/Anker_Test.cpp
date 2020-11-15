#include "../include/Anker.hpp"
#include "../include/httplib.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;

TEST(Anker_tests, create_deck_test)
{
    Anker anker;

    std::string deck_name = "Math";

    EXPECT_TRUE( anker.create_deck(const string deck_name, const string parent_deck_name) );
    
    EXPECT_TRUE( anker.has_deck(const std::string deck name) );
}

TEST(Anker_tests, add_new_card_test)
{
    Anker anker;

    // card info
    std::string deck_name = "demo";
    std::string note_type = "basic";
    std::string front_content = "this is front";
    std::string back_content = "this is back";
    std::vector< std::string > tags = { "math","calculus" };
    bool allow_duplicate = true;

    EXPECT_TRUE( anker.add_card(
            deck_name,
            note_type,
            front_content,
            back_content,
            tags,
            allow_duplicate
        ) 
    );

    EXPECT_TRUE( anker.has_card(card_name) );

    EXPECT_TRUE( anker.delete_card(card_name) );

    EXPECT_FALSE( anker.has_card(card_name) );
}

TEST(Anker_tests, add_image_test)
{   
    Anker anker;
    std::vector< uint8_t > image_in_binary;
}

TEST(Anker_tests, add_video_test)
{
    Anker anker;
    std::vector< uint8_t > video_in_binary;
}

TEST(Anker_tests, add_audio_test)
{
    Anker anker;
    std::vector< uint8_t > audio_in_binary;
}

