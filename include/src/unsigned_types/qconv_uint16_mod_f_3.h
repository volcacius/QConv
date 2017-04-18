//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv_constants.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"
#include "qconv_int32.h"
#include "qconv_uint16_mod_f_3_constants.h"
#include "qconv_utils.h"

inline qconv_uint16_mod_f_3 qconv_reduce_uint32_mod_f_3(qconv_inner_uint32 x) {
    qconv_inner_uint32 r = x & 0xff;
    qconv_inner_uint32 q = x >> QCONV_EXP_F_3;
    qconv_inner_int32 y = r - q;
    if (y < 0) {
        y += QCONV_F_3;
    }
    qconv_uint16_mod_f_3 z = {.value = (qconv_inner_uint16) y};
    return z;
}

/*
 * @brief Fast multiplication modulo F_3 = 2^8 + 1
 */
inline qconv_uint16_mod_f_3 qconv_mul_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y) {
    qconv_inner_uint32 z  = x.value * y.value;
    qconv_uint16_mod_f_3 reduced = qconv_reduce_uint32_mod_f_3(z);
    return reduced;
}

inline qconv_uint16_mod_f_3 qconv_forward_shift_uint16_mod_f_3(const qconv_uint16_mod_f_3 x,
                                                               const qconv_uint16_mod_f_3 y) {
    qconv_inner_uint32 z  = x.value << y.value;
    qconv_uint16_mod_f_3 reduced = qconv_reduce_uint32_mod_f_3(z);
    return reduced;
}


inline qconv_uint16_mod_f_3 qconv_inverse_shift_uint16_mod_f_3(const qconv_uint16_mod_f_3 x, const qconv_uint16_mod_f_3 y) {
    qconv_inner_uint32 z  = (QCONV_F_3 - x.value) << y.value;
    qconv_uint16_mod_f_3 reduced = qconv_reduce_uint32_mod_f_3(z);
    return reduced;
}

/*
 * @brief Addition modulo F_3 = 2^8 + 1
 */
inline qconv_uint16_mod_f_3 qconv_add_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y) {
    qconv_uint16_mod_f_3 result = {.value = x.value + y.value};
    if (result.value < qconv_const_f_3.mod_f_3.value) {
        return result;
    } else {
        result.value = result.value - qconv_const_f_3.mod_f_3.value;
        return result;
    }
}

/*
 * @brief Subtraction modulo F_3 = 2^8 + 1
 */
inline qconv_uint16_mod_f_3 qconv_subtract_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y) {
    qconv_uint16_mod_f_3 result;
    if (x.value >= y.value) {
        result.value = x.value - y.value;
    } else {
        result.value = qconv_const_f_3.mod_f_3.value + x.value;
        result.value = result.value - y.value;
    }
    return result;
}

/*
 * @brief Fast exponentiation modulo F_3 = 2^8 + 1
 * Credits: https://discuss.codechef.com/questions/20451/a-tutorial-on-fast-modulo-multiplication-exponential-squaring
 */
qconv_uint16_mod_f_3 qconv_power_uint16_mod_f_3(qconv_uint16_mod_f_3 base, unsigned int exp);

/*
 * @brief Point to point product modulo F_3 of two array
 */
inline void qconv_pmul_mod_f_3(const size_t size,
                               const qconv_uint16_mod a[static const size],
                               const qconv_uint16_mod b[static const size],
                               qconv_uint16_mod c[static size]) {
    for (size_t i = 0; i < size; i++) {
        c[i].mod_f_3 = qconv_mul_uint16_mod_f_3(a[i].mod_f_3, b[i].mod_f_3);
    }
}

/*
 * @brief CT transform with input scrambling
 */
void qconv_DIT_r2_std2std_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size,
                                            const bool inverse);

/*
 * @brief CT transform with input scrambling and precomputed root powers
 */
void qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers);

void qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(const size_t size,
                                                            const size_t log2_size,
                                                            qconv_uint16_mod a[static size],
                                                            const qconv_inner_uint8 *powers);

void qconv_DIT_r2_rev2std_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size,
                                            bool inverse);

void qconv_DIF_r2_std2rev_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size);

void qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers);

void qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers);

/*
 * @brief NTT of length up to 256 mod F_3
 */
enum qconv_status qconv_NTT_1D_uint16_mod_f_3(const size_t size,
                                              qconv_uint16_mod a[static size],
                                              const enum qconv_optimize_transform optimize_level);

/*
 * @brief INTT of length up to 256 mod F_3, including normalization at the end so that a = INTT(NTT(a))
 */
enum qconv_status qconv_INTT_1D_uint16_mod_f_3(const size_t size,
                                               qconv_uint16_mod a[static size],
                                               const enum qconv_optimize_transform optimize_level);

/*
 * @brief a^-1 mod CONV_F_3
 */
qconv_uint16_mod_f_3 qconv_inverse_uint16_mod_f_3(qconv_uint16_mod a);

/*
 * @brief Normalization of an 1D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_1D_size_norm_uint16_mod_f_3(const size_t size, qconv_uint16_mod a[static size]);

/*
 * @brief Normalization of an 2D array based on its length, to be performed at the end of INTT
 */
void qconv_INTT_2D_size_norm_uint16_mod_f_3(const size_t size_width,
                                            const size_t size_height,
                                            qconv_uint16_mod a[static size_width * size_height]);

/*
 * @brief NTT 1D circular convolution of length up to 256, mod F_3
 */
enum qconv_status qconv_NTT_1D_circular_convolution_uint16_mod_f_3(const size_t size,
                                                                   qconv_uint16_mod a[static size],
                                                                   qconv_uint16_mod b[static size],
                                                                   qconv_uint16_mod ntt[size],
                                                                   const enum qconv_optimize_transform optimize_level);

/*
 * @brief NTT 1D linear convolution of output length up to 256, mod F_3
 */
enum qconv_status qconv_NTT_1D_linear_convolution_uint16_mod_f_3(const size_t input_size,
                                                                 const size_t kernel_size,
                                                                 qconv_uint16_mod input[static input_size],
                                                                 qconv_uint16_mod kernel[static kernel_size],
                                                                 qconv_uint16_mod ntt[input_size + kernel_size - 1],
                                                                 const enum qconv_optimize_transform optimize_level);

void qconv_DIT_std2std_2D_uint16_mod_f_3(const size_t size_width,
                                         const size_t size_height,
                                         const size_t log2_size_width,
                                         const size_t log2_size_height,
                                         qconv_uint16_mod a[static size_width * size_height],
                                         qconv_uint16_mod row_p_root,
                                         qconv_uint16_mod column_p_root,
                                         const size_t row_p_root_size,
                                         const size_t column_p_root_size,
                                         const bool inverse);

void qconv_DIT_std2std_forward_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers);

void qconv_DIT_std2std_inverse_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers);

enum qconv_status qconv_NTT_2D_uint16_mod_f_3(const size_t size_width,
                                              const size_t size_height,
                                              qconv_uint16_mod a[static size_width * size_height],
                                              const enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_INTT_2D_uint16_mod_f_3(const size_t size_width,
                                               const size_t size_height,
                                               qconv_uint16_mod a[static size_width * size_height],
                                               const enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_circular_convolution_uint16_mod_f_3(const size_t size_width,
                                                                   const size_t size_height,
                                                                   qconv_uint16_mod a[static size_width * size_height],
                                                                   qconv_uint16_mod b[static size_width * size_height],
                                                                   qconv_uint16_mod ntt[size_width * size_height],
                                                                   const enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_linear_convolution_uint16_mod_f_3(const size_t input_size_width,
                                                                 const size_t input_size_height,
                                                                 const size_t kernel_size_width,
                                                                 const size_t kernel_size_height,
                                                                 qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                 qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                 qconv_uint16_mod ntt[(input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)],
                                                                 const enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_block_linear_convolution_uint16_mod_f_3(size_t input_size_width,
                                                                       size_t input_size_height,
                                                                       size_t kernel_size_width,
                                                                       size_t kernel_size_height,
                                                                       size_t block_size_width,
                                                                       size_t block_size_height,
                                                                       qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                       qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                       qconv_uint16_mod output[static (input_size_width + kernel_size_width - 1)
                                                                                                      * (input_size_height + kernel_size_height - 1)]);

void qconv_block_convolution_uint16_mod_f_3_top_left_pad(size_t input_size_width, size_t input_size_height,
                                                         size_t block_size_width, size_t block_size_height, size_t block_size,
                                                         size_t log2_block_size_width, size_t log2_block_size_height,
                                                         size_t output_size_width, size_t output_size_height,
                                                         size_t input_offset_width, size_t input_offset_height,
                                                         size_t output_offset_width, size_t output_offset_height,
                                                         size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                         size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                         qconv_uint16_mod_f_3 norm_const,
                                                         qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                         qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                         const qconv_uint16_mod *input,
                                                         const qconv_uint16_mod *kernel_block,
                                                         qconv_uint16_mod *output,
                                                         enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_top_pad(size_t input_size_width, size_t input_size_height,
                                                    size_t block_size_width, size_t block_size_height, size_t block_size,
                                                    size_t log2_block_size_width, size_t log2_block_size_height,
                                                    size_t output_size_width, size_t output_size_height,
                                                    size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                    size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                    size_t input_offset_width, size_t input_offset_height,
                                                    size_t output_offset_width, size_t output_offset_height,
                                                    qconv_uint16_mod_f_3 norm_const,
                                                    qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                    qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                    const qconv_uint16_mod *input, const qconv_uint16_mod *kernel_block,
                                                    qconv_uint16_mod *output,
                                                    enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_top_right_pad(size_t input_size_width, size_t input_size_height,
                                                          size_t block_size_width, size_t block_size_height, size_t block_size,
                                                          size_t log2_block_size_width, size_t log2_block_size_height,
                                                          size_t output_size_width, size_t output_size_height,
                                                          size_t input_offset_width, size_t input_offset_height,
                                                          size_t output_offset_width, size_t output_offset_height,
                                                          size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                          size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                          qconv_uint16_mod_f_3 norm_const,
                                                          qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                          qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                          const qconv_uint16_mod *input,
                                                          const qconv_uint16_mod *kernel_block,
                                                          qconv_uint16_mod *output,
                                                          enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_left_pad(size_t input_size_width, size_t input_size_height,
                                                     size_t block_size_width, size_t block_size_height, size_t block_size,
                                                     size_t log2_block_size_width, size_t log2_block_size_height,
                                                     size_t output_size_width, size_t output_size_height,
                                                     size_t input_offset_width, size_t input_offset_height,
                                                     size_t output_offset_width, size_t output_offset_height,
                                                     size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                     size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                     qconv_uint16_mod_f_3 norm_const,
                                                     qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                     qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                     const qconv_uint16_mod *input,
                                                     const qconv_uint16_mod *kernel_block,
                                                     qconv_uint16_mod *output,
                                                     enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_bottom_right_pad(size_t input_size_width, size_t input_size_height,
                                                             size_t block_size_width, size_t block_size_height, size_t block_size,
                                                             size_t log2_block_size_width, size_t log2_block_size_height,
                                                             size_t output_size_width, size_t output_size_height,
                                                             size_t input_offset_width, size_t input_offset_height,
                                                             size_t output_offset_width, size_t output_offset_height,
                                                             size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                             size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                             size_t valid_input_subblock_size_height, size_t valid_output_subblock_size_height,
                                                             qconv_uint16_mod_f_3 norm_const,
                                                             qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                             qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                             const qconv_uint16_mod *input,
                                                             const qconv_uint16_mod *kernel_block,
                                                             qconv_uint16_mod *output,
                                                             enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_bottom_pad(size_t input_size_width, size_t input_size_height,
                                                       size_t block_size_width, size_t block_size_height, size_t block_size,
                                                       size_t log2_block_size_width, size_t log2_block_size_height,
                                                       size_t output_size_width, size_t output_size_height,
                                                       size_t input_offset_width, size_t input_offset_height,
                                                       size_t output_offset_width, size_t output_offset_height,
                                                       size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                       size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                       size_t valid_input_subblock_size_height, size_t valid_output_subblock_size_height,
                                                       qconv_uint16_mod_f_3 norm_const,
                                                       qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                       qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                       const qconv_uint16_mod *input,
                                                       const qconv_uint16_mod *kernel_block,
                                                       qconv_uint16_mod *output,
                                                       enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_bottom_left_pad(size_t input_size_width, size_t input_size_height,
                                                            size_t block_size_width, size_t block_size_height, size_t block_size,
                                                            size_t log2_block_size_width, size_t log2_block_size_height,
                                                            size_t output_size_width, size_t output_size_height,
                                                            size_t input_offset_width, size_t input_offset_height,
                                                            size_t output_offset_width, size_t output_offset_height,
                                                            size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                            size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                            size_t valid_input_subblock_size_height, size_t valid_output_subblock_size_height,
                                                            qconv_uint16_mod_f_3 norm_const,
                                                            qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                            qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                            const qconv_uint16_mod *input,
                                                            const qconv_uint16_mod *kernel_block,
                                                            qconv_uint16_mod *output,
                                                            enum qconv_optimize_transform optimize_level);

void qconv_block_convolution_uint16_mod_f_3_right_pad(size_t input_size_width, size_t input_size_height,
                                                      size_t block_size_width, size_t block_size_height, size_t block_size,
                                                      size_t log2_block_size_width, size_t log2_block_size_height,
                                                      size_t output_size_width, size_t output_size_height,
                                                      size_t input_offset_width, size_t input_offset_height,
                                                      size_t output_offset_width, size_t output_offset_height,
                                                      size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                      size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                      qconv_uint16_mod_f_3 norm_const,
                                                      qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                      qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                      const qconv_uint16_mod *input,
                                                      const qconv_uint16_mod *kernel_block,
                                                      qconv_uint16_mod *output,
                                                      enum qconv_optimize_transform optimize_level) ;

void qconv_block_convolution_uint16_mod_f_3_no_pad(size_t input_size_width, size_t input_size_height,
                                                   size_t block_size_width, size_t block_size_height, size_t block_size,
                                                   size_t log2_block_size_width, size_t log2_block_size_height,
                                                   size_t output_size_width, size_t output_size_height,
                                                   size_t input_offset_width, size_t input_offset_height,
                                                   size_t output_offset_width, size_t output_offset_height,
                                                   size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                   size_t valid_subblock_size_width, size_t valid_subblock_size_height,
                                                   qconv_uint16_mod_f_3 norm_const,
                                                   qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                   qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                   const qconv_uint16_mod *input,
                                                   const qconv_uint16_mod *kernel_block,
                                                   qconv_uint16_mod *output,
                                                   enum qconv_optimize_transform optimize_level) ;

void qconv_block_convolution_uint16_mod_f_3_output_subblock(size_t block_size_width, size_t block_size_height, size_t block_size,
                                                            size_t log2_block_size_width, size_t log2_block_size_height,
                                                            size_t output_size_width, size_t output_size_height,
                                                            size_t output_offset_width, size_t output_offset_height,
                                                            size_t discard_subblock_size_width, size_t discard_subblock_size_height,
                                                            size_t valid_output_subblock_size_width, size_t valid_output_subblock_size_height,
                                                            qconv_uint16_mod_f_3 norm_const,
                                                            qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                            qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                            qconv_uint16_mod *block,
                                                            const qconv_uint16_mod *kernel_block,
                                                            qconv_uint16_mod *output,
                                                            enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_block_CNN_convolution_uint16_mod_f_3(size_t input_size_width,
                                                                    size_t input_size_height,
                                                                    size_t kernel_size_width,
                                                                    size_t kernel_size_height,
                                                                    size_t block_size_width,
                                                                    size_t block_size_height,
                                                                    qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                    qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                    qconv_uint16_mod output[static (input_size_width - kernel_size_width + 1)
                                                                                                   * (input_size_height - kernel_size_height + 1)]);

