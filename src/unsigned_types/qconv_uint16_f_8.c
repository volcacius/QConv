//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_f_8.h"

extern inline qconv_uint16_mod_f_8 qconv_reduce_uint32_mod_f_8(qconv_uint32 x);

extern inline qconv_uint16_mod_f_8 qconv_mul_uint16_mod_f_8(const qconv_uint16_mod_f_8 x, const qconv_uint16_mod_f_8 y);

//Declare the useful constants as const structs as well
const qconv_uint16_mod qconv_const_f_8 = {.mod_f_8.value = QCONV_F_8};

qconv_uint16_mod_f_8 qconv_power_uint16_mod_f_8(qconv_uint16_mod_f_8 base, unsigned int exp) {
    qconv_uint16_mod_f_8 res = {.value = (qconv_inner_uint16) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_uint16_mod_f_8(res, base);
        }
        base = qconv_mul_uint16_mod_f_8(base, base);
        exp /= 2;
    }
    return res;
}