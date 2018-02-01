#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <infix_parser.h>

enum class token_type
{
    Invalid = -1,
    Plus = TOK_PLUS,
    Minus = TOK_MINUS,
    Times = TOK_TIMES,
    Div = TOK_DIV,
    Exp = TOK_EXP,
    LParen = TOK_LPAREN,
    RParen = TOK_RPAREN,
    Literal = TOK_LITERAL,
    Identifier = TOK_IDENTIFIER,
    Comma = TOK_COMMA
};

struct token
{
    token_type Type;
    bool IsInteger;
    int64_t Integer;
    double Double;
    std::string Name;
    token() : Type(token_type::Invalid) {}
    token(token_type T) : Type(T) {}
    token(int64_t V) : Type(token_type::Literal), IsInteger(true), Integer(V) {}
    token(double V) : Type(token_type::Literal), IsInteger(false), Double(V) {}
    token(const std::string & N) :
        Type(token_type::Identifier),
        Name(N)
    {}
};
