%option unicode
%option fast

%top{
    #include "infix_parser.h"
    #include "driver.hpp"
    #include "token.hpp"
    #include <cerrno>
    #include <cstdlib>
%}

%class{
public:
    token * NextToken;
    driver * Driver;
%}

%%

0|[1-9][0-9]*  {
    errno = 0;
    int64_t Val = std::strtoll(text(), nullptr, 10);
    if (errno == ERANGE)
    {
        Driver->Error();
        return -1;
    }
    NextToken = MakeIntLiteral(Val);
    return TOK_LITERAL;
}

[1-9][0-9]*"."[0-9]*|"."[0-9]+ {
    errno = 0;
    double Val = std::strtod(text(), nullptr);
    if (errno == ERANGE)
    {
        Driver->Error();
        return -1;
    }
    NextToken = MakeDblLiteral(Val);
    return TOK_LITERAL;
}

[a-zA-Z]+_?[a-zA-Z]* {
    NextToken = MakeIdentifier(text());
    return TOK_IDENTIFIER;
}

"+" { NextToken = MakePlus(); return TOK_PLUS; }
"-" { NextToken = MakeMinus(); return TOK_MINUS; }
"*" { NextToken = MakeTimes(); return TOK_TIMES; }
"/" { NextToken = MakeDiv(); return TOK_DIV; }
"^" { NextToken = MakeExp(); return TOK_EXP; }
"(" { NextToken = MakeLParen(); return TOK_LPAREN; }
")" { NextToken = MakeRParen(); return TOK_RPAREN; }
"," { NextToken = MakeComma(); return TOK_COMMA; }

[ \t]+

. { Driver->Error(); return -1; }

%%
