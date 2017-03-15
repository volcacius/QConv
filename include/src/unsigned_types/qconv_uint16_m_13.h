//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "qconv.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"

#define QCONV_EXP_M_13 13

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_M_13 8191

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_m_13;

/*
 * @brief Fast reduction modulo M_13 = 2^13 - 1
 * Credits: http://www.mersenneforum.org/showthread.php?t=1955
 */
inline qconv_uint16_mod_m_13 qconv_reduce_uint32_mod_m_13(qconv_uint32 x) {
    qconv_uint32 z;
    z.value = (qconv_inner_uint32) ((z.value & qconv_const_m_13.mod_m_13.value) + (z.value >> QCONV_EXP_M_13));
    z.value = (qconv_inner_uint32) ((z.value & qconv_const_m_13.mod_m_13.value) + (z.value >> QCONV_EXP_M_13));
    qconv_uint16_mod_m_13 reduced;
    reduced.value = (qconv_inner_uint16) ((z.value == qconv_const_m_13.mod_m_13.value) ? 0 : z.value);
    return reduced;
}

/*
 * @brief Fast multiplication modulo M_13 = 2^13 - 1
 */
inline qconv_uint16_mod_m_13 qconv_mul_uint16_mod_m_13(const qconv_uint16_mod_m_13 x, const qconv_uint16_mod_m_13 y) {
    qconv_uint32 z = {.value = x.value * y.value};
    qconv_uint16_mod_m_13 reduced = qconv_reduce_uint32_mod_m_13(z);
    return reduced;
}

/*
 * @brief Fast exponentiation modulo M_13 = 2^13- 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint16_mod_m_13 qconv_power_uint16_mod_m_13(const qconv_uint16_mod_m_13 base, unsigned int exp);

