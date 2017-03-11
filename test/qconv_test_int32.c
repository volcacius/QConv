//
// Created by alessandro on 3/7/17.
//

#include <test_qconv_int32.h>

void qconv_test_mul_mod_f_8() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_mod_f_8 a = {.value =  (qconv_inner_int32) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_mod_f_8 b = {.value = (qconv_inner_int32) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_mod_f_8 correct = {.value = (qconv_inner_int32) (a.value * b.value % qconv_const_f_8.mod_f_8.value)};
        qconv_mod_f_8 test = qconv_mul_mod_f_8(a, b);
        assert(test.value == correct.value);
    }
}

void qconv_test_power_mod_f_8() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_int32_mod base = {.int32.value = (qconv_inner_int32) (rand() % qconv_const_f_8.mod_f_8.value)};
        int exp = rand() % qconv_const_f_8.mod_f_8.value;
        qconv_int32_mod correct = qconv_test_util_naive_power_int32_mod(base, exp, qconv_const_f_8);
        qconv_mod_f_8 test = qconv_power_mod_f_8(base.mod_f_8, exp);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_mul_mod_f_8_union() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_int32_mod a = {.mod_f_8.value = (qconv_inner_int32) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_int32_mod b = {.mod_f_8.value = (qconv_inner_int32) (rand() % qconv_const_f_8.mod_f_8.value)};
        qconv_int32_mod correct = {.mod_f_8.value = (qconv_inner_int32) (a.mod_f_8.value * b.mod_f_8.value % qconv_const_f_8.mod_f_8.value)};
        qconv_mod_f_8 test = qconv_mul_mod_f_8(a.mod_f_8, b.mod_f_8);
        assert(test.value == correct.mod_f_8.value);
    }
}

void qconv_test_mul_mod_m_13() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_mod_m_13 a = {.value =  (qconv_inner_int32) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_mod_m_13 b = {.value = (qconv_inner_int32) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_mod_m_13 correct = {.value = (qconv_inner_int32) (a.value * b.value % qconv_const_m_13.mod_m_13.value)};
        qconv_mod_m_13 test = qconv_mul_mod_m_13(a, b);
        assert(test.value == correct.value);
    }
}

void qconv_test_power_mod_m_13() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_int32_mod base = {.int32.value = (qconv_inner_int32) (rand() % qconv_const_m_13.mod_m_13.value)};
        int exp = rand() % qconv_const_m_13.mod_m_13.value;
        qconv_int32_mod correct = qconv_test_util_naive_power_int32_mod(base, exp, qconv_const_m_13);
        qconv_mod_m_13 test = qconv_power_mod_m_13(base.mod_m_13, exp);
        assert(test.value == correct.mod_m_13.value);
    }
}

void qconv_test_mul_mod_m_13_union() {
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_int32_mod a = {.mod_m_13.value = (qconv_inner_int32) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_int32_mod b = {.mod_m_13.value = (qconv_inner_int32) (rand() % qconv_const_m_13.mod_m_13.value)};
        qconv_int32_mod correct = {.mod_m_13.value = (qconv_inner_int32) (a.mod_m_13.value * b.mod_m_13.value % qconv_const_m_13.mod_m_13.value)};
        qconv_mod_m_13 test = qconv_mul_mod_m_13(a.mod_m_13, b.mod_m_13);
        assert(test.value == correct.mod_m_13.value);
    }
}

void qconv_test_ntt_12289() {
    for (int k = 0; k < 1000; k++) {
        qconv_int32_mod a[PARAMETER_N], b[PARAMETER_N], c[PARAMETER_N], d[PARAMETER_N], e[PARAMETER_N];
        unsigned int bit_size = 2;

        qconv_test_util_random_poly(PARAMETER_N, a, bit_size);
        qconv_test_util_random_poly(PARAMETER_N, b, bit_size);
        qconv_int32_direct_1D_circular_convolution(PARAMETER_N, a, b, c);
        qconv_test_util_poly_mul(PARAMETER_N, a, b, e, qconv_const_12289);

        qconv_NTT_CT_std2rev_mod_12289(a, psi_rev_ntt1024_12289, PARAMETER_N);
        qconv_NTT_CT_std2rev_mod_12289(b, psi_rev_ntt1024_12289, PARAMETER_N);
        qconv_pmul_mod_12289(a, b, d, PARAMETER_N);
        qconv_correction_mod_12289(d, PARAMETER_N);

        qconv_INTT_GS_rev2std_mod_12289(d, omegainv_rev_ntt1024_12289, omegainv7N_rev_ntt1024_12289.int32, Ninv8_ntt1024_12289.int32, PARAMETER_N);
        qconv_two_reduce_mod_12289(d, PARAMETER_N);
        qconv_correction_mod_12289(d, PARAMETER_N);

        assert(qconv_test_util_compare_poly(c, e, PARAMETER_N) == 0);
    }

}

void qconv_test_int32_mod_all() {
    qconv_test_ntt_12289();
}

