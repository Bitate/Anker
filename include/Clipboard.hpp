#pragma once

#include <stack>
#include <string>
#include <iostream>
#include <Windows.h>

class Clipboard
{
public:
    /**
     * @brief  Open windows' clipboard.
     * @return  True if succeeds.
     * @remark  open_clipboard() fails if another window has the clipboard open.
     *          An application should call the close_clipboard() after every 
     *          successful call to open_clipboard().
     */
    bool open_clipboard();

    /**
     * @brief  Close windows' clipboard.
     * @return  True if succeeds.
     * @remark  When the window has finished examining or changing the clipboard, 
     *          close the clipboard by calling this function. This enables other 
     *          windows to access the clipboard. Do not place an object on the 
     *          clipboard after calling CloseClipboard.
     */
    bool close_clipboard();

    /**
     * @brief  Get most recently copied test and put it into clipboard_stack.
     * @return  True if succeeds.
     */
    bool get_clipboard_text();

    /**
     * @brief  Set given text to the top of clipboard.
     * @param  text  Given text to be put on the top of the clipboard.
     * @return  True if succeeds.
     */
    bool set_clipboard_text(const std::string& text);

    /**
     * @brief  Whether is the clipboard stack is empty?
     * @return  True if the clipboard_stack is empty.
     */
    bool is_clipboard_stack_empty();

    /**
     * @brief  Get the last text within clipboard_stack.
     * @return  Text string.
     */
    std::string& get_last_text();

private:
    std::stack< std::string > clipboard_stack;
};
