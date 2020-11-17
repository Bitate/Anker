#include "Clipboard.hpp"

bool Clipboard::open_clipboard()
{
    return OpenClipboard(nullptr);
}

bool Clipboard::close_clipboard()
{
    return CloseClipboard();
}

bool Clipboard::get_clipboard_text()
{
    // Try opening the clipboard
    if (!open_clipboard())
        return false;
    
    // Get handle of clipboard object for ANSI text
    HANDLE handle_for_data = GetClipboardData(CF_TEXT);
    if (handle_for_data == nullptr)
        return false;

    // Lock the handle to get the actual text pointer
    char *text_pointer = static_cast<char*>(GlobalLock(handle_for_data));
    if (text_pointer == nullptr)
        return false;
    
    // Save text in a string class instance
    std::string text(text_pointer);

    // Save to my own clipboard stack
    clipboard_stack.push(text);

    // Release the lock for clipboard
    GlobalUnlock(handle_for_data);

    // Release the clipboard
    close_clipboard();

    return true;
}

bool Clipboard::set_clipboard_text(const std::string& text)
{
    // TODO: Why text.size() must plus 1?
    HGLOBAL handle_for_data = GlobalAlloc(GMEM_MOVEABLE, text.size()+1 );
    memcpy(GlobalLock(handle_for_data), text.c_str(), text.size());

    // Release the lock for clipboard
    GlobalUnlock(handle_for_data);

    // Try opening the clipboard
    if (!open_clipboard())
        return false;
    
    EmptyClipboard();
    
    // Get handle of clipboard object for ANSI text
    auto set_result = SetClipboardData(CF_TEXT, handle_for_data);
    if (set_result == nullptr)
        return false;

    // Close the clipboard
    close_clipboard();

    return true;
}

std::string& Clipboard::get_last_text()
{
    return clipboard_stack.top();
}

