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

NodoL *find(NodoL *inicio, void *key, int (*igual)(void *, void *)){
    NodoL *p;
    for(p = inicio; p; p = p->sig)
        if(!(*igual)(p->dato, key))
            return p;
    return NULL;
}

Symbol *creaSymbol(char *s, int t, double d){
    Symbol *sp = (Symbol *)malloc(sizeof(Symbol));
    if (sp == NULL) return NULL;
    sp->name = strdup(s);
    sp->type = t;
    if (t == TYPE_VECTOR) {
        sp->u.vec = NULL;
    } else {
        sp->u.val = d;
    }
    return sp;
}

int cmpSymbol(void *p1, void *p2){
    Symbol *s1 = (Symbol*)p1;
    Symbol *s2 = (Symbol*)p2;
    return strcmp(s1->name, s2->name);
}

NodoL *lookup(char *s){
    Symbol *temp = creaSymbol(s, TYPE_INDEF, 0.0);
    if (temp == NULL) return NULL;
    
    NodoL *result = find(symlist, (void *)temp, cmpSymbol);
    free(temp->name);
    free(temp);
    return result;
}

NodoL *install(char *s, int t, double d) {
    // Primero verificar si ya existe
    NodoL *existing = lookup(s);
    if (existing != NULL) {
        Symbol *sym = (Symbol *)existing->dato;
        if (t == TYPE_VECTOR) {
            sym->type = TYPE_VECTOR;
            sym->u.vec = NULL;
        } else {
            sym->type = t;
            sym->u.val = d;
        }
        return existing;
    }
    
    Symbol *sp = creaSymbol(s, t, d);
    if (sp == NULL) return NULL;
    
    symlist = creaNodoL(sp, symlist);
    return symlist; 
}