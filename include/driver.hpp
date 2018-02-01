#pragma once

#include <string>

class driver
{
public:
    driver() : Data(nullptr), Success(true) {}
    bool Parse(const std::string &);

    void Error();

    void * Data;
    bool Success;
};
