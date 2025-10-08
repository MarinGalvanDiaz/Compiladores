#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

// Función auxiliar para verificar tamaños
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

Vector *vector_scalar_mult(Vector *v, double scalar) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "multiplicacion escalar");
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
        execerror("vector nulo en operacion", "magnitud");
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i] * v->data[i];
    }
    return sqrt(sum);
}

/* NUEVAS FUNCIONES VECTORIALES COMPLETAS */

// Producto punto (producto escalar)
double vector_dot(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "producto punto")) return 0.0;
    
    double result = 0.0;
    for (int i = 0; i < a->size; i++) {
        result += a->data[i] * b->data[i];
    }
    return result;
}

// Producto cruz (solo para vectores 3D)
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

// Normalizar vector (vector unitario)
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

// Suma de todos los elementos del vector
double vector_sum(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "suma de elementos");
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i];
    }
    return sum;
}

// Promedio de los elementos del vector
double vector_mean(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "promedio");
        return 0.0;
    }
    if (v->size == 0) {
        execerror("vector vacio", "promedio");
        return 0.0;
    }
    
    return vector_sum(v) / v->size;
}

// Mínimo elemento del vector
double vector_min(Vector *v) {
    if (v == NULL || v->size == 0) {
        execerror("vector vacio o nulo", "minimo");
        return 0.0;
    }
    
    double min_val = v->data[0];
    for (int i = 1; i < v->size; i++) {
        if (v->data[i] < min_val) {
            min_val = v->data[i];
        }
    }
    return min_val;
}

// Máximo elemento del vector
double vector_max(Vector *v) {
    if (v == NULL || v->size == 0) {
        execerror("vector vacio o nulo", "maximo");
        return 0.0;
    }
    
    double max_val = v->data[0];
    for (int i = 1; i < v->size; i++) {
        if (v->data[i] > max_val) {
            max_val = v->data[i];
        }
    }
    return max_val;
}

// Concatenar dos vectores
Vector *vector_concat(Vector *a, Vector *b) {
    if (a == NULL || b == NULL) {
        execerror("vector nulo en operacion", "concatenacion");
        return NULL;
    }
    if (a->size + b->size > MAX_VECTOR_SIZE) {
        execerror("vector resultante demasiado grande", "concatenacion");
        return NULL;
    }
    
    Vector *result = create_vector(a->size + b->size);
    if (result == NULL) return NULL;
    
    result->size = a->size + b->size;
    
    // Copiar elementos del primer vector
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i];
    }
    // Copiar elementos del segundo vector
    for (int i = 0; i < b->size; i++) {
        result->data[a->size + i] = b->data[i];
    }
    
    return result;
}

// Crear vector de ceros
Vector *vector_zeros(int size) {
    if (size <= 0 || size > MAX_VECTOR_SIZE) {
        execerror("tamaño de vector invalido", "ceros");
        return NULL;
    }
    
    Vector *result = create_vector(size);
    if (result == NULL) return NULL;
    
    result->size = size;
    for (int i = 0; i < size; i++) {
        result->data[i] = 0.0;
    }
    return result;
}

// Crear vector de unos
Vector *vector_ones(int size) {
    if (size <= 0 || size > MAX_VECTOR_SIZE) {
        execerror("tamaño de vector invalido", "unos");
        return NULL;
    }
    
    Vector *result = create_vector(size);
    if (result == NULL) return NULL;
    
    result->size = size;
    for (int i = 0; i < size; i++) {
        result->data[i] = 1.0;
    }
    return result;
}

// Crear vector con valores linealmente espaciados
Vector *vector_linspace(double start, double end, int n) {
    if (n <= 0 || n > MAX_VECTOR_SIZE) {
        execerror("numero de puntos invalido", "linspace");
        return NULL;
    }
    
    Vector *result = create_vector(n);
    if (result == NULL) return NULL;
    
    result->size = n;
    if (n == 1) {
        result->data[0] = start;
    } else {
        double step = (end - start) / (n - 1);
        for (int i = 0; i < n; i++) {
            result->data[i] = start + i * step;
        }
    }
    return result;
}

// Producto elemento a elemento (Hadamard product)
Vector *vector_hadamard(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "producto hadamard")) return NULL;
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] * b->data[i];
    }
    return result;
}

// División elemento a elemento
Vector *vector_divide(Vector *a, Vector *b) {
    if (!check_sizes(a, b, "division elemento a elemento")) return NULL;
    
    Vector *result = create_vector(a->size);
    if (result == NULL) return NULL;
    
    result->size = a->size;
    for (int i = 0; i < a->size; i++) {
        if (b->data[i] == 0.0) {
            execerror("division por cero en elemento", "");
            return NULL;
        }
        result->data[i] = a->data[i] / b->data[i];
    }
    return result;
}

// Potencia elemento a elemento
Vector *vector_power(Vector *v, double exponent) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "potencia");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = pow(v->data[i], exponent);
    }
    return result;
}

// Valor absoluto de cada elemento
Vector *vector_abs(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "valor absoluto");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = fabs(v->data[i]);
    }
    return result;
}

// Seno de cada elemento
Vector *vector_sin(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "seno");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = sin(v->data[i]);
    }
    return result;
}

// Coseno de cada elemento
Vector *vector_cos(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "coseno");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = cos(v->data[i]);
    }
    return result;
}

// Tangente de cada elemento
Vector *vector_tan(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "tangente");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = tan(v->data[i]);
    }
    return result;
}

// Exponencial de cada elemento
Vector *vector_exp(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "exponencial");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = exp(v->data[i]);
    }
    return result;
}

// Logaritmo natural de cada elemento
Vector *vector_log(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "logaritmo");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        if (v->data[i] <= 0.0) {
            execerror("logaritmo de numero no positivo", "");
            return NULL;
        }
        result->data[i] = log(v->data[i]);
    }
    return result;
}

// Raíz cuadrada de cada elemento
Vector *vector_sqrt(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "raiz cuadrada");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        if (v->data[i] < 0.0) {
            execerror("raiz cuadrada de numero negativo", "");
            return NULL;
        }
        result->data[i] = sqrt(v->data[i]);
    }
    return result;
}

// Redondear cada elemento al entero más cercano
Vector *vector_round(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "redondeo");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = round(v->data[i]);
    }
    return result;
}

// Piso de cada elemento (mayor entero menor o igual)
Vector *vector_floor(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "piso");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = floor(v->data[i]);
    }
    return result;
}

// Techo de cada elemento (menor entero mayor o igual)
Vector *vector_ceil(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo en operacion", "techo");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = ceil(v->data[i]);
    }
    return result;
}

// Obtener tamaño del vector
int vector_size(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo", "tamaño");
        return 0;
    }
    return v->size;
}

// Copiar vector
Vector *vector_copy(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo", "copia");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[i];
    }
    return result;
}

// Revertir vector
Vector *vector_reverse(Vector *v) {
    if (v == NULL) {
        execerror("vector nulo", "reversion");
        return NULL;
    }
    
    Vector *result = create_vector(v->size);
    if (result == NULL) return NULL;
    
    result->size = v->size;
    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[v->size - 1 - i];
    }
    return result;
}