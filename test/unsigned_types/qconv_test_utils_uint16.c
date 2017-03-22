//
// Created by alessandro on 3/8/17.
//

#include "qconv_test_utils_uint16.h"

qconv_uint16_mod qconv_test_util_naive_power_uint16_mod(qconv_uint16_mod base, const unsigned int exp, qconv_uint16_mod module) {
    qconv_uint16_mod result = {.uint16.value = 1};
    for (int i = 0; i < exp; i++) {
        result.uint16.value = (result.uint16.value * base.uint16.value) % module.uint16.value;
    }
    return result;
}

void qconv_test_util_uint16_poly_mul(const size_t size,
                                     const qconv_uint16_mod a[static const size],
                                     const qconv_uint16_mod b[static const size],
                                     qconv_uint16_mod c[static size],
                                     const qconv_uint16_mod p) {
    size_t i, j, index, mask = size - 1;
    for (i = 0; i < size; i++) {
        c[i].uint16.value = 0;
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            index = (i+j) & mask;
            if (i+j >= size) {
                c[index].uint16.value = qconv_test_util_reduce_inner_uint16(c[index].uint16.value - (a[i].uint16.value * b[j].uint16.value), p.uint16.value);
            } else {
                c[index].uint16.value = qconv_test_util_reduce_inner_uint16(c[index].uint16.value + (a[i].uint16.value * b[j].uint16.value), p.uint16.value);
            }
        }
    }
}

void qconv_test_util_random_uint16_1D_array(const size_t size,
                                 qconv_uint16_mod a[static size],
                                 const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < size; i++) {
        a[i].uint16.value = (qconv_inner_uint16) (rand() % mask);
    }
}

void qconv_test_util_random_zero_padded_uint16_1D_array(const size_t outer_size,
                                                        const size_t inner_size,
                                                        qconv_uint16_mod a[static outer_size],
                                            const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < outer_size; i++) {
        if (i < inner_size) {
            a[i].uint16.value = (qconv_inner_uint16) (rand() % mask);
        } else {
            a[i].uint16.value = 0;
        }
    }
}

void qconv_test_util_max_uint16_1D_array(const size_t size,
                                     qconv_uint16_mod a[static size],
                                     const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < size; i++) {
        a[i].uint16.value = mask - 1;
    }
}

void qconv_test_util_clone_uint16_1D_array(size_t size,
                                           qconv_uint16_mod source[static size],
                                           qconv_uint16_mod destination[static size]) {
    for (size_t k = 0; k < size; k++) {
        destination[k].uint16.value = source[k].uint16.value;
    }
}

void qconv_test_util_random_uint16_2D_array(const size_t size_x,
                                           const size_t size_y,
                                           qconv_uint16_mod a[size_x * size_y],
                                           const size_t bit_size) {
    unsigned int mask = (unsigned int) 1 << bit_size;
    for (size_t i = 0; i < size_x; i++) {
       for (size_t j = 0; j < size_y; j++) {
           a[i * size_x + j].uint16.value = (rand() % mask);
       }
    }
}

bool qconv_test_util_compare_uint16_2D_array(const size_t size_x,
                                             const size_t size_y,
                                             qconv_uint16_mod a[static size_x * size_y],
                                             qconv_uint16_mod b[static size_x * size_y]) {
    for (size_t i = 0; i < size_x; i++) {
        for (size_t j = 0; j < size_y; j++) {
            if (a[i * size_x + j].uint16.value != b[i * size_x + j].uint16.value) {
                printf("Error with %d %d\n", a[i * size_x + j].uint16.value, b[i * size_x + j].uint16.value);
                return false;
            }
        }
    }
    return true;
}

bool qconv_test_util_compare_uint16_1D_array(const size_t size,
                                const qconv_uint16_mod a[static const size],
                                const qconv_uint16_mod b[static const size]) {
    for (size_t i = 0; i < size; i++) {
        //printf("%d %d\n", a[i].uint16.value, b[i].uint16.value);
        if (a[i].uint16.value != b[i].uint16.value) {
            printf("Error with %d %d\n", a[i].uint16.value, b[i].uint16.value);
            return false;
        }
    }
    return true;
}

qconv_inner_uint16 qconv_test_util_reduce_inner_uint16(qconv_inner_uint16 a, qconv_inner_uint16 p) {
    a %= p;
    if (a < 0) {
        a += p;
    }
    return a;
}