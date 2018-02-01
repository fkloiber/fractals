#pragma once

#include <vector>

inline std::vector<token>& getT(driver * D)
{
    return *(std::vector<token>*)D->Data;
}

#define EMPLACE(a)                       \
    NextToken++;                         \
    if(Driver->Data) {                   \
        getT(Driver).emplace_back(a);    \
    }
