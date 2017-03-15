//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "qconv.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"

#define QCONV_EXP_F_8 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_8 257

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_f_8;

inline qconv_uint16_mod_f_8 qconv_reduce_uint32_mod_f_8(qconv_uint32 x) {
    qconv_uint16_mod_f_8 y = {.value = (qconv_inner_uint16) x.value % qconv_const_f_8.mod_f_8.value};
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
 * @brief Fast exponentiation modulo F_8 = 2^8 + 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint16_mod_f_8 qconv_power_uint16_mod_f_8(const qconv_uint16_mod_f_8 base, unsigned int exp);
