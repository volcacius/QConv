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
typedef struct qconv_uint16_mod_f_8 qconv_uint16_mod_f_8;
struct qconv_uint16_mod_f_8 {
    qconv_inner_uint16 value;
};

typedef struct qconv_uint16_mod_m_13 qconv_uint16_mod_m_13;
struct qconv_uint16_mod_m_13 {
    qconv_inner_uint16 value;
};

//Overlay the various unsigned 16bit struct representation since they share the same inner unsigned 16bit representation
typedef union qconv_uint16_mod qconv_uint16_mod;
union qconv_uint16_mod {
    qconv_uint16_mod_f_8 mod_f_8;
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

qconv_uint16 qconv_uint16_gcd(qconv_uint16 a, qconv_uint16 b);

/*
 * @brief Zero pad input array of size inner_size to output array of size outer_size
 */
enum qconv_status qconv_zero_pad_uint16_1D_array(size_t outer_size,
                                                 size_t inner_size,
                                                 qconv_uint16_mod input[static inner_size],
                                                 qconv_uint16_mod output[static outer_size]);

/*
 * @brief Slice input array of size outer_size to output_array of size inner_size,
 * starting from index starting_index of the input array
 */
enum qconv_status qconv_slice_uint16_1D_array(size_t outer_size,
                                              size_t inner_size,
                                              size_t starting_index,
                                              qconv_uint16_mod input[static outer_size],
                                              qconv_uint16_mod output[static inner_size]);
