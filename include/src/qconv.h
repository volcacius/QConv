//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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

#define QCONV_KERNEL_SIZE_3 3
#define QCONV_KERNEL_SIZE_4 4
#define QCONV_KERNEL_SIZE_5 5
#define QCONV_KERNEL_SIZE_7 7
#define QCONV_KERNEL_SIZE_9 9
#define QCONV_KERNEL_SIZE_11 11
#define QCONV_KERNEL_SIZE_13 13
#define QCONV_KERNEL_SIZE_15 15
#define QCONV_KERNEL_SIZE_17 17

#define QCONV_KERN_SIZES 9

#define QCONV_LOG_SIZE_8 3
#define QCONV_LOG_SIZE_16 4
#define QCONV_LOG_SIZE_32 5
#define QCONV_LOG_SIZE_64 6
#define QCONV_LOG_SIZE_128 7
#define QCONV_LOG_SIZE_256 8
#define QCONV_LOG_SIZE_512 9
#define QCONV_LOG_SIZE_1024 10
#define QCONV_LOG_SIZE_2048 11
#define QCONV_LOG_SIZE_65536 16

#define CHECK_STATUS(status)({if (status) {return status;}})
#define CHECK_TEST_STATUS(status)(assert(!status))

/*
 * @brief Status code for QConv function calls.
 */
enum qconv_status {
    status_success,
    status_invalid_input_size,
    status_invalid_kernel_size,
    status_invalid_padding_size,
    status_invalid_slicing_size
};

/*
 * @brief Optimization level for transformation.
 */
enum qconv_optimize_transform {
    optimize_null,
    optimize_order,
    optimize_precomp_order,
    optimize_precomp
};