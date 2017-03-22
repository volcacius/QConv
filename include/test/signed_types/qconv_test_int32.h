//
// Created by alessandro on 3/7/17.
//

#pragma once


#include <assert.h>
#include <stdio.h>

#include "qconv_int32.h"
#include "qconv_test_utils_int32.h"
#include "qconv_int32_mod_12289.h"
#include "qconv_int32_mod_12289_constants.h"
#include "qconv.h"
#include "time.h"

void qconv_test_ntt_identity_12289();

void qconv_test_ntt_identity_12289_2D();

void qconv_test_int32_mod_runall();