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

// Declaraciones de funciones vectoriales
Vector *create_vector(int size);
void free_vector(Vector *v);
Vector *vector_add(Vector *a, Vector *b);
Vector *vector_sub(Vector *a, Vector *b);
double vector_dot(Vector *a, Vector *b);
Vector *vector_cross(Vector *a, Vector *b);
double vector_magnitude(Vector *v);
Vector *vector_normalize(Vector *v);

jmp_buf begin;
char *progname;
int lineno = 1;
%}

%union {
    double val;
    Vector *vec;
    Symbol *sym;
}

%token <sym> VAR BLTIN
%token <val> NUMBER
%type <vec> vector_expr vector_asgn vector_list vector_primary
%type <sym> print_var

%left '+' '-'

%% /* Reglas gramaticales y acciones */

list:   
    | list '\n'
    | list vector_asgn '\n'  
    | list vector_expr '\n' { 
        printf("\t[");
        for(int i = 0; i < $2->size; i++) {
            printf("%.8g", $2->data[i]);
            if(i < $2->size - 1) printf(", ");
        }
        printf("]\n"); 
    }
    | list print_var '\n' { 
        // Manejar variable sola
        if($2->type == TYPE_INDEF)
            execerror("variable no definida", $2->name);
        printf("\t[");
        for(int i = 0; i < $2->u.vec->size; i++) {
            printf("%.8g", $2->u.vec->data[i]);
            if(i < $2->u.vec->size - 1) printf(", ");
        }
        printf("]\n");
    }
    | list error '\n' { yyerrok; } 
    ;

print_var: VAR { $$ = $1; }
    ;

vector_asgn: VAR '=' vector_expr { 
        // Permitir cambiar entre tipos
        if ($1->type == TYPE_VECTOR && $1->u.vec != NULL) {
            free_vector($1->u.vec);
        }
        $1->u.vec = $3;
        $1->type = TYPE_VECTOR;
        // Mostrar el vector asignado
        printf("\t[");
        for(int i = 0; i < $3->size; i++) {
            printf("%.8g", $3->data[i]);
            if(i < $3->size - 1) printf(", ");
        }
        printf("]\n");
    }
    ;
vector_primary: '[' vector_list ']' { $$ = $2; }
    | VAR { 
        if($1->type != TYPE_VECTOR)
            execerror("variable no es un vector", $1->name);
        $$ = $1->u.vec; 
    }
    ;
/* Expresiones vectoriales */
vector_expr: vector_primary { $$ = $1; }
    | vector_expr '+' vector_expr { $$ = vector_add($1, $3); }
    | vector_expr '-' vector_expr { $$ = vector_sub($1, $3); }
    | BLTIN '(' vector_expr ')' { 
        // Funciones que toman 1 vector y retornan vector o escalar
        if (strcmp($1->name, "mag") == 0) {
            double result = vector_magnitude($3);
            Vector *v = create_vector(1);
            v->data[0] = result;
            v->size = 1;
            $$ = v;
        } else if (strcmp($1->name, "norm") == 0) {
            $$ = vector_normalize($3);
        } else {
            execerror("funcion vectorial desconocida", $1->name);
            $$ = $3;
        }
    }
    | BLTIN '(' vector_expr ',' vector_expr ')' { 
        // Funciones que toman 2 vectores
        if (strcmp($1->name, "dot") == 0) {
            double result = vector_dot($3, $5);
            Vector *v = create_vector(1);
            v->data[0] = result;
            v->size = 1;
            $$ = v;
        } else if (strcmp($1->name, "cross") == 0) {
            $$ = vector_cross($3, $5);
        } else if (strcmp($1->name, "sum") == 0) {
            $$ = vector_add($3, $5);
        } else if (strcmp($1->name, "sub") == 0) {
            $$ = vector_sub($3, $5);
        } else {
            execerror("funcion vectorial desconocida", $1->name);
            $$ = $3;
        }
    }
    ;



vector_list: NUMBER { 
        Vector *v = create_vector(1);
        v->data[0] = $1;
        v->size = 1;
        $$ = v;
    }
    | vector_list ',' NUMBER { 
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

%%

/* Resto del código */
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
        double value;
        scanf("%lf", &value);
        yylval.val = value;
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
        
        n = lookup(sbuf);
        if (n == NULL) {
            // Instalar como vector por defecto
            n = install(sbuf, TYPE_VECTOR, 0.0);
            s = (Symbol*)(n->dato);
            s->u.vec = NULL;
        }
        s = (Symbol*)(n->dato);
        yylval.sym = s;
        
        // Si es una función builtin, retornar BLTIN
        if (s->type == TYPE_BLTIN) {
            return BLTIN;
        } else {
            return VAR;
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