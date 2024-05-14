#include"./vector.h"

linvector linvector_new(size_t n, ...) {
    linvector vec = linvector_with_capacity(n+1);
    va_list args;
    va_start(args, n);
    for (size_t i = 0; i < n; i++) {
        realnum num = realnum_from_aprox(va_arg(args, double));
        linvector_push(&vec, num);
    }
    va_end(args);
    return vec;
}

linvector linvector_with_capacity(size_t capacity) {
    linvector vec;
    vec.size = 0;
    vec.capacity = capacity;
    vec.data = malloc(capacity * sizeof(realnum));
    return vec;
}

linvector* linvector_clone(linvector* vec) {
    linvector* clone = malloc(sizeof(linvector));
    clone->size = vec->size;
    clone->capacity = vec->size;
    clone->data = malloc(vec->size * sizeof(realnum));

    for (size_t i = 0; i < vec->size; i++) {
        clone->data[i] = vec->data[i];
    }
    return clone;
}

void linvector_free(linvector* vec) {
    free(vec->data);
    vec->size = 0;
    vec->capacity = 0;
}

void linvector_print(linvector* vec, uint16_t precision) {
    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        realnum_print(&vec->data[i], precision);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void linvector_push(linvector* vec, realnum value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(realnum));
    }
    vec->data[(vec->size)++] = value;
}

linvector linvector_add(linvector* vec1, linvector* vec2) {
    if (vec1->size != vec2->size) {
        fprintf(stderr, "Error: vectors must have the same size to be added.\n");
        exit(1);
    }
    linvector vec3 = linvector_with_capacity(vec1->size);
    for (size_t i = 0; i < vec1->size; i++) {
        vec3.data[i] = realnum_add(&vec1->data[i], &vec2->data[i]);
    }
    vec3.size = vec1->size;
    return vec3;
}

linvector linvector_sub(linvector* vec1, linvector* vec2) {
    if (vec1->size != vec2->size) {
        fprintf(stderr, "Error: vectors must have the same size to be subtracted.\n");
        exit(1);
    }
    linvector vec3 = linvector_with_capacity(vec1->size);
    for (size_t i = 0; i < vec1->size; i++) {
        vec3.data[i] = realnum_sub(&vec1->data[i], &vec2->data[i]);
    }
    vec3.size = vec1->size;
    return vec3;
}

linvector linvector_mul(linvector* a, realnum scalar) {
    linvector vec = linvector_with_capacity(a->size);
    for (size_t i = 0; i < a->size; i++) {
        vec.data[i] = realnum_mul(&a->data[i], &scalar);
    }
    vec.size = a->size;
    return vec;
}

linvector linvector_div(linvector* a, realnum scalar) {
    linvector vec = linvector_with_capacity(a->size);
    for (size_t i = 0; i < a->size; i++) {
        vec.data[i] = realnum_div(&a->data[i], &scalar);
    }
    vec.size = a->size;
    return vec;
}

realnum linvector_dot(linvector* vec1, linvector* vec2) {
    if (vec1->size != vec2->size) {
        fprintf(stderr, "Error: vectors must have the same size to calculate the dot product.\n");
        exit(1);
    }
    realnum result = realnum_from_aprox(0.0);
    for (size_t i = 0; i < vec1->size; i++) {
        realnum temp = realnum_mul(&vec1->data[i], &vec2->data[i]);
        result = realnum_add(&result, &temp);
    }
    return result;
}

realnum linvector_norm(linvector* vec) {
    realnum res = linvector_dot(vec, vec);
    return realnum_sqrt(&res);
}

linvector linvector_normalize(linvector* vec) {
    realnum norm = linvector_norm(vec);
    return linvector_div(vec, norm);
}

linvector linvector_cross(linvector* vec1, linvector* vec2) {
    if (vec1->size != 3 || vec2->size != 3) {
        fprintf(stderr, "Error: cross product is only applicable to 3D vectors.\n");
        exit(1);
    }
    linvector vec3 = linvector_with_capacity(3);
    realnum temp1 = realnum_mul(&vec1->data[1], &vec2->data[2]);
    realnum temp2 = realnum_mul(&vec1->data[2], &vec2->data[1]);
    vec3.data[0] = realnum_sub(&temp1, &temp2);

    temp1 = realnum_mul(&vec1->data[2], &vec2->data[0]);
    temp2 = realnum_mul(&vec1->data[0], &vec2->data[2]);
    vec3.data[1] = realnum_sub(&temp1, &temp2);

    temp1 = realnum_mul(&vec1->data[0], &vec2->data[1]);
    temp2 = realnum_mul(&vec1->data[1], &vec2->data[0]);
    vec3.data[2] = realnum_sub(&temp1, &temp2);
    return vec3;
}
