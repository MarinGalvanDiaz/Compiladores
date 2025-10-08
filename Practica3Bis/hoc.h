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