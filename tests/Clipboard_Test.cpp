#include "../include/Clipboard.hpp"

#include <gtest/gtest.h>

TEST(clipboard_tests, open_and_close_clipboard_test)
{
    Clipboard clipboard;

    EXPECT_TRUE( clipboard.open_clipboard() );
    EXPECT_TRUE( clipboard.close_clipboard() );
}

TEST(clipboard_tests, set_and_get_clipboard_text_test)
{
    Clipboard clipboard;
    
    std::string text = "This is text copied into clipboard";

    EXPECT_TRUE( clipboard.set_clipboard_text(text) );
    
    EXPECT_TRUE( clipboard.get_clipboard_text() );  
    
    EXPECT_EQ( clipboard.get_last_text(), text );
}