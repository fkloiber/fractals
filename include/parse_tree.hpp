#pragma once

#include <list>
#include <string>
#include <memory>
#include <cstdint>

struct parse_tree;
using parse_tree_ptr = std::shared_ptr<parse_tree>;

#include "driver.hpp"
#include "parser_extra.hpp"

enum class expression_type
{
    Invalid = -1,
    Addition,
    Negation,
    Multiplication,
    Inversion,
    Exponentiation,
    Function,
    Literal,
    Identifier
};


struct parse_tree
{
    expression_type Type;
    int64_t IntVal;
    double DblVal;
    bool IsInteger;
    std::string Name;
    std::list<parse_tree_ptr> Params;
};

inline parse_tree * makeAddition(parse_tree * A, parse_tree * B)
{
    parse_tree * Result;

    if (A->Type == expression_type::Addition)
    {
        Result = A;
    } else
    {
        Result = new parse_tree;

        Result->Type = expression_type::Addition;
        Result->Params.emplace_back(A);
    }

    Result->Params.emplace_back(B);

    return Result;
}

inline parse_tree * makeNegation(parse_tree * A)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Negation;
    Result->Params.emplace_back(A);

    return Result;
}

inline parse_tree * makeSubtraction(parse_tree * A, parse_tree * B)
{
    return makeAddition(A, makeNegation(B));
}

inline parse_tree * makeMultiplication(parse_tree * A, parse_tree * B)
{
    parse_tree * Result;

    if (A->Type == expression_type::Multiplication)
    {
        Result = A;
    } else
    {
        Result = new parse_tree;

        Result->Type = expression_type::Multiplication;
        Result->Params.emplace_back(A);
    }

    Result->Params.emplace_back(B);

    return Result;
}

inline parse_tree * makeInversion(parse_tree * A)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Inversion;
    Result->Params.emplace_back(A);

    return Result;
}

inline parse_tree * makeDivision(parse_tree * A, parse_tree * B)
{
    return makeMultiplication(A, makeInversion(B));
}

inline parse_tree * makeExponentiation(parse_tree * A, parse_tree * B)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Exponentiation;
    Result->Params.emplace_back(A);
    Result->Params.emplace_back(B);

    return Result;
}

inline parse_tree * makeFunction(std::string && Name, std::list<parse_tree_ptr> && Args)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Function;
    Result->Name = std::move(Name);
    Result->Params = std::move(Args);

    return Result;
}

inline parse_tree * makeLiteral(int64_t Val)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Literal;
    Result->IsInteger = true;
    Result->IntVal = Val;

    return Result;
}

inline parse_tree * makeLiteral(double Val)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Literal;
    Result->IsInteger = false;
    Result->DblVal = Val;

    return Result;
}

inline parse_tree * makeLiteral(int Idx, driver * D)
{
    token & T = getT(D)[Idx];
    if (T.IsInteger)
    {
        return makeLiteral(T.Integer);
    } else
    {
        return makeLiteral(T.Double);
    }
}

inline parse_tree * makeIdentifier(std::string && Name)
{
    auto Result = new parse_tree;

    Result->Type = expression_type::Identifier;
    Result->Name = std::move(Name);

    return Result;
}


void print(parse_tree_ptr P, int Indent = 0);
