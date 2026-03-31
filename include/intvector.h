#ifndef INTVEC_H
#define INTVEC_H

#include <stddef.h>

typedef struct {
    int *data;       // Apontador para os elementos
    size_t size;     // Numero atual de elementos
    size_t capacity; // Capacidade maxima
} IntVector;

// Function Prototypes
void intvector_init(IntVector *v);
void intvector_push(IntVector *v, int value);
void intvector_append(IntVector *v, size_t index, int value);
int intvector_pop(IntVector *v);
int intvector_swap_remove(IntVector *v, size_t index);
int intvector_remove(IntVector *v, size_t index);
void intvector_free(IntVector *v);

#endif