//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv_constants.h"
#include "qconv_uint32.h"
#include "qconv_int32.h"
#include "qconv_int64.h"
#include "qconv_uint64.h"
#include "qconv_uint32_mod_f_4_constants.h"
#include "qconv_utils.h"

inline qconv_uint32_mod_f_4 qconv_reduce_uint32_mod_f_4(qconv_inner_uint32 x) {
    qconv_inner_uint32 r = x & 0xffff;
    qconv_inner_uint32 q = x >> QCONV_EXP_F_4;
    qconv_inner_int32 y = r - q;
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
    qconv_uint32_mod_f_4 reduced;
    if (x.value == QCONV_F_4 - 1 && y.value == QCONV_F_4 - 1) {
        reduced.value = 1;
    } else {
        qconv_inner_uint32 z = x.value *  y.value;
        reduced = qconv_reduce_uint32_mod_f_4(z);
    }
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

    for (size_t i = 0; i < size; i++) {
        c[i].mod_f_4 = qconv_mul_uint32_mod_f_4(a[i].mod_f_4, b[i].mod_f_4);
    }
}

/*
 * @brief CT transform with input scrambling
 */
void qconv_DIT_r2_std2std_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size,
                                            const bool inverse);

/*
 * @brief CT transform with input scrambling and precomputed root powers
 */
void qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers);

void qconv_DIT_r2_rev2std_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size,
                                            bool inverse);

void qconv_DIF_r2_std2rev_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size);

void qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers);

void qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers);


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

enum qconv_status qconv_NTT_1D_block_cnn_convolution_uint32_mod_f_4(size_t input_size,
                                                                    size_t kernel_size,
                                                                    size_t stride,
                                                                    qconv_uint32_mod input[input_size],
                                                                    qconv_uint32_mod kernel[kernel_size],
                                                                    qconv_uint32_mod output[input_size + kernel_size - 1],
                                                                    enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_1D_block_linear_convolution_uint32_mod_f_4(size_t input_size,
                                                                       size_t kernel_size,
                                                                       qconv_uint32_mod input[input_size],
                                                                       qconv_uint32_mod kernel[kernel_size],
                                                                       qconv_uint32_mod output[input_size + kernel_size - 1],
                                                                       enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_block_linear_convolution_uint32_mod_f_4(size_t input_size_width,
                                                                       size_t input_size_height,
                                                                       size_t kernel_size_width,
                                                                       size_t kernel_size_height,
                                                                       size_t block_size_width,
                                                                       size_t block_size_height,
                                                                       qconv_uint32_mod input[static input_size_width * input_size_height],
                                                                       qconv_uint32_mod kernel[static kernel_size_width * kernel_size_height],
                                                                       qconv_uint32_mod output[static (input_size_width + kernel_size_width - 1)
                                                                                                   * (input_size_height + kernel_size_height - 1)],
                                                                       enum qconv_optimize_transform optimize_level);

