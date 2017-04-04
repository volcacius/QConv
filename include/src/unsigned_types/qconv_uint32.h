//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "qconv_constants.h"

#define QCONV_MAX_UINT32_CONV_BITSIZE 16

//Typedef a 32bit unsigned data type to a project wide inner 32bit representation
typedef uint32_t qconv_inner_uint32;

//Wrap the inner unsigned 32bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_uint32 qconv_uint32;
struct qconv_uint32 {
    qconv_inner_uint32 value;
};

//Define all the uint32 structs in the same header to avoid circular dependencies
typedef struct qconv_uint32_mod_f_4 qconv_uint32_mod_f_4;
struct qconv_uint32_mod_f_4 {
    qconv_inner_uint32 value;
};

//Overlay the various 32bit struct representation since they share the same inner 32bit representation
typedef union qconv_uint32_mod qconv_uint32_mod;
union qconv_uint32_mod {
    qconv_uint32_mod_f_4 mod_f_4;
    qconv_uint32 uint32;
};

enum qconv_status qconv_uint32_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_uint32_mod input[static const kernel_size],
        const qconv_uint32_mod kernel[static const input_size],
        qconv_uint32_mod output[static input_size + kernel_size - 1]);

enum qconv_status qconv_uint32_direct_1D_circular_convolution (
        const size_t size,
        const qconv_uint32_mod input[static const size],
        const qconv_uint32_mod kernel[static const size],
        qconv_uint32_mod output[static size]);

/*
 * @brief Scramble array
 */
void qconv_bit_reverse_uint32_array_order(const size_t size, qconv_uint32_mod a[static size]);

/*
 * @brief GCD
 */
qconv_uint32 qconv_uint32_gcd(qconv_uint32 a, qconv_uint32 b);

/*
 * @brief Right zero input array of size inner_size to output array of size outer_size
 */
enum qconv_status qconv_right_zero_pad_uint32_1D_array(const size_t outer_size,
                                                       const size_t inner_size,
                                                       const qconv_uint32_mod input[inner_size],
                                                       qconv_uint32_mod output[outer_size]);

/*
 * @brief Left zero input array of size inner_size to output array of size outer_size
 */
enum qconv_status qconv_left_zero_pad_uint32_1D_array(const size_t outer_size,
                                                      const size_t inner_size,
                                                      const qconv_uint32_mod input[inner_size],
                                                      qconv_uint32_mod output[outer_size]);

/*
 * @brief Zero pad input array of size inner_size_width * inner_size_height to output array of size outer_size_width * outer_size_height
 */
enum qconv_status qconv_bottom_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                             const size_t outer_size_height,
                                                             const size_t inner_size_width,
                                                             const size_t inner_size_height,
                                                             const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                             qconv_uint32_mod output[static outer_size_width * outer_size_height]);

enum qconv_status qconv_bottom_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                              const size_t outer_size_height,
                                                              const size_t inner_size_width,
                                                              const size_t inner_size_height,
                                                              const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                              qconv_uint32_mod output[static outer_size_width * outer_size_height]);

enum qconv_status qconv_top_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                          const size_t outer_size_height,
                                                          const size_t inner_size_width,
                                                          const size_t inner_size_height,
                                                          const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                          qconv_uint32_mod output[static outer_size_width * outer_size_height]);

enum qconv_status qconv_top_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                           const size_t outer_size_height,
                                                           const size_t inner_size_width,
                                                           const size_t inner_size_height,
                                                           const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                           qconv_uint32_mod output[static outer_size_width * outer_size_height]);

enum qconv_status qconv_top_zero_pad_uint32_2D_array(const size_t size_width,
                                                     const size_t outer_size_height,
                                                     const size_t inner_size_height,
                                                     const qconv_uint32_mod input[static const size_width * inner_size_height],
                                                     qconv_uint32_mod output[static size_width * outer_size_height]);

enum qconv_status qconv_bottom_zero_pad_uint32_2D_array(const size_t size_width,
                                                        const size_t outer_size_height,
                                                        const size_t inner_size_height,
                                                        const qconv_uint32_mod input[static const size_width * inner_size_height],
                                                        qconv_uint32_mod output[static size_width * outer_size_height]);

enum qconv_status qconv_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                      const size_t size_height,
                                                      const size_t inner_size_width,
                                                      const qconv_uint32_mod input[static const inner_size_width * size_height],
                                                      qconv_uint32_mod output[static inner_size_width * size_height]);

enum qconv_status qconv_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                       const size_t size_height,
                                                       const size_t inner_size_width,
                                                       const qconv_uint32_mod input[static const inner_size_width * size_height],
                                                       qconv_uint32_mod output[static inner_size_width * size_height]);

enum qconv_status qconv_reverse_uint32_array(const size_t size,
                                             qconv_uint32_mod a[static size]);

/*
 * @brief Slice input array of size outer_size to output_array of size inner_size,
 * starting from index starting_index of the input array
 */
enum qconv_status qconv_slice_uint32_1D_array(const size_t outer_size,
                                              const size_t inner_size,
                                              const size_t starting_index,
                                              const qconv_uint32_mod input[static const outer_size],
                                              qconv_uint32_mod output[static inner_size]);

enum qconv_status qconv_slice_uint32_2D_array(const size_t outer_size_width,
                                              const size_t outer_size_height,
                                              const size_t inner_size_width,
                                              const size_t inner_size_height,
                                              const size_t starting_row_index,
                                              const size_t starting_column_index,
                                              const qconv_uint32_mod input[static const outer_size_width * outer_size_height],
                                              qconv_uint32_mod output[static inner_size_width * inner_size_height]);

enum qconv_status qconv_insert_uint32_2D_array(const size_t outer_size_width,
                                               const size_t outer_size_height,
                                               const size_t inner_size_width,
                                               const size_t inner_size_height,
                                               const size_t top_left_width_offset,
                                               const size_t top_left_height_offset,
                                               const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                               qconv_uint32_mod output[static outer_size_width * outer_size_height]);

enum qconv_status qconv_transpose_uint32_2D(size_t size_width,
                                            size_t size_height,
                                            qconv_uint32_mod input[static size_width * size_height],
                                            qconv_uint32_mod output[static size_height * size_width]);

enum qconv_status qconv_uint32_direct_2D_circular_convolution (const size_t size_width,
                                                               const size_t size_height,
                                                               const qconv_uint32_mod input[static const size_width * size_height],
                                                               const qconv_uint32_mod kernel[static const size_width * size_height],
                                                               qconv_uint32_mod output[static size_width * size_height]);

enum qconv_status qconv_uint32_direct_2D_linear_convolution (const size_t input_size_width,
                                                             const size_t input_size_height,
                                                             const size_t kernel_size_width,
                                                             const size_t kernel_size_height,
                                                             const qconv_uint32_mod input[static const input_size_width * input_size_height],
                                                             const qconv_uint32_mod kernel[static const kernel_size_width * kernel_size_height],
                                                             qconv_uint32_mod output[static (input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)]);

enum qconv_status qconv_uint32_direct_2D_cnn_convolution(const size_t input_size_width,
                                                         const size_t input_size_height,
                                                         const size_t kernel_size_width,
                                                         const size_t kernel_size_height,
                                                         const qconv_uint32_mod input[static const input_size_width * input_size_height],
                                                         const qconv_uint32_mod kernel[static const kernel_size_width * kernel_size_height],
                                                         qconv_uint32_mod output[static (input_size_width - kernel_size_width + 1) * (input_size_height - kernel_size_height + 1)]);

void qconv_clone_uint32_2D_array(const size_t size_width,
                                 const size_t size_height,
                                 const qconv_uint32_mod source[static const size_width * size_height],
                                 qconv_uint32_mod destination[static size_width * size_height]);

void qconv_clone_uint32_array(const size_t size,
                              const qconv_uint32_mod source[static const size],
                              qconv_uint32_mod destination[static size]);