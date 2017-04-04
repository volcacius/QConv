//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint32_mod qconv_const_f_4 = {.mod_f_4.value = QCONV_F_4};
const qconv_uint32_mod qconv_const_p_root_f_4_size_32 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_32};
const qconv_uint32_mod qconv_const_p_root_f_4_size_65536 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_65536};


const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_8_forward[] =
        {1, 256, 1, 256, 1, 16, 256, 4096};

//1 = -65536 is kept as 1 to ease the reudction step after multiplication
const qconv_inner_int16 qconv_const_f_4_DIT_r2_std2std_size_8_inverse[] =
        {1, -256, 1, -256, 1, -4096, -256, -16};

const qconv_inner_uint16 qconv_const_f_4_DIF_r2_std2rev_size_8_forward[] =
        {1, 16, 256, 4096, 1, 256, 1, 256};

const qconv_inner_int16 *qconv_const_f_4_DIT_r2_rev2std_size_8_inverse =
        qconv_const_f_4_DIT_r2_std2std_size_8_inverse;

const qconv_inner_uint16 qconv_const_f_4_DIT_r2_std2std_size_16_forward[] =
        {1, 256, 1, 256, 1, 256, 1, 256, 1, 16, 256, 4096, 1, 16, 256, 4096, 1, 4, 16, 64, 256, 1024, 4096, 16384};

//1 = -65536 is kept as 1 to ease the reudction step after multiplication
const qconv_inner_int16 qconv_const_f_4_DIT_r2_std2std_size_16_inverse[] =
        {1, -256, 1, -256, 1, -256, 1, -256, 1, -4096, -256, -16, 1, -4096, -256, -16, 1, -16384, -4096, -1024, -256, -64, -16, -4};

const qconv_inner_uint16 qconv_const_f_4_DIF_r2_std2rev_size_16_forward[] =
        {1, 4, 16, 64, 256, 1024, 4096, 16384, 1, 16, 256, 4096, 1, 16, 256, 4096, 1, 256, 1, 256, 1, 256, 1, 256};

const qconv_inner_int16 *qconv_const_f_4_DIT_r2_rev2std_size_16_inverse =
        qconv_const_f_4_DIT_r2_std2std_size_16_inverse;

qconv_inner_uint16 *qconv_get_const_f_4_DIF_std2rev_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIF_r2_std2rev_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIF_r2_std2rev_size_16_forward;
    }
}

qconv_inner_uint16 *qconv_get_const_f_4_DIT_std2std_forward(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_8_forward;
        case QCONV_SIZE_16:
            return (qconv_inner_uint16 *) qconv_const_f_4_DIT_r2_std2std_size_16_forward;
    }
}

qconv_inner_int16 *qconv_get_const_f_4_DIT_std2std_inverse(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_std2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_std2std_size_16_inverse;
    }
}

qconv_inner_int16 *qconv_get_const_f_4_DIT_rev2std_inverse(size_t size) {
    switch(size) {
        case QCONV_SIZE_8:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_rev2std_size_8_inverse;
        case QCONV_SIZE_16:
            return (qconv_inner_int16 *) qconv_const_f_4_DIT_r2_rev2std_size_16_inverse;
    }
}
