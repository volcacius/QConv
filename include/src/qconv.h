//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define QCONV_SIZE_8 8
#define QCONV_SIZE_16 16
#define QCONV_SIZE_32 32
#define QCONV_SIZE_64 64
#define QCONV_SIZE_128 128
#define QCONV_SIZE_256 256
#define QCONV_SIZE_512 512
#define QCONV_SIZE_1024 1024
#define QCONV_SIZE_2048 2048
#define QCONV_SIZE_65536 65536

//Consider only sizes up to 2048 in tests, bigger constants are used only as algorithm inner magic numbers
#define QCONV_CONV_SIZES 9

#define CHECK_STATUS(status)({if (status) {return status;}})
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