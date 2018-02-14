#pragma once

#include <memory>

template <typename F>
struct render_info
{
    uint32_t * Pixels;
    uint32_t Rows, Cols;
    uint32_t RowStride;
    uint32_t MaxIter;
    F Bottom, Top, Left, Right;
    F Bailout;
};

namespace float_type{
enum float_type
{
    Single = 0,
    Double = 1
};
}


struct parse_tree;
using parse_tree_ptr = std::shared_ptr<parse_tree>;
using func = void(*)(const void*);

func Assemble(parse_tree_ptr, int f = float_type::Double);
void FreeFunc(func);
