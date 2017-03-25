//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "qconv.h"
#include "qconv_uint8.h"
#include "qconv_uint16.h"
#include "qconv_uint32.h"

#define QCONV_EXP_F_8 8
#define QCONV_MAX_F_8_NTT_IDENTITY_BITSIZE 4
#define QCONV_F_8_1D_CONV_SIZES 6
#define QCONV_F_8_2D_CONV_SIZES 2

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_8 257
#define QCONV_P_ROOT_F_8_LEN_UP_TO_16 3
#define QCONV_P_ROOT_F_8_LEN_UP_TO_256 3

extern const size_t qconv_test_NTT_circular_convolution_uint16_mod_f_3_sizes[];

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_f_3;
extern const qconv_uint16_mod qconv_const_p_root_f_3_len_up_to_16;
extern const qconv_uint16_mod qconv_const_p_root_f_3_len_up_to_256;

extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_8_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_8_inverse[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_16_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_16_inverse[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_32_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_32_inverse[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_64_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_64_inverse[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_128_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_128_inverse[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_256_forward[];
extern const qconv_uint8 qconv_const_uint16_mod_f_3_CT_precomp_size_256_inverse[];