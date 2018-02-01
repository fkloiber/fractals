#pragma once

#include <vector>

inline std::vector<token>& getT(driver * D)
{
    return *(std::vector<token>*)D->Data;
}

#define EMPLACE(a) if(Driver->Data) {NextToken = getT(Driver).size(); getT(Driver).emplace_back(a);}
