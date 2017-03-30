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

#define QCONV_EXP_F_3 8

//Access the following values through the const variables so that their representation is consisted with the global inner one
#define QCONV_F_3 257
#define QCONV_P_ROOT_F_3_SIZE_16 2
#define QCONV_P_ROOT_F_3_SIZE_256 3

//Declare the useful constants as const structs
//Global structs must be declared extern in header and put in source
extern const qconv_uint16_mod qconv_const_f_3;
extern const qconv_uint16_mod qconv_const_p_root_f_3_size_16;
extern const qconv_uint16_mod qconv_const_p_root_f_3_size_256;

extern const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_8_forward[];
extern const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_8_inverse[];

extern const qconv_inner_uint8 qconv_const_f_3_DIF_r2_std2rev_size_8_forward[];
extern const qconv_inner_uint8 *qconv_const_f_3_DIT_r2_rev2std_size_8_inverse;

extern const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_16_forward[];
extern const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_16_inverse[];

extern const qconv_inner_uint8 qconv_const_f_3_DIF_r2_std2rev_size_16_forward[];
extern const qconv_inner_uint8 *qconv_const_f_3_DIT_r2_rev2std_size_16_inverse;

qconv_inner_uint8 *qconv_get_const_f_3_DIF_std2rev_forward(size_t size);

qconv_inner_uint8 *qconv_get_const_f_3_DIT_std2std_forward(size_t size);

qconv_inner_uint8 *qconv_get_const_f_3_DIT_std2std_inverse(size_t size);

qconv_inner_uint8 *qconv_get_const_f_3_DIT_rev2std_inverse(size_t size);