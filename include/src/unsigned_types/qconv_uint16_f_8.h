//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"

#define QCONV_EXP_F_8 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_8 257
#define QCONV_P_ROOT_F_8_LEN_16 2

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_f_8;
extern const qconv_uint16_mod qconv_const_p_root_f_8_len_16;

inline qconv_uint16_mod_f_8 qconv_reduce_uint32_mod_f_8(qconv_uint32 x) {
    qconv_uint16_mod_f_8 y = {.value = x.value % qconv_const_f_8.mod_f_8.value};
    return y;
}

/*
 * @brief Fast multiplication modulo F_8 = 2^8 + 1
 */
inline qconv_uint16_mod_f_8 qconv_mul_uint16_mod_f_8(const qconv_uint16_mod_f_8 x, const qconv_uint16_mod_f_8 y) {
    qconv_uint32 z  = {.value = (qconv_inner_uint32) x.value * y.value};
    qconv_uint16_mod_f_8 reduced = qconv_reduce_uint32_mod_f_8(z);
    return reduced;
}

/*
 * @brief Addition modulo F_8 = 2^ + 1
 */
inline qconv_uint16_mod_f_8 qconv_add_uint16_mod_f_8(qconv_uint16_mod_f_8 x, qconv_uint16_mod_f_8 y) {
    qconv_uint16_mod_f_8 result = {.value = x.value + y.value};
    if (result.value < qconv_const_f_8.mod_f_8.value) {
        return result;
    } else {
        result.value = result.value - qconv_const_f_8.mod_f_8.value;
        return result;
    }
}

/*
 * @brief Subtraction modulo F_8 = 2^ + 1
 */
inline qconv_uint16_mod_f_8 qconv_subtract_uint16_mod_f_8(qconv_uint16_mod_f_8 x, qconv_uint16_mod_f_8 y) {
    qconv_uint16_mod_f_8 result;
    if (x.value >= y.value) {
        result.value = x.value - y.value;
    } else {
        result.value = qconv_const_f_8.mod_f_8.value + x.value;
        result.value = result.value - y.value;
    }
    return result;
}

/*
 * @brief Fast exponentiation modulo F_8 = 2^8 + 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint16_mod_f_8 qconv_power_uint16_mod_f_8(const qconv_uint16_mod_f_8 base, unsigned int exp);

/*
 * @brief Point to point product modulo F_8 of two array
 */
inline void qconv_pmul_mod_f_8(const size_t size,
                               const qconv_uint16_mod a[static const size],
                               const qconv_uint16_mod b[static const size],
                               qconv_uint16_mod c[static size]) {
    for (size_t i = 0; i < size; i++) {
        c[i].mod_f_8 = qconv_mul_uint16_mod_f_8(a[i].mod_f_8, b[i].mod_f_8);
    }
}

/*
 * @brief CT butterfly with input scrambling
 */
void qconv_CT_mod_f_8(size_t size, qconv_uint16_mod a[static size], qconv_uint16_mod p_root, bool inverse);

/*
 * @brief NTT of length 16 mod F_8
 */
void qconv_NTT_len_16_mod_f_8(qconv_uint16_mod a[static QCONV_LEN_16]);

/*
 * @brief INTT of length 16 mod F_8, including normalization at the end so that a = INTT(NTT(a))
 */
void qconv_INTT_len_16_mod_f_8(qconv_uint16_mod a[static QCONV_LEN_16]);

/*
 * @brief a^-1 mod CONV_F_8
 */
qconv_uint16_mod_f_8 qconv_inverse_mod_f_8(qconv_uint16_mod a);

/*
 * @brief Normalization of an array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_len_norm_mod_f_8(const size_t size, qconv_uint16_mod a[static size]);


