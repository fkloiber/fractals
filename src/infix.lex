%option unicode
%option fast

%top{
    #include "driver.hpp"
    #include "token.hpp"
    #include "parser_extra.hpp"
    #include <cerrno>
    #include <cstdlib>
%}

%class{
public:
    int NextToken;
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
    EMPLACE(Val);
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
    EMPLACE(Val);
    return TOK_LITERAL;
}

[a-zA-Z]+_?[a-zA-Z]* {
    EMPLACE(str());
    return TOK_IDENTIFIER;
}

"+" { EMPLACE(token_type::Plus);   return TOK_PLUS; }
"-" { EMPLACE(token_type::Minus);  return TOK_MINUS; }
"*" { EMPLACE(token_type::Times);  return TOK_TIMES; }
"/" { EMPLACE(token_type::Div);    return TOK_DIV; }
"^" { EMPLACE(token_type::Exp);    return TOK_EXP; }
"(" { EMPLACE(token_type::LParen); return TOK_LPAREN; }
")" { EMPLACE(token_type::RParen); return TOK_RPAREN; }
"," { EMPLACE(token_type::Comma);  return TOK_COMMA; }

[ \t]+

. { Driver->Error(); return -1; }

%%
