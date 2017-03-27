//
// Created by alessandro on 3/7/17.
//

#include "qconv_test_uint32_mod_f_4.h"

enum qconv_status qconv_test_mul_mod_f_4() {
    printf("Test multiplication mod F_4\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod_f_4 a = {.value =  (qconv_inner_uint32) (rand() % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod_f_4 b = {.value = (qconv_inner_uint32) (rand() % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod_f_4 correct = {.value = (qconv_inner_uint32) (a.value * b.value % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod_f_4 test = qconv_mul_uint32_mod_f_4(a, b);
        assert(test.value == correct.value);
    }
    return status_success;
}

enum qconv_status qconv_test_fast_reduction_mod_f_4(bool big_int) {
    printf("Test fast reduction mod F_4\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod_f_4 a;
        if (big_int) {
            a.value =  (qconv_inner_uint32) rand() * rand();
        } else {
            a.value =  (qconv_inner_uint32) rand();
        }
        qconv_uint32_mod_f_4 correct = {.value = (qconv_inner_uint32) (a.value % qconv_const_f_4.mod_f_4.value)};
        qconv_inner_int64 z = (qconv_inner_int64) a.value;
        qconv_uint32_mod_f_4 test = qconv_reduce_int64_mod_f_4(z);
        assert(test.value == correct.value);
    }
    return status_success;
}

enum qconv_status qconv_test_mul_mod_f_4_union() {
    printf("Test multiplication mod F_4 with unions\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod a = {.mod_f_4.value = (qconv_inner_uint32) (rand() % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod b = {.mod_f_4.value = (qconv_inner_uint32) (rand() % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod correct = {.mod_f_4.value = (qconv_inner_uint32) (a.mod_f_4.value * b.mod_f_4.value % qconv_const_f_4.mod_f_4.value)};
        qconv_uint32_mod_f_4 test = qconv_mul_uint32_mod_f_4(a.mod_f_4, b.mod_f_4);
        assert(test.value == correct.mod_f_4.value);
    }
    return status_success;
}

enum qconv_status qconv_test_power_mod_f_4() {
    printf("Test power mod F_4\n");
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod base = {.uint32.value = (qconv_inner_uint32) (rand() % qconv_const_f_4.mod_f_4.value)};
        unsigned int exp = rand() % qconv_const_f_4.mod_f_4.value;
        qconv_uint32_mod correct = qconv_test_util_naive_power_uint32_mod(base, exp, qconv_const_f_4);
        qconv_uint32_mod_f_4 test = qconv_power_uint32_mod_f_4(base.mod_f_4, exp);
        //printf("Test power mod F_4 base %d exp %d, %d %d\n", base.mod_f_4.value, exp, correct.mod_f_4.value, test.value);
        assert(test.value == correct.mod_f_4.value);
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_identity_mod_f_4(size_t size, size_t bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 identity\n size %d %dbit, max\n",
           size, bit_size);
    qconv_uint32_mod max[size], max_precomp[size], original[size];
    qconv_test_util_max_uint32_1D_array(size, max, bit_size);
    qconv_test_util_clone_uint32_1D_array(size, max, max_precomp);
    qconv_test_util_clone_uint32_1D_array(size, max, original);
    status = qconv_NTT_1D_uint32_mod_f_4(size, max, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_1D_uint32_mod_f_4(size, max, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_NTT_1D_uint32_mod_f_4(size, max_precomp, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_1D_uint32_mod_f_4(size, max_precomp, optimize_null);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(size, max, original));
    assert(qconv_test_util_compare_uint32_1D_array(size, max_precomp, original));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_identity_mod_f_4(size_t size_width,
                                            size_t size_height,
                                            size_t bit_size) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 max identity\n size %dx%d %dbit\n",
           size_width, size_height, bit_size);
    qconv_uint32_mod max[size_width * size_height], max_precomp[size_width * size_height], original[size_width * size_height];
    qconv_test_util_max_uint32_2D_array(size_width, size_height, max, bit_size);
    qconv_test_util_clone_uint32_2D_array(size_width, size_height, max, max_precomp);
    qconv_test_util_clone_uint32_2D_array(size_width, size_height, max, original);
    status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, max, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, max, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, max_precomp, optimize_null);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, max_precomp, optimize_null);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, max, original));
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, max_precomp, original));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_identity_mod_f_4(size_t size, size_t bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 random identity\n size %d %dbit\n",
           size, bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod a[size], original[size];
        qconv_test_util_random_uint32_1D_array(size, a, bit_size);
        qconv_test_util_clone_uint32_1D_array(size, a, original);
        status = qconv_NTT_1D_uint32_mod_f_4(size, a, optimize_null);
        CHECK_TEST_STATUS(status);
        status = qconv_INTT_1D_uint32_mod_f_4(size, a, optimize_null);
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_1D_array(size, a, original));
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_random_identity_mod_f_4(size_t size_width,
                                               size_t size_height,
                                               size_t bit_size) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 random identity\n size %dx%d %dbit\n",
           size_width, size_height, bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod random[size_width * size_height], original[size_width * size_height];
        qconv_test_util_random_uint32_2D_array(size_width, size_height, random, bit_size);
        qconv_test_util_clone_uint32_2D_array(size_width, size_height, random, original);
        status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, random, optimize_null);
        CHECK_TEST_STATUS(status);
        status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, random, optimize_null);
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, random, original));
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_circular_convolution_mod_f_4(size_t size, size_t input_bit_size, size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 max circular convolution\n, size %d, input %dbit, kernel %dbit\n",
           size, input_bit_size, kernel_bit_size);
    qconv_uint32_mod input[size], kernel[size], ntt[size], conv[size];;
    //Generate max input
    qconv_test_util_max_uint32_1D_array(size, input, input_bit_size);
    qconv_test_util_max_uint32_1D_array(size, kernel, kernel_bit_size);
    //Direct linear convolution
    status = qconv_uint32_direct_1D_circular_convolution(size, input, kernel, conv);
    CHECK_TEST_STATUS(status);
    //NTT linear convolution
    status = qconv_NTT_1D_circular_convolution_uint32_mod_f_4(size, input, kernel, ntt, optimize_null);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_circular_convolution_mod_f_4(size_t size_width,
                                                        size_t size_height,
                                                        size_t input_bit_size,
                                                        size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 max circular convolution\n size %dx%d, input %dbit, kernel %dbit\n",
           size_width, size_height, input_bit_size, kernel_bit_size);
    qconv_uint32_mod input[size_width * size_height], kernel[size_width * size_height], ntt[size_width * size_height], conv[size_width * size_height];
    //Generate max input
    qconv_test_util_max_uint32_2D_array(size_width, size_height, input, input_bit_size);
    qconv_test_util_max_uint32_2D_array(size_width, size_height, kernel, kernel_bit_size);
    //Direct linear convolution
    status = qconv_uint32_direct_2D_circular_convolution(size_width, size_height, input, kernel, conv);
    CHECK_TEST_STATUS(status);
    //NTT linear convolution
    status = qconv_NTT_2D_circular_convolution_uint32_mod_f_4(size_width, size_height, input, kernel, ntt, optimize_precomp);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_circular_convolution_mod_f_4(size_t size, size_t input_bit_size, size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 random circular convolution\n size %d, input %dbit, kernel %dbit\n",
           size, input_bit_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    qconv_uint32_mod a[size], b[size], ntt[size], conv[size];

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint32_1D_array(size, a, input_bit_size);
        qconv_test_util_random_uint32_1D_array(size, b, kernel_bit_size);
        //Direct circular convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_uint32_direct_1D_circular_convolution(size, a, b, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        CHECK_TEST_STATUS(status);
        //NTT circuar convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_NTT_1D_circular_convolution_uint32_mod_f_4(size, a, b, ntt, optimize_null);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_random_circular_convolution_mod_f_4(size_t size_width,
                                                           size_t size_height,
                                                           size_t input_bit_size,
                                                           size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 random circular convolution\n size %dx%d, input %dbit, kernel %dbit\n",
           size_width, size_height, input_bit_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    qconv_uint32_mod input[size_width * size_height], kernel[size_width * size_height], ntt[size_width * size_height], conv[size_width * size_height];

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint32_2D_array(size_width, size_height, input, input_bit_size);
        qconv_test_util_random_uint32_2D_array(size_width, size_height, kernel, kernel_bit_size);
        //Direct circular convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_uint32_direct_2D_circular_convolution(size_width, size_height, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        CHECK_TEST_STATUS(status);
        //NTT circuar convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_NTT_2D_circular_convolution_uint32_mod_f_4(size_width, size_height, input, kernel, ntt, optimize_precomp);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_linear_convolution_mod_f_4(size_t input_size,
                                                      size_t kernel_size,
                                                      size_t input_bit_size,
                                                      size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 max linear convolution\n input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);
    size_t output_size = input_size + kernel_size - 1;
    qconv_uint32_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];;
    //Generate max input
    qconv_test_util_max_uint32_1D_array(input_size, input, input_bit_size);
    qconv_test_util_max_uint32_1D_array(kernel_size, kernel, kernel_bit_size);
    //Direct linear convolution
    status = qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
    CHECK_TEST_STATUS(status);
    //NTT linear convolution
    status = qconv_NTT_1D_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, ntt, optimize_null);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(output_size, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_linear_convolution_mod_f_4(size_t input_size_width,
                                                      size_t input_size_height,
                                                      size_t kernel_size_width,
                                                      size_t kernel_size_height,
                                                      size_t input_bit_size,
                                                      size_t kernel_bit_size) {

    enum qconv_status status;
    printf("Test 2D NTT mod F_4 max linear convolution\n input size %dx%d %dbit, kernel size %dx%d %dbit\n",
           input_size_width, input_size_height, input_bit_size, kernel_size_width, kernel_size_height, kernel_bit_size);
    size_t output_size_width = input_size_width + kernel_size_width - 1;
    size_t output_size_height = input_size_height + kernel_size_height - 1;
    qconv_uint32_mod input[input_size_width * input_size_height],
            kernel[kernel_size_width * kernel_size_height],
            ntt[output_size_width * output_size_height],
            conv[output_size_width * output_size_height];
    //Generate max input
    qconv_test_util_max_uint32_2D_array(input_size_width, input_size_height, input, input_bit_size);
    qconv_test_util_max_uint32_2D_array(kernel_size_width, kernel_size_height, kernel, kernel_bit_size);
    //Direct linear convolution
    status = qconv_uint32_direct_2D_linear_convolution(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, conv);
    CHECK_TEST_STATUS(status);
    //NTT linear convolution
    status = qconv_NTT_2D_linear_convolution_uint32_mod_f_4(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, ntt, optimize_null);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_linear_convolution_mod_f_4(size_t input_size,
                                                         size_t kernel_size,
                                                         size_t input_bit_size,
                                                         size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 random linear convolution\n input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size = input_size + kernel_size - 1;
    qconv_uint32_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];;

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint32_1D_array(input_size, input, input_bit_size);
        qconv_test_util_random_uint32_1D_array(kernel_size, kernel, kernel_bit_size);
        //Direct linear convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        CHECK_TEST_STATUS(status);
        //NTT linear convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_NTT_1D_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, ntt, optimize_null);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_1D_array(output_size, ntt, conv));
    }

    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_random_linear_convolution_mod_f_4(size_t input_size_width,
                                                         size_t input_size_height,
                                                         size_t kernel_size_width,
                                                         size_t kernel_size_height,
                                                         size_t input_bit_size,
                                                         size_t kernel_bit_size) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 random linear convolution\n input size %dx%d %dbit, kernel size %dx%d %dbit\n",
           input_size_width, input_size_height, input_bit_size, kernel_size_width, kernel_size_height, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size_width = input_size_width + kernel_size_width - 1;
    size_t output_size_height = input_size_height + kernel_size_height - 1;
    qconv_uint32_mod input[input_size_width * input_size_height],
            kernel[kernel_size_width * kernel_size_height],
            ntt[output_size_width * output_size_height],
            conv[output_size_width * output_size_height];

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint32_2D_array(input_size_width, input_size_height, input, input_bit_size);
        qconv_test_util_random_uint32_2D_array(kernel_size_width, kernel_size_height, kernel, kernel_bit_size);
        //Direct linear convolution
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_uint32_direct_2D_linear_convolution(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        CHECK_TEST_STATUS(status);
        //NTT linear convolution
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_NTT_2D_linear_convolution_uint32_mod_f_4(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, ntt, optimize_null);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4(size_t size, size_t bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_identity_mod_f_4(size, bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_identity_mod_f_4(size, bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_2D_identity_mod_f_4(size_t size_width, size_t size_height, size_t bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_identity_mod_f_4(size_width, size_height, bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_identity_mod_f_4(size_width, size_height, bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4(size_t size,
                                                    size_t input_bit_size,
                                                    size_t kernel_bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_circular_convolution_mod_f_4(size, input_bit_size, kernel_bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_circular_convolution_mod_f_4(size, input_bit_size, kernel_bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_2D_circular_convolution_mod_f_4(size_t size_width,
                                                    size_t size_height,
                                                    size_t input_bit_size,
                                                    size_t kernel_bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_circular_convolution_mod_f_4(size_width, size_height, input_bit_size, kernel_bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_circular_convolution_mod_f_4(size_width, size_height, input_bit_size, kernel_bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4(size_t input_size,
                                                  size_t kernel_size,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_linear_convolution_mod_f_4(input_size, kernel_size, input_bit_size, kernel_bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_linear_convolution_mod_f_4(input_size, kernel_size, input_bit_size, kernel_bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_2D_linear_convolution_mod_f_4(size_t input_size_width,
                                                  size_t input_size_height,
                                                  size_t kernel_size_width,
                                                  size_t kernel_size_height,
                                                  size_t input_bit_size,
                                                  size_t kernel_bit_size) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_linear_convolution_mod_f_4(input_size_width,
                                                              input_size_height,
                                                              kernel_size_width,
                                                              kernel_size_height,
                                                              input_bit_size,
                                                              kernel_bit_size);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_linear_convolution_mod_f_4(input_size_width,
                                                               input_size_height,
                                                               kernel_size_width,
                                                               kernel_size_height,
                                                               input_bit_size,
                                                               kernel_bit_size);
    return status;
}

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t bit_size = 1; bit_size <= QCONV_MAX_F_4_NTT_IDENTITY_BITSIZE; bit_size++) {
        for (size_t i = 0; i < QCONV_F_4_1D_IDENTITY_SIZES; i++) {
            status = qconv_test_NTT_1D_identity_mod_f_4(qconv_test_sizes[i], bit_size);
            CHECK_TEST_STATUS(status);
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_identity_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t bit_size = 1; bit_size <= QCONV_MAX_F_4_NTT_IDENTITY_BITSIZE; bit_size++) {
        for (size_t i = 0; i < QCONV_F_4_2D_IDENTITY_SIZES; i++) {
            for (size_t j = 0; j < QCONV_F_4_2D_IDENTITY_SIZES; j++) {
                status = qconv_test_NTT_2D_identity_mod_f_4(qconv_test_sizes[i],
                                                   qconv_test_sizes[j],
                                                   bit_size);
                CHECK_TEST_STATUS(status);
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;
    status = qconv_test_NTT_1D_linear_convolution_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, 2, 2);
    CHECK_TEST_STATUS(status);
    return status;
}

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4_runall() {
    enum qconv_status status;
    status = qconv_test_NTT_1D_circular_convolution_mod_f_4(QCONV_SIZE_16, 2, 2);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_circular_convolution_mod_f_4(QCONV_SIZE_16, 3, 3);
    CHECK_TEST_STATUS(status);
    return status;
}

enum qconv_status qconv_test_NTT_2D_circular_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_SIZE_8X8_INPUT_BITSIZE; input_bit_size++) {
        for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_SIZE_8X8_KERNEL_BITSIZE; kernel_bit_size++) {
            status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, input_bit_size, kernel_bit_size);
            CHECK_TEST_STATUS(status);
        }
    }
    for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_SIZE_16X16_INPUT_BITSIZE; input_bit_size++) {
        for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_SIZE_16X16_KERNEL_BITSIZE; kernel_bit_size++) {
            status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, input_bit_size, kernel_bit_size);
            CHECK_TEST_STATUS(status);
        }
    }
    return status;
}

enum qconv_status qconv_test_NTT_2D_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;
    status = qconv_test_NTT_2D_linear_convolution_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, QCONV_SIZE_8, QCONV_SIZE_8, 2, 1);
    return status;
}

void qconv_test_uint32_mod_f_4_runall() {
    enum qconv_status status;
    status = qconv_test_mul_mod_f_4();
    CHECK_TEST_STATUS(status);
    status = qconv_test_fast_reduction_mod_f_4(false);
    CHECK_TEST_STATUS(status);
    status = qconv_test_fast_reduction_mod_f_4(true);
    CHECK_TEST_STATUS(status);
    status = qconv_test_mul_mod_f_4_union();
    CHECK_TEST_STATUS(status);
    status = qconv_test_power_mod_f_4();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_identity_mod_f_4_runall();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_circular_convolution_mod_f_4_runall();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_linear_convolution_mod_f_4_runall();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_identity_mod_f_4_runall();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_circular_convolution_mod_f_4_runall();
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_linear_convolution_mod_f_4_runall();
    CHECK_TEST_STATUS(status);

}

