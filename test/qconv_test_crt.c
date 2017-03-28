//
// Created by alessandro on 3/27/17.
//

#include "qconv_test_crt.h"

void qconv_test_NTT_1D_random_convolution_mod_crt_f_3_f_4(size_t size,
                                                          size_t input_bit_size,
                                                          size_t kernel_bit_size,
                                                          enum qconv_optimize_transform optimize_level) {
    double direct_tot_time = 0;
    double ntt_tot_time = 0;
    printf("Test 1D NTT mod CRT F_3_F_4 random circular convolution\n size %d, input %dbit, kernel %dbit\n\n",
           size, input_bit_size, kernel_bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod input[size], kernel[size], conv[size], ntt[size];
        qconv_test_util_random_uint32_1D_array(size, input, input_bit_size);
        qconv_test_util_random_uint32_1D_array(size, kernel, kernel_bit_size);
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint32_direct_1D_circular_convolution(size, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size, input, kernel, ntt, optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);

}

void qconv_test_NTT_2D_random_convolution_mod_crt_f_3_f_4(size_t size_width,
                                                          size_t size_height,
                                                          size_t input_bit_size,
                                                          size_t kernel_bit_size,
                                                          enum qconv_optimize_transform optimize_level) {
    double direct_tot_time = 0;
    double ntt_tot_time = 0;
    printf("Test 2D NTT mod CRT F_3_F_4 random circular convolution\n size %dx%d, input %dbit, kernel %dbit\n\n",
           size_width, size_height, input_bit_size, kernel_bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod input[size_width * size_height], kernel[size_width * size_height], conv[size_width * size_height], ntt[size_width * size_height];
        qconv_test_util_random_uint32_2D_array(size_width, size_height, input, input_bit_size);
        qconv_test_util_random_uint32_2D_array(size_width, size_height, kernel, kernel_bit_size);
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint32_direct_2D_circular_convolution(size_width, size_height, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_2D_circular_convolution_mod_crt_f_3_f_4(size_width, size_height, input, kernel, ntt, optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);

}

void qconv_test_NTT_1D_max_convolution_mod_crt_f_3_f_4(size_t size,
                                                       size_t input_bit_size,
                                                       size_t kernel_bit_size,
                                                       enum qconv_optimize_transform optimize_level) {
    printf("Test 1D NTT mod CRT F_3_F_4 max circular convolution\n size %d, input %dbit, kernel %dbit\n\n",
           size, input_bit_size, kernel_bit_size);
    qconv_uint32_mod input[size], kernel[size], conv[size], ntt[size];
    qconv_test_util_max_uint32_1D_array(size, input, input_bit_size);
    qconv_test_util_max_uint32_1D_array(size, kernel, kernel_bit_size);
    qconv_uint32_direct_1D_circular_convolution(size, input, kernel, conv);
    qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size, input, kernel, ntt, optimize_level);
    assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
}

void qconv_test_NTT_2D_max_convolution_mod_crt_f_3_f_4(size_t size_width,
                                                       size_t size_height,
                                                       size_t input_bit_size,
                                                       size_t kernel_bit_size,
                                                       enum qconv_optimize_transform optimize_level) {
    printf("Test 2D NTT mod CRT F_3_F_4 max circular convolution\n size %dx%d, input %dbit, kernel %dbit\n\n",
           size_width, size_height, input_bit_size, kernel_bit_size);
    qconv_uint32_mod input[size_width * size_height], kernel[size_width * size_height], conv[size_width * size_height], ntt[size_width * size_height];
    qconv_test_util_max_uint32_2D_array(size_width, size_height, input, input_bit_size);
    qconv_test_util_max_uint32_2D_array(size_width, size_height, kernel, kernel_bit_size);
    qconv_uint32_direct_2D_circular_convolution(size_width, size_height, input, kernel, conv);
    qconv_NTT_2D_circular_convolution_mod_crt_f_3_f_4(size_width, size_height, input, kernel, ntt, optimize_level);
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
}

void qconv_test_NTT_1D_convolution_mod_crt_f_3_f_4_run_all() {
    for (size_t optimize_level = optimize_null; optimize_level < optimize_precomp; optimize_level++) {
        for (size_t input_bit_size = 1; input_bit_size <= QCONV_MAX_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_BITSIZE; kernel_bit_size++) {
                for (size_t size_index = 0; size_index < QCONV_CRT_F_3_F_4_1D_CONV_SIZES; size_index++) {
                    qconv_test_NTT_1D_max_convolution_mod_crt_f_3_f_4(qconv_test_sizes[size_index], input_bit_size, kernel_bit_size, optimize_level);
                    qconv_test_NTT_1D_random_convolution_mod_crt_f_3_f_4(qconv_test_sizes[size_index], input_bit_size, kernel_bit_size, optimize_level);
                }
            }
        }

    }
}

void qconv_test_NTT_2D_convolution_mod_crt_f_3_f_4_run_all() {
    for (size_t optimize_level = optimize_null; optimize_level < optimize_precomp; optimize_level++) {
        for (size_t input_bit_size = 1; input_bit_size <= QCONV_MAX_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_BITSIZE; kernel_bit_size++) {
                for (size_t size_width_index = 0; size_width_index < QCONV_CRT_F_3_F_4_2D_CONV_SIZES; size_width_index++) {
                    for (size_t size_height_index = 0; size_height_index < QCONV_CRT_F_3_F_4_2D_CONV_SIZES; size_height_index++) {
                        qconv_test_NTT_2D_max_convolution_mod_crt_f_3_f_4(qconv_test_sizes[size_width_index], qconv_test_sizes[size_height_index], input_bit_size, kernel_bit_size, optimize_level);
                        qconv_test_NTT_2D_random_convolution_mod_crt_f_3_f_4(qconv_test_sizes[size_width_index], qconv_test_sizes[size_height_index], input_bit_size, kernel_bit_size, optimize_level);
                    }

                }
            }
        }

    }
}

void qconv_test_mod_crt_f_3_f_4_run_all() {
    qconv_test_NTT_1D_convolution_mod_crt_f_3_f_4_run_all();
    qconv_test_NTT_2D_convolution_mod_crt_f_3_f_4_run_all();
}