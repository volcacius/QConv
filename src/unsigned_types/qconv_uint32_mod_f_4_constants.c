//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint32_mod qconv_const_f_4 = {.mod_f_4.value = QCONV_F_4};
const qconv_uint32_mod qconv_const_p_root_f_4_size_32 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_32};
const qconv_uint32_mod qconv_const_p_root_f_4_size_65536 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_65536};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward[5] = {[0].value = 65281,
        [1].value = 65281,
        [2].value = 4096,
        [3].value = 65281,
        [4].value = 16};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse[5] = {[0].value = 256,
        [1].value = 256,
        [2].value = 65521,
        [3].value = 256,
        [4].value = 61441};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward[17] = {[0].value = 65281,
        [1].value = 65281,
        [2].value = 65281,
        [3].value = 65281,
        [4].value = 4096,
        [5].value = 4096,
        [6].value = 65281,
        [7].value = 65281,
        [8].value = 16,
        [9].value = 16,
        [10].value = 64,
        [11].value = 4096,
        [12].value = 65533,
        [13].value = 65281,
        [14].value = 49153,
        [15].value = 16,
        [16].value = 1024};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse[17] = {[0].value = 256,
        [1].value = 256,
        [2].value = 256,
        [3].value = 256,
        [4].value = 65521,
        [5].value = 65521,
        [6].value = 256,
        [7].value = 256,
        [8].value = 61441,
        [9].value = 61441,
        [10].value = 64513,
        [11].value = 65521,
        [12].value = 16384,
        [13].value = 256,
        [14].value = 4,
        [15].value = 61441,
        [16].value = 65473};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_forward[] = {};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_inverse[] = {};