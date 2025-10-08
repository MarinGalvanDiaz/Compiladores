struct nodoL {
    void *dato;
    struct nodoL *sig;
};
typedef struct nodoL NodoL;

#define MAX_VECTOR_SIZE 100

struct vector {
    double data[MAX_VECTOR_SIZE];
    int size;
};
typedef struct vector Vector;

// Usar prefijos para evitar conflictos con YACC
#define TYPE_INDEF 0
#define TYPE_VAR 1
#define TYPE_BLTIN 2
#define TYPE_VECTOR 3

struct symbol { 
    char   *name;
    short   type;   
    union {
        double val;	  	      
        double (*ptr)(double);
        Vector *vec;
    } u;
};
typedef struct symbol Symbol;

NodoL *lookup(char *s);
NodoL *install(char *s,int t, double d);
void init( );
Vector *create_vector(int size);
void free_vector(Vector *v);
Vector *vector_add(Vector *a, Vector *b);
Vector *vector_sub(Vector *a, Vector *b);
Vector *vector_scalar_mult(Vector *v, double scalar);
double vector_magnitude(Vector *v);
// Agregar estas declaraciones al final de hoc.h
// Agregar estas declaraciones al final de hoc.h

/* Funciones vectoriales */
double vector_dot(Vector *a, Vector *b);
Vector *vector_cross(Vector *a, Vector *b);
Vector *vector_normalize(Vector *v);
double vector_sum(Vector *v);
double vector_mean(Vector *v);
double vector_min(Vector *v);
double vector_max(Vector *v);
Vector *vector_concat(Vector *a, Vector *b);
Vector *vector_zeros(int size);
Vector *vector_ones(int size);
Vector *vector_linspace(double start, double end, int n);
Vector *vector_hadamard(Vector *a, Vector *b);
Vector *vector_divide(Vector *a, Vector *b);
Vector *vector_power(Vector *v, double exponent);
Vector *vector_abs(Vector *v);
Vector *vector_sin(Vector *v);
Vector *vector_cos(Vector *v);
Vector *vector_tan(Vector *v);
Vector *vector_exp(Vector *v);
Vector *vector_log(Vector *v);
Vector *vector_sqrt(Vector *v);
Vector *vector_round(Vector *v);
Vector *vector_floor(Vector *v);
Vector *vector_ceil(Vector *v);
int vector_size(Vector *v);
Vector *vector_copy(Vector *v);
Vector *vector_reverse(Vector *v);