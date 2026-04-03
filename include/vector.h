#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void *data;       // Apontador para os elementos
    size_t size;      // Numero atual de elementos
    size_t capacity;  // Capacidade maxima
    size_t item_size; // Tamanho (bytes) dos elementos obtido por sizeof()
} Vector;

// Function Prototypes
void vector_reserve(Vector *v, size_t new_cap);
void vector_grow(Vector *v, size_t goal);
void vector_init(Vector *v, size_t item_size);
void *vector_at(const Vector *v, size_t index);
bool vector_get(const Vector *v, size_t index, void *out_ptr);
void vector_push(Vector *v, const void *value_ptr);
void vector_insert(Vector *v, size_t index, const void *value_ptr);
bool vector_pop(Vector *v, void *out_ptr);
bool vector_swap_remove(Vector *v, size_t index, void *out_ptr);
bool vector_remove(Vector *v, size_t index, void *out_ptr);
void vector_free(Vector *v);

#endif