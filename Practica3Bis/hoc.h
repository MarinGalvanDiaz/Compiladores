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

// Tipos
#define TYPE_VECTOR 1
#define TYPE_INDEF 0
#define TYPE_BLTIN 2  // Para funciones builtin

struct symbol { 
    char   *name;
    short   type;   // TYPE_VECTOR, TYPE_INDEF, o TYPE_BLTIN
    union {
        Vector *vec;    // Para variables vectoriales
        double (*ptr)(); // Para funciones builtin (no se usa directamente)
    } u;
};
typedef struct symbol Symbol;

NodoL *lookup(char *s);
NodoL *install(char *s, int t, double d);
void init();

/* Funciones vectoriales básicas */
Vector *create_vector(int size);
void free_vector(Vector *v);
Vector *vector_add(Vector *a, Vector *b);
Vector *vector_sub(Vector *a, Vector *b);
double vector_dot(Vector *a, Vector *b);
Vector *vector_cross(Vector *a, Vector *b);
double vector_magnitude(Vector *v);
Vector *vector_normalize(Vector *v);