//
// Created by alessandro on 3/7/17.
//

#include "qconv_test_uint16_mod_f_8.h"

void qconv_test_mul_mod_f_8() {
    printf("Test multiplication mod F_8\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod_f_8 a = {.value =  (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 b = {.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 correct = {.value = (qconv_inner_uint16) (a.value * b.value % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 test = qconv_mul_uint16_mod_f_8(a, b);
        assert(test.value == correct.value);
    }
}

void qconv_test_mul_mod_f_8_union() {
    printf("Test multiplication mod F_8 with unions\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod a = {.mod_f_8.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod b = {.mod_f_8.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod correct = {.mod_f_8.value = (qconv_inner_uint16) (a.mod_f_8.value * b.mod_f_8.value % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 test = qconv_mul_uint16_mod_f_8(a.mod_f_8, b.mod_f_8);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_power_mod_f_8() {
    printf("Test power mod F_8\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod base = {.uint16.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        unsigned int exp = rand() % qconv_const_f_8.mod_f_8.value;
        qconv_uint16_mod correct = qconv_test_util_naive_power_uint16_mod(base, exp, qconv_const_f_8);
        qconv_uint16_mod_f_8 test = qconv_power_uint16_mod_f_8(base.mod_f_8, exp);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_NTT_1D_max_identity_mod_f_8(size_t size, size_t bit_size) {
    printf("Test 1D NTT mod F_8 identity\n size %d %dbit, max\n",
           size, bit_size);
    qconv_uint16_mod max[size], original[size];
    qconv_test_util_max_uint16_1D_array(size, max, bit_size);
    qconv_test_util_clone_uint16_1D_array(size, max, original);
    qconv_NTT_mod_f_8(size, max);
    qconv_INTT_mod_f_8(size, max);
    assert(qconv_test_util_compare_uint16_1D_array(size, max, original));
}

void qconv_test_NTT_1D_random_identity_mod_f_8(size_t size, size_t bit_size) {
    printf("Test 1D NTT mod F_8 identity\n size %d %dbit, random\n",
           size, bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod a[size], original[size];
        qconv_test_util_random_uint16_1D_array(size, a, bit_size);
        qconv_test_util_clone_uint16_1D_array(size, a, original);
        qconv_NTT_mod_f_8(size, a);
        qconv_INTT_mod_f_8(size, a);
        assert(qconv_test_util_compare_uint16_1D_array(size, a, original));
    }
}

void qconv_test_NTT_1D_max_circular_convolution_mod_f_8(size_t size, size_t input_bit_size, size_t kernel_bit_size) {
    printf("Test 1D NTT mod F_8 max circular convolution\n, size %d, input %dbit, kernel %dbit\n",
           size, input_bit_size, kernel_bit_size);
    qconv_uint16_mod input[size], kernel[size], ntt[size], conv[size];;
    //Generate max input
    qconv_test_util_max_uint16_1D_array(size, input, input_bit_size);
    qconv_test_util_max_uint16_1D_array(size, kernel, kernel_bit_size);
    //Direct linear convolution
    qconv_uint16_direct_1D_circular_convolution(size, input, kernel, conv);
    //NTT linear convolution
    qconv_NTT_1D_circular_convolution_uint16_mod_f_8(size, input, kernel, ntt);
    assert(qconv_test_util_compare_uint16_1D_array(size, ntt, conv));
}

void qconv_test_NTT_1D_random_circular_convolution_mod_f_8(size_t size, size_t input_bit_size, size_t kernel_bit_size) {
    printf("Test 1D NTT mod F_8 random circular convolution\n size %d, input %dbit, kernel %dbit\n",
           size, input_bit_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    qconv_uint16_mod a[size], b[size], ntt[size], conv[size];

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint16_1D_array(size, a, input_bit_size);
        qconv_test_util_random_uint16_1D_array(size, b, kernel_bit_size);
        //Direct circular convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint16_direct_1D_circular_convolution(size, a, b, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        //NTT circuar convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_1D_circular_convolution_uint16_mod_f_8(size, a, b, ntt);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint16_1D_array(size, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
}

void qconv_test_NTT_1D_max_linear_convolution_mod_f_8(size_t input_size,
                                                      size_t kernel_size,
                                                      size_t input_bit_size,
                                                      size_t kernel_bit_size) {
    printf("Test 1D NTT mod F_8 max linear convolution\n input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);
    size_t output_size = input_size + kernel_size - 1;
    qconv_uint16_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];;
    //Generate max input
    qconv_test_util_max_uint16_1D_array(input_size, input, input_bit_size);
    qconv_test_util_max_uint16_1D_array(kernel_size, kernel, kernel_bit_size);
    //Direct linear convolution
    qconv_uint16_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
    //NTT linear convolution
    qconv_NTT_1D_linear_convolution_uint16_mod_f_8(input_size, kernel_size, input, kernel, ntt);
    assert(qconv_test_util_compare_uint16_1D_array(output_size, ntt, conv));
}

void qconv_test_NTT_1D_random_linear_convolution_mod_f_8(size_t input_size,
                                                  size_t kernel_size,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size) {
    printf("Test 1D NTT mod F_8 random linear convolution\n input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size = input_size + kernel_size - 1;
    qconv_uint16_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];;

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint16_1D_array(input_size, input, input_bit_size);
        qconv_test_util_random_uint16_1D_array(kernel_size, kernel, kernel_bit_size);
        //Direct linear convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint16_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        //NTT linear convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_1D_linear_convolution_uint16_mod_f_8(input_size, kernel_size, input, kernel, ntt);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint16_1D_array(output_size, ntt, conv));
    }

    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
}

void qconv_test_NTT_1D_identity_mod_f_8(size_t size, size_t bit_size) {
    qconv_test_NTT_1D_max_identity_mod_f_8(size, bit_size);
    qconv_test_NTT_1D_random_identity_mod_f_8(size, bit_size);
}

void qconv_test_NTT_1D_circular_convolution_mod_f_8(size_t size,
                                                    size_t input_bit_size,
                                                    size_t kernel_bit_size) {
    qconv_test_NTT_1D_max_circular_convolution_mod_f_8(size, input_bit_size, kernel_bit_size);
    qconv_test_NTT_1D_random_circular_convolution_mod_f_8(size, input_bit_size, kernel_bit_size);
}

void qconv_test_NTT_1D_linear_convolution_mod_f_8(size_t input_size,
                                                  size_t kernel_size,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size) {
    qconv_test_NTT_1D_max_linear_convolution_mod_f_8(input_size, kernel_size, input_bit_size, kernel_bit_size);
    qconv_test_NTT_1D_random_linear_convolution_mod_f_8(input_size, kernel_size, input_bit_size, kernel_bit_size);
}

void qconv_test_NTT_1D_identity_mod_f_8_runall() {
    for (size_t bit_size = 1; bit_size <= QCONV_MAX_F_8_NTT_IDENTITY_BITSIZE; bit_size++) {
        for (size_t i = 0; i < QCONV_F_8_CONV_SIZES; i++) {
            qconv_test_NTT_1D_identity_mod_f_8(qconv_test_NTT_1D_circular_convolution_uint16_mod_f_8_sizes[i], bit_size);
        }
    }
}

void qconv_test_NTT_1D_linear_convolution_mod_f_8_runall() {
    qconv_test_NTT_1D_linear_convolution_mod_f_8(QCONV_LEN_16, QCONV_LEN_16, 2, 2);
    qconv_test_NTT_1D_linear_convolution_mod_f_8(QCONV_LEN_32, QCONV_LEN_32, 2, 1);
    qconv_test_NTT_1D_linear_convolution_mod_f_8(QCONV_LEN_64, QCONV_LEN_64, 2, 1);
    qconv_test_NTT_1D_linear_convolution_mod_f_8(QCONV_LEN_128, QCONV_LEN_32, 2, 1);
}

void qconv_test_NTT_1D_circular_convolution_mod_f_8_runall() {
    qconv_test_NTT_1D_circular_convolution_mod_f_8(QCONV_LEN_16, 2, 2);
    qconv_test_NTT_1D_circular_convolution_mod_f_8(QCONV_LEN_32, 2, 1);
    qconv_test_NTT_1D_circular_convolution_mod_f_8(QCONV_LEN_64, 2, 1);
}

void qconv_test_uint16_mod_f_8_runall() {
    qconv_test_mul_mod_f_8();
    qconv_test_mul_mod_f_8_union();
    qconv_test_power_mod_f_8();
    qconv_test_NTT_1D_identity_mod_f_8_runall();
    qconv_test_NTT_1D_circular_convolution_mod_f_8_runall();
    qconv_test_NTT_1D_linear_convolution_mod_f_8_runall();
}

