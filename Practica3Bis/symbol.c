#include <stdlib.h>
#include <string.h>
#include "hoc.h" 

static NodoL *symlist = NULL;

NodoL *creaNodoL(void *dato, NodoL *sig){
    NodoL *nvo = (NodoL*)malloc(sizeof(NodoL));
    if (nvo == NULL) return NULL;
    nvo->dato = dato;
    nvo->sig = sig;
    return nvo;
}

Symbol *creaSymbol(char *s, int t, double d){
    Symbol *sp = (Symbol *)malloc(sizeof(Symbol));
    if (sp == NULL) return NULL;
    sp->name = strdup(s);
    sp->type = t;
    if (t == TYPE_VECTOR) {
        sp->u.vec = NULL;
    } else {
        sp->u.ptr = NULL;
    }
    return sp;
}

NodoL *lookup(char *s){
    NodoL *p;
    for(p = symlist; p; p = p->sig) {
        Symbol *sym = (Symbol*)p->dato;
        if(strcmp(sym->name, s) == 0)
            return p;
    }
    return NULL;
}

NodoL *install(char *s, int t, double d) {
    // Verificar si ya existe
    NodoL *existing = lookup(s);
    if (existing != NULL) {
        Symbol *sym = (Symbol *)existing->dato;
        sym->type = t;
        return existing;
    }
    
    // Crear nuevo símbolo
    Symbol *sp = creaSymbol(s, t, d);
    if (sp == NULL) return NULL;
    
    symlist = creaNodoL(sp, symlist);
    return symlist; 
}