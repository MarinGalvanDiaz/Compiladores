#ifndef VECTOR_H
#define VECTOR_H

#include "hoc.h"

// Declarar las variables globales como extern
extern double temp_vector_data[];
extern int temp_vector_size;

// Declarar funciones de vectores
void assign_vector_to_var(Symbol *s, double *data, int size);

#endif /* VECTOR_H */