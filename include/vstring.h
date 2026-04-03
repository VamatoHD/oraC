#ifndef VSTRING_H
#define VSTRING_H

#include <stddef.h>
#include <vector.h>

typedef Vector VString;

void vstring_init(VString *str);
char vstring_get(const VString *str, size_t index);
void vstring_push(VString *str, const char c);
void vstring_concat_vstring(VString *dest, const VString *src);
void vstring_concat_cstr(VString *dest, const char *src);
void vstring_insert(VString *str, size_t index, const char c);
char vstring_pop(VString *str);
char vstring_remove(VString *str, size_t index);
bool vstring_equals(VString *a, VString *b);
void vstring_free(VString *str);

//#define vstring_concat(dest, src)                                              \
//    _Generic((src),                                                            \
//        const char: vstring_push,                                              \
//        char: vstring_push,                                                    \
//        char *: vstring_concat_cstr,                                           \
//        const char *: vstring_concat_cstr,                                     \
//        VString *: vstring_concat_vstring,                                     \
//        const VString *: vstring_concat_vstring)(dest, src)

#endif