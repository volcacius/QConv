//
// Created by alessandro on 3/7/17.
//

#pragma once

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "qconv_uint32.h"
#include "qconv_uint32_mod_f_4.h"
#include "qconv_test_utils_uint32.h"
#include "qconv_test_constants.h"

enum qconv_status qconv_test_mul_mod_f_4();

enum qconv_status qconv_test_power_mod_f_4();

enum qconv_status qconv_test_mul_mod_f_4_union();

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4(size_t size, size_t bit_size);

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4_runall();

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4(size_t size,
                                                    size_t input_bit_size,
                                                    size_t kernel_bit_size);

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4_runall();

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4(size_t input_size,
                                                  size_t kernel_size,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size);

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4_runall();

enum qconv_status qconv_test_NTT_2D_identity_mod_f_4_runall();

void qconv_test_uint32_mod_f_4_runall();

