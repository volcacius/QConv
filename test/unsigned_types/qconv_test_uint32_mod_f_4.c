//
// Created by alessandro on 3/7/17.
//

#include <sys/time.h>
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
        assert(test.value == correct.mod_f_4.value);
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_identity_mod_f_4(size_t size,
                                                         size_t bit_size,
                                                         enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 identity\n size %d %dbit, max\n",
           size, bit_size);
    qconv_uint32_mod max[size], original[size];
    qconv_test_util_max_uint32_1D_array(size, max, bit_size);
    qconv_clone_uint32_array(size, max, original);
    status = qconv_NTT_1D_uint32_mod_f_4(size, max, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_1D_uint32_mod_f_4(size, max, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(size, max, original));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_identity_mod_f_4(size_t size_width,
                                                         size_t size_height,
                                                         size_t bit_size,
                                                         enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 max identity\n size %dx%d %dbit\n",
           size_width, size_height, bit_size);
    qconv_uint32_mod max[size_width * size_height], original[size_width * size_height];
    qconv_test_util_max_uint32_2D_array(size_width, size_height, max, bit_size);
    qconv_clone_uint32_array(size_width * size_height, max, original);
    status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, max, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, max, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, max, original));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_identity_mod_f_4(size_t size,
                                                            size_t bit_size,
                                                            enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 random identity\n size %d %dbit\n",
           size, bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod a[size], original[size];
        qconv_test_util_random_uint32_1D_array(size, a, bit_size);
        qconv_clone_uint32_array(size, a, original);
        status = qconv_NTT_1D_uint32_mod_f_4(size, a, optimize_level);
        CHECK_TEST_STATUS(status);
        status = qconv_INTT_1D_uint32_mod_f_4(size, a, optimize_level);
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_1D_array(size, a, original));
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_random_identity_mod_f_4(size_t size_width,
                                                            size_t size_height,
                                                            size_t bit_size,
                                                            enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 2D NTT mod F_4 random identity\n size %dx%d %dbit\n",
           size_width, size_height, bit_size);
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod random[size_width * size_height], original[size_width * size_height];
        qconv_test_util_random_uint32_2D_array(size_width, size_height, random, bit_size);
        qconv_clone_uint32_array(size_width * size_height, random, original);
        status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, random, optimize_level);
        CHECK_TEST_STATUS(status);
        status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, random, optimize_level);
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, random, original));
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_circular_convolution_mod_f_4(size_t size,
                                                                     size_t input_bit_size,
                                                                     size_t kernel_bit_size,
                                                                     enum qconv_optimize_transform optimize_level) {
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
    status = qconv_NTT_1D_circular_convolution_uint32_mod_f_4(size, input, kernel, ntt, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_circular_convolution_mod_f_4(size_t size_width,
                                                                     size_t size_height,
                                                                     size_t input_bit_size,
                                                                     size_t kernel_bit_size,
                                                                     enum qconv_optimize_transform optimize_level) {
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
    status = qconv_NTT_2D_circular_convolution_uint32_mod_f_4(size_width, size_height, input, kernel, ntt, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_circular_convolution_mod_f_4(size_t size,
                                                                        size_t input_bit_size,
                                                                        size_t kernel_bit_size,
                                                                        enum qconv_optimize_transform optimize_level) {
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
        status = qconv_NTT_1D_circular_convolution_uint32_mod_f_4(size, a, b, ntt, optimize_level);
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
                                                                        size_t kernel_bit_size,
                                                                        enum qconv_optimize_transform optimize_level) {
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
        status = qconv_NTT_2D_circular_convolution_uint32_mod_f_4(size_width, size_height, input, kernel, ntt, optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(size_width, size_height, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_block_linear_convolution_mod_f_4(size_t input_size,
                                                                            size_t kernel_size,
                                                                            size_t input_bit_size,
                                                                            size_t kernel_bit_size,
                                                                            enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 random block linear convolution\n, input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size = input_size + kernel_size - 1;
    qconv_uint32_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        //Generate random input
        qconv_test_util_random_uint32_1D_array(input_size, input, input_bit_size);
        qconv_test_util_random_uint32_1D_array(kernel_size, kernel, kernel_bit_size);
        //Compute direct
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
        CHECK_TEST_STATUS(status);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        //Compute NTT
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        status = qconv_NTT_1D_block_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, ntt, optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint32_1D_array(input_size + kernel_size - 1, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_max_linear_convolution_mod_f_4(size_t input_size,
                                                                   size_t kernel_size,
                                                                   size_t input_bit_size,
                                                                   size_t kernel_bit_size,
                                                                   enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    printf("Test 1D NTT mod F_4 max linear convolution\n input size %d %dbit, kernel size %d %dbit\n",
           input_size, input_bit_size, kernel_size, kernel_bit_size);
    size_t output_size = input_size + kernel_size - 1;
    qconv_uint32_mod input[input_size], kernel[kernel_size], ntt[output_size], conv[output_size];
    //Generate max input
    qconv_test_util_max_uint32_1D_array(input_size, input, input_bit_size);
    qconv_test_util_max_uint32_1D_array(kernel_size, kernel, kernel_bit_size);
    //Direct linear convolution
    status = qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, conv);
    CHECK_TEST_STATUS(status);
    //NTT linear convolution
    status = qconv_NTT_1D_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, ntt, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_1D_array(output_size, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_linear_convolution_mod_f_4(size_t input_size_width,
                                                                   size_t input_size_height,
                                                                   size_t kernel_size_width,
                                                                   size_t kernel_size_height,
                                                                   size_t input_bit_size,
                                                                   size_t kernel_bit_size,
                                                                   enum qconv_optimize_transform optimize_level) {

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
    status = qconv_NTT_2D_linear_convolution_uint32_mod_f_4(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, ntt, optimize_level);
    CHECK_TEST_STATUS(status);
    assert(qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv));
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_random_linear_convolution_mod_f_4(size_t input_size,
                                                                      size_t kernel_size,
                                                                      size_t input_bit_size,
                                                                      size_t kernel_bit_size,
                                                                      enum qconv_optimize_transform optimize_level) {
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
        status = qconv_NTT_1D_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, ntt, optimize_level);
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
                                                                      size_t kernel_bit_size,
                                                                      enum qconv_optimize_transform optimize_level) {
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
        status = qconv_NTT_2D_linear_convolution_uint32_mod_f_4(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, ntt, optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);
        assert(qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_max_block_CNN_convolution_mod_f_4(size_t input_size_width,
                                                                         size_t input_size_height,
                                                                         size_t kernel_size_width,
                                                                         size_t kernel_size_height,
                                                                      size_t block_size_width,
                                                                      size_t block_size_height,
                                                                         size_t input_bit_size,
                                                                         size_t kernel_bit_size,
                                                                         enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size_width = input_size_width - kernel_size_width + 1;
    size_t output_size_height = input_size_height - kernel_size_height + 1;

    qconv_uint32_mod *input = malloc(input_size_width * input_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *kernel = malloc(kernel_size_width * kernel_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *ntt = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *conv = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));

    printf("Test 2D NTT mod F_4 max block CNN convolution\n input size %dx%d %dbit, kernel size %dx%d %dbit, block size %dx%d\n",
           input_size_width, input_size_height, input_bit_size, kernel_size_width, kernel_size_height, kernel_bit_size, block_size_width, block_size_height);

    //Generate max input and kernel
    qconv_test_util_max_uint32_2D_array(input_size_width, input_size_height, input, input_bit_size);
    qconv_test_util_max_uint32_2D_array(kernel_size_width, kernel_size_height, kernel, kernel_bit_size);

    //Direct CNN convolution
    struct timeval direct_start, direct_end;
    gettimeofday(&direct_start, NULL);

    status = qconv_uint32_direct_2D_cnn_convolution(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, conv);

    gettimeofday(&direct_end, NULL);
    direct_tot_time += ((direct_end.tv_sec - direct_start.tv_sec) * 1000000 + direct_end.tv_usec - direct_start.tv_usec);

    CHECK_TEST_STATUS(status);

    //NTT linear convolution

    struct timeval ntt_start, ntt_end;
    gettimeofday(&ntt_start, NULL);

    qconv_reverse_uint32_array(kernel_size_width * kernel_size_height, kernel);
    status = qconv_NTT_2D_block_CNN_convolution_uint32_mod_f_4(input_size_width,
                                                               input_size_height,
                                                               kernel_size_width,
                                                               kernel_size_height,
                                                               block_size_width,
                                                               block_size_height,
                                                               input,
                                                               kernel,
                                                               ntt,
                                                               optimize_level);
    gettimeofday(&ntt_end, NULL);

    ntt_tot_time += ((ntt_end.tv_sec - ntt_start.tv_sec) * 1000000 + ntt_end.tv_usec - ntt_start.tv_usec);

    CHECK_TEST_STATUS(status);

    bool correct = qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv);
    assert(correct);

    free(input);
    free(kernel);
    free(ntt);
    free(conv);

    printf(" Direct %f, NTT %f, NTT/Direct %f\n\n", direct_tot_time/TEST_ITERATIONS, ntt_tot_time/TEST_ITERATIONS, direct_tot_time/ntt_tot_time);

    return status_success;
}

enum qconv_status qconv_test_NTT_2D_random_block_CNN_convolution_mod_f_4(size_t input_size_width,
                                                                  size_t input_size_height,
                                                                  size_t kernel_size_width,
                                                                  size_t kernel_size_height,
                                                                         size_t block_size_width,
                                                                         size_t block_size_height,
                                                                  size_t input_bit_size,
                                                                  size_t kernel_bit_size,
                                                                  enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t output_size_width = input_size_width - kernel_size_width + 1;
    size_t output_size_height = input_size_height - kernel_size_height + 1;

    qconv_uint32_mod *input = malloc(input_size_width * input_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *kernel = malloc(kernel_size_width * kernel_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *ntt = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *conv = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));

    printf("Test 2D NTT mod F_4 random block CNN convolution\n input size %dx%d %dbit, kernel size %dx%d %dbit, block size %dx%d\n",
           input_size_width, input_size_height, input_bit_size, kernel_size_width, kernel_size_height, kernel_bit_size, block_size_width, block_size_height);

    for (int i = 0; i < TEST_ITERATIONS; i++) {

        //Generate random input and kernel
        qconv_test_util_random_uint32_2D_array(input_size_width, input_size_height, input, input_bit_size);
        qconv_test_util_random_uint32_2D_array(kernel_size_width, kernel_size_height, kernel, kernel_bit_size);

        //Direct CNN convolution

        struct timeval direct_start, direct_end;
        gettimeofday(&direct_start, NULL);

        status = qconv_uint32_direct_2D_cnn_convolution(input_size_width, input_size_height, kernel_size_width, kernel_size_height, input, kernel, conv);

        gettimeofday(&direct_end, NULL);
        direct_tot_time += ((direct_end.tv_sec - direct_start.tv_sec) * 1000000 + direct_end.tv_usec - direct_start.tv_usec);

        CHECK_TEST_STATUS(status);

        //NTT linear convolution

        struct timeval ntt_start, ntt_end;
        gettimeofday(&ntt_start, NULL);

        qconv_reverse_uint32_array(kernel_size_width * kernel_size_height, kernel);
        status = qconv_NTT_2D_block_CNN_convolution_uint32_mod_f_4(input_size_width,
                                                                   input_size_height,
                                                                   kernel_size_width,
                                                                   kernel_size_height,
                                                                   block_size_width,
                                                                   block_size_height,
                                                                   input,
                                                                   kernel,
                                                                   ntt,
                                                                   optimize_level);
        gettimeofday(&ntt_end, NULL);

        ntt_tot_time += ((ntt_end.tv_sec - ntt_start.tv_sec) * 1000000 + ntt_end.tv_usec - ntt_start.tv_usec);

        CHECK_TEST_STATUS(status);

        bool correct = qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv);
        assert(correct);
    }

    free(input);
    free(kernel);
    free(ntt);
    free(conv);

    printf(" Direct %f, NTT %f, NTT/Direct %f\n\n", direct_tot_time/TEST_ITERATIONS, ntt_tot_time/TEST_ITERATIONS, direct_tot_time/ntt_tot_time);

    return status_success;
}

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4(size_t size,
                                                     size_t bit_size,
                                                     enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_identity_mod_f_4(size, bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_identity_mod_f_4(size, bit_size, optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_2D_identity_mod_f_4(size_t size_width,
                                                     size_t size_height,
                                                     size_t bit_size,
                                                     enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_identity_mod_f_4(size_width, size_height, bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_identity_mod_f_4(size_width, size_height, bit_size, optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4(size_t size,
                                                                 size_t input_bit_size,
                                                                 size_t kernel_bit_size,
                                                                 enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_circular_convolution_mod_f_4(size, input_bit_size, kernel_bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_circular_convolution_mod_f_4(size, input_bit_size, kernel_bit_size, optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_2D_circular_convolution_mod_f_4(size_t size_width,
                                                                 size_t size_height,
                                                                 size_t input_bit_size,
                                                                 size_t kernel_bit_size,
                                                                 enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_circular_convolution_mod_f_4(size_width, size_height, input_bit_size, kernel_bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_circular_convolution_mod_f_4(size_width, size_height, input_bit_size, kernel_bit_size, optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4(size_t input_size,
                                                               size_t kernel_size,
                                                               size_t input_bit_size,
                                                               size_t kernel_bit_size,
                                                               enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_max_linear_convolution_mod_f_4(input_size, kernel_size, input_bit_size, kernel_bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_1D_random_linear_convolution_mod_f_4(input_size, kernel_size, input_bit_size, kernel_bit_size, optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_1D_block_linear_convolution_mod_f_4(size_t input_size,
                                                                     size_t kernel_size,
                                                                     size_t input_bit_size,
                                                                     size_t kernel_bit_size,
                                                                     enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_1D_random_block_linear_convolution_mod_f_4(input_size, kernel_size, input_bit_size, kernel_bit_size, optimize_level);
    CHECK_TEST_STATUS(status);
    return status;
}



enum qconv_status qconv_test_NTT_2D_linear_convolution_mod_f_4(size_t input_size_width,
                                                               size_t input_size_height, 
                                                               size_t kernel_size_width, 
                                                               size_t kernel_size_height, 
                                                               size_t input_bit_size, 
                                                               size_t kernel_bit_size,
                                                               enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_linear_convolution_mod_f_4(input_size_width,
                                                              input_size_height,
                                                              kernel_size_width,
                                                              kernel_size_height,
                                                              input_bit_size,
                                                              kernel_bit_size,
                                                              optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_linear_convolution_mod_f_4(input_size_width,
                                                                 input_size_height,
                                                                 kernel_size_width,
                                                                 kernel_size_height,
                                                                 input_bit_size,
                                                                 kernel_bit_size, 
                                                                 optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(size_t input_size_width,
                                                               size_t input_size_height,
                                                               size_t kernel_size_width,
                                                               size_t kernel_size_height,
                                                                  size_t block_size_width,
                                                                  size_t block_size_height,
                                                               size_t input_bit_size,
                                                               size_t kernel_bit_size,
                                                               enum qconv_optimize_transform optimize_level) {
    enum qconv_status status;
    status = qconv_test_NTT_2D_max_block_CNN_convolution_mod_f_4(input_size_width,
                                                              input_size_height,
                                                              kernel_size_width,
                                                              kernel_size_height,
                                                                 block_size_width,
                                                                 block_size_height,
                                                              input_bit_size,
                                                              kernel_bit_size,
                                                              optimize_level);
    CHECK_TEST_STATUS(status);
    status = qconv_test_NTT_2D_random_block_CNN_convolution_mod_f_4(input_size_width,
                                                                 input_size_height,
                                                                 kernel_size_width,
                                                                 kernel_size_height,
                                                                    block_size_width,
                                                                    block_size_height,
                                                                 input_bit_size,
                                                                 kernel_bit_size,
                                                                 optimize_level);
    return status;
}

enum qconv_status qconv_test_NTT_1D_identity_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        for (size_t bit_size = 1; bit_size <= QCONV_MAX_F_4_NTT_IDENTITY_BITSIZE; bit_size++) {
            for (size_t i = 0; i < QCONV_F_4_1D_IDENTITY_SIZES; i++) {
                status = qconv_test_NTT_1D_identity_mod_f_4(qconv_test_sizes[i], bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_identity_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        for (size_t bit_size = 1; bit_size <= QCONV_MAX_F_4_NTT_IDENTITY_BITSIZE; bit_size++) {
            for (size_t i = 0; i < QCONV_F_4_2D_IDENTITY_SIZES; i++) {
                for (size_t j = 0; j < QCONV_F_4_2D_IDENTITY_SIZES; j++) {
                    status = qconv_test_NTT_2D_identity_mod_f_4(qconv_test_sizes[i],
                                                                qconv_test_sizes[j],
                                                                bit_size,
                                                                optimize_level);
                    CHECK_TEST_STATUS(status);
                }
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        status = qconv_test_NTT_1D_linear_convolution_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, 2, 2, optimize_level);
        CHECK_TEST_STATUS(status);
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_1D_block_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        for (size_t i = 0; i < QCONV_KERN_SIZES; i++) {
            status = qconv_test_NTT_1D_block_linear_convolution_mod_f_4(QCONV_SIZE_32, qconv_kernel_test_sizes[i], 4, 4, optimize_level);
            CHECK_TEST_STATUS(status);
            status = qconv_test_NTT_1D_block_linear_convolution_mod_f_4(QCONV_SIZE_64, qconv_kernel_test_sizes[i], 4, 4, optimize_level);
            CHECK_TEST_STATUS(status);
            status = qconv_test_NTT_1D_block_linear_convolution_mod_f_4(QCONV_SIZE_128, qconv_kernel_test_sizes[i], 4, 4, optimize_level);
            CHECK_TEST_STATUS(status);
            status = qconv_test_NTT_1D_block_linear_convolution_mod_f_4(QCONV_SIZE_256, qconv_kernel_test_sizes[i], 4, 4, optimize_level);
            CHECK_TEST_STATUS(status);
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_block_CNN_convolution_mod_f_4_runall() {
    enum qconv_status status;

    for (size_t input_index = 6; input_index < 7; input_index++) {
        //Kernel size = 3x3
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                        QCONV_KERNEL_SIZE_3, QCONV_KERNEL_SIZE_3,
                                                        QCONV_SIZE_8, QCONV_SIZE_8,
                                                        6, 6,
                                                        optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_3, QCONV_KERNEL_SIZE_3,
                                                                 QCONV_SIZE_16, QCONV_SIZE_16,
                                                                 6, 6,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_3, QCONV_KERNEL_SIZE_3,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 6, 6,
                                                                 optimize_precomp_order);
        //Kernel size = 5x5
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_5, QCONV_KERNEL_SIZE_5,
                                                                 QCONV_SIZE_8, QCONV_SIZE_8,
                                                                 6, 5,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_5, QCONV_KERNEL_SIZE_5,
                                                                 QCONV_SIZE_16, QCONV_SIZE_16,
                                                                 6, 5,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_5, QCONV_KERNEL_SIZE_5,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 6, 5,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);

        //kernel size = 7x7
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_7, QCONV_KERNEL_SIZE_7,
                                                                 QCONV_SIZE_16, QCONV_SIZE_16,
                                                                 5, 5,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_7, QCONV_KERNEL_SIZE_7,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 5, 5,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);

        //kernel size = 9x9
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_9, QCONV_KERNEL_SIZE_9,
                                                                 QCONV_SIZE_16, QCONV_SIZE_16,
                                                                 5, 4,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_9, QCONV_KERNEL_SIZE_9,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 5, 4,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);

        //kernel size = 11x11
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_11, QCONV_KERNEL_SIZE_11,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 5, 4,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);

        //kernel size = 13x13
        status = qconv_test_NTT_2D_block_cnn_convolution_mod_f_4(qconv_test_sizes[input_index], qconv_test_sizes[input_index],
                                                                 QCONV_KERNEL_SIZE_13, QCONV_KERNEL_SIZE_13,
                                                                 QCONV_SIZE_32, QCONV_SIZE_32,
                                                                 4, 4,
                                                                 optimize_precomp_order);
        CHECK_TEST_STATUS(status);
    }

    return status_success;
}

enum qconv_status qconv_test_NTT_2D_block_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;

    double direct_tot_time = 0;
    double ntt_tot_time = 0;

    size_t input_size_width = 300;
    size_t input_size_height = 300;
    size_t kernel_size_width = 16;
    size_t kernel_size_height = 16;
    size_t block_size_width = 32;
    size_t block_size_height = 32;
    size_t input_bit_size = 2;
    size_t kernel_bit_size = 2;
    enum qconv_optimize_transform optimize_level = optimize_precomp_order;

    size_t output_size_width = input_size_width + kernel_size_width - 1;
    size_t output_size_height = input_size_height + kernel_size_height - 1;

    qconv_uint32_mod *input = malloc(input_size_width * input_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *kernel = malloc(kernel_size_width * kernel_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *ntt = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));
    qconv_uint32_mod *conv = malloc(output_size_width * output_size_height * sizeof(qconv_uint32_mod));

    printf("Test 2D NTT mod F_4 random block linear convolution\n, input size %dx%d %dbit, kernel size %dx%d %dbit\n",
           input_size_width, input_size_height, input_bit_size, kernel_size_width, kernel_size_height, kernel_bit_size);

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
        status = qconv_NTT_2D_block_linear_convolution_uint32_mod_f_4(input_size_width,
                                                                   input_size_height,
                                                                   kernel_size_width,
                                                                   kernel_size_height,
                                                                   block_size_width,
                                                                   block_size_height,
                                                                   input,
                                                                   kernel,
                                                                   ntt,
                                                                   optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        CHECK_TEST_STATUS(status);

        printf("NTT Linear Output:\n");
        for (size_t i = 0; i < output_size_height; i++) {
            for(size_t j = 0; j < output_size_width; j++) {
                printf("%d ", ntt[i * output_size_width + j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("Direct Linear Output:\n");
        for (size_t i = 0; i < output_size_height; i++) {
            for(size_t j = 0; j < output_size_width; j++) {
                printf("%d ", conv[i * output_size_width + j]);
            }
            printf("\n");
        }
        printf("\n");

        bool error = qconv_test_util_compare_uint32_2D_array(output_size_width, output_size_height, ntt, conv);
        assert(error);
    }

    free(input);
    free(kernel);
    free(ntt);
    free(conv);

    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);

    return status_success;
}

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        status = qconv_test_NTT_1D_circular_convolution_mod_f_4(QCONV_SIZE_16, 2, 2, optimize_level);
        CHECK_TEST_STATUS(status);
        status = qconv_test_NTT_1D_circular_convolution_mod_f_4(QCONV_SIZE_16, 3, 3, optimize_level);
        CHECK_TEST_STATUS(status);
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_circular_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_8X8_INPUT_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_8X8_KERNEL_BITSIZE; kernel_bit_size++) {
                status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, input_bit_size, kernel_bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }
        for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_16X16_INPUT_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_16X16_KERNEL_BITSIZE; kernel_bit_size++) {
                status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, input_bit_size, kernel_bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }
        for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_32X32_INPUT_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_32X32_KERNEL_BITSIZE; kernel_bit_size++) {
                status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_32, QCONV_SIZE_32, input_bit_size, kernel_bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }

        for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_64X64_INPUT_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_64X64_KERNEL_BITSIZE; kernel_bit_size++) {
                status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_64, QCONV_SIZE_64, input_bit_size, kernel_bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }

        for (size_t input_bit_size = 2; input_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_128X128_INPUT_BITSIZE; input_bit_size++) {
            for (size_t kernel_bit_size = 1; kernel_bit_size <= QCONV_MAX_F_4_NTT_2D_CIRC_128X128_KERNEL_BITSIZE; kernel_bit_size++) {
                status = qconv_test_NTT_2D_circular_convolution_mod_f_4(QCONV_SIZE_128, QCONV_SIZE_128, input_bit_size, kernel_bit_size, optimize_level);
                CHECK_TEST_STATUS(status);
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_test_NTT_2D_linear_convolution_mod_f_4_runall() {
    enum qconv_status status;
    for (size_t optimize_level = optimize_null; optimize_level <= optimize_precomp_order; optimize_level++) {
        printf("%s:\n", qconv_get_optimize_level_string(optimize_level));
        status = qconv_test_NTT_2D_linear_convolution_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, QCONV_SIZE_8, QCONV_SIZE_8, 2, 1, optimize_level);
    }
    return status_success;
}

void qconv_test_uint32_mod_f_4_runall() {
    /*qconv_test_mul_mod_f_4();
    qconv_test_mul_mod_f_4_union();
    qconv_test_power_mod_f_4();
    qconv_test_NTT_1D_identity_mod_f_4_runall();
    qconv_test_NTT_1D_circular_convolution_mod_f_4_runall();
    qconv_test_NTT_1D_linear_convolution_mod_f_4_runall();
    qconv_test_NTT_2D_identity_mod_f_4_runall();
    qconv_test_NTT_2D_circular_convolution_mod_f_4_runall();
    qconv_test_NTT_2D_linear_convolution_mod_f_4_runall();
    qconv_test_NTT_1D_block_linear_convolution_mod_f_4_runall();*/
    //qconv_test_NTT_2D_block_linear_convolution_mod_f_4_runall();
    qconv_test_NTT_2D_block_CNN_convolution_mod_f_4_runall();
    //qconv_test_NTT_1D_max_identity_mod_f_4(32, 2, optimize_null);
}

