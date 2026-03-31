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
void vector_append(Vector *v, size_t index, int value);
int vector_pop(Vector *v);
int vector_swap_remove(Vector *v, size_t index);
int vector_remove(Vector *v, size_t index);
void vector_free(Vector *v);

#endif