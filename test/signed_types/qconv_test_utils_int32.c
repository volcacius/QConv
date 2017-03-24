//
// Created by alessandro on 3/8/17.
//

#include "qconv_test_utils_int32.h"

qconv_int32_mod qconv_test_util_naive_power_int32_mod(qconv_int32_mod base, const unsigned int exp, qconv_int32_mod module) {
    qconv_int32_mod result = {.int32.value = 1};
    for (int i = 0; i < exp; i++) {
        result.int32.value = (result.int32.value * base.int32.value) % module.int32.value;
    }
    return result;
}

void qconv_test_util_poly_mul(const size_t size,
                              const qconv_int32_mod a[static const size],
                              const qconv_int32_mod b[static const size],
                              qconv_int32_mod c[static size],
                              const qconv_int32_mod p) {
    size_t i, j, index, mask = size - 1;
    for (i = 0; i < size; i++) {
        c[i].int32.value = 0;
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            index = (i+j) & mask;
            if (i+j >= size) {
                c[index].int32.value = qconv_test_util_reduce(c[index].int32.value - (a[i].int32.value * b[j].int32.value), p.int32.value);
            } else {
                c[index].int32.value = qconv_test_util_reduce(c[index].int32.value + (a[i].int32.value * b[j].int32.value), p.int32.value);
            }
        }
    }
}

void qconv_test_util_random_poly(const size_t size,
                                 qconv_int32_mod a[static size],
                                 const size_t bit_size) {
    unsigned int mask = ((unsigned int) 1 << bit_size) - 1;
    for (int i = 0; i < size; i++) {
        a[i].int32.value = 0;
    }
}

void qconv_test_util_random_int32_2D_array(const size_t size_x,
                                           const size_t size_y,
                                           qconv_int32_mod a[size_x][size_y],
                                           const size_t bit_size) {
    unsigned int mask = ((unsigned int) 1 << bit_size) - 1;
    for (size_t i = 0; i < size_x; i++) {
       for (size_t j = 0; j < size_y; j++) {
           if (i < size_x/2 && j < size_y/2) {
               a[i][j].int32.value = (rand() % mask);
           } else {
               a[i][j].int32.value = 0;
           }
       }
    }
}

bool qconv_test_util_compare_1D(const size_t size,
                                const qconv_int32_mod a[static const size],
                                const qconv_int32_mod b[static const size]) {
    for (size_t i = 0; i < size; i++) {
        if (a[i].int32.value != b[i].int32.value) {
            printf("Error with %d %d\n", a[i].int32.value, b[i].int32.value);
            return false;
        }
    }
    return true;
}