#pragma once

#include <string>

#include "parse_tree.hpp"

class driver
{
public:
    driver() : Data(nullptr), Success(true) {}
    bool Parse(const std::string &);

    void Error();

    parse_tree_ptr Root;
    void * Data;
    bool Success;
};
