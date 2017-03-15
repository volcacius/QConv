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
    qconv_test_mul_mod_f_8();
    qconv_test_mul_mod_f_8_union();
    qconv_test_mul_mod_m_13();
    qconv_test_mul_mod_m_13_union();
    qconv_test_power_mod_f_8();
    qconv_test_power_mod_m_13();
}

