//
// Created by alessandro on 3/3/17.
//
#include "qconv_int32.h"

extern int qconv_int32_logshiftr(qconv_inner_int32 x, qconv_inner_uint32 c);

extern int qconv_int32_arishiftr(qconv_inner_int32 x, qconv_inner_uint32 c);

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
