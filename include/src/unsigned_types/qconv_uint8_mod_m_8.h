//
// Created by Alessandro on 02/03/2017.
//

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "qconv_constants.h"
#include "qconv_uint8.h"
#include "qconv_uint16.h"

#define QCONV_EXP_M_8 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_M_8 255

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint8_mod qconv_const_m_8;

/*
 * @brief Fast reduction modulo QCONV_M_8 = 2^8 - 1
 * Credits: http://www.mersenneforum.org/showthread.php?t=1955
 */
inline qconv_uint8_mod_m_8 qconv_reduce_uint16_mod_m_8(qconv_uint16 x) {
    qconv_uint16 z;
    z.value = ((z.value & ((qconv_inner_uint16) qconv_const_m_8.mod_m_8.value)) + (z.value >> QCONV_EXP_M_8));
    z.value = ((z.value & ((qconv_inner_uint16) qconv_const_m_8.mod_m_8.value)) + (z.value >> QCONV_EXP_M_8));
    qconv_uint8_mod_m_8 reduced;
    reduced.value = ((((qconv_inner_uint8) z.value) == qconv_const_m_8.mod_m_8.value) ? 0 : z.value);
    return reduced;
}

/*
 * @brief Fast multiplication modulo M_8 = 2^8 - 1
 */
inline qconv_uint8_mod_m_8 qconv_mul_uint8_mod_m_8(const qconv_uint8_mod_m_8 x, const qconv_uint8_mod_m_8 y) {
    qconv_uint16 z = {.value = (qconv_inner_uint16) x.value * y.value};
    return qconv_reduce_uint16_mod_m_8(z);
}

/*
 * @brief Fast exponentiation modulo QCONV_M_8 = 2^8 - 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint8_mod_m_8 qconv_power_uint8_mod_m_8(qconv_uint8_mod_m_8 base, unsigned int exp);

