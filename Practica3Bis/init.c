#include "hoc.h"
#include <math.h>

extern double Log(), Log10(), Sqrt(), Exp(), integer();

// Eliminar los wrappers duplicados ya que ahora manejamos las funciones directamente en hoc3.y

static struct {
    char *name; 
    double cval;
} consts[] = {
    "PI",    3.14159265358979323846,
    "E",     2.71828182845904523536,
    "GAMMA", 0.57721566490153286060,
    "DEG",  57.29577951308232087680,
    "PHI",   1.61803398874989484820,
    0,       0
};

static struct {
    char *name;
    double (*func)(double);
} builtins[] = {
    "sin",  sin,
    "cos",  cos,
    "atan", atan,
    "log",  Log,
    "log10", Log10,
    "exp",  Exp,
    "sqrt", Sqrt,
    "int",  integer,
    "abs",  fabs,
    0,      0
};
// En init.c, comentar o eliminar la sección de vector_builtins
// ya que ahora manejamos las funciones directamente en el parser

void init() {
    int i;
    Symbol *s;

    // Instalar constantes como VARIABLES escalares
    for (i = 0; consts[i].name; i++) {
        install(consts[i].name, TYPE_VAR, consts[i].cval);
    }
    
    // Instalar funciones built-in escalares
    for (i = 0; builtins[i].name; i++) {
        s = (Symbol *)(install(builtins[i].name, TYPE_BLTIN, 0.0)->dato);
        s->u.ptr = builtins[i].func;
    }
    
    // NO instalar las funciones vectoriales aquí
    // Se manejan directamente en el parser con tokens específicos
}