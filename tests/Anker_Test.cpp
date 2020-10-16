#include "../include/Anker.hpp"
#include "../include/httplib.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;

TEST(Anker_tests, add_note_test)
{
    Anker anker;

    cout << anker.add_note(
        "demo",
        "Basic",
        "This is front",
        "This is back",
        { "tag1", "tag2" }
    );
}
