#pragma once

#include <vector>

#include "token.hpp"


class driver;

std::vector<token>& getT(driver * D);

#define EMPLACE(a)                       \
    NextToken++;                         \
    if(Driver->Data) {                   \
        getT(Driver).emplace_back(a);    \
    }
