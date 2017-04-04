//
// Created by alessandro on 3/11/17.
//

#pragma once

#include <stdint.h>
#include <limits.h>

#include "qconv_constants.h"

//Typedef a 16bit signed data type to a project wide inner 16bit representation
typedef int16_t qconv_inner_int16;

//Wrap the inner signed 16bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_int16 qconv_int16;
struct qconv_int16 {
    qconv_inner_int16 value;
};

//Overlay the various signed 16bit struct representation since they share the same inner signed 16bit representation
typedef union qconv_int16_mod qconv_int16_mod;
union qconv_int16_mod {
    qconv_int16 int16;
};