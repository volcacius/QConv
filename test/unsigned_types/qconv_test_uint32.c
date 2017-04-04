//
// Created by alessandro on 3/7/17.
//

#include <time.h>

#include "qconv_test_uint32.h"

void qconv_test_lin_circ_convolution_uint32(size_t input_bit_size,
                                            size_t kernel_bit_size,
                                            size_t input_size,
                                            size_t kernel_size) {
    size_t size;
    if (input_size > kernel_size) {
        size = input_size * 2;
    } else {
        size = kernel_size * 2;
    }
    qconv_uint32_mod input[input_size];
    qconv_uint32_mod kernel[kernel_size];
    qconv_uint32_mod lin[input_size + kernel_size - 1];
    qconv_uint32_mod sliced_circ[input_size + kernel_size - 1];

    qconv_uint32_mod padded_input[size];
    qconv_uint32_mod padded_kernel[size];
    qconv_uint32_mod circ[size];

    qconv_test_util_random_uint32_1D_array(input_size, input, input_bit_size);
    qconv_test_util_random_uint32_1D_array(kernel_size, kernel, kernel_bit_size);
    qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, lin);

    qconv_right_zero_pad_uint32_1D_array(size, input_size, input, padded_input);
    qconv_right_zero_pad_uint32_1D_array(size, kernel_size, kernel, padded_kernel);
    qconv_uint32_direct_1D_circular_convolution(size, padded_input, padded_kernel, circ);
    qconv_slice_uint32_1D_array(size, input_size + kernel_size - 1, 0, circ, sliced_circ);

    assert(qconv_test_util_compare_uint32_1D_array(input_size + kernel_size - 1, lin, sliced_circ));
}

void qconv_test_convolution_uint32_runall() {
    for (size_t i = 0; i < QCONV_CONV_SIZES; i++) {
        for (size_t k = 0; k < QCONV_CONV_SIZES; k++) {
            for (size_t input_bit_size = 2; input_bit_size < QCONV_MAX_UINT32_CONV_BITSIZE; input_bit_size++) {
                for (size_t kernel_bit_size = 2; kernel_bit_size < QCONV_MAX_UINT32_CONV_BITSIZE; kernel_bit_size++) {
                    qconv_test_lin_circ_convolution_uint32(input_bit_size,
                                                           kernel_bit_size,
                                                           qconv_test_sizes[i],
                                                           qconv_test_sizes[k]);
                }
            }
        }
    }
}

void qconv_test_zero_pad_uint32_1D_array() {
    size_t inner_size = 4;
    size_t outer_size = 9;
    qconv_uint32_mod input[] = {{.uint32.value = 0},
                                {.uint32.value = 1},
                                {.uint32.value = 2},
                                {.uint32.value = 3}};
    qconv_uint32_mod test[] = {{.uint32.value = 0},
                               {.uint32.value = 1},
                               {.uint32.value = 2},
                               {.uint32.value = 3},
                               {.uint32.value = 0},
                               {.uint32.value = 0},
                               {.uint32.value = 0},
                               {.uint32.value = 0},
                               {.uint32.value = 0}};
    qconv_uint32_mod output[outer_size];
    qconv_right_zero_pad_uint32_1D_array(outer_size, inner_size, input, output);
    assert(qconv_test_util_compare_uint32_1D_array(outer_size, test, output));
}

void qconv_test_zero_pad_uint32_2D_array() {
    size_t inner_size_width = 2;
    size_t inner_size_height = 2;
    size_t outer_size_width = 3;
    size_t outer_size_height = 3;
    qconv_uint32_mod input[] = {{.uint32.value = 0}, {.uint32.value = 1},
                                {.uint32.value = 2}, {.uint32.value = 3}};
    qconv_uint32_mod test[] = {{.uint32.value = 0}, {.uint32.value = 1}, {.uint32.value = 0},
                               {.uint32.value = 2}, {.uint32.value = 3}, {.uint32.value = 0},
                               {.uint32.value = 0}, {.uint32.value = 0}, {.uint32.value = 0}};
    qconv_uint32_mod output[outer_size_width * outer_size_height];
    qconv_bottom_right_zero_pad_uint32_2D_array(outer_size_width, outer_size_height, inner_size_width, inner_size_height, input, output);
    assert(qconv_test_util_compare_uint32_2D_array(outer_size_width, outer_size_height, test, output));
}

void qconv_test_slice_uint32_1D_array() {
    size_t inner_size = 4;
    size_t outer_size = 9;
    qconv_uint32_mod input[] = {{.uint32.value = 0},
                                {.uint32.value = 1},
                                {.uint32.value = 2},
                                {.uint32.value = 3},
                                {.uint32.value = 0},
                                {.uint32.value = 0},
                                {.uint32.value = 0},
                                {.uint32.value = 0},
                                {.uint32.value = 0}};
    qconv_uint32_mod test[] = {{.uint32.value = 0},
                               {.uint32.value = 1},
                               {.uint32.value = 2},
                               {.uint32.value = 3}};
    qconv_uint32_mod output[inner_size];
    qconv_slice_uint32_1D_array(outer_size, inner_size, 0, input, output);
    assert(qconv_test_util_compare_uint32_1D_array(inner_size, test, output));
}

void qconv_test_slice_uint32_2D_array() {
    size_t inner_size_width = 2;
    size_t inner_size_height = 2;
    size_t outer_size_width = 3;
    size_t outer_size_height = 3;
    qconv_uint32_mod input[] = {{.uint32.value = 0}, {.uint32.value = 1}, {.uint32.value = 0},
                                {.uint32.value = 2}, {.uint32.value = 3}, {.uint32.value = 0},
                                {.uint32.value = 0}, {.uint32.value = 0}, {.uint32.value = 0}};
    qconv_uint32_mod test[] = {{.uint32.value = 0}, {.uint32.value = 1},
                               {.uint32.value = 2}, {.uint32.value = 3}};
    qconv_uint32_mod output[inner_size_width * inner_size_height];
    qconv_slice_uint32_2D_array(outer_size_width, outer_size_height, inner_size_width, inner_size_height, 0, 0, input, output);
    assert(qconv_test_util_compare_uint32_2D_array(inner_size_width, inner_size_height, test, output));
}

void qconv_test_direct_2D_cnn_convolution_uint32() {
    size_t input_size_width = 3;
    size_t input_size_height = 3;
    size_t kernel_size_width = 2;
    size_t kernel_size_height = 2;
    qconv_uint32_mod input[] = {{.uint32.value = 0}, {.uint32.value = 1}, {.uint32.value = 6},
                                {.uint32.value = 2}, {.uint32.value = 3}, {.uint32.value = 7},
                                {.uint32.value = 4}, {.uint32.value = 5}, {.uint32.value = 8}};
    qconv_uint32_mod kernel[] = {{.uint32.value = 0}, {.uint32.value = 1},
                                 {.uint32.value = 2}, {.uint32.value = 3}};
    qconv_uint32_mod output[] = {{.uint32.value = 0 * 0 + 1 * 1 + 2 * 2 + 3 * 3}, {.uint32.value = 0 * 1 + 6 * 1 + 3 * 2 + 7 * 3},
                                 {.uint32.value = 2 * 0 + 3 * 1 + 4 * 2 + 5 * 3}, {.uint32.value = 3 * 0 + 7 * 1 + 5 * 2 + 8 * 3}};
    qconv_uint32_mod test[4];
    qconv_uint32_direct_2D_cnn_convolution(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, test);
    assert(qconv_test_util_compare_uint32_2D_array(2, 2, test, output));
}

void qconv_test_uint32_runall() {
    qconv_test_zero_pad_uint32_1D_array();
    qconv_test_zero_pad_uint32_2D_array();
    qconv_test_slice_uint32_1D_array();
    qconv_test_slice_uint32_2D_array();
    qconv_test_convolution_uint32_runall();
    qconv_test_direct_2D_cnn_convolution_uint32();
}

