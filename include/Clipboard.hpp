#ifndef CLIPBOARD_HPP
#define CLIPBOARD_HPP

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

    bool set_clipboard_text(const std::string& text);

    /**
     * @brief  Get the last text within clipboard_stack.
     * @return  Text string.
     */
    std::string& get_last_text();

private:
    std::stack< std::string > clipboard_stack;
};

#endif