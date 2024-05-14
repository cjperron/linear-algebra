/**
 * @file realnum.c
 * @brief Implementation of real number operations.
 *
 * This file contains the implementation of various operations on real numbers,
 * including addition, subtraction, multiplication, division, exponentiation,
 * square root, cube root, and more. The operations can be performed on both
 * fractional numbers and approximate numbers.
 *
 * The realnum struct represents a real number and can store either a fractional
 * number or an approximate number. The realnum_new function creates a new
 * realnum object with default values. The realnum_from_frac function creates a
 * realnum object from a given numerator and denominator. The realnum_from_aprox
 * function creates a realnum object from a given approximate value. The
 * realnum_clone function creates a copy of a realnum object. The realnum_free
 * function frees the memory allocated for a realnum object.
 *
 * The realnum_add, realnum_sub, realnum_mul, and realnum_div functions perform
 * addition, subtraction, multiplication, and division operations on realnum
 * objects. The realnum_neg function calculates the negation of a realnum
 * object. The realnum_inv function calculates the inverse of a realnum object.
 * The realnum_abs function calculates the absolute value of a realnum object.
 * The realnum_pow function calculates the power of a realnum object. The
 * realnum_sqrt function calculates the square root of a realnum object. The
 * realnum_cbrt function calculates the cube root of a realnum object. The
 * realnum_exp function calculates the exponential value of a realnum object.
 *
 * The realnum_as_frac function converts a realnum object to a fractional
 * representation. The realnum_as_aprox function converts a realnum object to an
 * approximate representation. The realnum_fracsimp function simplifies a
 * fractional realnum object. The apply_op function applies a given operation
 * function to two realnum objects.
 *
 * The realnum_print and realnum_println functions print the value of a realnum
 * object to the console. The realnum_print_as_frac and realnum_print_as_aprox
 * functions print the value of a realnum object as a fractional or approximate
 * representation, respectively.
 */
#include"realnum.h"

#define BUF_SIZE 128

realnum realnum_new() {
    realnum num;
    num.kind = REALNUM_FRAC;
    num.value.frac.num = 0;
    num.value.frac.den = 1;
    return num;
}

realnum realnum_from_frac(int64_t num, int64_t den) {
    realnum frac;
    frac.kind = REALNUM_FRAC;
    frac.value.frac.num = num;
    frac.value.frac.den = den;
    return frac;
}

realnum realnum_from_aprox(__float128 aprox) {
    realnum num;
    num.kind = REALNUM_APROX;
    num.value.aprox = aprox;
    return num;
}

realnum realnum_add(realnum* a, realnum* b) {
    realnum result;
    if (a->kind == REALNUM_FRAC && b->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = a->value.frac.num * b->value.frac.den + b->value.frac.num * a->value.frac.den;
        result.value.frac.den = a->value.frac.den * b->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = (a->kind == REALNUM_FRAC ? (long double)a->value.frac.num / a->value.frac.den : a->value.aprox) + (b->kind == REALNUM_FRAC ? (long double)b->value.frac.num / b->value.frac.den : b->value.aprox);
    }
    return result;
}

realnum realnum_sub(realnum* a, realnum* b) {
    realnum result;
    if (a->kind == REALNUM_FRAC && b->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = a->value.frac.num * b->value.frac.den - b->value.frac.num * a->value.frac.den;
        result.value.frac.den = a->value.frac.den * b->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = (a->kind == REALNUM_FRAC ? (long double)a->value.frac.num / a->value.frac.den : a->value.aprox) - (b->kind == REALNUM_FRAC ? (long double)b->value.frac.num / b->value.frac.den : b->value.aprox);
    }
    return result;
}

realnum realnum_mul(realnum* a, realnum* b) {
    realnum result;
    if (a->kind == REALNUM_FRAC && b->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = a->value.frac.num * b->value.frac.num;
        result.value.frac.den = a->value.frac.den * b->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = (a->kind == REALNUM_FRAC ? (long double)a->value.frac.num / a->value.frac.den : a->value.aprox) * (b->kind == REALNUM_FRAC ? (long double)b->value.frac.num / b->value.frac.den : b->value.aprox);
    }
    return result;
}

realnum realnum_div(realnum* a, realnum* b) {
    realnum result;
    if (a->kind == REALNUM_FRAC && b->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = a->value.frac.num * b->value.frac.den;
        result.value.frac.den = a->value.frac.den * b->value.frac.num;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = (a->kind == REALNUM_FRAC ? (long double)a->value.frac.num / a->value.frac.den : a->value.aprox) / (b->kind == REALNUM_FRAC ? (long double)b->value.frac.num / b->value.frac.den : b->value.aprox);
    }
    return result;
}

realnum realnum_neg(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = -num->value.frac.num;
        result.value.frac.den = num->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = -num->value.aprox;
    }
    return result;
}

realnum realnum_inv(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = num->value.frac.den;
        result.value.frac.den = num->value.frac.num;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = 1 / (num->kind == REALNUM_FRAC ? (long double)num->value.frac.num / num->value.frac.den : num->value.aprox);
    }
    return result;
}

realnum realnum_abs(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = num->value.frac.num < 0 ? -num->value.frac.num : num->value.frac.num;
        result.value.frac.den = num->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = num->value.aprox < 0 ? -num->value.aprox : num->value.aprox;
    }
    return result;
}

realnum realnum_pow(realnum* num, realnum* exp) {
    realnum result;
    if (num->kind == REALNUM_FRAC && exp->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = powl(num->value.frac.num, exp->value.frac.num);
        result.value.frac.den = powl(num->value.frac.den, exp->value.frac.num);
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = powl(num->kind == REALNUM_FRAC ? (long double)num->value.frac.num / num->value.frac.den : num->value.aprox, exp->kind == REALNUM_FRAC ? (long double)exp->value.frac.num / exp->value.frac.den : exp->value.aprox);
    }
    return result;
}

realnum realnum_sqrt(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = sqrtl(num->value.frac.num);
        result.value.frac.den = sqrtl(num->value.frac.den);
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = sqrtl(num->kind == REALNUM_FRAC ? (long double)num->value.frac.num / num->value.frac.den : num->value.aprox);
    }
    return result;
}

realnum realnum_cbrt(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = cbrtl(num->value.frac.num);
        result.value.frac.den = cbrtl(num->value.frac.den);
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = cbrtl(num->kind == REALNUM_FRAC ? (long double)num->value.frac.num / num->value.frac.den : num->value.aprox);
    }
    return result;
}

realnum realnum_exp(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = expl(num->value.frac.num);
        result.value.frac.den = expl(num->value.frac.den);
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = expl(num->kind == REALNUM_FRAC ? (long double)num->value.frac.num / num->value.frac.den : num->value.aprox);
    }
    return result;
}

realnum realnum_as_frac(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = num->value.frac.num;
        result.value.frac.den = num->value.frac.den;
    } else {
        result.kind = REALNUM_FRAC;
        result.value.frac.num = num->value.aprox;
        result.value.frac.den = 1;
    }
    return result;
}

realnum realnum_as_aprox(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        result.kind = REALNUM_APROX;
        result.value.aprox = (long double)num->value.frac.num / num->value.frac.den;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = num->value.aprox;
    }
    return result;
}

realnum realnum_fracsimp(realnum* num) {
    realnum result;
    if (num->kind == REALNUM_FRAC) {
        int64_t a = num->value.frac.num;
        int64_t b = num->value.frac.den;
        int64_t c;
        while (b != 0) {
            c = a % b;
            a = b;
            b = c;
        }
        result.kind = REALNUM_FRAC;
        result.value.frac.num = num->value.frac.num / a;
        result.value.frac.den = num->value.frac.den / a;
    } else {
        result.kind = REALNUM_APROX;
        result.value.aprox = num->value.aprox;
    }
    return result;
}

realnum apply_op(realnum* a, realnum* b, realnum (*op)(realnum*, realnum*)) {
    return op(a, b);
}

void realnum_print(realnum* num, uint16_t precision) {
    if (num->kind == REALNUM_FRAC) {
        printf("%ld/%ld", num->value.frac.num, num->value.frac.den);
    } else {
        char buf[BUF_SIZE];
        quadmath_snprintf (buf, sizeof buf, "%.*Qf", precision, num->value.aprox);
        printf("%s", buf);
    }
}

void realnum_println(realnum* num, uint16_t precision) {
    realnum_print(num, precision);
    printf("\n");
}

void realnum_print_as_frac(realnum* num) {
    if (num->kind == REALNUM_FRAC) {
        printf("%ld/%ld", num->value.frac.num, num->value.frac.den);
    } else {
        realnum frac = realnum_as_frac(num);
        realnum_print_as_frac(&frac);
    }
}

void realnum_print_as_aprox(realnum* num, uint16_t precision) {
    if (num->kind == REALNUM_FRAC) {
        realnum aprox = realnum_as_aprox(num);
        realnum_print_as_aprox(&aprox, precision);
    } else {
        char buf[BUF_SIZE];
        quadmath_snprintf (buf, sizeof buf, "%.*Qf", precision, num->value.aprox);
        printf("%s", buf);
    }
}

#undef BUF_SIZE
