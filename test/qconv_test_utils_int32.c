//
// Created by alessandro on 3/8/17.
//

#include <test_qconv_int32_utils.h>

qconv_int32_mod qconv_test_util_naive_power_int32_mod(qconv_int32_mod base, int exp, qconv_int32_mod module) {
    qconv_int32_mod result = {.int32.value = 1};
    for (int i = 0; i < exp; i++) {
        result.int32.value = (result.int32.value * base.int32.value) % module.int32.value;
    }
    return result;
}

void qconv_test_util_poly_mul(unsigned int N,
                              qconv_int32_mod a[static 1],
                              qconv_int32_mod b[static 1],
                              qconv_int32_mod c[N],
                              qconv_int32_mod p) {
    unsigned int i, j, index, mask = N - 1;
    for (i = 0; i < N; i++) {
        c[i].int32.value = 0;
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            index = (i+j) & mask;
            if (i+j >= N) {
                c[index].int32.value = qconv_test_util_reduce(c[index].int32.value - (a[i].int32.value * b[j].int32.value), p.int32.value);
            } else {
                c[index].int32.value = qconv_test_util_reduce(c[index].int32.value + (a[i].int32.value * b[j].int32.value), p.int32.value);
            }
        }
    }
}

// Generating a pseudo-random polynomial a[x] over GF(p)
void qconv_test_util_random_poly(unsigned int N, qconv_int32_mod a[N], unsigned int bit_size) {
    unsigned int mask = ((unsigned int) 1 << bit_size) - 1;
    for (int i = 0; i < N; i++) {
        if (i < N/2) {
            a[i].int32.value = (rand() % mask);
        } else {
            a[i].int32.value = 0;
        }
    }
}

// Comparing two polynomials over GF(p), a[x]=b[x]? : (0) a=b, (1) a!=b
int qconv_test_util_compare_poly(qconv_int32_mod a[static 1], qconv_int32_mod b[static 1], unsigned int N) {
    unsigned int i;

    for (i = 0; i < N; i++) {
        if (a[i].int32.value != b[i].int32.value) {
            printf("Error with %d %d\n", a[i].int32.value, b[i].int32.value);
            return 1;
        }
    }
    return 0;
}

int qconv_test_util_reduce(int a, int p) {
    a %= p;
    if (a < 0) a += p;
    return a;
}