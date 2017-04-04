//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include "qconv_constants.h"
#include "qconv_uint32.h"

/*
 * Source: https://gustedt.wordpress.com/2010/06/02/right-shift-on-signed-types-is-not-well-defined/
 */
#define QCONV_INT32_HIGHONES(c) ((qconv_inner_int32)(~(qconv_inner_uint32)0 << (sizeof(qconv_inner_int32)*CHAR_BIT - (c))))
#define QCONV_INT32_HIGHZEROS(c) (~QCONV_INT32_HIGHONES(c))

//Typedef a 32bit signed data type to a project wide inner 32bit representation
typedef int32_t qconv_inner_int32;

//Wrap the inner signed 32bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_int32 qconv_int32;
struct qconv_int32 {
    qconv_inner_int32 value;
};

//Define all the int32 structs in the same header to avoid circular dependencies
typedef struct qconv_int32_mod_12289 qconv_int32_mod_12289;
struct qconv_int32_mod_12289 {
    qconv_inner_int32 value;
};

//Overlay the various 32bit struct representation since they share the same inner 32bit representation
typedef union qconv_int32_mod qconv_int32_mod;
union qconv_int32_mod {
    qconv_int32_mod_12289 mod_12289;
    qconv_int32 int32;
};

/*
 * Source: https://gustedt.wordpress.com/2010/06/02/right-shift-on-signed-types-is-not-well-defined/
 */
inline int qconv_int32_logshiftr(qconv_inner_int32 x, qconv_inner_uint32 c) {
    return (x >> c) & QCONV_INT32_HIGHZEROS(c);
}
/*
 * Source: https://gustedt.wordpress.com/2010/06/02/right-shift-on-signed-types-is-not-well-defined/
 */
inline int qconv_int32_arishiftr(qconv_inner_int32 x, qconv_inner_uint32 c) {
    return qconv_int32_logshiftr(x, c) ^ (x < 0 ? QCONV_INT32_HIGHONES(c) : 0);
}

enum qconv_status qconv_int32_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_int32_mod input[static const kernel_size],
        const qconv_int32_mod kernel[static const input_size],
        qconv_int32_mod output[static input_size + kernel_size - 1]);

enum qconv_status qconv_int32_direct_1D_circular_convolution (
        const size_t size,
        const qconv_int32_mod input[static const size],
        const qconv_int32_mod kernel[static const size],
        qconv_int32_mod output[static size]);
