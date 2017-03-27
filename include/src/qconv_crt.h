//
// Created by alessandro on 3/27/17.
//

#pragma once

#include <stddef.h>

#include "qconv_uint16.h"
#include "qconv_uint16_mod_f_3.h"
#include "qconv_uint32_mod_f_4.h"

enum qconv_status qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size_t size,
                                                                    qconv_uint32_mod input[size],
                                                                    qconv_uint32_mod kernel[size],
                                                                    qconv_uint32_mod output[size],
                                                                    enum qconv_optimize_transform optimize_level);
