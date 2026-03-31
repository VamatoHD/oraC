#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct {
    int *data;       // Apontador para os elementos
    size_t size;     // Numero atual de elementos
    size_t capacity; // Capacidade maxima
} Vector;

// Function Prototypes
void vector_init(Vector *v);
void vector_push(Vector *v, int value);
void vector_free(Vector *v);

#endif