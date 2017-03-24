//
// Created by alessandro on 3/8/17.
//

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "qconv_int32.h"

qconv_int32_mod qconv_test_util_naive_power_int32_mod(const qconv_int32_mod base,
                                                      const unsigned int exp,
                                                      const qconv_int32_mod module);

/*
 * @brief Polynomial multiplication using the schoolbook method, c[x] = a[x]*b[x]
 */
void qconv_test_util_poly_mul(const size_t size,
                              const qconv_int32_mod a[static const size],
                              const qconv_int32_mod b[static const size],
                              qconv_int32_mod c[static size],
                              const qconv_int32_mod p);

void qconv_test_util_random_poly(size_t size,
                                 qconv_int32_mod a[static size],
                                 size_t bit_size);

bool qconv_test_util_compare_1D(const size_t size,
                                const qconv_int32_mod a[static const size],
                                const qconv_int32_mod b[static const size]);

void qconv_test_util_random_int32_2D_array(const size_t size_x,
                                           const size_t size_y,
                                           qconv_int32_mod a[static size_x][size_y],
                                           const size_t bit_size);

