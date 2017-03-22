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
#include "qconv_uint16_mod_f_8_constants.h"

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
void qconv_CT_1D_mod_f_8(size_t size, qconv_uint16_mod *a, qconv_uint16_mod p_root, bool inverse);

/*
 * @brief NTT of length up to 256 mod F_8
 */
enum qconv_status qconv_NTT_1D_uint16_mod_f_8(const size_t size, qconv_uint16_mod a[static size]);

/*
 * @brief INTT of length up to 256 mod F_8, including normalization at the end so that a = INTT(NTT(a))
 */
enum qconv_status qconv_INTT_1D_uint16_mod_f_8(const size_t size, qconv_uint16_mod a[static size]);

/*
 * @brief a^-1 mod CONV_F_8
 */
qconv_uint16_mod_f_8 qconv_inverse_uint16_mod_f_8(qconv_uint16_mod a);

/*
 * @brief Normalization of an 1D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_1D_size_norm_uint16_mod_f_8(const size_t size, qconv_uint16_mod a[static size]);

/*
 * @brief Normalization of an 2D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_2D_size_norm_uint16_mod_f_8(const size_t size_width,
                                            const size_t size_height,
                                            qconv_uint16_mod a[static size_width * size_height]);

/*
 * @brief NTT 1D circular convolution of length up to 256, mod F_8
 */
enum qconv_status qconv_NTT_1D_circular_convolution_uint16_mod_f_8(size_t size,
                                                                   qconv_uint16_mod a[static size],
                                                                   qconv_uint16_mod b[static size],
                                                                   qconv_uint16_mod ntt[size]);

/*
 * @brief NTT 1D linear convolution of output length up to 256, mod F_8
 */
enum qconv_status qconv_NTT_1D_linear_convolution_uint16_mod_f_8(size_t input_size,
                                                                 size_t kernel_size,
                                                                 qconv_uint16_mod input[static input_size],
                                                                 qconv_uint16_mod kernel[static kernel_size],
                                                                 qconv_uint16_mod ntt[input_size + kernel_size - 1]);

enum qconv_status qconv_CT_2D_uint16_mod_f_8(size_t size_width,
                                             size_t size_height,
                                             qconv_uint16_mod *a,
                                             qconv_uint16_mod p_root,
                                             bool inverse);

enum qconv_status qconv_NTT_2D_circular_convolution_uint16_mod_f_8(size_t size_width,
                                                                   size_t size_height,
                                                                   qconv_uint16_mod a[static size_width * size_height],
                                                                   qconv_uint16_mod b[static size_width * size_height],
                                                                   qconv_uint16_mod ntt[size_width * size_height]);

enum qconv_status qconv_NTT_2D_linear_convolution_uint16_mod_f_8(size_t input_size_width,
                                                                 size_t input_size_height,
                                                                 size_t kernel_size_width,
                                                                 size_t kernel_size_height,
                                                                 qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                 qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                 qconv_uint16_mod ntt[(input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)]);


