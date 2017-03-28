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

#define QCONV_EXP_F_4 8

#define QCONV_MAX_F_4_NTT_2D_SIZE_8X8_INPUT_BITSIZE 5
#define QCONV_MAX_F_4_NTT_2D_SIZE_8X8_KERNEL_BITSIZE 5
#define QCONV_MAX_F_4_NTT_2D_SIZE_16X16_INPUT_BITSIZE 4
#define QCONV_MAX_F_4_NTT_2D_SIZE_16X16_KERNEL_BITSIZE 4

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_4 65537
#define QCONV_P_ROOT_F_4_SIZE_32 2
#define QCONV_P_ROOT_F_4_SIZE_65536 3

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint32_mod qconv_const_f_4;
extern const qconv_uint32_mod qconv_const_p_root_f_4_size_32;
extern const qconv_uint32_mod qconv_const_p_root_f_4_size_65536;

extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward[];
extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse[];
extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward[];
extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse[];
extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_forward[];
extern const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_inverse[];