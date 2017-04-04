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

enum qconv_status qconv_right_zero_pad_uint32_1D_array(const size_t outer_size,
                                                       const size_t inner_size,
                                                       const qconv_uint32_mod input[static inner_size],
                                                       qconv_uint32_mod output[static outer_size]) {
    for (size_t i = 0; i <inner_size; i++) {
        output[i].uint32.value = input[i].uint32.value;
    }
    for (size_t i = inner_size; i < outer_size; i++) {
        output[i].uint32.value = 0;
    }
    return status_success;
}

enum qconv_status qconv_left_zero_pad_uint32_1D_array(const size_t outer_size,
                                                      const size_t inner_size,
                                                      const qconv_uint32_mod input[inner_size],
                                                      qconv_uint32_mod output[outer_size]) {
    size_t pad_size = outer_size - inner_size;

    /*printf("1D to left pad:\n");
    for (size_t i = 0; i <inner_size; i++) {
        printf("%d ", input[i].uint32.value);
    }
    printf("\n");*/

    for (size_t i = 0; i < pad_size; i++) {
        output[i].uint32.value = 0;
    }
    for (size_t i = pad_size; i <outer_size; i++) {
        output[i].uint32.value = input[i - pad_size].uint32.value;
    }
    return status_success;
}

enum qconv_status qconv_bottom_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                             const size_t outer_size_height,
                                                             const size_t inner_size_width,
                                                             const size_t inner_size_height,
                                                             const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                             qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    // Pad all the inner rows
    for (size_t row = 0; row < inner_size_height; row++) {
        qconv_left_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                             &output[row * outer_size_width]);
    }
    //Zero the bottom rows
    for (size_t i = outer_size_width * inner_size_height; i < outer_size_width * outer_size_height; i++) {
        output[i].uint32.value = 0;
    }
    return status_success;
}

enum qconv_status qconv_bottom_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                              const size_t outer_size_height,
                                                              const size_t inner_size_width,
                                                              const size_t inner_size_height,
                                                              const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                              qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    // Pad all the inner rows
    for (size_t row = 0; row < inner_size_height; row++) {
        qconv_right_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                                 &output[row * outer_size_width]);
    }
    //Zero the bottom rows
    for (size_t i = outer_size_width * inner_size_height; i < outer_size_width * outer_size_height; i++) {
        output[i].uint32.value = 0;
    }
    return status_success;
}

enum qconv_status qconv_top_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                          const size_t outer_size_height,
                                                          const size_t inner_size_width,
                                                          const size_t inner_size_height,
                                                          const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                          qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    size_t pad_size = outer_size_width * (outer_size_height - inner_size_height);
    //Zero the top rows
    for (size_t i = 0; i < pad_size; i++) {
        output[i].uint32.value = 0;
    }
    // Pad all the inner rows
    for (size_t row = 0; row < inner_size_height; row++) {
        qconv_left_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                             &output[pad_size + row * outer_size_width]);
    }
    return status_success;
}

enum qconv_status qconv_top_zero_pad_uint32_2D_array(const size_t size_width,
                                                     const size_t outer_size_height,
                                                     const size_t inner_size_height,
                                                     const qconv_uint32_mod input[static const size_width * inner_size_height],
                                                     qconv_uint32_mod output[static size_width * outer_size_height]) {
    size_t pad_size = size_width * (outer_size_height - inner_size_height);
    for (size_t i = 0; i < pad_size; i++) {
        output[i].uint32.value = 0;
    }
    qconv_clone_uint32_array(size_width * inner_size_height, input, &output[pad_size]);
}

enum qconv_status qconv_bottom_zero_pad_uint32_2D_array(const size_t size_width,
                                                        const size_t outer_size_height,
                                                        const size_t inner_size_height,
                                                        const qconv_uint32_mod input[static const size_width * inner_size_height],
                                                        qconv_uint32_mod output[static size_width * outer_size_height]) {
    size_t input_size = size_width * inner_size_height;
    qconv_clone_uint32_array(input_size, input, output);
    for (size_t i = input_size; i < size_width * outer_size_height; i++) {
        output[i].uint32.value = 0;
    }
}

enum qconv_status qconv_left_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                      const size_t size_height,
                                                      const size_t inner_size_width,
                                                      const qconv_uint32_mod input[static const inner_size_width * size_height],
                                                      qconv_uint32_mod output[static inner_size_width * size_height]) {
    for (size_t row = 0; row < size_height; row++) {
        qconv_left_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                             &output[row * outer_size_width]);
    }
}

enum qconv_status qconv_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                       const size_t size_height,
                                                       const size_t inner_size_width,
                                                       const qconv_uint32_mod input[static const inner_size_width * size_height],
                                                       qconv_uint32_mod output[static inner_size_width * size_height]) {
    for (size_t row = 0; row < size_height; row++) {
        qconv_right_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                            &output[row * outer_size_width]);
    }
}

enum qconv_status qconv_top_right_zero_pad_uint32_2D_array(const size_t outer_size_width,
                                                           const size_t outer_size_height,
                                                           const size_t inner_size_width,
                                                           const size_t inner_size_height,
                                                           const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                                           qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    size_t pad_size = outer_size_width * (outer_size_height - inner_size_height);
    //Zero the top rows
    for (size_t i = 0; i < pad_size; i++) {
        output[i].uint32.value = 0;
    }
    // Pad all the inner rows
    for (size_t row = 0; row < inner_size_height; row++) {
        qconv_right_zero_pad_uint32_1D_array(outer_size_width, inner_size_width, &input[row * inner_size_width],
                                             &output[pad_size + row * outer_size_width]);
    }
    return status_success;
}

enum qconv_status qconv_reverse_uint32_array(const size_t size,
                                             qconv_uint32_mod a[static size]) {
    size_t start = 0;
    size_t end = size - 1;
    while (start < end) {
        qconv_inner_uint32 temp = a[start].uint32.value;
        a[start].uint32.value = a[end].uint32.value;
        a[end].uint32.value = temp;
        start++;
        end--;
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
                                              const size_t top_left_width_offset,
                                              const size_t top_left_height_offset,
                                              const qconv_uint32_mod input[static const outer_size_width * outer_size_height],
                                              qconv_uint32_mod output[static inner_size_width * inner_size_height]) {
    if (inner_size_width + top_left_width_offset > outer_size_width
        || inner_size_height + top_left_height_offset > outer_size_height) {
        return status_invalid_slicing_size;
    }
    for (size_t row = 0; row < inner_size_height; row++) {
        for (size_t column = 0; column < inner_size_width; column++) {
            output[row * inner_size_width + column].uint32.value =
                    input[(row + top_left_height_offset) * outer_size_width + (top_left_width_offset + column)].uint32.value;
        }
    }
    return status_success;
}

enum qconv_status qconv_insert_uint32_2D_array(const size_t outer_size_width,
                                               const size_t outer_size_height,
                                               const size_t inner_size_width,
                                               const size_t inner_size_height,
                                               const size_t top_left_width_offset,
                                               const size_t top_left_height_offset,
                                               const qconv_uint32_mod input[static const inner_size_width * inner_size_height],
                                               qconv_uint32_mod output[static outer_size_width * outer_size_height]) {
    for (size_t row = 0; row < inner_size_height; row++) {
        for (size_t column = 0; column < inner_size_width; column++) {
            output[(row + top_left_height_offset) * outer_size_width + (top_left_width_offset + column)] =
                    input[row * inner_size_width +  + column];
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

enum qconv_status qconv_uint32_direct_2D_linear_convolution(const size_t input_size_width,
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

enum qconv_status qconv_uint32_direct_2D_circular_convolution(const size_t size_width,
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

enum qconv_status qconv_uint32_direct_2D_cnn_convolution(const size_t input_size_width,
                                                         const size_t input_size_height,
                                                         const size_t kernel_size_width,
                                                         const size_t kernel_size_height,
                                                         const qconv_uint32_mod input[static const input_size_width * input_size_height],
                                                         const qconv_uint32_mod kernel[static const kernel_size_width * kernel_size_height],
                                                         qconv_uint32_mod output[static (input_size_width - kernel_size_width + 1) * (input_size_height - kernel_size_height + 1)]) {
    //define offset of the current portion of input that overlaps with the kernel,
    //defined as positive index starting at 0,0 on upper left corner
    size_t i_row_offset = 0;
    size_t i_column_offset = 0;

    size_t output_size_width = input_size_width - kernel_size_width + 1;
    size_t output_size_height = input_size_height - kernel_size_height + 1;

    //iterate over output rows
    for(size_t o_row = 0; o_row < output_size_height; o_row++) {

        //iterate over output columns
        for (size_t o_column = 0; o_column < output_size_width; o_column++) {

            //set the starting value of a single point of output to 0.
            //a single point of output is the sum of the dot product between the
            //shifted kernel and the overlapped region of input
            //the current overlapped region of input is retrived from i_row_offset, i_column_offset
            output[o_row * output_size_width + o_column].uint32.value = 0;

            //iterate over kernel rows
            for (size_t k_row = 0; k_row < kernel_size_height; k_row++) {

                //iterate over kernel columns
                for (size_t k_column = 0; k_column < kernel_size_width; k_column++) {
                    size_t i_row = i_row_offset + k_row;
                    size_t i_column = i_column_offset + k_column;
                    output[o_row * output_size_width + o_column].uint32.value +=
                            input[i_row * input_size_width + i_column].uint32.value * kernel[k_row * kernel_size_width + k_column].uint32.value;
                }
            }
            //at the end of the computation of a single output point, compute the new offset for the next point.
            //we shift first the kernel to the right, and when it reaches the end of the input we start again on the left by going down one row
            //
            if (i_column_offset + kernel_size_width == input_size_width) {
                i_column_offset = 0;
                i_row_offset += QCONV_STRIDE;
            } else {
                i_column_offset += QCONV_STRIDE;
            }
        }
    }
    return status_success;
}

void qconv_clone_uint32_2D_array(const size_t size_width,
                                 const size_t size_height,
                                 const qconv_uint32_mod source[static size_width * size_height],
                                 qconv_uint32_mod destination[static size_width * size_height]) {
    qconv_clone_uint32_array(size_width * size_height, source, destination);
}

void qconv_clone_uint32_array(size_t size,
                              const qconv_uint32_mod source[static size],
                              qconv_uint32_mod destination[static size]) {
    for (size_t k = 0; k < size; k++) {
        destination[k].uint32.value = source[k].uint32.value;
    }
}