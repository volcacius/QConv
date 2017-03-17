//
// Created by alessandro on 3/8/17.
//

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "qconv_uint16.h"
#include "qconv_uint16_f_8.h"

qconv_uint16_mod qconv_test_util_naive_power_uint16_mod(const qconv_uint16_mod base, const unsigned int exp, const qconv_uint16_mod module);

/*
 * @brief Polynomial multiplication using the schoolbook method, c[x] = a[x]*b[x]
 */
void qconv_test_util_uint16_poly_mul(const size_t size,
                                     const qconv_uint16_mod a[static const size],
                                     const qconv_uint16_mod b[static const size],
                                     qconv_uint16_mod c[static size],
                                     const qconv_uint16_mod p);

void qconv_test_util_random_uint16_poly(size_t size,
                                        qconv_uint16_mod a[static size],
                                        size_t bit_size);

bool qconv_test_util_compare_uint16_1D_array(const size_t size,
                                const qconv_uint16_mod a[static const size],
                                const qconv_uint16_mod b[static const size]);

void qconv_test_util_random_uint16_2D_array(const size_t size_x,
                                           const size_t size_y,
                                           qconv_uint16_mod a[static size_x][size_y],
                                           const size_t bit_size);

qconv_inner_uint16 qconv_test_util_reduce_inner_uint16(qconv_inner_uint16 a, const qconv_inner_uint16 p);

