//
// Created by alessandro on 3/7/17.
//

#pragma once


#include <assert.h>
#include <stdio.h>

#include "qconv_uint16.h"
#include "qconv_uint16_mod_f_8.h"
#include "qconv_uint16_mod_m_13.h"
#include "qconv_test_utils_uint16.h"

const size_t qconv_test_convolution_uint16_sizes[QCONV_CONV_SIZES];

void qconv_test_lin_circ_convolution_uint16(size_t input_size,
                                            size_t kernel_size,
                                            size_t input_bit_size,
                                            size_t kernel_bit_size);

void qconv_test_convolution_uint16_runall();

void qconv_test_uint16_runall();

