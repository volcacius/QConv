//
// Created by alessandro on 3/3/17.
//
#include "qconv_int32.h"

enum qconv_status qconv_int32_direct_1D_linear_convolution (const size_t input_size,
                                                            const size_t kernel_size,
                                                            const qconv_int32_mod input[static input_size],
                                                            const qconv_int32_mod kernel[static kernel_size],
                                                            qconv_int32_mod output[input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (size_t o = 0; o < output_size; o++) {
        output[o].int32.value = 0;
        for (size_t i = 0; i < input_size; i++) {
            int k = (int) (o - i);
            if (k >= 0 && k < kernel_size) {
                output[o].int32.value += input[i].int32.value * kernel[k].int32.value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_int32_direct_1D_circular_convolution (const size_t size,
                                                              const qconv_int32_mod input[static const size],
                                                              const qconv_int32_mod kernel[static const size],
                                                              qconv_int32_mod output[static size]) {
    for (size_t o = 0; o < size; o++) {
        output[o].int32.value = 0;
        for (size_t i = 0; i < size; i++) {
            int k = (int) (o - i);
            while (k < 0 || k >= size) {
                k += size;
            }
            output[o].int32.value += input[i].int32.value * kernel[k].int32.value;
        }
    }
    return status_success;
}

enum qconv_status qconv_int32_direct_2D_circular_convolution (size_t size_x,
                                                              size_t size_y,
                                                              const qconv_int32_mod input[static const size_x][size_y],
                                                              const qconv_int32_mod kernel[static const size_x][size_y],
                                                              qconv_int32_mod output[static size_x][size_y]) {
    for (size_t o_x = 0; o_x < size_x; o_x++) {
        for (size_t o_y = 0; o_y < size_y; o_y++) {
            output[o_x][o_y].int32.value = 0;
            for (int i_x = 0; i_x < size_x; i_x++) {
                for (size_t i_y = 0; i_y < size_y; i_y++) {
                    int k_x = (int) (o_x - i_x);
                    int k_y = (int) (o_y - i_y);
                    while (k_x < 0 || k_x >= size_x) {
                        k_x += size_x;
                    }
                    while (k_y < 0 || k_y >= size_y) {
                        k_y += size_y;
                    }
                    if (k_x >= 0 && k_y >= 0 && k_x < size_x && k_y < size_y) {
                        output[o_x][o_y].int32.value += input[i_x][i_y].int32.value * kernel[i_x][i_y].int32.value;
                    }
                }
            }
        }
    }

    return status_success;
}

enum qconv_status qconv_int32_direct_2D_linear_convolution (
        size_t input_size_x,
        size_t input_size_y,
        size_t kernel_size_x,
        size_t kernel_size_y,
        const qconv_int32_mod input[static const input_size_x][input_size_y],
        const qconv_int32_mod kernel[static const kernel_size_x][kernel_size_y],
        qconv_int32_mod output[static input_size_x + kernel_size_x - 1][input_size_y + kernel_size_y - 1]) {

    size_t output_size_x = input_size_x + kernel_size_x - 1;
    size_t output_size_y = input_size_y + kernel_size_y - 1;

    for (size_t o_x = 0; o_x < output_size_x; o_x++) {
        for (size_t o_y = 0; o_y < output_size_y; o_y++) {
            output[o_x][o_y].int32.value = 0;
            for (int i_x = 0; i_x < input_size_x; i_x++) {
                for (size_t i_y = 0; i_y < input_size_y; i_y++) {
                    int k_x = (int) (o_x - i_x);
                    int k_y = (int) (o_y - i_y);
                    if (k_x >= 0 && k_y >= 0 && k_x < kernel_size_x && k_y < kernel_size_y) {
                        output[o_x][o_y].int32.value += input[i_x][i_y].int32.value * kernel[i_x][i_y].int32.value;
                    }
                }
            }
        }
    }
    return status_success;
}


