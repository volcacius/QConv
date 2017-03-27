//
// Created by alessandro on 3/11/17.
//

#pragma once

#include <stdint.h>

#include "qconv_int64.h"
#include "qconv_uint32.h"

//Typedef a 64bit unsigned data type to a project wide inner 64bit representation
typedef uint64_t qconv_inner_uint64;

//Wrap the inner unsigned 64bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_uint64 qconv_uint64;
struct qconv_uint64 {
    qconv_inner_uint64 value;
};

//Overlay the various unsigned 64bit struct representation since they share the same inner unsigned 64bit representation
typedef union qconv_uint64_mod qconv_uint64_mod;
union qconv_uint64_mod {
    qconv_uint64 uint64;
};