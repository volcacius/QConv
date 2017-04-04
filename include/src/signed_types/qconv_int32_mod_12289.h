//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "qconv_constants.h"
#include "qconv_int32.h"
#include "qconv_int64.h"

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_12289 12289

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_int32_mod qconv_const_12289;

extern const int32_t mask12;

/*
 * @brief Reduction modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline qconv_int32_mod_12289 qconv_reduce_mod_12289(const qconv_inner_int64 a) {
    qconv_int32_mod_12289 c0, c1;
    qconv_int32_mod_12289 output;

    c0.value = (qconv_inner_int32) (a & mask12);
    c1.value = (qconv_inner_int32) (a >> 12);

    output.value = (3*c0.value - c1.value);
    return output;
}

/*
 * @brief Two consecutive reductions modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_two_reduce_mod_12289(const size_t size, qconv_int32_mod a[static size]) {
    for (size_t i = 0; i < size; i++) {
        a[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[i].mod_12289.value);
        a[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[i].mod_12289.value);
    }
}

/*
 * @brief Two merged reductions modulo 12289
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline qconv_int32_mod_12289 qconv_two_merged_reduce_mod_12289(const qconv_inner_int64 a) {
    qconv_int32_mod_12289 c0, c1, c2;
    qconv_int32_mod_12289 output;

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
inline void qconv_correction_mod_12289(const size_t size, qconv_int32_mod a[static size]) {
    qconv_inner_int32 mask;

    for (size_t i = 0; i < size; i++) {
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
inline void qconv_pmul_mod_12289(const size_t size,
                                 const qconv_int32_mod a[static const size],
                                 const qconv_int32_mod b[static const size],
                                 qconv_int32_mod c[static size]) {
    for (size_t i = 0; i < size; i++) {
        c[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[i].mod_12289.value * b[i].mod_12289.value);
        c[i].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) c[i].mod_12289.value);
    }
}

/*
 * @brief Component-wise multiplication and addition
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_pmuladd_mod_12289(const size_t size,
                                    const qconv_int32_mod_12289 a[static const size],
                                    const qconv_int32_mod_12289 b[static const size],
                                    const qconv_int32_mod_12289 c[static const size],
                                    qconv_int32_mod_12289 d[static size]) {
    for (size_t i = 0; i < size; i++) {
        d[i] = qconv_reduce_mod_12289((qconv_inner_int64) a[i].value * b[i].value + c[i].value);
        d[i] = qconv_reduce_mod_12289((qconv_inner_int64) d[i].value);
    }
}

/*
 * @brief Forward NTT
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
void qconv_NTT_CT_std2rev_mod_12289(const size_t size,
                                    qconv_int32_mod a[static size],
                                    const qconv_inner_int32 psi_rev[static const size]);

/*
 * @brief Inverse NTT
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
void qconv_INTT_GS_rev2std_mod_12289(const size_t size,
                                     qconv_int32_mod a[static size],
                                     const qconv_inner_int32 omegainv_rev[static const size],
                                     const qconv_int32_mod_12289 omegainv1N_rev,
                                     const qconv_int32_mod_12289 Ninv);

/*
 * @brief Component-wise multiplication with scalar
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */
inline void qconv_int32_smul(const size_t size,
                             qconv_int32_mod a[static size],
                             const qconv_int32 scalar) {
    for (size_t i = 0; i < size; i++) {
        a[i].int32.value = a[i].int32.value * scalar.value;
    }
}

enum qconv_status qconv_2D_NTT_rc_mod_12289 (size_t size_x,
                                             size_t size_y,
                                             qconv_int32_mod a[static size_x * size_y],
                                             const qconv_inner_int32 psi_rev_x[static const size_x],
                                             const qconv_inner_int32 psi_rev_y[static const size_y]);

enum qconv_status qconv_2D_INTT_rc_mod_12289 (size_t size_x,
                                              size_t size_y,
                                              qconv_int32_mod a[static size_x * size_y],
                                              const qconv_inner_int32 omegainv_rev_x[static const size_x],
                                              const qconv_inner_int32 omegainv_rev_y[static const size_y],
                                              const qconv_int32 omegainv1N_rev,
                                              const qconv_int32 Ninv);

