#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void _vector_grow(Vector *v) {
    // TODO: realloc pode falhar e retomar NULL
    // deixando memória por limpar

    size_t new_capacity = (v->capacity == 0) ? 2 : v->capacity * 2;
    v->data = realloc(v->data, new_capacity * v->item_size);
    v->capacity = new_capacity;
    assert(v->data);
}

inline void *vector_at(const Vector *v, size_t index) {
    // Char = 1 byte -> permite adicionar pointers
    return (char *)v->data + (index * v->item_size);
}
void vector_init(Vector *v, size_t item_size) {
    v->size = 0;
    v->capacity = 2;
    v->item_size = item_size;
    v->data = malloc(item_size * v->capacity);
    assert(v->data);
}

void vector_get(const Vector *v, size_t index, void *out_ptr) {
    assert(index < v->size);
    if (out_ptr) {
        memcpy(out_ptr, vector_at(v, index), v->item_size);
    }
}

void vector_push(Vector *v, const void *value_ptr) {
    // TODO: improve error handling
    assert(v && v->data && value_ptr);

    if (v->size == v->capacity) {
        _vector_grow(v);
    }

    void *dest = vector_at(v, v->size);
    memcpy(dest, value_ptr, v->item_size);
    v->size++;
}

void vector_append(Vector *v, size_t index, void *value_ptr) {
    assert(v && v->data && value_ptr);
    assert(index <= v->size);

    if (v->size == v->capacity) {
        _vector_grow(v);
    }

    size_t elem_count = v->size - index;
    char *index_ptr = vector_at(v, index);

    if (elem_count > 0) {
        memmove(index_ptr + v->item_size, index_ptr, elem_count * v->item_size);
    }
    memcpy(index_ptr, value_ptr, v->item_size);
    v->size++;
}

void vector_pop(Vector *v, void *out_ptr) {
    assert(v->size > 0);
    // Diminui size e retoma o valor nesse index
    v->size--;
    if (out_ptr) {
        memcpy(out_ptr, vector_at(v, v->size), v->item_size);
    }
}

void vector_swap_remove(Vector *v, size_t index, void *out_ptr) {
    // 0 <= index && index < size => 0 < size
    assert(index < v->size);

    v->size--;
    void *last_ptr = vector_at(v, v->size);

    if (v->size > 0 && index != v->size) {
        // Se houver elementos para substituir
        // e não for para remover o último
        void *index_ptr = vector_at(v, index);
        if (out_ptr) {
            memcpy(out_ptr, index_ptr, v->item_size);
        }
        memcpy(index_ptr, last_ptr, v->item_size);
    } else {
        if (out_ptr) {
            memcpy(out_ptr, last_ptr, v->item_size);
        }
    }
}

void vector_remove(Vector *v, size_t index, void *out_ptr) {
    assert(v && v->data);
    // Verifica automaticamente que o vetor tem elementos
    assert(index < v->size);

    char *index_ptr = vector_at(v, index);

    if (out_ptr) {
        memcpy(out_ptr, index_ptr, v->item_size);
    }

    size_t elem_count = v->size - index;
    if (elem_count > 0) {
        memmove(index_ptr, index_ptr + v->item_size, elem_count * v->item_size);
    }

    v->size--;
}

void vector_free(Vector *v) {
    if (v->data) {
        free(v->data);
    }
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}