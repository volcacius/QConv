//
// Created by alessandro on 3/7/17.
//

#pragma once


#include <assert.h>
#include <stdio.h>

#include "qconv_uint16.h"
#include "qconv_uint16_f_8.h"
#include "qconv_uint16_m_13.h"
#include "qconv_test_utils_uint16.h"

#define TEST_ITERATIONS 100000

void qconv_test_mul_mod_f_8();

void qconv_test_power_mod_f_8();

void qconv_test_mul_mod_f_8_union();

void qconv_test_mul_mod_m_13();

void qconv_test_power_mod_m_13();

void qconv_test_mul_mod_m_13_union();

void qconv_test_uint16_mod_runall();
