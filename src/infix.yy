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
expr ::= FUNC LPAREN args RPAREN.
expr ::= LITERAL.
expr ::= IDENTIFIER.

args ::= expr.
args ::= args COMMA expr.
