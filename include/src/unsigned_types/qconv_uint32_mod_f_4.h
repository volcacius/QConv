//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv.h"
#include "qconv_uint32.h"
#include "qconv_int32.h"
#include "qconv_int64.h"
#include "qconv_uint64.h"
#include "qconv_uint32_mod_f_4_constants.h"

inline qconv_uint32_mod_f_4 qconv_reduce_int64_mod_f_4(qconv_inner_int64 x) {
    qconv_inner_int64 r = x & 0xffff;
    qconv_inner_int64 q = qconv_int64_arishiftr(x, 16);
    qconv_inner_int64 y = r - q;
    if (y < 0) {
        y += QCONV_F_4;
    }
    qconv_uint32_mod_f_4 z = {.value = (qconv_inner_uint32) y};
    return z;
}

/*
 * @brief Fast multiplication modulo F_4 = 2^16 + 1
 */
inline qconv_uint32_mod_f_4 qconv_mul_uint32_mod_f_4(const qconv_uint32_mod_f_4 x, const qconv_uint32_mod_f_4 y) {
    //The cast after the = is not optional!
    qconv_inner_uint64 z  = ((qconv_inner_uint64) x.value) * ((qconv_inner_uint64) y.value);
    qconv_uint32_mod_f_4 reduced = qconv_reduce_int64_mod_f_4(z);
    return reduced;
}

/*
 * @brief Addition modulo F_4 = 2^16 + 1
 */
inline qconv_uint32_mod_f_4 qconv_add_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y) {
    qconv_uint32_mod_f_4 result = {.value = x.value + y.value};
    if (result.value < qconv_const_f_4.mod_f_4.value) {
        return result;
    } else {
        result.value = result.value - qconv_const_f_4.mod_f_4.value;
        return result;
    }
}

/*
 * @brief Subtraction modulo F_4 = 2^16 + 1
 */
inline qconv_uint32_mod_f_4 qconv_subtract_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y) {
    qconv_uint32_mod_f_4 result;
    if (x.value >= y.value) {
        result.value = x.value - y.value;
    } else {
        result.value = qconv_const_f_4.mod_f_4.value + x.value;
        result.value = result.value - y.value;
    }
    return result;
}

/*
 * @brief Fast exponentiation modulo F_4 = 2^16 + 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint32_mod_f_4 qconv_power_uint32_mod_f_4(qconv_uint32_mod_f_4 base, unsigned int exp);

/*
 * @brief Point to point product modulo F_4 of two array
 */
inline void qconv_pmul_mod_f_4(const size_t size,
                               const qconv_uint32_mod a[static const size],
                               const qconv_uint32_mod b[static const size],
                               qconv_uint32_mod c[static size]) {

    #pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        c[i].mod_f_4 = qconv_mul_uint32_mod_f_4(a[i].mod_f_4, b[i].mod_f_4);
    }
}

/*
 * @brief CT butterfly with input scrambling
 */
void qconv_CT_1D_uint32_mod_f_4(const size_t size,
                                qconv_uint32_mod a[static size],
                                const qconv_uint32_mod p_root,
                                const size_t p_root_size,
                                const bool inverse);

/*
 * @brief CT butterfly with input scrambling and precomputed root powers
 */
void qconv_CT_1D_precomp_uint32_mod_f_4(const size_t size,
                                        qconv_uint32_mod a[static size],
                                        const qconv_uint16 *powers);

/*
 * @brief NTT of length up to 32 mod F_4
 */
enum qconv_status qconv_NTT_1D_uint32_mod_f_4(const size_t size,
                                              qconv_uint32_mod a[static size],
                                              const enum qconv_optimize_transform optimize_level);

/*
 * @brief INTT of length up to 32 mod F_4, including normalization at the end so that a = INTT(NTT(a))
 */
enum qconv_status qconv_INTT_1D_uint32_mod_f_4(const size_t size,
                                               qconv_uint32_mod a[static size],
                                               const enum qconv_optimize_transform optimize_level);

/*
 * @brief a^-1 mod CONV_F_4
 */
qconv_uint32_mod_f_4 qconv_inverse_uint32_mod_f_4(qconv_uint32_mod a);

/*
 * @brief Normalization of an 1D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_1D_size_norm_uint32_mod_f_4(const size_t size, qconv_uint32_mod a[static size]);

/*
 * @brief Normalization of an 2D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_2D_size_norm_uint32_mod_f_4(const size_t size_width,
                                            const size_t size_height,
                                            qconv_uint32_mod a[static size_width * size_height]);

/*
 * @brief NTT 1D circular convolution of length up to 256, mod F_4
 */
enum qconv_status qconv_NTT_1D_circular_convolution_uint32_mod_f_4(const size_t size,
                                                                   qconv_uint32_mod a[static size],
                                                                   qconv_uint32_mod b[static size],
                                                                   qconv_uint32_mod ntt[size],
                                                                   const enum qconv_optimize_transform optimize_level);

/*
 * @brief NTT 1D linear convolution of output length up to 256, mod F_4
 */
enum qconv_status qconv_NTT_1D_linear_convolution_uint32_mod_f_4(const size_t input_size,
                                                                 const size_t kernel_size,
                                                                 qconv_uint32_mod input[static input_size],
                                                                 qconv_uint32_mod kernel[static kernel_size],
                                                                 qconv_uint32_mod ntt[input_size + kernel_size - 1],
                                                                 const enum qconv_optimize_transform optimize_level);

void qconv_CT_2D_uint32_mod_f_4(const size_t size_width,
                                const size_t size_height,
                                qconv_uint32_mod a[size_width * size_height],
                                qconv_uint32_mod row_p_root,
                                qconv_uint32_mod column_p_root,
                                const size_t row_p_root_size,
                                const size_t column_p_root_size,
                                const bool inverse);

void qconv_CT_2D_precomp_uint32_mod_f_4(const size_t size_width,
                                        const size_t size_height,
                                        qconv_uint32_mod a[size_width * size_height],
                                        const qconv_uint16 *row_powers,
                                        const qconv_uint16 *column_powers);

enum qconv_status qconv_NTT_2D_uint32_mod_f_4(const size_t size_width,
                                              const size_t size_height,
                                              qconv_uint32_mod a[static size_width * size_height],
                                              enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_INTT_2D_uint32_mod_f_4(const size_t size_width,
                                               const size_t size_height,
                                               qconv_uint32_mod a[static size_width * size_height],
                                               enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_circular_convolution_uint32_mod_f_4(const size_t size_width,
                                                                   const size_t size_height,
                                                                   qconv_uint32_mod a[static size_width * size_height],
                                                                   qconv_uint32_mod b[static size_width * size_height],
                                                                   qconv_uint32_mod ntt[size_width * size_height],
                                                                   const enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_linear_convolution_uint32_mod_f_4(const size_t input_size_width,
                                                                 const size_t input_size_height,
                                                                 const size_t kernel_size_width,
                                                                 const size_t kernel_size_height,
                                                                 qconv_uint32_mod input[static input_size_width * input_size_height],
                                                                 qconv_uint32_mod kernel[static kernel_size_width * kernel_size_height],
                                                                 qconv_uint32_mod ntt[(input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)],
                                                                 const enum qconv_optimize_transform optimize_level);

