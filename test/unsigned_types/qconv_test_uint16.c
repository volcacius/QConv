//
// Created by alessandro on 3/7/17.
//

#include "qconv_test_uint16.h"

void qconv_test_mul_mod_f_8() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod_f_8 a = {.value =  (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 b = {.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 correct = {.value = (qconv_inner_uint16) (a.value * b.value % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 test = qconv_mul_uint16_mod_f_8(a, b);
        printf("%d, %d, %d %d\n", a.value, b.value, test.value, correct.value);
        assert(test.value == correct.value);
    }
}

void qconv_test_power_mod_f_8() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod base = {.uint16.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        unsigned int exp = rand() % qconv_const_f_8.mod_f_8.value;
        qconv_uint16_mod correct = qconv_test_util_naive_power_uint16_mod(base, exp, qconv_const_f_8);
        qconv_uint16_mod_f_8 test = qconv_power_uint16_mod_f_8(base.mod_f_8, exp);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_NTT_identity_len_16_mod_f_8() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        unsigned int bit_size = 2;
        qconv_uint16_mod a[QCONV_LEN_16], original[QCONV_LEN_16];
        qconv_test_util_random_uint16_poly(QCONV_LEN_16, a, bit_size);
        for (size_t k = 0; k < QCONV_LEN_16; k++) {
            original[k].mod_f_8.value = a[k].mod_f_8.value;
        }
        qconv_NTT_len_16_mod_f_8(a);
        qconv_INTT_len_16_mod_f_8(a);
        assert(qconv_test_util_compare_uint16_1D_array(QCONV_LEN_16, a, original));
    }
}

void qconv_test_NTT_circular_convolution_len_16_mod_f_8() {
    for (int i = 0; i < 1; i++) {
        unsigned int bit_size = 2;
        qconv_uint16_mod a[QCONV_LEN_16], b[QCONV_LEN_16], ntt[QCONV_LEN_16], poly[QCONV_LEN_16], conv[QCONV_LEN_16];

        //Generate input
        qconv_test_util_random_uint16_poly(QCONV_LEN_16, a, bit_size);
        qconv_test_util_random_uint16_poly(QCONV_LEN_16, b, bit_size);

        //Naive convolution
        qconv_uint16_direct_1D_circular_convolution(QCONV_LEN_16, a, b, conv);
        qconv_test_util_uint16_poly_mul(QCONV_LEN_16, a, b, poly, qconv_const_f_8);

        //NTT of input
        qconv_NTT_len_16_mod_f_8(a);
        qconv_NTT_len_16_mod_f_8(b);

        //Point to point product
        qconv_pmul_mod_f_8(QCONV_LEN_16, a, b, ntt);

        //INTT of output
        qconv_INTT_len_16_mod_f_8(ntt);
        qconv_test_util_compare_uint16_1D_array(QCONV_LEN_16, ntt, conv);
    }
}

void qconv_test_mul_mod_f_8_union() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod a = {.mod_f_8.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod b = {.mod_f_8.value = (qconv_inner_uint16) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod correct = {.mod_f_8.value = (qconv_inner_uint16) (a.mod_f_8.value * b.mod_f_8.value % qconv_const_f_8.mod_f_8.value)};
        qconv_uint16_mod_f_8 test = qconv_mul_uint16_mod_f_8(a.mod_f_8, b.mod_f_8);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_mul_mod_m_13() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod_m_13 a = {.value =  (qconv_inner_uint16) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod_m_13 b = {.value = (qconv_inner_uint16) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod_m_13 correct = {.value = (qconv_inner_uint16) (a.value * b.value % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod_m_13 test = qconv_mul_uint16_mod_m_13(a, b);
        printf("%d, %d, %d %d\n", a.value, b.value, test.value, correct.value);
        assert(test.value == correct.value);
    }
}

void qconv_test_power_mod_m_13() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod base = {.uint16.value = (qconv_inner_uint16) (rand() % qconv_const_m_13.mod_m_13.value)};
        unsigned int exp = rand() % qconv_const_m_13.mod_m_13.value;
        qconv_uint16_mod correct = qconv_test_util_naive_power_uint16_mod(base, exp, qconv_const_m_13);
        qconv_uint16_mod_m_13 test = qconv_power_uint16_mod_m_13(base.mod_m_13, exp);
        assert(test.value == correct.mod_m_13.value);
    }
}

void qconv_test_mul_mod_m_13_union() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint16_mod a = {.mod_m_13.value = (qconv_inner_uint16) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod b = {.mod_m_13.value = (qconv_inner_uint16) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod correct = {.mod_m_13.value = (qconv_inner_uint16) (a.mod_m_13.value * b.mod_m_13.value % qconv_const_m_13.mod_m_13.value)};
        qconv_uint16_mod_m_13 test = qconv_mul_uint16_mod_m_13(a.mod_m_13, b.mod_m_13);
        assert(test.value == correct.mod_m_13.value);
    }
}

void qconv_test_uint16_mod_runall() {
    qconv_test_NTT_circular_convolution_len_16_mod_f_8();
    /*qconv_test_mul_mod_f_8();
    qconv_test_mul_mod_f_8_union();
    qconv_test_mul_mod_m_13();
    qconv_test_mul_mod_m_13_union();
    qconv_test_power_mod_f_8();
    qconv_test_power_mod_m_13();*/
}

