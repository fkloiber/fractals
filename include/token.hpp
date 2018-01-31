#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <infix_parser.h>

enum class token_type
{
    Invalid = -1,
    End = 0,
    Plus = TOK_PLUS,
    Minus = TOK_MINUS,
    Times = TOK_TIMES,
    Div = TOK_DIV,
    Exp = TOK_EXP,
    LParen = TOK_LPAREN,
    RParen = TOK_RPAREN,
#if 0
    Func = TOK_FUNC,
#endif
    Literal = TOK_LITERAL,
    Identifier = TOK_IDENTIFIER,
    Comma = TOK_COMMA,
    IntLiteral,
    DoubleLiteral
};

namespace detail {

inline char * strdup(const char * s)
{
    if (s == nullptr)
        return nullptr;
    char * r = (char*) malloc(strlen(s)+1);
    strcpy(r, s);
    return r;
}

}

struct token
{
    token_type Type;
    token(token_type t) : Type(t), V((int64_t)0) {}
    token(int64_t v) : Type(token_type::IntLiteral), V(v) {}
    token(double v) : Type(token_type::DoubleLiteral), V(v) {}
    token(const char * s) : Type(token_type::Identifier), V(detail::strdup(s)) {}
    ~token() { if(Type == token_type::Identifier) free((void*)V.Name); }
    union u {
        u(int64_t v) : IntLit(v) {}
        u(double v) : DblLit(v) {}
        u(const char * v) : Name(v) {}
        int64_t IntLit;
        double DblLit;
        const char * Name;
    } V;
};

inline token* MakeEnd()
{
    auto Result = new token{token_type::End};

    return Result;
}

inline token* MakePlus()
{
    auto Result = new token{token_type::Plus};

    return Result;
}

inline token* MakeMinus()
{
    auto Result = new token{token_type::Minus};

    return Result;
}

inline token* MakeTimes()
{
    auto Result = new token{token_type::Times};

    return Result;
}

inline token* MakeDiv()
{
    auto Result = new token{token_type::Div};

    return Result;
}

inline token* MakeExp()
{
    auto Result = new token{token_type::Exp};

    return Result;
}

inline token* MakeLParen()
{
    auto Result = new token{token_type::LParen};

    return Result;
}

inline token* MakeRParen()
{
    auto Result = new token{token_type::RParen};

    return Result;
}

inline token* MakeIntLiteral(int64_t Val)
{
    auto Result = new token{Val};

    return Result;
}

inline token* MakeDblLiteral(double Val)
{
    auto Result = new token{Val};

    return Result;
}

inline token* MakeIdentifier(const char * Name)
{
    auto Result = new token{Name};

    return Result;
}

inline token* MakeComma()
{
    auto Result = new token{token_type::Comma};

    return Result;
}
