#include "vstring.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

static void _add_terminator(VString *str) {
    const char null_byte = '\0';
    vector_push(str, &null_byte);
    // Terminator doesn't count for size
    str->size--;
}

void vstring_init(VString *str) {
    vector_init(str, sizeof(char));
    _add_terminator(str);
};

char vstring_get(const VString *str, size_t index) {
    // Returns character if found, otherwise null termination
    char out;
    return vector_get(str, index, &out) ? out : '\0';
};

void vstring_push(VString *str, const char c) {
    const char temp = c;
    vector_push(str, &temp);
    _add_terminator(str);
};

void vstring_concat_vstring(VString *dest, const VString *src) {
    assert(dest && dest->data && src && src->data);

    // + 1 para o terminador
    size_t needed_capa = dest->size + src->size + 1;

    if (needed_capa > dest->capacity) {
        vector_grow(dest, needed_capa);
    }

    memcpy(vector_at(dest, dest->size), vector_at(src, 0),
           src->size * sizeof(char));

    dest->size += src->size;

    _add_terminator(dest);
};

void vstring_concat_cstr(VString *dest, const char *src) {
    size_t src_len = strlen(src);
    // + 1 para o terminador
    size_t needed_capa = dest->size + src_len + 1;
    if (needed_capa > dest->capacity) {
        vector_grow(dest, needed_capa);
    }

    memcpy(vector_at(dest, dest->size), src, src_len * sizeof(char));

    dest->size += src_len;

    _add_terminator(dest);
};

void vstring_insert(VString *str, size_t index, const char c) {
    char temp = c;
    vector_insert(str, index, &temp);
    _add_terminator(str);
};

char vstring_pop(VString *str) {
    char out;
    if (vector_pop(str, &out)) {
        _add_terminator(str);
        return out;
    } else {
        return '\0';
    }
};

char vstring_remove(VString *str, size_t index) {
    char out;
    if (vector_remove(str, index, &out)) {
        _add_terminator(str);
        return out;
    } else {
        return '\0';
    }
};

bool vstring_equals(VString *a, VString *b) {
    return (a->size == b->size && memcmp(a->data, b->data, a->size) == 0);
};

void vstring_free(VString *str) { vector_free(str); };