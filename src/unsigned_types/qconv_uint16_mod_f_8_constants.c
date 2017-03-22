//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_mod_f_8_constants.h"

const size_t qconv_test_NTT_circular_convolution_uint16_mod_f_8_sizes[] = {
        QCONV_LEN_8,
        QCONV_LEN_16,
        QCONV_LEN_32,
        QCONV_LEN_64,
        QCONV_LEN_128,
        QCONV_LEN_256
};

//Declare the useful constants as const structs as well
const qconv_uint16_mod qconv_const_f_8 = {.mod_f_8.value = QCONV_F_8};
const qconv_uint16_mod qconv_const_p_root_f_8_len_up_to_16 = {.mod_f_8.value = QCONV_P_ROOT_F_8_LEN_UP_TO_16};
const qconv_uint16_mod qconv_const_p_root_f_8_len_up_to_256 = {.mod_f_8.value = QCONV_P_ROOT_F_8_LEN_UP_TO_256};



