#pragma once

#include <string>
#include <vector>

class Card
{
public:
    Card();
    ~Card();

public:
    void set_front(const std::string& input);

    void set_back(const std::string& input);

    std::string get_front();

    std::string get_back();

private:
    std::string front;
    std::string back;
};