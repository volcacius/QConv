//
// Created by alessandro on 3/7/17.
//

#pragma once

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "qconv_uint16.h"
#include "qconv_uint16_mod_f_3.h"
#include "qconv_uint16_mod_m_13.h"
#include "qconv_test_utils_uint16.h"
#include "qconv_test_constants.h"

enum qconv_status qconv_test_mul_mod_f_3();

enum qconv_status qconv_test_power_mod_f_3();

enum qconv_status qconv_test_mul_mod_f_3_union();

enum qconv_status qconv_test_NTT_1D_identity_mod_f_3_runall();

enum qconv_status qconv_test_NTT_1D_circular_convolution_mod_f_3_runall();

enum qconv_status qconv_test_NTT_1D_linear_convolution_mod_f_3_runall();

enum qconv_status qconv_test_NTT_2D_identity_mod_f_3_runall();

void qconv_test_uint16_mod_f_3_runall();
