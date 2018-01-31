#include "driver.hpp"

#include <cstdlib>
#include <memory>

#include "infix_lexer.hpp"
#include "infix_parser.h"
#include "token.hpp"

void * InfixParseAlloc(void*(*)(size_t));
void InfixParseFree(void*, void(*)(void*));
void InfixParse(void*, int, token*, driver*);

struct parse_deleter
{
    void operator()(void * p) { InfixParseFree(p, free); }
};

bool
driver::Parse(const std::string & Line)
{
    Lexer MyLexer(Line);
    std::unique_ptr<void, parse_deleter> Parser(InfixParseAlloc(malloc));
    int TokenType;

    MyLexer.Driver = this;

    while ((TokenType = MyLexer.lex()) != 0)
    {
        InfixParse(Parser.get(), TokenType, MyLexer.NextToken, this);
        delete MyLexer.NextToken;
        MyLexer.NextToken = nullptr;
    }

    return false;
}

void
driver::Error()
{}
