//
// Created by alessandro on 3/4/17.
//
#include "qconv_uint8_m_8.h"

extern inline qconv_uint8_mod_m_8 qconv_reduce_uint16_mod_m_8(qconv_uint16 x);

//Declare the useful constants as const structs as well
const qconv_uint8_mod qconv_const_m_8 = {.mod_m_8.value = QCONV_M_8};

qconv_uint8_mod_m_8 qconv_power_uint8_mod_m_8(qconv_uint8_mod_m_8 base, unsigned int exp) {
        qconv_uint8_mod_m_8 res = {.value = (qconv_inner_uint8) 1};
        while(exp > 0) {
            if (exp % 2 == 1) {
                res = qconv_mul_uint8_mod_m_8(res, base);
            }
            base = qconv_mul_uint8_mod_m_8(base, base);
            exp /= 2;
        }
        return res;
}

