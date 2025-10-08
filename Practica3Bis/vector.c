#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoc.h"

// Declarar execerror que está definido en hoc3.y
extern void execerror(char *s, char *t);

Vector *create_vector(int size) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (v == NULL) {
        execerror("memoria insuficiente para vector", "");
        return NULL;
    }
    v->size = 0;
    return v;
}

void free_vector(Vector *v) {
    if (v != NULL) {
        free(v);
    }
}

Vector *vector_add(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) {
        execerror("vector nulo en operacion", "");
        return NULL;
    }
    
    if (a->size != b->size) {
        execerror("vectores de diferente tamaño en suma", "");
        return NULL;
    }
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }
    
    return result;
}

Vector *vector_sub(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) {
        execerror("vector nulo en operacion", "");
        return NULL;
    }
    
    if (a->size != b->size) {
        execerror("vectores de diferente tamaño en resta", "");
        return NULL;
    }
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    
    return result;
}

Vector *vector_scalar_mult(Vector *v, double scalar) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    
    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[i] * scalar;
    }
    
    return result;
}

double vector_magnitude(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "");
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i] * v->data[i];
    }
    return sqrt(sum);
}