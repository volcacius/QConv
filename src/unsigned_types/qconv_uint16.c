//
// Created by alessandro on 3/4/17.
//
#include "qconv_uint16.h"

enum qconv_status qconv_uint16_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_uint16_mod input[static const input_size],
        const qconv_uint16_mod kernel[static const kernel_size],
        qconv_uint16_mod output[input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (int o = 0; o < output_size; o++) {
        output[o].uint16.value = 0;
        for (int i = 0; i < input_size; i++) {
            int k = o - i;
            if (k >= 0 && k < kernel_size) {
                output[o].uint16.value += input[i].uint16.value * kernel[k].uint16.value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_uint16_direct_1D_circular_convolution (
        const size_t size,
        const qconv_uint16_mod input[static const size],
        const qconv_uint16_mod kernel[static const size],
        qconv_uint16_mod output[static size]) {
    for (int o = 0; o < size; o++) {
        output[o].uint16.value = 0;
        for (int i = 0; i < size; i++) {
            int k = o - i;
            while (k < 0 || k >= size) {
                k += size;
            }
            output[o].uint16.value += input[i].uint16.value * kernel[k].uint16.value;
        }
    }
    return status_success;
}

void qconv_bit_reverse_uint16_array_order(const size_t size, qconv_uint16_mod a[static size]) {
    size_t target = 0;
    size_t position = 0;
    for (position = 0; position < size; position++) {
        if (target > position) {
            //Swap the content
            qconv_uint16 temp = a[target].uint16;
            a[target].uint16.value = a[position].uint16.value;
            a[position].uint16 = temp;
        }
        size_t mask = size;
        while (target & (mask >>= 1)) {
            target &= ~mask;
        }
        target |= mask;
    }
}

qconv_uint16 qconv_uint16_gcd(qconv_uint16 a, qconv_uint16 b) {
    if (a.value == 0) {
        return b;
    }
    qconv_uint16 c = {.value = b.value % a.value};
    return qconv_uint16_gcd(c, a);
}

enum qconv_status qconv_zero_pad_uint16_1D_array(size_t outer_size,
                                                 size_t inner_size,
                                                 qconv_uint16_mod input[static inner_size],
                                                 qconv_uint16_mod output[static outer_size]) {
    if (inner_size > outer_size) {
        return status_invalid_padding_size;
    }
    for (size_t i = 0; i < outer_size; i++) {
        if (i < inner_size) {
            output[i].uint16.value = input[i].uint16.value;
        } else {
            output[i].uint16.value = 0;
        }
    }
    return status_success;
}

enum qconv_status qconv_slice_uint16_1D_array(size_t outer_size,
                                              size_t inner_size,
                                              size_t starting_index,
                                              qconv_uint16_mod input[static outer_size],
                                              qconv_uint16_mod output[static inner_size]) {
    if (inner_size + starting_index > outer_size) {
        return status_invalid_slicing_size;
    }
    for (size_t i = starting_index; i < inner_size + starting_index; i++) {
        output[i].uint16.value = input[i].uint16.value;
    }
    return status_success;
}