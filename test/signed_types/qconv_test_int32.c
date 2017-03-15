//
// Created by alessandro on 3/7/17.
//

#include "qconv_test_int32.h"

void qconv_test_ntt_12289() {
    for (int k = 0; k < TEST_ITERATIONS; k++) {
        qconv_int32_mod a[PARAMETER_N], b[PARAMETER_N], c[PARAMETER_N], d[PARAMETER_N], e[PARAMETER_N];
        unsigned int bit_size = 3;

        //generate input and kernel
        qconv_test_util_random_poly(PARAMETER_N, a, bit_size);
        qconv_test_util_random_poly(PARAMETER_N, b, bit_size);

        //direct convolution
        float direct_start_time = (float) clock() / CLOCKS_PER_SEC;
        qconv_int32_direct_1D_circular_convolution(PARAMETER_N, a, b, c);
        float direct_end_time = (float) clock() / CLOCKS_PER_SEC;
        float direct_time = direct_end_time - direct_start_time;

        //schoolbook convolution
        float school_start_time = (float) clock() / CLOCKS_PER_SEC;
        qconv_test_util_poly_mul(PARAMETER_N, a, b, e, qconv_const_12289);
        float school_end_time = (float) clock() / CLOCKS_PER_SEC;
        float school_time = school_end_time - school_start_time;

        //ntt convolution
        float ntt_start_time = (float) clock() / CLOCKS_PER_SEC;
        qconv_NTT_CT_std2rev_mod_12289(PARAMETER_N, a, psi_rev_ntt1024_12289);
        qconv_NTT_CT_std2rev_mod_12289(PARAMETER_N, b, psi_rev_ntt1024_12289);
        qconv_pmul_mod_12289(PARAMETER_N, a, b, d);
        qconv_correction_mod_12289(PARAMETER_N, d);
        qconv_INTT_GS_rev2std_mod_12289(PARAMETER_N,
                                        d,
                                        omegainv_rev_ntt1024_12289,
                                        omegainv7N_rev_ntt1024_12289,
                                        Ninv8_ntt1024_12289);
        qconv_two_reduce_mod_12289(PARAMETER_N, d);
        qconv_correction_mod_12289(PARAMETER_N, d);
        float ntt_end_time = (float) clock() / CLOCKS_PER_SEC;
        float ntt_time = ntt_end_time - ntt_start_time;

        printf("Direct: %fs, Schoolbook: %fs, NTT %fs, Speed ratio over direct: %f, Speed ratio over Schoolbook: %f\n",
               direct_time, school_time, ntt_time, direct_time/ntt_time, school_time/ntt_time);

        assert(qconv_test_util_compare_1D(PARAMETER_N, c, d));
        assert(qconv_test_util_compare_1D(PARAMETER_N, d, e));
    }

}

void qconv_test_ntt_identity_12289() {
    for (int k = 0; k < TEST_ITERATIONS; k++) {
        qconv_int32_mod a[PARAMETER_N], c[PARAMETER_N];
        unsigned int bit_size = 3;

        //generate input
        qconv_test_util_random_poly(PARAMETER_N, a, bit_size);
        for (size_t i = 0; i < PARAMETER_N; i++) {
            c[i].int32.value = a[i].int32.value;
        }

        qconv_NTT_CT_std2rev_mod_12289(PARAMETER_N, a, psi_rev_ntt1024_12289);

        for (size_t i = 0; i < PARAMETER_N; i++) {
            a[i].mod_12289 = qconv_reduce_mod_12289((int64_t) a[i].mod_12289.value);
            a[i].mod_12289 = qconv_reduce_mod_12289((int64_t) a[i].mod_12289.value);
        }
        qconv_correction_mod_12289(PARAMETER_N, a);
        qconv_INTT_GS_rev2std_mod_12289(PARAMETER_N,
                                        a,
                                        omegainv_rev_ntt1024_12289,
                                        omegainv7N_rev_ntt1024_12289,
                                        Ninv8_ntt1024_12289);
        qconv_two_reduce_mod_12289(PARAMETER_N, a);
        qconv_two_reduce_mod_12289(PARAMETER_N, a);
        for (size_t i = 0; i < PARAMETER_N; i++) {
            a[i].mod_12289.value /= 3;
        }
        assert(qconv_test_util_compare_1D(PARAMETER_N, a, c));
    }

}

void qconv_test_ntt_identity_12289_2D() {
    for (int k = 0; k < 1; k++) {
        qconv_int32_mod* a = malloc(PARAMETER_N * PARAMETER_N * sizeof(qconv_int32_mod));
        qconv_int32_mod* c = malloc(PARAMETER_N * PARAMETER_N * sizeof(qconv_int32_mod));
        unsigned int bit_size = 2;

        //generate input
        qconv_test_util_random_poly(PARAMETER_N * PARAMETER_N, a, bit_size);
        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                c[i * PARAMETER_N + j].int32.value = a[i * PARAMETER_N + j].int32.value;
            }
        }

        //Transform rows
        for (size_t i = 0; i < PARAMETER_N; i++) {
            qconv_NTT_CT_std2rev_mod_12289(PARAMETER_N, &a[i * PARAMETER_N], psi_rev_ntt1024_12289);
            qconv_two_reduce_mod_12289(PARAMETER_N, &a[i * PARAMETER_N]);
        }
/*
        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                printf("Transformed rows %d\n", a[i * PARAMETER_N + j].int32.value);
            }
        }
*/
        //Transpose and transform columns
        qconv_int32_mod* a_transpose = malloc(PARAMETER_N * PARAMETER_N * sizeof(qconv_int32_mod));
        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                a_transpose[i] = a[j * PARAMETER_N + i];
                //printf("Transposed rows %d\n", a[j * PARAMETER_N + i].int32.value);
            }
            qconv_NTT_CT_std2rev_mod_12289(PARAMETER_N, &a_transpose[i * PARAMETER_N], psi_rev_ntt1024_12289);
            qconv_two_reduce_mod_12289(PARAMETER_N, &a_transpose[i * PARAMETER_N]);
        }

        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                printf("Transformed columns %d\n", a_transpose[i * PARAMETER_N + j].int32.value);
            }
        }

        free(a);

        //Antitransform columns
        for (size_t i = 0; i < PARAMETER_N; i++) {
            qconv_INTT_GS_rev2std_mod_12289(PARAMETER_N, &a_transpose[i * PARAMETER_N], omegainv_rev_ntt1024_12289, omegainv7N_rev_ntt1024_12289, Ninv8_ntt1024_12289);
            qconv_two_reduce_mod_12289(PARAMETER_N, &a_transpose[i * PARAMETER_N]);
        }

        a = malloc(PARAMETER_N * PARAMETER_N * sizeof(qconv_int32_mod));

        //Transpose and antitransform rows
        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                a[i] = a_transpose[j * PARAMETER_N + i];
            }
            qconv_INTT_GS_rev2std_mod_12289(PARAMETER_N, &a[i * PARAMETER_N], omegainv_rev_ntt1024_12289, omegainv7N_rev_ntt1024_12289, Ninv8_ntt1024_12289);
            qconv_two_reduce_mod_12289(PARAMETER_N, &a[i * PARAMETER_N]);
        }

        for (size_t i = 0; i < PARAMETER_N; i++) {
            for (size_t j = 0; j < PARAMETER_N; j++) {
                printf("%d %d\n", a[i * PARAMETER_N + j].int32.value, c[i * PARAMETER_N + j].int32.value);
            }
        }
        //assert(qconv_test_util_compare_1D(PARAMETER_N, a, c));
        free(a);
        free(c);
    }

}

void qconv_test_int32_mod_runall() {
   qconv_test_ntt_identity_12289_2D();
}

