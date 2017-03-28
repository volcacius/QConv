//
// Created by alessandro on 3/4/17.
//
#include "qconv_uint8.h"

enum qconv_status qconv_uint8_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_uint8_mod input[static const input_size],
        const qconv_uint8_mod kernel[static const kernel_size],
        qconv_uint8_mod output[static input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (int o = 0; o < output_size; o++) {
        output[o].uint8.value = 0;
        for (int i = 0; i < input_size; i++) {
            int k = o - i;
            if (k >= 0 && k < kernel_size) {
                output[o].uint8.value += input[i].uint8.value * kernel[k].uint8.value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_uint8_direct_1D_circular_convolution (
        const size_t size,
        const qconv_uint8_mod input[static const size],
        const qconv_uint8_mod kernel[static const size],
        qconv_uint8_mod output[static size]) {
    for (int o = 0; o < size; o++) {
        output[o].uint8.value = 0;
        for (int i = 0; i < size; i++) {
            int k = o - i;
            while (k < 0) {
                k += size;
            }
            output[o].uint8.value += input[i].uint8.value * kernel[k].uint8.value;
        }
    }
    return status_success;
}