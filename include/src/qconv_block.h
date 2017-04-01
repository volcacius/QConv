//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stdint.h>

#include "qconv_uint32_mod_f_4.h"

enum qconv_status qconv_NTT_1D_block_cnn_convolution_uint32_mod_f_4(size_t input_size,
                                                                    size_t kernel_size,
                                                                    size_t block_size,
                                                                    qconv_uint32_mod input[input_size],
                                                                    qconv_uint32_mod kernel[kernel_size],
                                                                    qconv_uint32_mod output[input_size + kernel_size - 1],
                                                                    enum qconv_optimize_transform optimize_level);