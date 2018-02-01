#pragma once

#include <string>

class driver
{
public:
    driver() {};
    bool Parse(const std::string &);

    void Error();

    void * Data;
    bool Success;
};
