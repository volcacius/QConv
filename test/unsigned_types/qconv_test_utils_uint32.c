//
// Created by alessandro on 3/8/17.
//

#include "qconv_test_utils_uint32.h"

qconv_uint32_mod qconv_test_util_naive_power_uint32_mod(qconv_uint32_mod base, const unsigned int exp, qconv_uint32_mod module) {
    qconv_uint32_mod result = {.uint32.value = 1};
    for (int i = 0; i < exp; i++) {
        qconv_inner_uint64 temp = (qconv_inner_uint64) result.uint32.value * (qconv_inner_uint64) base.uint32.value;
        temp %= module.uint32.value;
        result.uint32.value = (qconv_inner_uint32) temp;
    }
    return result;
}

void qconv_test_util_uint32_poly_mul(const size_t size,
                                     const qconv_uint32_mod a[static const size],
                                     const qconv_uint32_mod b[static const size],
                                     qconv_uint32_mod c[static size],
                                     const qconv_uint32_mod p) {
    size_t i, j, index, mask = size - 1;
    for (i = 0; i < size; i++) {
        c[i].uint32.value = 0;
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            index = (i+j) & mask;
            if (i+j >= size) {
                c[index].uint32.value = qconv_test_util_reduce_inner_uint32(c[index].uint32.value - (a[i].uint32.value * b[j].uint32.value), p.uint32.value);
            } else {
                c[index].uint32.value = qconv_test_util_reduce_inner_uint32(c[index].uint32.value + (a[i].uint32.value * b[j].uint32.value), p.uint32.value);
            }
        }
    }
}

void qconv_test_util_random_uint32_1D_array(const size_t size,
                                            qconv_uint32_mod a[static size],
                                            const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < size; i++) {
        a[i].uint32.value = (qconv_inner_uint32) (rand() % mask);
    }
}

void qconv_test_util_random_zero_padded_uint32_1D_array(const size_t outer_size,
                                                        const size_t inner_size,
                                                        qconv_uint32_mod a[static outer_size],
                                            const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < outer_size; i++) {
        if (i < inner_size) {
            a[i].uint32.value = (qconv_inner_uint32) (rand() % mask);
        } else {
            a[i].uint32.value = 0;
        }
    }
}

void qconv_test_util_max_uint32_1D_array(const size_t size,
                                     qconv_uint32_mod a[static size],
                                     const size_t bit_size) {
    unsigned int mask = (unsigned int) ((1 << bit_size));
    for (int i = 0; i < size; i++) {
        a[i].uint32.value = mask - 1;
    }
}

void qconv_test_util_clone_uint32_1D_array(size_t size,
                                           qconv_uint32_mod source[static size],
                                           qconv_uint32_mod destination[static size]) {
    for (size_t k = 0; k < size; k++) {
        destination[k].uint32.value = source[k].uint32.value;
    }
}

void qconv_test_util_random_uint32_2D_array(const size_t size_x,
                                            const size_t size_y,
                                            qconv_uint32_mod a[size_x * size_y],
                                            const size_t bit_size) {
    qconv_test_util_random_uint32_1D_array(size_x * size_y, a, bit_size);
}


bool qconv_test_util_compare_uint32_2D_array(const size_t size_x,
                                             const size_t size_y,
                                             qconv_uint32_mod a[static size_x * size_y],
                                             qconv_uint32_mod b[static size_x * size_y]) {
    return qconv_test_util_compare_uint32_1D_array(size_x * size_y, a, b);
}

bool qconv_test_util_compare_uint32_1D_array(const size_t size,
                                const qconv_uint32_mod a[static const size],
                                const qconv_uint32_mod b[static const size]) {
    for (size_t i = 0; i < size; i++) {
        printf("%d %d\n", a[i].uint32.value, b[i].uint32.value);
        if (a[i].uint32.value != b[i].uint32.value) {
            printf("Error with %d %d\n", a[i].uint32.value, b[i].uint32.value);
            return false;
        }
    }
    return true;
}

void qconv_test_util_max_uint32_2D_array(const size_t size_width,
                                         const size_t size_height,
                                         qconv_uint32_mod a[static size_width * size_height],
                                         const size_t bit_size) {
    qconv_test_util_max_uint32_1D_array(size_width * size_height, a, bit_size);
}

void qconv_test_util_clone_uint32_2D_array(size_t size_width,
                                           size_t size_height,
                                           qconv_uint32_mod source[static size_width * size_height],
                                           qconv_uint32_mod destination[static size_width * size_height]) {
    qconv_test_util_clone_uint32_1D_array(size_width * size_height, source, destination);
}

qconv_inner_uint32 qconv_test_util_reduce_inner_uint32(qconv_inner_uint32 a, qconv_inner_uint32 p) {
    a %= p;
    if (a < 0) {
        a += p;
    }
    return a;
}