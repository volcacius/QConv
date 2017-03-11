//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <event.h>
#include <stdlib.h>

#include "qconv.h"
#include "qconv_int64.h"

#define QCONV_EXP_M_13 13
#define QCONV_EXP_F_8 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_M_13 8191
#define QCONV_12289 12289
#define QCONV_F_8 257

//Typedef a 32bit data type to a project wide inner 32bit representation
typedef int32_t qconv_inner_int32;

//Wrap the inner 32bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_int32 qconv_int32;
struct qconv_int32 {
    qconv_inner_int32 value;
};

typedef struct qconv_mod_f_8 qconv_mod_f_8;
struct qconv_mod_f_8 {
    qconv_inner_int32 value;
};

typedef struct qconv_mod_m_13 qconv_mod_m_13;
struct qconv_mod_m_13 {
    qconv_inner_int32 value;
};

typedef struct qconv_mod_12289 qconv_mod_12289;
struct qconv_mod_12289 {
    qconv_inner_int32 value;
};

//Overlay the various 32bit struct representation since they share the same inner 32bit representation
typedef union qconv_int32_mod qconv_int32_mod;
union qconv_int32_mod {
    qconv_mod_f_8 mod_f_8;
    qconv_mod_m_13 mod_m_13;
    qconv_mod_12289 mod_12289;
    qconv_int32 int32;
};

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_int32_mod qconv_const_f_8;
extern const qconv_int32_mod qconv_const_m_13;
extern const qconv_int32_mod qconv_const_12289;

extern const int32_t mask12;


inline qconv_mod_f_8 qconv_reduce_mod_f_8(qconv_mod_f_8 x) {
    qconv_mod_f_8 y = {.value = x.value % qconv_const_f_8.mod_f_8.value};
    return y;
}

/*
 * @brief Fast reduction modulo M_13 = 2^13 - 1
 * Credits: http://www.mersenneforum.org/showthread.php?t=1955
 */
inline qconv_mod_m_13 qconv_reduce_mod_m_13(qconv_mod_m_13 x) {
    x.value = (qconv_inner_int32) ((x.value & qconv_const_m_13.mod_m_13.value) + (x.value >> QCONV_EXP_M_13));
    x.value = (qconv_inner_int32) ((x.value & qconv_const_m_13.mod_m_13.value) + (x.value >> QCONV_EXP_M_13));
    x.value = (qconv_inner_int32) ((x.value == qconv_const_m_13.mod_m_13.value) ? 0 : x.value);
    return x;
}

/*
 * @brief Fast multiplication modulo M_13 = 2^13 - 1
 */
inline qconv_mod_m_13 qconv_mul_mod_m_13(qconv_mod_m_13 x, qconv_mod_m_13 y) {
    qconv_mod_m_13 z = {.value = x.value * y.value};
    z = qconv_reduce_mod_m_13(z);
    return z;
}

/*
 * @brief Fast multiplication modulo F_8 = 2^8 + 1
 */
inline qconv_mod_f_8 qconv_mul_mod_f_8(qconv_mod_f_8 x, qconv_mod_f_8 y) {
    qconv_mod_f_8 z = {.value = x.value * y.value};
    z = qconv_reduce_mod_f_8(z);
    return z;
}

/*
 * @brief Reduction modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline qconv_mod_12289 qconv_reduce_mod_12289(qconv_inner_int64 a) {
    qconv_mod_12289 c0, c1;
    qconv_mod_12289 output;

    c0.value = (qconv_inner_int32) (a & mask12);
    c1.value = (qconv_inner_int32) (a >> 12);

    output.value = (3*c0.value - c1.value);
    return output;
}

/*
 * @brief Two consecutive reductions modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_two_reduce_mod_12289(qconv_int32_mod a[static 1], unsigned int N) {
    unsigned int i;
    for (i = 0; i < N; i++) {
        a[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[i].mod_12289.value);
        a[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[i].mod_12289.value);
    }
}

/*
 * @brief Two merged reductions modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline qconv_mod_12289 qconv_two_merged_reduce_mod_12289(qconv_inner_int64 a) {
    qconv_mod_12289 c0, c1, c2;
    qconv_mod_12289 output;

    c0.value = (qconv_inner_int32) (a & mask12);
    c1.value = (qconv_inner_int32) ((a >> 12) & mask12);
    c2.value = (qconv_inner_int32) (a >> 24);

    output.value = 9 * c0.value - 3 * c1.value + c2.value;
    return output;
}

/*
 * @brief Correction modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_correction_mod_12289(qconv_int32_mod a[static 1], unsigned int N) {
    unsigned int i;
    qconv_inner_int32 mask;

    for (i = 0; i < N; i++) {
        mask = a[i].mod_12289.value >> (4 * sizeof(qconv_inner_int32) - 1);
        a[i].mod_12289.value += (qconv_const_12289.mod_12289.value & mask) - qconv_const_12289.mod_12289.value;
        mask = a[i].mod_12289.value >> (4 * sizeof(qconv_inner_int32) - 1);
        a[i].mod_12289.value += (qconv_const_12289.mod_12289.value & mask);
    }
}

/*
 * @brief Component-wise multiplication
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_pmul_mod_12289(qconv_int32_mod a[static 1],
                                 qconv_int32_mod b[static 1],
                                 qconv_int32_mod *c,
                                 unsigned int N) {
    unsigned int i;
    for (i = 0; i < N; i++) {
        c[i].mod_12289 = qconv_reduce_mod_12289((int64_t) a[i].mod_12289.value * b[i].mod_12289.value);
        c[i].mod_12289 = qconv_reduce_mod_12289((int64_t) c[i].mod_12289.value);
    }
}

/*
 * @brief Component-wise multiplication and addition
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_pmuladd_mod_12289(qconv_mod_12289 a[static 1],
                                    qconv_mod_12289 b[static 1],
                                    qconv_mod_12289 c[static 1],
                                    qconv_mod_12289* d, unsigned int N) {
    unsigned int i;
    for (i = 0; i < N; i++) {
        d[i] = qconv_reduce_mod_12289((int64_t) a[i].value * b[i].value + c[i].value);
        d[i] = qconv_reduce_mod_12289((int64_t) d[i].value);
    }
}

/*
 * @brief Fast exponentiation modulo F_8 = 2^8 + 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_mod_f_8 qconv_power_mod_f_8(qconv_mod_f_8 base, int exp);

/*
 * @brief Fast exponentiation modulo M_13 = 2^13- 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_mod_m_13 qconv_power_mod_m_13(qconv_mod_m_13 base, int exp);

/*
 * @brief Forward NTT
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
void qconv_NTT_CT_std2rev_mod_12289(qconv_int32_mod a[static 1],
                                    const qconv_inner_int32 psi_rev[static 1],
                                    unsigned int N);

/*
 * @brief Inverse NTT
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
void qconv_INTT_GS_rev2std_mod_12289(qconv_int32_mod a[static 1],
                                     const qconv_inner_int32 omegainv_rev[static 1],
                                     const qconv_int32 omegainv1N_rev,
                                     const qconv_int32 Ninv,
                                     unsigned int N);

// Component-wise multiplication with scalar
inline void qconv_int32_smul(qconv_int32_mod a[static 1], qconv_int32 scalar, unsigned int N) {
    unsigned int i;
    for (i = 0; i < N; i++) {
        a[i].int32.value = a[i].int32.value * scalar.value;
    }
}

enum qconv_status qconv_int32_direct_1D_linear_convolution (
        size_t input_size,
        size_t kernel_size,
        const qconv_int32_mod input[static 1],
        const qconv_int32_mod kernel[static 1],
        qconv_int32_mod* output);

enum qconv_status qconv_int32_direct_1D_circular_convolution (
        size_t size,
        const qconv_int32_mod input[static 1],
        const qconv_int32_mod kernel[static 1],
        qconv_int32_mod* output);
