#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void _vector_grow(Vector *v) {
    // TODO: realloc pode falhar e retomar NULL
    // deixando memória por limpar

    size_t new_capacity = (v->capacity == 0) ? 2 : v->capacity * 2;
    v->data = realloc(v->data, new_capacity * sizeof(int));
    v->capacity = new_capacity;
    assert(v->data);
}

void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 2;
    v->data = malloc(sizeof(int) * v->capacity);
    assert(v->data);
}

void vector_push(Vector *v, int value) {
    if (v->size == v->capacity) {
        _vector_grow(v);
    }
    v->data[v->size++] = value;
}

void vector_append(Vector *v, size_t index, int value) {
    assert(v && v->data);

    if (v->size == v->capacity) {
        _vector_grow(v);
    }

    size_t elem_count = v->size - index - 1;
    if (elem_count > 0) {
        memmove(&v->data[index], &v->data[index + 1], elem_count * sizeof(int));
    }

    v->data[index] = value;
    v->size++;
}

int vector_pop(Vector *v) {
    assert(v->size > 0);
    // Diminui size e retoma o valor nesse index
    return v->data[--v->size];
}

int vector_swap_remove(Vector *v, size_t index) {
    // 0 <= index && index < size => 0 < size
    assert(index < v->size);

    int last = v->data[--v->size];
    if (v->size > 0 && index != v->size) {
        // Se houver elementos para substituir
        // e não for para remover o último
        int temp = v->data[index];
        v->data[index] = last;
        return temp;
    }
    return last;
}

int vector_remove(Vector *v, size_t index) {
    assert(v && v->data);
    // Verifica automaticamente que o vetor tem elementos
    assert(index < v->size);

    int res = v->data[index];

    size_t elem_count = v->size - index - 1;
    if (elem_count > 0) {
        memmove(&v->data[index], &v->data[index + 1], elem_count * sizeof(int));
    }

    v->size--;
    return res;
}

void vector_free(Vector *v) {
    if (v->data) {
        free(v->data);
    }
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}