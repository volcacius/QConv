//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "qconv.h"

//Typedef a 32bit unsigned data type to a project wide inner 32bit representation
typedef uint32_t qconv_inner_uint32;

//Wrap the inner unsigned 32bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_uint32 qconv_uint32;
struct qconv_uint32 {
    qconv_inner_uint32 value;
};

//Overlay the various 32bit struct representation since they share the same inner 32bit representation
typedef union qconv_uint32_mod qconv_uint32_mod;
union qconv_uint32_mod {
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

enum qconv_status qconv_uint32_direct_2D_linear_convolution (
        size_t input_size_x,
        size_t input_size_y,
        size_t kernel_size_x,
        size_t kernel_size_y,
        const qconv_uint32_mod input[static const input_size_x][input_size_y],
        const qconv_uint32_mod kernel[static const kernel_size_x][kernel_size_y],
        qconv_uint32_mod output[static input_size_x + kernel_size_x - 1][input_size_y + kernel_size_y - 1]);

enum qconv_status qconv_uint32_direct_2D_circular_convolution (
        size_t size_x,
        size_t size_y,
        const qconv_uint32_mod input[static const size_x][size_y],
        const qconv_uint32_mod kernel[static const size_x][size_y],
        qconv_uint32_mod output[static size_x][size_y]);
