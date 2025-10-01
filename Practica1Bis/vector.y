%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int n;
    double *vec;
} Vector;

void yyerror(char *s);
int yylex();
Vector *creaVector(int n);
void imprimeVector(Vector *v);
Vector *copiaVector(Vector *v);
Vector *sumaVector(Vector *a, Vector *b);
Vector *restaVector(Vector *a, Vector *b);
Vector *productoCruz(Vector *a, Vector *b);
double productoPunto(Vector *a, Vector *b);
Vector *parseVector(const char *input);

// Definición de la unión para YYSTYPE
%}

%union {
    double number;
    Vector *vector;
}

%token <vector> VECTOR
%token <number> NUMBER
%type <vector> exp vector_operation
%type <number> dot_product

%left '+' '-'
%left '*' '/'
%left DOT CROSS

%%
input:
    | input line
    ;

line:
    '\n'
    | exp '\n' {
        printf("\tResultado: ");
        imprimeVector($1);
        free($1->vec);
        free($1);
    }
    | dot_product '\n' {
        printf("\tProducto punto: %f\n", $1);
    }
    | error '\n' { yyerrok; }
    ;

exp: 
    VECTOR { $$ = $1; }
    | exp '+' exp {
        Vector *a = $1;
        Vector *b = $3;
        if (a->n != b->n) {
            printf("Error: Vectores de dimensiones diferentes (%d vs %d)\n", a->n, b->n);
            exit(1);
        }
        $$ = sumaVector(a, b);
        free(a->vec); free(a);
        free(b->vec); free(b);
    }
    | exp '-' exp {
        Vector *a = $1;
        Vector *b = $3;
        if (a->n != b->n) {
            printf("Error: Vectores de dimensiones diferentes (%d vs %d)\n", a->n, b->n);
            exit(1);
        }
        $$ = restaVector(a, b);
        free(a->vec); free(a);
        free(b->vec); free(b);
    }
    | exp '*' exp {
        // Producto cruz (solo para vectores 3D)
        Vector *a = $1;
        Vector *b = $3;
        if (a->n != 3 || b->n != 3) {
            printf("Error: Producto cruz solo definido para vectores 3D\n");
            exit(1);
        }
        $$ = productoCruz(a, b);
        free(a->vec); free(a);
        free(b->vec); free(b);
    }
    | '(' exp ')' { $$ = $2; }
    ;

dot_product:
    exp DOT exp {
        Vector *a = $1;
        Vector *b = $3;
        if (a->n != b->n) {
            printf("Error: Vectores de dimensiones diferentes (%d vs %d)\n", a->n, b->n);
            exit(1);
        }
        $$ = productoPunto(a, b);
        free(a->vec); free(a);
        free(b->vec); free(b);
    }
    ;

%%

int yylex() {
    int c;
    static char buffer[256];
    static int buffer_index = 0;
    
    while ((c = getchar()) == ' ' || c == '\t')  
        ;
    
    if (c == EOF) return 0;
    
    // Detectar inicio de vector [
    if (c == '[') {
        buffer_index = 0;
        buffer[buffer_index++] = c;
        
        // Leer hasta encontrar el ] correspondiente
        while ((c = getchar()) != ']' && c != EOF && buffer_index < 255) {
            buffer[buffer_index++] = c;
        }
        if (c == ']') {
            buffer[buffer_index++] = c;
            buffer[buffer_index] = '\0';
            
            // Parsear el vector
            yylval.vector = parseVector(buffer);
            return VECTOR;
        }
    }
    
    // Detectar producto punto "."
    if (c == '.') {
        return DOT;
    }
    
    // Detectar producto cruz (usaremos '*' pero añadimos token CROSS para claridad)
    if (c == '*') {
        return '*'; // Ya definido en la gramática
    }
    
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval.number);
        return NUMBER;
    }
    
    return c;
}

Vector *parseVector(const char *input) {
    char *copy = strdup(input);
    char *token;
    double values[100];
    int count = 0;
    
    // Remover los corchetes
    copy[strlen(copy)-1] = '\0'; // remover ]
    token = strtok(copy+1, ","); // saltar [
    
    while (token != NULL && count < 100) {
        // Remover espacios
        char *clean_token = token;
        while (*clean_token == ' ') clean_token++;
        
        values[count++] = atof(clean_token);
        token = strtok(NULL, ",");
    }
    
    free(copy);
    
    Vector *vec = creaVector(count);
    for (int i = 0; i < count; i++) {
        vec->vec[i] = values[i];
    }
    
    return vec;
}

void init() {
    // Ya no necesitamos memoria para variables
}

int main() { 
    init();
    printf("Calculadora de Vectores - Operaciones Directas\n");
    printf("Operaciones disponibles:\n");
    printf("  Suma: [1,2,3] + [4,5,6]\n");
    printf("  Resta: [1,2,3] - [4,5,6]\n");
    printf("  Producto punto: [1,2,3] . [4,5,6]\n");
    printf("  Producto cruz: [1,2,3] * [4,5,6] (solo 3D)\n");
    printf("> ");
    yyparse(); 
    return 0;
}

void yyerror(char *s) { 
    printf("Error de sintaxis: %s\n", s); 
}

Vector *creaVector(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->n = n;    
    vec->vec = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++)
        vec->vec[i] = 0.0;
    return vec;
}

void imprimeVector(Vector *v) {
    int i; 
    printf("[");
    for (i = 0; i < v->n; i++) {
        printf("%.2f", v->vec[i]);
        if (i < v->n - 1) printf(", ");
    }
    printf("] (dimensión: %d)\n", v->n);
}

Vector *copiaVector(Vector *v) {
    Vector *copy = creaVector(v->n);
    for (int i = 0; i < v->n; i++)
        copy->vec[i] = v->vec[i];    
    return copy;    
}

Vector *sumaVector(Vector *a, Vector *b) {
    Vector *c = creaVector(a->n);
    for (int i = 0; i < a->n; i++)
        c->vec[i] = a->vec[i] + b->vec[i];
    return c;
}

Vector *restaVector(Vector *a, Vector *b) {
    Vector *c = creaVector(a->n);
    for (int i = 0; i < a->n; i++)
        c->vec[i] = a->vec[i] - b->vec[i];
    return c;
}

double productoPunto(Vector *a, Vector *b) {
    double resultado = 0.0;
    for (int i = 0; i < a->n; i++)
        resultado += a->vec[i] * b->vec[i];
    return resultado;
}

Vector *productoCruz(Vector *a, Vector *b) {
    if (a->n != 3 || b->n != 3) {
        return NULL;
    }
    
    Vector *c = creaVector(3);
    c->vec[0] = a->vec[1] * b->vec[2] - a->vec[2] * b->vec[1];
    c->vec[1] = a->vec[2] * b->vec[0] - a->vec[0] * b->vec[2];
    c->vec[2] = a->vec[0] * b->vec[1] - a->vec[1] * b->vec[0];
    return c;
}
