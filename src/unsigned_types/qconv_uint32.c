//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32.h"

enum qconv_status qconv_uint32_direct_1D_linear_convolution (const size_t input_size,
                                                            const size_t kernel_size,
                                                            const qconv_uint32_mod input[static input_size],
                                                            const qconv_uint32_mod kernel[static kernel_size],
                                                            qconv_uint32_mod output[input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (size_t o = 0; o < output_size; o++) {
        output[o].uint32.value = 0;
        for (size_t i = 0; i < input_size; i++) {
            int k = (int) (o - i);
            if (k >= 0 && k < kernel_size) {
                output[o].uint32.value += input[i].uint32.value * kernel[k].uint32.value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_uint32_direct_1D_circular_convolution (const size_t size,
                                                              const qconv_uint32_mod input[static const size],
                                                              const qconv_uint32_mod kernel[static const size],
                                                              qconv_uint32_mod output[static size]) {
    for (size_t o = 0; o < size; o++) {
        output[o].uint32.value = 0;
        for (size_t i = 0; i < size; i++) {
            int k = (int) (o - i);
            while (k < 0) {
                k += size;
            }
            output[o].uint32.value += input[i].uint32.value * kernel[k].uint32.value;
        }
    }
    return status_success;
}

void qconv_bit_reverse_uint32_array_order(const size_t size, qconv_uint32_mod a[static size]) {
    size_t target = 0;
    size_t position = 0;
    for (position = 0; position < size; position++) {
        if (target > position) {
            //Swap the content
            qconv_uint32 temp = a[target].uint32;
            a[target].uint32.value = a[position].uint32.value;
            a[position].uint32 = temp;
        }
        size_t mask = size;
        while (target & (mask >>= 1)) {
            target &= ~mask;
        }
        target |= mask;
    }
}

qconv_uint32 qconv_uint32_gcd(qconv_uint32 a, qconv_uint32 b) {
    if (a.value == 0) {
        return b;
    }
    qconv_uint32 c = {.value = b.value % a.value};
    return qconv_uint32_gcd(c, a);
}

enum qconv_status qconv_zero_pad_uint32_1D_array(const size_t outer_size,
                                                 const size_t inner_size,
                                                 const qconv_uint32_mod input[static const inner_size],
                                                 qconv_uint32_mod output[static outer_size]) {
    if (inner_size > outer_size) {
        return status_invalid_padding_size;
    }
    for (size_t i = 0; i < outer_size; i++) {
        if (i < inner_size) {
            output[i].uint32.value = input[i].uint32.value;
        } else {
            output[i].uint32.value = 0;
        }
    }
    return status_success;
}

enum qconv_status qconv_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                 const size_t outer_size_height,
                                                 const size_t inner_size_width,
                                                 const size_t inner_size_height,
                                                 const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                 qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    if (inner_size_height > outer_size_height || inner_size_width > outer_size_width) {
        return status_invalid_padding_size;
    }
    for (size_t row = 0; row < outer_size_height; row++) {
        if (row < inner_size_height) {
            qconv_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width], &output[row * outer_size_width]);
        } else {
            for (size_t i = 0; i < outer_size_width; i++) {
                output[row * outer_size_width + i].uint32.value = 0;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_slice_uint32_1D_array(const size_t outer_size,
                                              const size_t inner_size,
                                              const size_t starting_index,
                                              const qconv_uint32_mod input[static const outer_size],
                                              qconv_uint32_mod output[static inner_size]) {
    if (inner_size + starting_index > outer_size) {
        return status_invalid_slicing_size;
    }
    for (size_t i = 0; i < inner_size; i++) {
        output[i].uint32.value = input[i + starting_index].uint32.value;
    }
    return status_success;
}

enum qconv_status qconv_slice_uint32_2D_array(const size_t outer_size_width,
                                              const size_t outer_size_height,
                                              const size_t inner_size_width,
                                              const size_t inner_size_height,
                                              const size_t starting_row_index,
                                              const size_t starting_column_index,
                                              const qconv_uint32_mod input[static const outer_size_width * outer_size_height],
                                              qconv_uint32_mod output[static inner_size_width * inner_size_height]) {
    for (size_t row = 0; row < inner_size_height; row++) {
        if (inner_size_width + starting_column_index > outer_size_width
            || inner_size_height + starting_row_index > outer_size_height) {
            return status_invalid_slicing_size;
        }
        for (size_t column = 0; column < inner_size_width; column++) {
            output[row * inner_size_width + column] = input[(row + starting_row_index) * outer_size_width + (starting_column_index + column)];
        }
    }
    return status_success;
}

enum qconv_status qconv_transpose_uint32_2D(size_t size_width,
                                            size_t size_height,
                                            qconv_uint32_mod input[static size_width * size_height],
                                            qconv_uint32_mod output[static size_height * size_width]) {
    for (size_t a_transpose_row = 0; a_transpose_row < size_width; a_transpose_row++) {
        for (size_t a_transpose_column = 0; a_transpose_column < size_height; a_transpose_column++) {
            output[a_transpose_row * size_height + a_transpose_column].uint32.value = input[a_transpose_column * size_width + a_transpose_row].uint32.value;
        }
    }
    return status_success;
}

enum qconv_status qconv_uint32_direct_2D_linear_convolution (const size_t input_size_width,
                                                             const size_t input_size_height,
                                                             const size_t kernel_size_width,
                                                             const size_t kernel_size_height,
                                                             const qconv_uint32_mod input[static const input_size_width * input_size_height],
                                                             const qconv_uint32_mod kernel[static const kernel_size_width * kernel_size_height],
                                                             qconv_uint32_mod output[static (input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)]) {

    size_t output_size_width = input_size_width + kernel_size_width - 1;
    size_t output_size_height = input_size_height + kernel_size_height - 1;

    for (size_t o_row = 0; o_row < output_size_height; o_row++) {
        for (size_t o_column = 0; o_column < output_size_width; o_column++) {
            output[o_row * output_size_width + o_column].uint32.value = 0;
            for (int i_row = 0; i_row < input_size_height; i_row++) {
                for (size_t i_column = 0; i_column < input_size_width; i_column++) {
                    int k_row = o_row - i_row;
                    int k_column = o_column - i_column;
                    if (k_row >= 0 && k_column >= 0 && k_row < kernel_size_height && k_column < kernel_size_width) {
                        output[o_row * output_size_width + o_column].uint32.value += input[i_row * input_size_width + i_column].uint32.value * kernel[k_row * kernel_size_width + k_column].uint32.value;
                    }
                }
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_uint32_direct_2D_circular_convolution (const size_t size_width,
                                                               const size_t size_height,
                                                               const qconv_uint32_mod input[static const size_width * size_height],
                                                               const qconv_uint32_mod kernel[static const size_width * size_height],
                                                               qconv_uint32_mod output[static size_width * size_height]) {
    for (size_t o_row = 0; o_row < size_height; o_row++) {
        for (size_t o_column = 0; o_column < size_width; o_column++) {
            output[o_row * size_width + o_column].uint32.value = 0;
            for (int i_row = 0; i_row < size_height; i_row++) {
                for (size_t i_column = 0; i_column < size_width; i_column++) {
                    int k_row = o_row - i_row;
                    int k_column = o_column - i_column;
                    while (k_row < 0) {
                        k_row += size_height;
                    }
                    while (k_column < 0) {
                        k_column += size_width;
                    }
                    output[o_row * size_width + o_column].uint32.value += input[i_row * size_width + i_column].uint32.value * kernel[k_row * size_width + k_column].uint32.value;
                }
            }
        }
    }
    return status_success;
}
