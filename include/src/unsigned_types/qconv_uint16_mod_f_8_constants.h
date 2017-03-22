//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"

#define QCONV_EXP_F_8 8
#define QCONV_MAX_F_8_NTT_IDENTITY_BITSIZE 4
#define QCONV_F_8_CONV_SIZES 6

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_8 257
#define QCONV_P_ROOT_F_8_LEN_UP_TO_16 3
#define QCONV_P_ROOT_F_8_LEN_UP_TO_256 3

extern const size_t qconv_test_NTT_1D_circular_convolution_uint16_mod_f_8_sizes[QCONV_F_8_CONV_SIZES];

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_f_8;
extern const qconv_uint16_mod qconv_const_p_root_f_8_len_up_to_16;
extern const qconv_uint16_mod qconv_const_p_root_f_8_len_up_to_256;