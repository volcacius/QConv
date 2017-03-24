//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define TEST_ITERATIONS 10000

#define QCONV_LEN_8 8
#define QCONV_LEN_16 16
#define QCONV_LEN_32 32
#define QCONV_LEN_64 64
#define QCONV_LEN_128 128
#define QCONV_LEN_256 256
#define QCONV_LEN_512 512
#define QCONV_LEN_1024 1024
#define QCONV_LEN_2048 2048

#define QCONV_CONV_SIZES 9

#define CHECK_STATUS(status)({if (status != status_success) {return status;}})
#define CHECK_TEST_STATUS(status)(assert(!status))


/*
 * @brief Status code for QConv function calls.
 */
enum qconv_status {
    status_success,
    status_invalid_input_size,
    status_invalid_padding_size,
    status_invalid_slicing_size
};

/*
 * @brief Optimization level for transformation.
 */
enum qconv_optimize_transform {
    optimize_null,
    optimize_precomp,
    optimize_precomp_order,
    optimize_precomp_fuse,
    optimize_precomp_fuse_order
};