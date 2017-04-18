//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_mod_f_3_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint16_mod qconv_const_f_3 = {.mod_f_3.value = QCONV_F_3};
const qconv_uint16_mod qconv_const_p_root_f_3_size_16 = {.mod_f_3.value = QCONV_P_ROOT_F_3_SIZE_16};
const qconv_uint16_mod qconv_const_p_root_f_3_size_256 = {.mod_f_3.value = QCONV_P_ROOT_F_3_SIZE_256};

const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_8_forward[] =
        {0, 4, 0, 4, 0, 2, 4, 6};

const qconv_inner_uint8 qconv_const_f_3_DIF_r2_std2rev_size_8_forward[] =
        {0, 2, 4, 6, 0, 4, 0, 4};

const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_16_forward[] =
        {0, 4, 0, 4, 0, 4, 0, 4, 0, 2, 4, 6, 0, 2, 4, 6, 0, 1, 2, 3, 4, 5, 6, 7};

const qconv_inner_uint8 qconv_const_f_3_DIF_r2_std2rev_size_16_forward[] =
        {0, 1, 2, 3, 4, 5, 6, 7, 0, 2, 4, 6, 0, 2, 4, 6, 0, 4, 0, 4, 0, 4, 0, 4};

const qconv_inner_uint8 *qconv_const_f_3_DIT_r2_rev2std_size_16_inverse =
        qconv_const_f_3_DIT_r2_std2std_size_16_inverse;

const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_8_inverse[] =
        {8, 4, 8, 4, 8, 6, 4, 2};

const qconv_inner_uint8 *qconv_const_f_3_DIT_r2_rev2std_size_8_inverse =
        qconv_const_f_3_DIT_r2_std2std_size_8_inverse;

const qconv_inner_uint8 qconv_const_f_3_DIT_r2_std2std_size_16_inverse[] =
        {8, 4, 8, 4, 8, 4, 8, 4, 8, 6, 4, 2, 8, 6, 4, 2, 8, 7, 6, 5, 4, 3, 2, 1};

qconv_inner_uint8 *qconv_get_const_f_3_DIF_std2rev_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIF_r2_std2rev_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIF_r2_std2rev_size_16_forward;
    }
}

qconv_inner_uint8 *qconv_get_const_f_3_DIT_std2std_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_std2std_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_std2std_size_16_forward;
    }
}

qconv_inner_uint8 *qconv_get_const_f_3_DIT_std2std_inverse(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_std2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_std2std_size_16_inverse;
    }
}

qconv_inner_uint8 *qconv_get_const_f_3_DIT_rev2std_inverse(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_rev2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_uint8 *) qconv_const_f_3_DIT_r2_rev2std_size_16_inverse;
    }
}
