%name InfixParse
%token_prefix TOK_
%token_type {int}
%extra_argument {driver * Driver}

%include {
#include "token.hpp"
#include "driver.hpp"
#include "parser_extra.hpp"
}

%parse_accept {
    Driver->Success = true;
}
%parse_failure {
    Driver->Success = false;
}

%left PLUS MINUS.
%left TIMES DIV.
%nonassoc NEG.
%right EXP.

line ::= expr.

expr ::= expr PLUS expr.
expr ::= expr MINUS expr.
expr ::= expr TIMES expr.
expr ::= expr DIV expr.
expr ::= expr EXP expr.
expr ::= LPAREN expr RPAREN.
expr ::= MINUS expr. [NEG]
expr ::= IDENTIFIER LPAREN args RPAREN.
expr ::= LITERAL.
expr ::= IDENTIFIER.

args ::= expr.
args ::= args COMMA expr.
