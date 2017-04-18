//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint32_mod qconv_const_f_4 = {.mod_f_4.value = QCONV_F_4};
const qconv_uint32_mod qconv_const_p_root_f_4_size_32 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_32};
const qconv_uint32_mod qconv_const_p_root_f_4_size_65536 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_65536};


const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_8_forward[] =
        {0, 8, 0, 8, 0, 4, 8, 12};

//16, which is later processed as if it were -16, is replaced by 1 and manually checked against, since shifting by 16 would overflow
const qconv_inner_int16 qconv_const_f_4_DIT_r2_std2std_size_8_inverse[] =
        {16, 8, 16, 8, 16, 12, 8, 4};

const qconv_inner_uint16 qconv_const_f_4_DIF_r2_std2rev_size_8_forward[] =
        {0, 4, 8, 12, 0, 8, 0, 8};

const qconv_inner_int16 *qconv_const_f_4_DIT_r2_rev2std_size_8_inverse =
        qconv_const_f_4_DIT_r2_std2std_size_8_inverse;

const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_16_forward[] =
        {0, 8, 0, 8, 0, 8, 0, 8, 0, 4, 8, 12, 0, 4, 8, 12, 0, 2, 4, 6, 8, 10, 12, 14};

const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_32_forward[] = 
        {0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8,
         0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 12,
         0, 2, 4, 6, 8, 10, 12,  14, 0, 2, 4, 6, 8, 10, 12, 14,
         0, 1, 2, 8, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  14, 15};

const qconv_inner_int16 qconv_const_f_4_DIT_r2_std2std_size_16_inverse[] =
        {16, 8, 16, 8, 16, 8, 16, 8, 16, 12, 8, 4, 16, 12, 8, 4, 16, 14, 12, 10, 8, 6, 4, 2};

const qconv_inner_uint16 qconv_const_f_4_DIF_r2_std2rev_size_16_forward[] =
        {0, 2, 4, 6, 8, 10, 12, 14, 0, 4, 8, 12, 0, 4, 8, 12, 0, 8, 0, 8, 0, 8, 0, 8};

const qconv_inner_int16 *qconv_const_f_4_DIT_r2_rev2std_size_16_inverse =
        qconv_const_f_4_DIT_r2_std2std_size_16_inverse;

const qconv_inner_uint16 qconv_const_f_4_DIF_r2_std2rev_size_32_forward[] =
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 2, 4, 6, 8, 10, 12,
         14, 0, 2, 4, 6, 8, 10, 12, 14, 0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 12, 0, 4, 8, 
         12, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8};

const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_32_inverse[] =
        {16, 8, 16, 8, 16, 8, 16, 8, 16, 8, 16, 8, 16, 8, 16, 8,
         16, 12, 8, 4, 16, 12, 8, 4, 16, 12, 8, 4, 16, 12, 8, 4,
         16, 14, 12, 10, 8, 6, 4, 2, 16, 14, 12, 10, 8, 6, 4, 2,
         16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

const qconv_inner_uint16 *qconv_const_f_4_DIT_r2_rev2std_size_32_inverse =
        qconv_const_f_4_DIT_r2_std2std_size_32_inverse;

qconv_inner_uint16 *qconv_get_const_f_4_DIF_std2rev_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIF_r2_std2rev_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIF_r2_std2rev_size_16_forward;
        case QCONV_SIZE_32:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIF_r2_std2rev_size_32_forward;
    }
}

qconv_inner_uint16 *qconv_get_const_f_4_DIT_std2std_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_16_forward;
        case QCONV_SIZE_32:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_32_forward;
    }
}

qconv_inner_int16 *qconv_get_const_f_4_DIT_std2std_inverse_signed(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_std2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_std2std_size_16_inverse;
    }
}

qconv_inner_uint16 *qconv_get_const_f_4_DIT_std2std_inverse_unsigned(size_t size) {
    switch(size) {
        case QCONV_SIZE_32:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_32_inverse;
    }
}

qconv_inner_int16 *qconv_get_const_f_4_DIT_rev2std_inverse_signed(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_rev2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_rev2std_size_16_inverse;
    }
}

qconv_inner_uint16 *qconv_get_const_f_4_DIT_rev2std_inverse_unsigned(size_t size) {
    switch(size) {
        case QCONV_SIZE_32:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_rev2std_size_32_inverse;
    }
}
