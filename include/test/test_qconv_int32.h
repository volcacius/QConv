//
// Created by alessandro on 3/7/17.
//

#pragma once


#include <assert.h>

#include "qconv_int32.h"
#include "LatticeCrypto_priv.h"
#include "test_qconv_int32_utils.h"
#include "qconv_int32_ntt_constants.h"
#include "qconv.h"
#include "time.h"

#define TEST_ITERATIONS 100000

void qconv_test_mul_mod_f_8();

void qconv_test_power_mod_f_8();

void qconv_test_mul_mod_f_8_union();

void qconv_test_mul_mod_m_13();

void qconv_test_power_mod_m_13();

void qconv_test_mul_mod_m_13_union();

void qconv_test_int32_mod_all();
