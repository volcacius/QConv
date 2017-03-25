//
// Created by Alessandro on 02/03/2017.
//

#pragma once

#include <stdint.h>
#include <stddef.h>

#include "qconv.h"

#define QCONV_MAX_UINT16_BITSIZE 8

//Typedef a 16bit unsigned data type to a project wide inner unsigned 16bit representation
typedef uint16_t qconv_inner_uint16;

//Wrap the inner unsigned 16bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_uint16 qconv_uint16;
struct qconv_uint16 {
    qconv_inner_uint16 value;
};

//Define all the uint16 structs in the same header to avoid circular dependencies
typedef struct qconv_uint16_mod_f_3 qconv_uint16_mod_f_3;
struct qconv_uint16_mod_f_3 {
    qconv_inner_uint16 value;
};

typedef struct qconv_uint16_mod_m_13 qconv_uint16_mod_m_13;
struct qconv_uint16_mod_m_13 {
    qconv_inner_uint16 value;
};

//Overlay the various unsigned 16bit struct representation since they share the same inner unsigned 16bit representation
typedef union qconv_uint16_mod qconv_uint16_mod;
union qconv_uint16_mod {
    qconv_uint16_mod_f_3 mod_f_3;
    qconv_uint16_mod_m_13 mod_m_13;
    qconv_uint16 uint16;
};

enum qconv_status qconv_uint16_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_uint16_mod input[static const input_size],
        const qconv_uint16_mod kernel[static const kernel_size],
        qconv_uint16_mod output[static input_size + kernel_size - 1]);

enum qconv_status qconv_uint16_direct_1D_circular_convolution (
        const size_t size,
        const qconv_uint16_mod input[static const size],
        const qconv_uint16_mod kernel[static const size],
        qconv_uint16_mod output[static size]);

/*
 * @brief Scramble array
 */
void qconv_bit_reverse_uint16_array_order(const size_t size, qconv_uint16_mod a[static size]);

/*
 * @brief GCD
 */
qconv_uint16 qconv_uint16_gcd(qconv_uint16 a, qconv_uint16 b);

/*
 * @brief Zero pad input array of size inner_size to output array of size outer_size
 */
enum qconv_status qconv_zero_pad_uint16_1D_array(const size_t outer_size,
                                                 const size_t inner_size,
                                                 const qconv_uint16_mod input[static const inner_size],
                                                 qconv_uint16_mod output[static outer_size]);

/*
 * @brief Zero pad input array of size inner_size_width * inner_size_height to output array of size outer_size_width * outer_size_height
 */
enum qconv_status qconv_zero_pad_uint16_2D_array(const size_t outer_size_width,
                                                 const size_t outer_size_height,
                                                 const size_t inner_size_width,
                                                 const size_t inner_size_height,
                                                 const qconv_uint16_mod input[static const inner_size_width * inner_size_height],
                                                 qconv_uint16_mod output[static outer_size_width * outer_size_height]);

/*
 * @brief Slice input array of size outer_size to output_array of size inner_size,
 * starting from index starting_index of the input array
 */
enum qconv_status qconv_slice_uint16_1D_array(const size_t outer_size,
                                              const size_t inner_size,
                                              const size_t starting_index,
                                              const qconv_uint16_mod input[static const outer_size],
                                              qconv_uint16_mod output[static inner_size]);

enum qconv_status qconv_slice_uint16_2D_array(const size_t outer_size_width,
                                              const size_t outer_size_height,
                                              const size_t inner_size_width,
                                              const size_t inner_size_height,
                                              const size_t starting_row_index,
                                              const size_t starting_column_index,
                                              const qconv_uint16_mod input[static const outer_size_width * outer_size_height],
                                              qconv_uint16_mod output[static inner_size_width * inner_size_height]);

enum qconv_status qconv_transpose_uint16_2D(size_t size_width,
                                            size_t size_height,
                                            qconv_uint16_mod input[static size_width * size_height],
                                            qconv_uint16_mod output[static size_height * size_width]);

enum qconv_status qconv_uint16_direct_2D_circular_convolution (const size_t size_width,
                                                               const size_t size_height,
                                                               const qconv_uint16_mod input[static const size_width * size_height],
                                                               const qconv_uint16_mod kernel[static const size_width * size_height],
                                                               qconv_uint16_mod output[static size_width * size_height]);

enum qconv_status qconv_uint16_direct_2D_linear_convolution (const size_t input_size_width,
                                                             const size_t input_size_height,
                                                             const size_t kernel_size_width,
                                                             const size_t kernel_size_height,
                                                             const qconv_uint16_mod input[static const input_size_width * input_size_height],
                                                             const qconv_uint16_mod kernel[static const kernel_size_width * kernel_size_height],
                                                             qconv_uint16_mod output[static (input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)]);