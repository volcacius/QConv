//
// Created by alessandro on 3/4/17.
//
#include "qconv_int16.h"

extern inline qconv_mod_m_8 qconv_reduce_mod_m_8(qconv_mod_m_8 x);

//Declare the useful constants as const structs as well
const qconv_int16_mod qconv_const_m_8 = {.mod_m_8.value = QCONV_M_8};

enum qconv_status qconv_int16_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_int16 input[static const input_size],
        const qconv_int16 kernel[static const kernel_size],
        qconv_int16 output[static input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (int o = 0; o < output_size; o++) {
        output[o].value = 0;
        for (int i = 0; i < input_size; i++) {
            int k = o - i;
            if (k >= 0 && k < kernel_size) {
                output[o].value += input[i].value * kernel[k].value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_int16_direct_1D_circular_convolution (
        const size_t size,
        const qconv_int16 input[static const size],
        const qconv_int16 kernel[static const size],
        qconv_int16 output[static size]) {
    for (int o = 0; o < size; o++) {
        output[o].value = 0;
        for (int i = 0; i < size; i++) {
            int k = o - i;
            while (k < 0 || k >= size) {
                k += size;
            }
            output[o].value += input[i].value * kernel[k].value;
        }
    }
    return status_success;
}




qconv_mod_m_8 qconv_power_mod_m_8(qconv_mod_m_8 base, int exp) {
        qconv_mod_m_8 res = {.value = (qconv_inner_int16) 1};
        while(exp > 0) {
            if (exp % 2 == 1) {
                res = qconv_mul_mod_m_8(res, base);
            }
            base = qconv_mul_mod_m_8(base, base);
            exp /= 2;
        }
        return res;
}

