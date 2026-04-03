#include "vector.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void vector_reserve(Vector *v, size_t new_cap) {
    if (new_cap <= v->capacity)
        return;

    void *temp = realloc(v->data, new_cap * v->item_size);
    if (temp) {
        v->data = temp;
        v->capacity = new_cap;
    } else {
        // TODO: melhorar erros
        assert(temp);
    }
}

void vector_grow(Vector *v, size_t goal) {
    size_t new_capacity;
    if (goal == 0) {
        new_capacity = (v->capacity == 0) ? 2 : strict_next_pow2(v->capacity);
    } else {
        new_capacity = strict_next_pow2(goal);
    }

    vector_reserve(v, new_capacity);
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

bool vector_get(const Vector *v, size_t index, void *out_ptr) {
    if (out_ptr && index < v->size) {
        memcpy(out_ptr, vector_at(v, index), v->item_size);
        return true;
    } else {
        return false;
    }
}

void vector_push(Vector *v, const void *value_ptr) {
    // TODO: improve error handling
    assert(v && v->data && value_ptr);

    if (v->size == v->capacity) {
        vector_grow(v, 0);
    }

    void *dest = vector_at(v, v->size);
    memcpy(dest, value_ptr, v->item_size);
    v->size++;
}

void vector_insert(Vector *v, size_t index, void *value_ptr) {
    assert(v && v->data && value_ptr);
    assert(index <= v->size);

    if (v->size == v->capacity) {
        vector_grow(v, 0);
    }

    size_t elem_count = v->size - index;
    char *index_ptr = vector_at(v, index);

    if (elem_count > 0) {
        memmove(index_ptr + v->item_size, index_ptr, elem_count * v->item_size);
    }
    memcpy(index_ptr, value_ptr, v->item_size);
    v->size++;
}

bool vector_pop(Vector *v, void *out_ptr) {
    // Diminui size e retoma o valor nesse index
    if (v->size == 0) {
        return false;
    }

    v->size--;
    if (out_ptr) {
        memcpy(out_ptr, vector_at(v, v->size), v->item_size);
    }

    return true;
}

bool vector_swap_remove(Vector *v, size_t index, void *out_ptr) {
    // 0 <= index && index < size => 0 < size
    // Logo não é necessário verificar vetores vazios (i hope)
    if (index >= v->size) {
        return false;
    }

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
    return true;
}

bool vector_remove(Vector *v, size_t index, void *out_ptr) {
    assert(v && v->data);

    // Verifica automaticamente que o vetor tem elementos
    if (index >= v->size) {
        return false;
    }

    char *index_ptr = vector_at(v, index);

    if (out_ptr) {
        memcpy(out_ptr, index_ptr, v->item_size);
    }

    size_t elem_count = v->size - index;
    if (elem_count > 0) {
        memmove(index_ptr, index_ptr + v->item_size, elem_count * v->item_size);
    }

    v->size--;
    return true;
}

Vector vector_clone(const Vector *v) {
    Vector new;

    new.size = v->size;
    new.capacity = v->capacity;
    new.item_size = v->item_size;

    new.data = malloc(new.capacity * v->item_size);
    if (new.data) {
        memcpy(new.data, v->data, new.size * v->item_size);
    }
    return new;
};

void vector_free(Vector *v) {
    if (v->data) {
        free(v->data);
    }
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}