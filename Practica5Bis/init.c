#include "hoc.h"
#include "y.tab.h"
#include <math.h>
#include <stdio.h>
extern double   Log(), Log10(), Sqrt(), Exp(), integer();

static struct { 
    char *name;  /* Palabras clave */
    int  kval;
} keywords[] = {
    "if",    HOC_IF,
    "else",  HOC_ELSE,
    "while", HOC_WHILE,
    "print", HOC_PRINT,
    0,       0,
};

static struct { 
    char *name; 
    double cval;
} consts[] = {
    "PI",    3.14159265358979323846,
    "E",     2.71828182845904523536,
    "GAMMA", 0.57721566490153286060,
    "DEG",  57.29577951308232087680,
    "PHI",   1.6180339887498948*820,
    0,       0
};

static struct {
    char *name;
    double (*func)();
} builtins[] = {
    "sin",   sin,
    "cos",   cos,
    "atan",  atan,
    "log",   Log,
    "log10", Log10,
    "exp",   Exp,
    "sqrt",  Sqrt,
    "int",   integer,
    "abs",   fabs,
    0,       0
};

void init()  /* instalar constantes y predefinidos en la tabla */
{
    int i;
    Symbol *s;

    for (i = 0; keywords[i].name; i++)
        install(keywords[i].name, keywords[i].kval, 0.0);
    for (i = 0; consts[i].name; i++)
        install(consts[i].name, HOC_VAR, consts[i].cval);
    for (i = 0; builtins[i].name; i++) {
        s = install(builtins[i].name, HOC_BLTIN, 0.0);
        s->u.ptr = builtins[i].func;
    }

    // Instalar algunas variables predefinidas
    install("vec", HOC_VAR, 0.0);
    install("a", HOC_VAR, 0.0);
    install("b", HOC_VAR, 0.0);
    install("c", HOC_VAR, 0.0);
}