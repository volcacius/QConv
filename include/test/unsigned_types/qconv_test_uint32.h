//
// Created by alessandro on 3/7/17.
//

#pragma once


#include <assert.h>
#include <stdio.h>

#include "qconv_uint32.h"
#include "qconv_uint32_mod_f_4.h"
#include "qconv_test_utils_uint32.h"
#include "qconv_test_constants.h"

void qconv_test_lin_circ_convolution_uint32(size_t input_size,
                                            size_t kernel_size,
                                            size_t input_bit_size,
                                            size_t kernel_bit_size);

void qconv_test_convolution_uint32_runall();

void qconv_test_uint32_runall();

