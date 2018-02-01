%name InfixParse
%token_prefix TOK_
%token_type {int}
%extra_argument {driver * Driver}

%include {
#include "token.hpp"
#include "driver.hpp"
#include "parser_extra.hpp"
#include "parse_tree.hpp"
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

%type expr {parse_tree *}
%type args {std::list<parse_tree_ptr> *}
%destructor expr { delete $$; }
%destructor args { delete $$; }

line ::= expr(A). { Driver->Root = parse_tree_ptr(A); }

expr(A) ::= expr(B) PLUS expr(C).  { A = makeAddition(B, C); }
expr(A) ::= expr(B) MINUS expr(C). { A = makeSubtraction(B, C); }
expr(A) ::= expr(B) TIMES expr(C). { A = makeMultiplication(B, C); }
expr(A) ::= expr(B) DIV expr(C).   { A = makeDivision(B, C); }
expr(A) ::= expr(B) EXP expr(C).   { A = makeExponentiation(B, C); }
expr(A) ::= LPAREN expr(B) RPAREN. { A = B; }
expr(A) ::= MINUS expr(B). [NEG]   { A = makeNegation(B); }
expr(A) ::= IDENTIFIER(B) LPAREN args(C) RPAREN. { A = makeFunction(std::move(getT(Driver)[B].Name), std::move(*C)); }
expr(A) ::= LITERAL(B).            { A = makeLiteral(B, Driver); }
expr(A) ::= IDENTIFIER(B).         { A = makeIdentifier(std::move(getT(Driver)[B].Name)); }

args(A) ::= expr(B).               { A = new std::list<parse_tree_ptr>; A->emplace_back(B); }
args(A) ::= args(B) COMMA expr(C). { A = B; A->emplace_back(C); }
