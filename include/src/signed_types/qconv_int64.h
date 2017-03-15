//
// Created by alessandro on 3/11/17.
//

#pragma once

#include <stdint.h>

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