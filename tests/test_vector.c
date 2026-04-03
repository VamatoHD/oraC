#include "vector.h"
#include <assert.h>
#include <stdio.h>

#define _vector_create(type)                                                   \
    Vector vec;                                                                \
    vector_init(&vec, sizeof(type));

#define _vector_fill_int(vec, amount)                                          \
    for (int i = 0; i < amount; i++) {                                         \
        vector_push(&vec, &i);                                                 \
    }

void test_vector_init() {
    printf("Vector - test_vector_init()\n");

    Vector vec;
    vector_init(&vec, sizeof(int));

    assert(vec.size == 0);
    assert(vec.capacity == 2);
    assert(vec.item_size == sizeof(int));
    assert(vec.data);

    vector_free(&vec);
};

void test_vector_free() {
    printf("Vector - test_vector_free()\n");

    _vector_create(int);
    _vector_fill_int(vec, 10);
    vector_free(&vec);

    assert(!vec.data);
    assert(vec.capacity == 0);
    assert(vec.size == 0);
    assert(vec.item_size == sizeof(int));
};

void test_vector_reserve() {
    printf("Vector - test_vector_reserve()\n");

    _vector_create(int);

    {
        int temp = 10;
        vector_push(&vec, &temp);
    }

    // Capacity is supposed to be 2;
    for (size_t i = 10; i <= 50; i += 10) {
        vector_reserve(&vec, i);
        assert(vec.capacity == i);
    }

    for (size_t i = 10; i <= 50; i += 10) {
        vector_reserve(&vec, i);
        assert(vec.capacity == 50);
    }

    {
        int temp;
        vector_get(&vec, 0, &temp);
        assert(temp == 10);
    }

    vector_free(&vec);
};

void test_vector_grow() {};
void test_vector_at() {};
void test_vector_get() {};
void test_vector_push() {};
void test_vector_insert() {};
void test_vector_pop() {};
void test_vector_swap_remove() {};
void test_vector_remove() {};
void test_vector_clone() {};

int main() {
    printf("Vector - Running Tests...\n");

    test_vector_init();
    test_vector_free();
    test_vector_reserve();
    test_vector_grow();
    test_vector_at();
    test_vector_get();
    test_vector_push();
    test_vector_insert();
    test_vector_pop();
    test_vector_swap_remove();
    test_vector_remove();
    test_vector_clone();

    printf("Vector - All tests passed!\n");
    return 0; // Success
}