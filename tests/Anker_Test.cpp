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
           front_content,
           back_content,
           tags,
           note_type,
           allow_duplicate
       )
   );

   EXPECT_TRUE( anker.delete_deck(deck_name, true) );
}

TEST(Anker_tests, get_unique_identifier_test)
{
    Anker anker;

    // See output
    std::cout << anker.get_unique_identifier();
}

TEST(Anker_tests, trim_qt_url_prefix)
{
    Anker anker;

    QUrl original_file_url_1 = QUrl("file:///D:/Aboboooooo/201210225151/9.mp3");
    const std::string trimmed_file_url_1 = "D:/Aboboooooo/201210225151/9.mp3";
    EXPECT_EQ(anker.trim_qt_file_url_prefix(original_file_url_1), trimmed_file_url_1);

    QUrl original_file_url_2 = QUrl("D:/Aboboooooo/201210225151/9.mp3");
    const std::string trimmed_file_url_2 = "D:/Aboboooooo/201210225151/9.mp3";
    EXPECT_EQ(anker.trim_qt_file_url_prefix(original_file_url_2), trimmed_file_url_2);
}

