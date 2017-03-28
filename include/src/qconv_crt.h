//
// Created by alessandro on 3/27/17.
//

#pragma once

#include <stddef.h>

#include "qconv_uint16.h"
#include "qconv_uint16_mod_f_3.h"
#include "qconv_uint32_mod_f_4.h"

#define QCONV_MAX_CRT_F_3_F_4_NTT_2D_SIZE_8X8_INPUT_BITSIZE 8
#define QCONV_MAX_CRT_F_3_F_4_NTT_2D_SIZE_8X8_KERNEL_BITSIZE 8
#define QCONV_MAX_CRT_F_3_F_4_NTT_2D_SIZE_16X16_INPUT_BITSIZE 8
#define QCONV_MAX_CRT_F_3_F_4_NTT_2D_SIZE_16X16_KERNEL_BITSIZE 8

enum qconv_status qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size_t size,
                                                                    qconv_uint32_mod input[size],
                                                                    qconv_uint32_mod kernel[size],
                                                                    qconv_uint32_mod output[size],
                                                                    enum qconv_optimize_transform optimize_level);

enum qconv_status qconv_NTT_2D_circular_convolution_mod_crt_f_3_f_4(size_t size_width,
                                                                    size_t size_height,
                                                                    qconv_uint32_mod input[size_width * size_height],
                                                                    qconv_uint32_mod kernel[size_width * size_height],
                                                                    qconv_uint32_mod output[size_width * size_height],
                                                                    enum qconv_optimize_transform optimize_level);
