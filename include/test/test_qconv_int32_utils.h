//
// Created by alessandro on 3/8/17.
//

#pragma once

#include "qconv_int32.h"

qconv_int32_mod qconv_test_util_naive_power_int32_mod(qconv_int32_mod base, int exp, qconv_int32_mod module);

/*
 * @brief Polynomial multiplication using the schoolbook method, c[x] = a[x]*b[x]
 */
void qconv_test_util_poly_mul(unsigned int N,
                              qconv_int32_mod a[static 1],
                              qconv_int32_mod b[static 1],
                              qconv_int32_mod c[N],
                              qconv_int32_mod p);

void qconv_test_util_random_poly(unsigned int N,
                                 qconv_int32_mod a[N],
                                 unsigned int bit_size);

int qconv_test_util_compare_poly(qconv_int32_mod a[static 1], qconv_int32_mod b[static 1], unsigned int N);

int qconv_test_util_reduce(int a, int p);

