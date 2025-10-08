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

// Nuevas funciones vectoriales
double vector_dot(Vector *a, Vector *b);
double vector_sum(Vector *v);
double vector_mean(Vector *v);
double vector_min(Vector *v);
double vector_max(Vector *v);
int vector_size(Vector *v);
Vector *vector_normalize(Vector *v);
Vector *vector_zeros(int size);
Vector *vector_ones(int size);
Vector *vector_linspace(double start, double end, int n);

jmp_buf begin;
char *progname;
int lineno = 1;
%}

%union {
    double val;
    Symbol *sym;
    Vector *vec;
}

// Definir los tokens ANTES de usarlos
%token <val> NUMBER
%token <sym> VAR BLTIN INDEF
%token VSUM VMEAN VMIN VMAX VSIZE VDOT VZEROS VONES VNORMALIZE VLINSPACE

%type <val> expr asgn term factor power unary scalar_expr vector_func_call
%type <vec> vector_expr vector_asgn vector_list vector_primary vector_func_vector
%type <sym> print_var

%right '='
%left '+' '-'
%left '*' '/'
%right '^'
%left UNARYMINUS

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
    | list print_var '\n' { 
        // Manejar variable sola
        if($2->type == TYPE_INDEF)
            execerror("variable no definida", $2->name);
        if($2->type == TYPE_VECTOR) {
            printf("\t[");
            for(int i = 0; i < $2->u.vec->size; i++) {
                printf("%.8g", $2->u.vec->data[i]);
                if(i < $2->u.vec->size - 1) printf(", ");
            }
            printf("]\n");
        } else {
            printf("\t%.8g\n", $2->u.val);
        }
    }
    | list error '\n' { yyerrok; } 
    ;

print_var: VAR { $$ = $1; }
    ;

asgn: VAR '=' expr { 
        // Permitir cambiar entre tipos
        if ($1->type == TYPE_VECTOR && $1->u.vec != NULL) {
            free_vector($1->u.vec);
        }
        $$ = $1->u.val = $3; 
        $1->type = TYPE_VAR;
        printf("\t%.8g\n", $3);
    }
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

/* Expresiones escalares */
scalar_expr: expr { $$ = $1; }
    ;

expr: term { $$ = $1; }
    | expr '+' term { $$ = $1 + $3; }
    | expr '-' term { $$ = $1 - $3; }
    | vector_func_call { $$ = $1; }  // Nuevo: llamadas a funciones vectoriales
    ;

term: factor { $$ = $1; }
    | term '*' factor { $$ = $1 * $3; }
    | term '/' factor { 
        if($3 == 0.0) execerror("division por cero", "");
        $$ = $1 / $3; 
    }
    ;

factor: power { $$ = $1; }
    | factor '^' power { $$ = Pow($1, $3); }
    ;

power: unary { $$ = $1; }
    ;

unary: NUMBER { $$ = $1; }
    | VAR { 
        if($1->type == TYPE_INDEF)
            execerror("variable no definida", $1->name);
        if($1->type == TYPE_VECTOR)
            execerror("variable es un vector, se necesita escalar", $1->name);
        $$ = $1->u.val;
    }
    | BLTIN '(' expr ')' { $$ = (*($1->u.ptr))($3); }
    | '(' expr ')' { $$ = $2; }
    | '-' unary %prec UNARYMINUS { $$ = -$2; }
    | '|' vector_expr '|' { $$ = vector_magnitude($2); }
    ;

/* NUEVO: Llamadas a funciones vectoriales que retornan escalares */
vector_func_call: VSUM '(' vector_expr ')' { 
        $$ = vector_sum($3);
    }
    | VMEAN '(' vector_expr ')' { 
        $$ = vector_mean($3);
    }
    | VMIN '(' vector_expr ')' { 
        $$ = vector_min($3);
    }
    | VMAX '(' vector_expr ')' { 
        $$ = vector_max($3);
    }
    | VSIZE '(' vector_expr ')' { 
        $$ = (double)vector_size($3);
    }
    | VDOT '(' vector_expr ',' vector_expr ')' { 
        $$ = vector_dot($3, $5);
    }
    ;

/* Expresiones vectoriales */
vector_expr: vector_primary { $$ = $1; }
    | vector_expr '+' vector_expr { $$ = vector_add($1, $3); }
    | vector_expr '-' vector_expr { $$ = vector_sub($1, $3); }
    | vector_expr '*' expr { $$ = vector_scalar_mult($1, $3); }
    | vector_func_vector { $$ = $1; }  // Nuevo: funciones que retornan vectores
    ;

/* NUEVO: Funciones que retornan vectores */
vector_func_vector: VZEROS '(' expr ')' { 
        $$ = vector_zeros((int)$3);
    }
    | VONES '(' expr ')' { 
        $$ = vector_ones((int)$3);
    }
    | VNORMALIZE '(' vector_expr ')' { 
        $$ = vector_normalize($3);
    }
    | VLINSPACE '(' expr ',' expr ',' expr ')' { 
        $$ = vector_linspace($3, $5, (int)$7);
    }
    ;

vector_primary: '[' vector_list ']' { $$ = $2; }
    | VAR { 
        if($1->type != TYPE_VECTOR)
            execerror("variable es escalar, se necesita vector", $1->name);
        $$ = $1->u.vec; 
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

%%

/* Resto del código permanece igual */
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
        
        n = lookup(sbuf);
        if (n == NULL) {
            // Instalar como INDEF y dejar que las asignaciones determinen el tipo
            n = install(sbuf, TYPE_INDEF, 0.0);
        }
        s = (Symbol*)(n->dato);
        yylval.sym = s;
        
        // Verificar si es una función vectorial
        if (strcmp(sbuf, "vsum") == 0) return VSUM;
        if (strcmp(sbuf, "vmean") == 0) return VMEAN;
        if (strcmp(sbuf, "vmin") == 0) return VMIN;
        if (strcmp(sbuf, "vmax") == 0) return VMAX;
        if (strcmp(sbuf, "vsize") == 0) return VSIZE;
        if (strcmp(sbuf, "vdot") == 0) return VDOT;
        if (strcmp(sbuf, "vzeros") == 0) return VZEROS;
        if (strcmp(sbuf, "vones") == 0) return VONES;
        if (strcmp(sbuf, "vnormalize") == 0) return VNORMALIZE;
        if (strcmp(sbuf, "vlinspace") == 0) return VLINSPACE;
        
        // Retornar tipo basado en el símbolo
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