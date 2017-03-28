//
// Created by alessandro on 3/27/17.
//

#include "qconv_crt.h"

enum qconv_status qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size_t size,
                                                                    qconv_uint32_mod input[size],
                                                                    qconv_uint32_mod kernel[size],
                                                                    qconv_uint32_mod output[size],
                                                                    enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;

    qconv_uint16_mod input_bis[size], kernel_bis[size], output_bis[size];

    for (size_t i = 0; i < size; i++) {
        //I'm assuming input and kernel fit into 16bit as well
        input_bis[i].uint16.value = (qconv_inner_uint16) input[i].uint32.value;
        kernel_bis[i].uint16.value = (qconv_inner_uint16) kernel[i].uint32.value;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_NTT_1D_circular_convolution_uint32_mod_f_4(size, input, kernel, output, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_1D_circular_convolution_uint16_mod_f_3(size, input_bis, kernel_bis, output_bis, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    #pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        qconv_uint32_mod_f_4 temp = {.value = (qconv_inner_uint32) output_bis[i].mod_f_3.value};
        output[i].mod_f_4 = qconv_subtract_uint32_mod_f_4(output[i].mod_f_4, temp);
    }

    qconv_uint32_mod f_3_mod_f4 = {.mod_f_4.value = QCONV_F_3};
    qconv_uint32_mod_f_4 f_3_inverse_mod_f4 = qconv_inverse_uint32_mod_f_4(f_3_mod_f4);

    #pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        output[i].mod_f_4 = qconv_mul_uint32_mod_f_4(f_3_inverse_mod_f4, output[i].mod_f_4);
        output[i].uint32.value = QCONV_F_3 * output[i].uint32.value + output_bis[i].uint16.value;
    }
    return status;
}

enum qconv_status qconv_NTT_2D_circular_convolution_mod_crt_f_3_f_4(size_t size_width,
                                                                    size_t size_height,
                                                                    qconv_uint32_mod input[size_width * size_height],
                                                                    qconv_uint32_mod kernel[size_width * size_height],
                                                                    qconv_uint32_mod output[size_width * size_height],
                                                                    enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;

    size_t size = size_width * size_height;
    qconv_uint16_mod input_bis[size], kernel_bis[size], output_bis[size];

    for (size_t i = 0; i < size; i++) {
        //I'm assuming input and kernel fit into 16bit as well
        input_bis[i].uint16.value = (qconv_inner_uint16) input[i].uint32.value;
        kernel_bis[i].uint16.value = (qconv_inner_uint16) kernel[i].uint32.value;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_NTT_2D_circular_convolution_uint32_mod_f_4(size_width, size_height, input, kernel, output, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_2D_circular_convolution_uint16_mod_f_3(size_width, size_height, input_bis, kernel_bis, output_bis, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    #pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        qconv_uint32_mod_f_4 temp = {.value = (qconv_inner_uint32) output_bis[i].mod_f_3.value};
        output[i].mod_f_4 = qconv_subtract_uint32_mod_f_4(output[i].mod_f_4, temp);
    }

    qconv_uint32_mod f_3_mod_f4 = {.mod_f_4.value = QCONV_F_3};
    qconv_uint32_mod_f_4 f_3_inverse_mod_f4 = qconv_inverse_uint32_mod_f_4(f_3_mod_f4);

    #pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        output[i].mod_f_4 = qconv_mul_uint32_mod_f_4(f_3_inverse_mod_f4, output[i].mod_f_4);
        output[i].uint32.value = QCONV_F_3 * output[i].uint32.value + output_bis[i].uint16.value;
    }
    return status;
}

enum qconv_status qconv_NTT_2D_overlap_and_add_linear_convolution() {

}
