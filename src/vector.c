#include "vector.h"
#include <assert.h>
#include <stdlib.h>

void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(sizeof(int) * v->capacity);
    assert(v->data);
}

void vector_push(Vector *v, int value) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
        assert(v->data);
    }
    v->data[v->size++] = value;
}

void vector_free(Vector *v) {
    if (v->data) {
        free(v->data);
    }
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}