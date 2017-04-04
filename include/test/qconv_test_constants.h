//
// Created by alessandro on 3/25/17.
//

#pragma once

#include "qconv_constants.h"

#define TEST_ITERATIONS 100

extern const size_t qconv_test_sizes[];
extern const size_t qconv_kernel_test_sizes[];

//As a design rule, we are interested only in input and kernels with 8 bits max
#define QCONV_MAX_BITSIZE 8

//Constants for identities, i.e. INTT(NTT(x)) = x
#define QCONV_MAX_F_3_NTT_IDENTITY_BITSIZE 4
#define QCONV_MAX_F_4_NTT_IDENTITY_BITSIZE 8
#define QCONV_F_3_1D_IDENTITY_SIZES 6
#define QCONV_F_3_2D_IDENTITY_SIZES 2
#define QCONV_F_4_1D_IDENTITY_SIZES 9
#define QCONV_F_4_2D_IDENTITY_SIZES 2

//Constants for convolution tests
#define QCONV_CRT_F_3_F_4_1D_CONV_SIZES 6
#define QCONV_CRT_F_3_F_4_2D_CONV_SIZES 2

