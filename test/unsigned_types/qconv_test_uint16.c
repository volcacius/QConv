//
// Created by alessandro on 3/7/17.
//

#include <time.h>

#include "qconv_test_uint16.h"

const size_t qconv_test_convolution_uint16_sizes[QCONV_CONV_SIZES] = {
        QCONV_LEN_8,
        QCONV_LEN_16,
        QCONV_LEN_32,
        QCONV_LEN_64,
        QCONV_LEN_128,
        QCONV_LEN_256,
        QCONV_LEN_512,
        QCONV_LEN_1024,
        QCONV_LEN_2048
};

void qconv_test_lin_circ_convolution_uint16(size_t input_bit_size,
                                            size_t kernel_bit_size,
                                            size_t input_size,
                                            size_t kernel_size) {
    size_t size;
    if (input_size > kernel_size) {
        size = input_size * 2;
    } else {
        size = kernel_size * 2;
    }
    qconv_uint16_mod input[input_size];
    qconv_uint16_mod kernel[kernel_size];
    qconv_uint16_mod lin[input_size + kernel_size - 1];
    qconv_uint16_mod sliced_circ[input_size + kernel_size - 1];

    qconv_uint16_mod padded_input[size];
    qconv_uint16_mod padded_kernel[size];
    qconv_uint16_mod circ[size];

    qconv_test_util_random_uint16_1D_array(input_size, input, input_bit_size);
    qconv_test_util_random_uint16_1D_array(kernel_size, kernel, kernel_bit_size);
    qconv_uint16_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, lin);

    qconv_zero_pad_uint16_1D_array(size, input_size, input, padded_input);
    qconv_zero_pad_uint16_1D_array(size, kernel_size, kernel, padded_kernel);
    qconv_uint16_direct_1D_circular_convolution(size, padded_input, padded_kernel, circ);
    qconv_slice_uint16_1D_array(size, input_size + kernel_size - 1, 0, circ, sliced_circ);

    qconv_test_util_compare_uint16_1D_array(input_size + kernel_size - 1, lin, sliced_circ);
}

void qconv_test_convolution_uint16_runall() {
    for (size_t iter = 0; iter < 1; iter++) {
        for (size_t i = 0; i < QCONV_CONV_SIZES; i++) {
            for (size_t k = 0; k < QCONV_CONV_SIZES; k++) {
                for (size_t input_bit_size = 2; input_bit_size < QCONV_MAX_UINT16_BITSIZE; input_bit_size++) {
                    for (size_t kernel_bit_size = 2; kernel_bit_size < QCONV_MAX_UINT16_BITSIZE; kernel_bit_size++) {
                        qconv_test_lin_circ_convolution_uint16(input_bit_size,
                                                               kernel_bit_size,
                                                               qconv_test_convolution_uint16_sizes[i],
                                                               qconv_test_convolution_uint16_sizes[k]);
                    }
                }
            }
        }
    }
}

void qconv_test_uint16_runall() {
    qconv_test_convolution_uint16_runall();
}

