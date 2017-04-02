//
// Created by alessandro on 3/8/17.
//

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "qconv_uint32.h"
#include "qconv_uint32_mod_f_4.h"

qconv_uint32_mod qconv_test_util_naive_power_uint32_mod(const qconv_uint32_mod base,
                                                        const unsigned int exp,
                                                        const qconv_uint32_mod module);

/*
 * @brief Polynomial multiplication using the schoolbook method, c[x] = a[x]*b[x]
 */
void qconv_test_util_uint32_poly_mul(const size_t size,
                                     const qconv_uint32_mod a[static const size],
                                     const qconv_uint32_mod b[static const size],
                                     qconv_uint32_mod c[static size],
                                     const qconv_uint32_mod p);

void qconv_test_util_max_uint32_1D_array(const size_t size,
                                         qconv_uint32_mod a[static size],
                                         const size_t bit_size);

void qconv_test_util_random_uint32_1D_array(const size_t size,
                                            qconv_uint32_mod a[static size],
                                            const size_t bit_size);

bool qconv_test_util_compare_uint32_1D_array(const size_t size,
                                             const qconv_uint32_mod a[static const size],
                                             const qconv_uint32_mod b[static const size]);

void qconv_test_util_random_uint32_2D_array(const size_t size_x,
                                            const size_t size_y,
                                            qconv_uint32_mod a[static size_x * size_y],
                                            const size_t bit_size);

bool qconv_test_util_compare_uint32_2D_array(const size_t size_x,
                                             const size_t size_y,
                                             qconv_uint32_mod a[static size_x * size_y],
                                             qconv_uint32_mod b[static size_x * size_y]);

void qconv_test_util_max_uint32_2D_array(const size_t size_width,
                                         const size_t size_height,
                                         qconv_uint32_mod a[static size_width * size_height],
                                         const size_t bit_size);

qconv_inner_uint32 qconv_test_util_reduce_inner_uint32(qconv_inner_uint32 a, const qconv_inner_uint32 p);

