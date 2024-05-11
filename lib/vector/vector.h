#pragma once
#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include"../numeric/realnum.h"

#define LINVECTOR_DEFAULT_CAPACITY 16

/**
 * @brief Represents a linear algebra vector.
 */
/**
 * @struct linvector
 * @brief Represents a linear vector.
 *
 * The `linvector` struct stores information about a linear vector, including its size, capacity, and data.
 */
typedef struct linvector {
    size_t size;
    size_t capacity;
    realnum* data;
} linvector;

// Vector data manipulation
linvector*  linvector_new();
linvector*  linvector_with_capacity(size_t capacity);
linvector*  linvector_with_size(size_t size);
linvector*  linvector_with_data(realnum* data, size_t size);
linvector*  linvector_clone(linvector* vec);
void        linvector_free(linvector* vec);

// Vector operations
linvector*  linvector_add(linvector* a, linvector* b);
linvector*  linvector_sub(linvector* a, linvector* b);
linvector*  linvector_mul(linvector* a, realnum scalar);
linvector*  linvector_div(linvector* a, realnum scalar);
realnum     linvector_dot(linvector* a, linvector* b);
realnum     linvector_norm(linvector* a);
linvector*  linvector_normalize(linvector* a);
linvector*  linvector_cross(linvector* a, linvector* b); // Only for 3D vectors
linvector*  linvector_zero(size_t size);
realnum     linvector_angle(linvector* a, linvector* b);
realnum     linvector_distance(linvector* a, linvector* b);
realnum     linvector_dim(linvector* a);


// To be implemented...
linvector*  linvector_project(linvector* a, linvector* b);
linvector*  linvector_reject(linvector* a, linvector* b);
linvector*  linvector_reflect(linvector* a, linvector* b);
linvector*  linvector_rotate(linvector* a, linvector* axis, realnum angle);
linvector*  linvector_rotate_x(linvector* a, realnum angle);
linvector*  linvector_rotate_y(linvector* a, realnum angle);
linvector*  linvector_rotate_z(linvector* a, realnum angle);
linvector*  linvector_translate(linvector* a, linvector* b);


