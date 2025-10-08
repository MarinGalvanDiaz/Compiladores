%{
#include <stdio.h>
#include <stdlib.h>
#include "hoc.h"
#include "vector.h"  // si defines Vector aquí
void yyerror(const char *s);
int yylex(void);
%}

%union {
    double val;        // para números
    Symbol *sym;       // para variables y funciones
    Vector *vec;       // para vectores
}

%token <val> NUMBER
%token <sym> VAR BLTIN INDEF
%token <vec> VECTOR
%token DOT
%type <val> expr
%type <vec> exp vector_operation
%type <sym> sym_expr

%left '+' '-'
%left '*' '/'
%right '^'
%right UNARYMINUS
%%

/* ----------- Gramática ----------- */

input:
      /* vacío */
    | input line
    ;

line:
      '\n'
    | expr '\n'   { printf("= %g\n", $1); }
    ;

expr:
      NUMBER              { $$ = $1; }
    | VAR                 { $$ = $1->u.val; }
    | expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr       { $$ = $1 - $3; }
    | expr '*' expr       { $$ = $1 * $3; }
    | expr '/' expr       { $$ = $1 / $3; }
    | '(' expr ')'        { $$ = $2; }
    | '-' expr %prec UNARYMINUS { $$ = -$2; }
    ;

%%

/* ----------- Código C auxiliar ----------- */

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis: %s\n", s);
}

int main(void) {
    printf("Analizador de expresiones matemáticas\n");
    init();  /* inicializa constantes y funciones */
    yyparse();
    return 0;
}
