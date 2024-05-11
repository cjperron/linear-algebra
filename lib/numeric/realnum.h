#pragma once
#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include<quadmath.h>
#include<math.h>
#include<stdio.h>

// TODO: Make realnum return a char* with its representation with all ops chained, but not undone unless if asked. (hard)

typedef enum realnum_kind {
    REALNUM_FRAC, // Inteded form for a rational number
    REALNUM_APROX // Approximated form for a real number (intended for irrational numbers)
} realnum_kind;

/**
 * Represents a real number.
 */
typedef struct realnum {
    realnum_kind kind; /**< The "kind" of real number. */
    union {
        struct {
            int64_t num; /**< The numerator of the fraction. */
            int64_t den; /**< The denominator of the fraction. */
        } frac; /**< The fraction value. */
        __float128 aprox; /**< The approximate value. */
    } value; /**< The value of the real number. */
} realnum;

/**
 * Creates a new realnum object.
 *
 * @return A pointer to the newly created realnum object.
 */
realnum* realnum_new();

/**
 * Creates a new realnum object from a fraction.
 *
 * @param num The numerator of the fraction.
 * @param den The denominator of the fraction.
 * @return A pointer to the newly created realnum object.
 */
realnum* realnum_from_frac(int64_t num, int64_t den);

/**
 * Creates a new realnum object from an approximate value.
 *
 * @param aprox The approximate value.
 * @return A pointer to the newly created realnum object.
 */
realnum* realnum_from_aprox(__float128 aprox);

/**
 * Creates a clone of a realnum object.
 *
 * @param num The realnum object to clone.
 * @return A pointer to the cloned realnum object.
 */
realnum* realnum_clone(realnum* num);

/**
 * Allocates memory for a realnum object.
 *
 * @param num The realnum object to allocate memory for.
 * @return A pointer to the allocated realnum object.
 */
realnum* realnum_allocate(realnum* num);

/**
 * Frees the memory allocated for a realnum object.
 *
 * @param num The realnum object to free.
 */
void realnum_free(realnum* num);

/**
 * Adds two realnum objects.
 *
 * @param a The first realnum object.
 * @param b The second realnum object.
 * @return The sum of the two realnum objects.
 */
realnum realnum_add(realnum* a, realnum* b);

/**
 * Subtracts two realnum objects.
 *
 * @param a The first realnum object.
 * @param b The second realnum object.
 * @return The difference between the two realnum objects.
 */
realnum realnum_sub(realnum* a, realnum* b);

/**
 * Multiplies two realnum objects.
 *
 * @param a The first realnum object.
 * @param b The second realnum object.
 * @return The product of the two realnum objects.
 */
realnum realnum_mul(realnum* a, realnum* b);

/**
 * Divides two realnum objects.
 *
 * @param a The first realnum object.
 * @param b The second realnum object.
 * @return The quotient of the two realnum objects.
 */
realnum realnum_div(realnum* a, realnum* b);

/**
 * Negates a realnum object.
 *
 * @param num The realnum object to negate.
 * @return The negation of the realnum object.
 */
realnum realnum_neg(realnum* num);

/**
 * Calculates the inverse of a realnum object.
 *
 * @param num The realnum object to calculate the inverse of.
 * @return The inverse of the realnum object.
 */
realnum realnum_inv(realnum* num);

/**
 * Calculates the absolute value of a realnum object.
 *
 * @param num The realnum object to calculate the absolute value of.
 * @return The absolute value of the realnum object.
 */
realnum realnum_abs(realnum* num);

/**
 * Raises a realnum object to a power.
 *
 * @param num The realnum object to raise to a power.
 * @param exp The exponent.
 * @return The result of raising the realnum object to the power of exp.
 */
realnum realnum_pow(realnum* num, realnum* exp);

/**
 * Calculates the square root of a realnum object.
 *
 * @param num The realnum object to calculate the square root of.
 * @return The square root of the realnum object.
 */
realnum realnum_sqrt(realnum* num);

/**
 * Calculates the cube root of a realnum object.
 *
 * @param num The realnum object to calculate the cube root of.
 * @return The cube root of the realnum object.
 */
realnum realnum_cbrt(realnum* num);

/**
 * Calculates the exponential function of a realnum object.
 *
 * @param num The realnum object to calculate the exponential function of.
 * @return The exponential function of the realnum object.
 */
realnum realnum_exp(realnum* num);

/**
 * Converts a realnum object to a fraction.
 *
 * @param num The realnum object to convert to a fraction.
 * @return The realnum object as a fraction.
 */
realnum realnum_as_frac(realnum* num);

/**
 * Converts a realnum object to an approximate value.
 *
 * @param num The realnum object to convert to an approximate value.
 * @return The realnum object as an approximate value.
 */
realnum realnum_as_aprox(realnum* num);

/**
 * Simplifies a realnum object as a fraction.
 *
 * @param num The realnum object to simplify as a fraction.
 * @return The simplified realnum object as a fraction.
 */
realnum realnum_fracsimp(realnum* num);

/**
 * Applies a binary operation to two realnum objects.
 *
 * @param a The first realnum object.
 * @param b The second realnum object.
 * @param op The binary operation to apply.
 * @return The result of applying the binary operation to the two realnum objects.
 */
realnum* apply_op(realnum* a, realnum* b, realnum* (*op)(realnum*, realnum*));

/**
 * Prints a realnum object.
 *
 * @param num The realnum object to print.
 */
void realnum_print(realnum* num);

/**
 * Prints a realnum object followed by a newline character.
 *
 * @param num The realnum object to print.
 */
void realnum_println(realnum* num);

/**
 * Prints a realnum object as a fraction.
 *
 * @param num The realnum object to print as a fraction.
 */
void realnum_print_as_frac(realnum* num);

/**
 * Prints a realnum object as an approximate value.
 *
 * @param num The realnum object to print as an approximate value.
 */
void realnum_print_as_aprox(realnum* num);
