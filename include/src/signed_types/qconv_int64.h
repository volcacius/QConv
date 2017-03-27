//
// Created by alessandro on 3/11/17.
//

#pragma once

#include <stdint.h>
#include <limits.h>

#include "qconv.h"
#include "qconv_uint32.h"
#include "qconv_uint64.h"

#define QCONV_INT64_HIGHONES(c) ((qconv_inner_int64)(~(qconv_inner_uint64)0 << (sizeof(qconv_inner_int64)*CHAR_BIT - (c))))
#define QCONV_INT64_HIGHZEROS(c) (~QCONV_INT64_HIGHONES(c))

//Typedef a 64bit signed data type to a project wide inner 64bit representation
typedef int64_t qconv_inner_int64;

//Wrap the inner signed 64bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_int64 qconv_int64;
struct qconv_int64 {
    qconv_inner_int64 value;
};

//Overlay the various signed 64bit struct representation since they share the same inner signed 64bit representation
typedef union qconv_int64_mod qconv_int64_mod;
union qconv_int64_mod {
    qconv_int64 int64;
};

inline int qconv_int64_logshiftr(qconv_inner_int64 x, qconv_inner_uint32 c) {
    return (x >> c) & QCONV_INT64_HIGHZEROS(c);
}

inline int qconv_int64_arishiftr(qconv_inner_int64 x, qconv_inner_uint32 c) {
    return qconv_int64_logshiftr(x, c) ^ (x < 0 ? QCONV_INT64_HIGHONES(c) : 0);
}