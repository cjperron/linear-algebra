#include"./vector.h"

linvector* linvector_new() {
    return linvector_with_capacity(LINVECTOR_DEFAULT_CAPACITY);
}

linvector* linvector_with_capacity(size_t capacity) {
    linvector* vec = malloc(sizeof(linvector));
    vec->size = 0;
    vec->capacity = capacity;
    vec->data = malloc(capacity * sizeof(__float128));
    return vec;
}

linvector* linvector_with_size(size_t size) {
    linvector* vec = malloc(sizeof(linvector));
    vec->size = size;
    vec->capacity = size;
    vec->data = malloc(size * sizeof(__float128));
    return vec;
}

linvector* linvector_clone(linvector* vec) {
    linvector* clone = linvector_with_size(vec->size);
    for (size_t i = 0; i < vec->size; i++) {
        clone->data[i] = vec->data[i];
    }
    return clone;
}

void linvector_free(linvector* vec) {
    free(vec->data);
    free(vec);
}

void linvector_push(linvector* vec, __float128 value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(__float128));
    }
    vec->data[vec->size++] = *realnum_from_aprox(value);
}