%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hoc.h"
#include "vector.tab.h"   // generado por Bison, contiene tokens y YYSTYPE
extern Vector *parseVector(const char *input);
%}

%%

[0-9]+(\.[0-9]+)? {
    yylval.val = atof(yytext); 
    return NUMBER; 
}

"["[^]]*"]" {
    yylval.vec = parseVector(yytext); 
    return VECTOR;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    NodoL *n = lookup(yytext);
    if (!n) n = install(yytext, INDEF, 0.0);
    yylval.sym = (Symbol *) n->dato;
    return VAR;
}

[ \t]+       ;        /* ignorar espacios */
\n           return '\n';
"+"          return '+';
"-"          return '-';
"*"          return '*';
"/"          return '/';
"("          return '(';
")"          return ')';
"."          return DOT;  /* producto punto */

.            return yytext[0];

%%

int yywrap(void) { return 1; }
