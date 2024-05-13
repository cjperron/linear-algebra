#pragma once
#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdarg.h>
#include"../numeric/realnum.h"

#define LINVECTOR_DEFAULT_CAPACITY 16

// #define linvector_print(vec) linvector_print(vec, 4)


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

/**
 * Creates a new linvector with default capacity.
 *
 * @param n The number of elements to initialize the linvector with.
 * @param ... The variable number of elements to initialize the linvector with.
 * @return The newly created linvector.
 */
linvector linvector_new(size_t n, ...);

/**
 * Creates a new linvector with the specified capacity.
 *
 * @param capacity The capacity of the linvector.
 * @return The newly created linvector.
 */
linvector linvector_with_capacity(size_t capacity);

/**
 * Creates a new linvector with the specified data and size.
 *
 * @param data The data array for the linvector.
 * @param size The size of the linvector.
 * @return The newly created linvector.
 */
linvector linvector_with_data(realnum* data, size_t size);

/**
 * Prints the elements of a vector.
 *
 * @param vec The linear vector to be printed.
 * @param precision The number of decimal places to print.
 */
void linvector_print(linvector* vec, uint16_t precision);

/**
 * Creates a new linvector that is a clone of the given linvector.
 *
 * @param vec The linvector to clone.
 * @return The cloned linvector.
 */
linvector* linvector_clone(linvector* vec);

/**
 * Adds a value to the end of the linear vector.
 *
 * @param vec The linear vector to push the value to.
 * @param value The value to be added to the linear vector.
 */
void linvector_push(linvector* vec, realnum value);

/**
 * Frees the memory occupied by the given linvector.
 *
 * @param vec The linvector to free.
 */
void linvector_free(linvector* vec);

/**
 * Adds two linvectors element-wise and returns the result.
 *
 * @param a The first linvector.
 * @param b The second linvector.
 * @return The result of the addition.
 */
linvector linvector_add(linvector* a, linvector* b);

/**
 * Subtracts the second linvector from the first linvector element-wise and returns the result.
 *
 * @param a The first linvector.
 * @param b The second linvector.
 * @return The result of the subtraction.
 */
linvector linvector_sub(linvector* a, linvector* b);

/**
 * Multiplies each element of the linvector by the given scalar and returns the result.
 *
 * @param a The linvector.
 * @param scalar The scalar value.
 * @return The result of the multiplication.
 */
linvector linvector_mul(linvector* a, realnum scalar);

/**
 * Divides each element of the linvector by the given scalar and returns the result.
 *
 * @param a The linvector.
 * @param scalar The scalar value.
 * @return The result of the division.
 */
linvector linvector_div(linvector* a, realnum scalar);

/**
 * Calculates the dot product of two linvectors and returns the result.
 *
 * @param a The first linvector.
 * @param b The second linvector.
 * @return The dot product of the two linvectors.
 */
realnum linvector_dot(linvector* a, linvector* b);

/**
 * Calculates the Euclidean norm (magnitude) of the linvector.
 *
 * @param a The linvector.
 * @return The Euclidean norm of the linvector.
 */
realnum linvector_norm(linvector* a);

/**
 * Normalizes the linvector to have a magnitude of 1 and returns the result.
 *
 * @param a The linvector.
 * @return The normalized linvector.
 */
linvector linvector_normalize(linvector* a);

/**
 * Calculates the cross product of two 3D linvectors and returns the result.
 * This function is only applicable to 3D linvectors.
 *
 * @param a The first 3D linvector.
 * @param b The second 3D linvector.
 * @return The cross product of the two 3D linvectors.
 */
linvector linvector_cross(linvector* a, linvector* b);

/**
 * Creates a new linvector of the specified size with all elements set to 0.
 *
 * @param size The size of the linvector.
 * @return The newly created linvector.
 */
linvector linvector_zero(size_t size);

/**
 * Calculates the angle between two linvectors in radians.
 *
 * @param a The first linvector.
 * @param b The second linvector.
 * @return The angle between the two linvectors in radians.
 */
realnum linvector_angle(linvector* a, linvector* b);

/**
 * Calculates the Euclidean distance between two linvectors.
 *
 * @param a The first linvector.
 * @param b The second linvector.
 * @return The Euclidean distance between the two linvectors.
 */
realnum linvector_distance(linvector* a, linvector* b);

/**
 * Returns the dimension (size) of the linvector.
 *
 * @param a The linvector.
 * @return The dimension (size) of the linvector.
 */
realnum linvector_dim(linvector* a);

/**
 * Projects the linvector 'a' onto the linvector 'b' and returns the result.
 *
 * @param a The linvector to be projected.
 * @param b The linvector onto which 'a' is projected.
 * @return The projected linvector.
 */
linvector linvector_project(linvector* a, linvector* b);

/**
 * Rejects the linvector 'a' from the linvector 'b' and returns the result.
 *
 * @param a The linvector to be rejected.
 * @param b The linvector from which 'a' is rejected.
 * @return The rejected linvector.
 */
linvector linvector_reject(linvector* a, linvector* b);

/**
 * Reflects the linvector 'a' about the linvector 'b' and returns the result.
 *
 * @param a The linvector to be reflected.
 * @param b The linvector about which 'a' is reflected.
 * @return The reflected linvector.
 */
linvector linvector_reflect(linvector* a, linvector* b);

/**
 * Rotates the linvector 'a' around the given axis by the specified angle (in radians) and returns the result.
 *
 * @param a The linvector to be rotated.
 * @param axis The axis of rotation.
 * @param angle The angle of rotation in radians.
 * @return The rotated linvector.
 */
linvector linvector_rotate(linvector* a, linvector* axis, realnum angle);

/**
 * Rotates the linvector 'a' around the x-axis by the specified angle (in radians) and returns the result.
 *
 * @param a The linvector to be rotated.
 * @param angle The angle of rotation in radians.
 * @return The rotated linvector.
 */
linvector linvector_rotate_x(linvector* a, realnum angle);

/**
 * Rotates the linvector 'a' around the y-axis by the specified angle (in radians) and returns the result.
 *
 * @param a The linvector to be rotated.
 * @param angle The angle of rotation in radians.
 * @return The rotated linvector.
 */
linvector linvector_rotate_y(linvector* a, realnum angle);

/**
 * Rotates the linvector 'a' around the z-axis by the specified angle (in radians) and returns the result.
 *
 * @param a The linvector to be rotated.
 * @param angle The angle of rotation in radians.
 * @return The rotated linvector.
 */
linvector linvector_rotate_z(linvector* a, realnum angle);

/**
 * Translates the linvector 'a' by the linvector 'b' and returns the result.
 *
 * @param a The linvector to be translated.
 * @param b The linvector by which 'a' is translated.
 * @return The translated linvector.
 */
linvector linvector_translate(linvector* a, linvector* b);

