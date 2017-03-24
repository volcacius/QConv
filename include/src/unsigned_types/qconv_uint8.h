//
// Created by alessandro on 3/11/17.
//

#pragma once

#include <stdint.h>

#include "qconv.h"

//Typedef a 64bit unsigned data type to a project wide inner 64bit representation
typedef uint8_t qconv_inner_uint8;

//Wrap the inner unsigned 64bit representation inside a struct (which carries no overhead) to enforce strong typing at compile time
typedef struct qconv_uint8 qconv_uint8;
struct qconv_uint8 {
    qconv_inner_uint8 value;
};

//Define all the uint8 structs in the same header to avoid circular dependencies
typedef struct qconv_uint8_mod_m_8 qconv_uint8_mod_m_8;
struct qconv_uint8_mod_m_8 {
    qconv_inner_uint8 value;
};

//Overlay the various unsigned 64bit struct representation since they share the same inner unsigned 64bit representation
typedef union qconv_uint8_mod qconv_uint8_mod;
union qconv_uint8_mod {
    qconv_uint8_mod_m_8 mod_m_8;
    qconv_uint8 uint8;
};