//
// Created by alessandro on 3/7/17.
//

#pragma once

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "qconv_uint16.h"
#include "qconv_uint16_mod_f_8.h"
#include "qconv_uint16_mod_m_13.h"
#include "qconv_test_utils_uint16.h"

void qconv_test_mul_mod_f_8();

void qconv_test_power_mod_f_8();

void qconv_test_mul_mod_f_8_union();

void qconv_test_NTT_1D_identity_mod_f_8(size_t size, size_t bit_size);

void qconv_test_NTT_1D_identity_mod_f_8_runall();

void qconv_test_NTT_1D_circular_convolution_mod_f_8(size_t size,
                                                    size_t input_bit_size,
                                                    size_t kernel_bit_size);

void qconv_test_NTT_1D_circular_convolution_mod_f_8_runall();

void qconv_test_NTT_1D_linear_convolution_mod_f_8(size_t input_size,
                                                  size_t kernel_size,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size);

void qconv_test_NTT_1D_linear_convolution_mod_f_8_runall();

void qconv_test_NTT_2D_identity_mod_f_8_runall();

void qconv_test_uint16_mod_f_8_runall();

