#ifndef HOC_H
#define HOC_H

#include "vector.h"

struct nodoL {
    void *dato;
    struct nodoL *sig;
};
typedef struct nodoL NodoL;

struct symbol { 
    char   *name;
    short   type;   
    union {
        double val;	  	      
        double (*ptr)(double);     
    } u;
};
typedef struct symbol Symbol;

/* Tipos internos (renombrados para evitar conflicto con tokens) */
enum { VAR_TYPE = 1, BLTIN_TYPE, UNDEF_TYPE };

NodoL *lookup(char *s);
NodoL *install(char *s,int t, double d);
void init(void);

#endif
