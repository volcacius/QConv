//
// Created by alessandro on 3/27/17.
//

#pragma once

#include <assert.h>
#include <time.h>

#include "qconv_crt.h"
#include "qconv_test_utils_uint32.h"
#include "qconv_uint32.h"

void qconv_test_NTT_1D_convolution_mod_crt_f_3_f_4(size_t size, size_t bit_size, enum qconv_optimize_transform optimize_level);