#include "vector.h"
#include <stdio.h>

int main() {
    Vector a;

    vector_grow(&a, sizeof(int));

    printf("Hello");
}