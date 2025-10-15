#include "hoc.h"
#include <math.h>

// Wrappers dummy para funciones builtin (no se usan directamente)
double builtin_dummy() { return 0.0; }

static struct {
    char *name; 
    double cval;
} consts[] = {
    "PI",    3.14159265358979323846,
    "E",     2.71828182845904523536,
    0,       0
};

// Las 5 funciones vectoriales básicas
static struct {
    char *name;
} vector_builtins[] = {
    "sum",      // suma de vectores
    "sub",      // resta de vectores  
    "dot",      // producto punto
    "cross",    // producto cruz
    "mag",      // magnitud
    "norm",     // normalizar
    0
};

void init() {
    int i;
    Symbol *s;

    // Instalar constantes como vectores de 1 elemento
    for (i = 0; consts[i].name; i++) {
        NodoL *n = install(consts[i].name, TYPE_VECTOR, 0.0);
        Symbol *sym = (Symbol *)(n->dato);
        sym->u.vec = create_vector(1);
        sym->u.vec->data[0] = consts[i].cval;
        sym->u.vec->size = 1;
    }
    
    // Instalar funciones vectoriales como BLTIN
    for (i = 0; vector_builtins[i].name; i++) {
        s = (Symbol *)(install(vector_builtins[i].name, TYPE_BLTIN, 0.0)->dato);
        s->u.ptr = builtin_dummy;  // No se usa directamente
    }
}