%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include "hoc.h"

void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
void execerror(char *s, char *t);
void fpecatch();
extern double Pow(double, double);

// Declaraciones de funciones vectoriales
Vector *create_vector(int size);
Vector *vector_add(Vector *a, Vector *b);
Vector *vector_sub(Vector *a, Vector *b);
Vector *vector_scalar_mult(Vector *v, double scalar);
double vector_magnitude(Vector *v);

jmp_buf begin;
char *progname;
int lineno = 1;
%}

%union {
    double val;
    Symbol *sym;
    Vector *vec;
}

%token <val> NUMBER
%token <sym> VAR BLTIN INDEF

%type <val> expr asgn
%type <vec> vector_expr vector_asgn vector_list

%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '^'

%% /* Reglas gramaticales y acciones */

list:   
    | list '\n'
    | list asgn '\n'
    | list vector_asgn '\n'  
    | list expr '\n'  { printf("\t%.8g\n", $2); }
    | list vector_expr '\n' { 
        printf("\t[");
        for(int i = 0; i < $2->size; i++) {
            printf("%.8g", $2->data[i]);
            if(i < $2->size - 1) printf(", ");
        }
        printf("]\n"); 
    }
    | list error '\n' { yyerrok; } 
    ;

asgn: VAR '=' expr { 
        $$ = $1->u.val = $3; 
        $1->type = TYPE_VAR;
    }
    ;

vector_asgn: VAR '=' vector_expr { 
        $1->u.vec = $3;
        $1->type = TYPE_VECTOR;
    }
    ;

vector_expr: '[' vector_list ']' { 
        $$ = $2; 
    }
    | VAR { 
        if($1->type != TYPE_VECTOR)
            execerror("no es un vector", $1->name);
        $$ = $1->u.vec; 
    }
    | vector_expr '+' vector_expr { 
        $$ = vector_add($1, $3); 
    }
    | vector_expr '-' vector_expr { 
        $$ = vector_sub($1, $3); 
    }
    | vector_expr '*' expr { 
        $$ = vector_scalar_mult($1, $3); 
    }
    | expr '*' vector_expr { 
        $$ = vector_scalar_mult($3, $1); 
    }
    ;

vector_list: expr { 
        Vector *v = create_vector(1);
        v->data[0] = $1;
        v->size = 1;
        $$ = v;
    }
    | vector_list ',' expr { 
        if($1->size < MAX_VECTOR_SIZE) {
            $1->data[$1->size] = $3;
            $1->size++;
            $$ = $1;
        } else {
            execerror("vector demasiado grande", "");
            $$ = $1;
        }
    }
    ;

expr: NUMBER { $$ = $1; }
    | VAR { 
        if($1->type == TYPE_INDEF)
            execerror("variable no definida", $1->name);
        if($1->type == TYPE_VECTOR)
            execerror("es un vector, no un escalar", $1->name);
        $$ = $1->u.val;
    }
    | asgn
    | BLTIN '(' expr ')' { $$ = (*($1->u.ptr))($3); }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if($3 == 0.0)
            execerror("division por cero", "");
        $$ = $1 / $3; 
    }
    | expr '^' expr { $$ = Pow($1, $3); }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UNARYMINUS { $$ = -$2; }
    | '|' vector_expr '|' { $$ = vector_magnitude($2); }
    ;
%%

/* Aquí van las funciones que faltaban */
void main(int argc, char *argv[]) {
    progname = argv[0];
    init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
    yyparse();
}

void execerror(char *s, char *t) {
    warning(s, t);
    longjmp(begin, 0);
}

void fpecatch() {
    execerror("excepcion de punto flotante", (char *)0);
}

int yylex() {
    int c;

    while ((c = getchar()) == ' ' || c == '\t')  
        ;
    if (c == EOF)                            
        return 0;
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval.val);
        return NUMBER;
    }
    if (isalpha(c)) {
        NodoL *n;
        Symbol *s;
        char sbuf[200], *p = sbuf;
        do {
            *p++ = c;
        } while ((c = getchar()) != EOF && isalnum(c));
        ungetc(c, stdin);
        *p = '\0';
        if ((n = lookup(sbuf)) == NULL)
            n = install(sbuf, TYPE_INDEF, 0.0);
        s = (Symbol*)(n->dato);
        yylval.sym = s;   
        if (s->type == TYPE_INDEF) {
            return VAR;
        } else {
            return s->type;
        }
    }
    if (c == '\n') {
        lineno++;
    }
    return c;
}

void yyerror(char *s) {
    warning(s, (char *)0);
}

void warning(char *s, char *t) {
    fprintf(stderr, "%s: %s", progname, s);
    if (t)
        fprintf(stderr, " %s", t);
    fprintf(stderr, " cerca de la linea %d\n", lineno);
}