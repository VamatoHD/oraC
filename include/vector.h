#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct {
    void *data;       // Apontador para os elementos
    size_t size;      // Numero atual de elementos
    size_t capacity;  // Capacidade maxima
    size_t item_size; // Tamanho (bytes) dos elementos obtido por sizeof()
} Vector;

// Function Prototypes
void vector_init(Vector *v, size_t item_size);
void *vector_at(const Vector *v, size_t index);
void vector_get(const Vector *v, size_t index, void *out_ptr);
void vector_push(Vector *v, const void *value_ptr);
void vector_append(Vector *v, size_t index, const void *value_ptr);
void vector_pop(Vector *v, void *out_ptr);
void vector_swap_remove(Vector *v, size_t index, void *out_ptr);
void vector_remove(Vector *v, size_t index, void *out_ptr);
void vector_free(Vector *v);

#endif