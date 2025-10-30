#include "hoc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX_VECTOR_SIZE 1000
#define MAX_VECTORS 100

// Estructura para vector
typedef struct {
    char name[50];
    double data[MAX_VECTOR_SIZE];
    int size;
} Vector;

static Vector vectors[MAX_VECTORS];
static int vector_count = 0;

// Variables temporales para construcción de vectores
static double temp_vector_data[MAX_VECTOR_SIZE];
static int temp_vector_size = 0;

// Buscar o crear vector
static Vector* get_vector(const char *name) {
    printf("DEBUG: Buscando vector '%s'\n", name); // Debug
    
    // Buscar si ya existe
    for (int i = 0; i < vector_count; i++) {
        if (strcmp(vectors[i].name, name) == 0) {
            printf("DEBUG: Vector encontrado, tamaño: %d\n", vectors[i].size); // Debug
            return &vectors[i];
        }
    }
    
    // Crear nuevo
    if (vector_count < MAX_VECTORS) {
        Vector *vec = &vectors[vector_count];
        strcpy(vec->name, name);
        vec->size = 0; // empezar vacío
        for (int i = 0; i < MAX_VECTOR_SIZE; i++) {
            vec->data[i] = 0.0;
        }
        vector_count++;
        printf("DEBUG: Nuevo vector creado '%s'\n", name); // Debug
        return vec;
    }
    
    execerror("too many vectors", name);
    return NULL;
}

// assignelem - asigna valor a elemento del vector
void assignelem() {
    printf("DEBUG: Iniciando assignelem\n"); // Debug
    
    Datum d = pop();      // valor a asignar
    double index_val = pop().val;  // índice
    Symbol *s = pop().sym; // símbolo del vector
    
    printf("DEBUG: asignando %g a %s[%g]\n", d.val, s->name, index_val); // Debug
    
    Vector *vec = get_vector(s->name);
    int index = (int)index_val;
    
    if (index < 0 || index >= MAX_VECTOR_SIZE) {
        char msg[100];
        sprintf(msg, "index %d out of bounds [0,%d]", index, MAX_VECTOR_SIZE-1);
        execerror(msg, s->name);
    }
    
    vec->data[index] = d.val;
    if (index >= vec->size) {
        vec->size = index + 1;
    }
    printf("DEBUG: Asignación completada\n"); // Debug
}

// evalelem - obtiene valor de elemento del vector
void evalelem() {
    printf("DEBUG: Iniciando evalelem\n"); // Debug
    
    double index_val = pop().val;  // índice
    Symbol *s = pop().sym; // símbolo del vector
    
    printf("DEBUG: evaluando %s[%g]\n", s->name, index_val); // Debug
    
    Vector *vec = get_vector(s->name);
    int index = (int)index_val;
    
    if (index < 0 || index >= vec->size) {
        char msg[100];
        sprintf(msg, "index %d out of bounds [0,%d]", index, vec->size-1);
        execerror(msg, s->name);
    }
    
    Datum result;
    result.val = vec->data[index];
    push(result);
    printf("DEBUG: Evaluación completada, valor: %g\n", result.val); // Debug
}

// createvector - inicia la creación de un nuevo vector
void createvector() {
    printf("DEBUG: createvector - reset temp_vector\n"); // Debug
    temp_vector_size = 0;
}

// addtovector - agrega un elemento al vector temporal
void addtovector() {
    printf("DEBUG: addtovector - tamaño actual: %d\n", temp_vector_size); // Debug
    
    Datum d = pop(); // el valor a agregar
    
    if (temp_vector_size < MAX_VECTOR_SIZE) {
        temp_vector_data[temp_vector_size] = d.val;
        temp_vector_size++;
        printf("DEBUG: agregado %g, nuevo tamaño: %d\n", d.val, temp_vector_size); // Debug
    } else {
        execerror("vector too large", "");
    }
    
    // Empujar un valor dummy a la pila
    Datum result;
    result.val = 0.0;
    push(result);
}

// Función para asignar vector a variable
void assign_vector_to_var(Symbol *s, double *data, int size) {
    printf("DEBUG: assign_vector_to_var - asignando %d elementos a %s\n", size, s->name); // Debug
    
    Vector *vec = get_vector(s->name);
    
    if (size > MAX_VECTOR_SIZE) {
        execerror("vector too large", s->name);
    }
    
    vec->size = size;
    for (int i = 0; i < size; i++) {
        vec->data[i] = data[i];
        printf("DEBUG: vec[%d] = %g\n", i, data[i]); // Debug
    }
    printf("DEBUG: Vector asignado completamente\n"); // Debug
}