//
// Created by Alessandro on 02/03/2017.
//

#pragma once

#include <stdint.h>
#include <stddef.h>

#include "qconv.h"
#include "qconv_int16.h"


#define QCONV_EXP_M_8 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_M_8 255

//Typedef a 16bit data type to a project wide inner 16bit representation
typedef int16_t qconv_inner_int16;

//Wrap the inner 16bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_int16 qconv_int16;
struct qconv_int16 {
    qconv_inner_int16 value;
};

typedef struct qconv_mod_m_8 qconv_mod_m_8;
struct qconv_mod_m_8 {
    qconv_inner_int16 value;
};

//Overlay the various 16bit struct representation since they share the same inner 16bit representation
typedef union int16_mod qconv_int16_mod;
union int16_mod {
    qconv_mod_m_8 mod_m_8;
    qconv_int16 int16;
};

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_int16_mod qconv_const_m_8;

/*
 * @brief Fast reduction modulo QCONV_M_8 = 2^8 - 1
 * Credits: http://www.mersenneforum.org/showthread.php?t=1955
 */
inline qconv_mod_m_8 qconv_reduce_mod_m_8(qconv_mod_m_8 x) {
    x.value = (qconv_inner_int16) ((x.value & qconv_const_m_8.mod_m_8.value) + (x.value >> QCONV_EXP_M_8));
    x.value = (qconv_inner_int16) ((x.value & qconv_const_m_8.mod_m_8.value) + (x.value >> QCONV_EXP_M_8));
    x.value = (qconv_inner_int16) ((x.value == qconv_const_m_8.mod_m_8.value) ? 0 : x.value);
    return x;
}

/*
 * @brief Fast multiplication modulo M_8 = 2^8 - 1
 */
inline qconv_mod_m_8 qconv_mul_mod_m_8(qconv_mod_m_8 x, qconv_mod_m_8 y) {
    qconv_mod_m_8 z = {.value = x.value * y.value};
    z = qconv_reduce_mod_m_8(z);
    return z;
}

/*
 * @brief Fast exponentiation modulo QCONV_M_8 = 2^8 - 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_mod_m_8 qconv_power_mod_m_8(qconv_mod_m_8 base, unsigned int exp);

enum qconv_status qconv_int16_direct_1D_linear_convolution (
        size_t input_size,
        size_t kernel_size,
        const qconv_int16 input[static 1],
        const qconv_int16 kernel[static 1],
        qconv_int16 output[static 1]);

enum qconv_status qconv_int16_direct_1D_circular_convolution (
        size_t size,
        const qconv_int16 input[static 1],
        const qconv_int16 kernel[static 1],
        qconv_int16 output[static 1]);

