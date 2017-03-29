//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_mod_f_3_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint16_mod qconv_const_f_3 = {.mod_f_3.value = QCONV_F_3};
const qconv_uint16_mod qconv_const_p_root_f_3_size_16 = {.mod_f_3.value = QCONV_P_ROOT_F_3_SIZE_16};
const qconv_uint16_mod qconv_const_p_root_f_3_size_256 = {.mod_f_3.value = QCONV_P_ROOT_F_3_SIZE_256};

const qconv_inner_uint8 qconv_const_uint8_mod_f_3_CT_precomp_size_8_forward[] =
        {1, 16, 1, 16, 1, 4, 16, 64};

const qconv_inner_uint8 qconv_const_uint8_mod_f_3_CT_precomp_size_8_inverse[] =
        {1, 241, 1, 241, 1, 193, 241, 253};

const qconv_inner_uint8 qconv_const_uint8_mod_f_3_CT_precomp_size_16_forward[] =
        {1, 16, 1, 16, 1, 16, 1, 16, 1, 4, 16, 64, 1, 4, 16, 64, 1, 2, 4, 8, 16, 32, 64, 128};

const qconv_inner_uint8 qconv_const_uint8_mod_f_3_CT_precomp_size_16_inverse[] =
        {1, 241, 1, 241, 1, 241, 1, 241, 1, 193, 241, 253, 1, 193, 241, 253, 1, 129, 193, 225, 241, 249, 253, 255};