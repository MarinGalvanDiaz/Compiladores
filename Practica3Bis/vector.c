#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hoc.h"

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

static int check_sizes(Vector *a, Vector *b, char *operation) {
    if (a == NULL || b == NULL) {
        execerror("vector nulo en operacion", operation);
        return 0;
    }
    if (a->size != b->size) {
        execerror("vectores de diferente tamaño", operation);
        return 0;
    }
    return 1;
}

Vector *vector_add(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "suma")) return NULL;
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }
    return result;
}

Vector *vector_sub(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "resta")) return NULL;
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    return result;
}

double vector_dot(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "producto punto")) return 0.0;
    
    double result = 0.0;
    for (int i = 0; i < a->size; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

Vector *vector_cross(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) {
        execerror("vector nulo en operacion", "producto cruz");
        return NULL;
    }
    if (a->size != 3 || b->size != 3) {
        execerror("producto cruz solo para vectores 3D", "");
        return NULL;
    }
    
    Vector *result = create_vector(3);
    if (result == NULL) return NULL;
    
    result->size = 3;
    result->data[0] = a->data[1] * b->data[2] - a->data[2] * b->data[1];
    result->data[1] = a->data[2] * b->data[0] - a->data[0] * b->data[2];
    result->data[2] = a->data[0] * b->data[1] - a->data[1] * b->data[0];
    
    return result;
}

double vector_magnitude(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "magnitud");
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i] * v->data[i];
    }
    return sqrt(sum);
}

Vector *vector_normalize(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "normalizacion");
        return NULL;
    }
    
    double mag = vector_magnitude(v);
    if (mag == 0.0) {
        execerror("no se puede normalizar vector cero", "");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[i] / mag;
    }
    return result;
}