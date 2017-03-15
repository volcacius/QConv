//
// Created by alessandro on 3/3/17.
//

#include "qconv_int32_mod_12289.h"

extern inline void qconv_int32_smul(const size_t size, qconv_int32_mod a[static size], const qconv_int32 scalar);

extern inline qconv_int32_mod_12289 qconv_reduce_mod_12289(const qconv_inner_int64 a);

extern inline qconv_int32_mod_12289 qconv_two_merged_reduce_mod_12289(const qconv_inner_int64 a);

extern inline void qconv_two_reduce_mod_12289(const size_t size, qconv_int32_mod a[static size]);

extern inline void qconv_pmul_mod_12289(const size_t size,
                                        const qconv_int32_mod a[static const size],
                                        const qconv_int32_mod b[static const size],
                                        qconv_int32_mod c[static size]);

extern inline void qconv_pmuladd_mod_12289(const size_t size,
                                           const qconv_int32_mod_12289 a[static const size],
                                           const qconv_int32_mod_12289 b[static const size],
                                           const qconv_int32_mod_12289 c[static const size],
                                           qconv_int32_mod_12289 d[static size]);

extern inline void qconv_correction_mod_12289(const size_t size, qconv_int32_mod a[static size]);

//Declare the useful constants as const structs as well
const qconv_int32_mod qconv_const_12289 = {.mod_12289.value = (qconv_inner_int32) QCONV_12289};

const int32_t mask12 = ((qconv_inner_int64) 1 << 12) - 1;

void qconv_NTT_CT_std2rev_mod_12289(size_t size,
                                    qconv_int32_mod a[static size],
                                    const qconv_inner_int32 psi_rev[static size]) {
    size_t m, i, j, j1, j2, k = size;
    qconv_int32_mod S, U, V;

    for (m = 1; m < 128; m = 2*m) {
        k = k >> 1;
        for (i = 0; i < m; i++) {
            j1 = 2*i*k;
            j2 = j1+k-1;
            S.mod_12289.value = psi_rev[m+i];
            for (j = j1; j <= j2; j++) {
                U.mod_12289.value = a[j].mod_12289.value;
                V.mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[j + k].mod_12289.value * S.mod_12289.value);
                a[j].mod_12289.value = U.mod_12289.value + V.mod_12289.value;
                a[j+k].mod_12289.value = U.mod_12289.value - V.mod_12289.value;
            }
        }
    }

    k = 4;
    for (i = 0; i < 128; i++) {
        j1 = 8*i;
        j2 = j1+3;
        S.mod_12289.value = psi_rev[i+128];
        for (j = j1; j <= j2; j++) {
            U.mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[j].mod_12289.value);
            V.mod_12289 = qconv_two_merged_reduce_mod_12289((qconv_inner_int64) a[j + 4].mod_12289.value * S.mod_12289.value);
            a[j].mod_12289.value = U.mod_12289.value + V.mod_12289.value;
            a[j+4].mod_12289.value = U.mod_12289.value - V.mod_12289.value;
        }
    }

    for (m = 256; m < size; m = 2*m) {
        k = k >> 1;
        for (i = 0; i < m; i++) {
            j1 = 2*i*k;
            j2 = j1+k-1;
            S.mod_12289.value = psi_rev[m+i];
            for (j = j1; j <= j2; j++) {
                U.mod_12289.value = a[j].mod_12289.value;
                V.mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[j + k].mod_12289.value * S.mod_12289.value);
                a[j].mod_12289.value = U.mod_12289.value + V.mod_12289.value;
                a[j+k].mod_12289.value = U.mod_12289.value - V.mod_12289.value;
            }
        }
    }
    return;
}

void qconv_INTT_GS_rev2std_mod_12289 (const size_t size,
                                      qconv_int32_mod a[static size],
                                      const qconv_inner_int32 omegainv_rev[static const size],
                                      const qconv_int32_mod_12289 omegainv1N_rev,
                                      const qconv_int32_mod_12289 Ninv) {
    size_t m, h, i, j, j1, j2, k = 1;
    qconv_int32_mod S, U, V;
    qconv_inner_int64 temp;

    for (m = size; m > 2; m >>= 1) {
        j1 = 0;
        h = m >> 1;
        for (i = 0; i < h; i++) {
            j2 = j1+k-1;
            S.mod_12289.value = omegainv_rev[h+i];
            for (j = j1; j <= j2; j++) {
                U.mod_12289.value = a[j].mod_12289.value;
                V.mod_12289.value = a[j+k].mod_12289.value;
                a[j].mod_12289.value = U.mod_12289.value + V.mod_12289.value;
                temp = (qconv_inner_int64)(U.mod_12289.value - V.mod_12289.value) * S.mod_12289.value;
                if (m == 32) {
                    a[j].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) a[j].mod_12289.value);
                    a[j+k].mod_12289 = qconv_two_merged_reduce_mod_12289(temp);
                } else {
                    a[j+k].mod_12289 = qconv_reduce_mod_12289(temp);
                }
            }
            j1 = j1+2*k;
        }
        k = 2*k;
    }
    for (j = 0; j < k; j++) {
        U.mod_12289.value = a[j].mod_12289.value;
        V.mod_12289.value = a[j+k].mod_12289.value;
        a[j].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) (U.mod_12289.value + V.mod_12289.value) * Ninv.value);
        a[j+k].mod_12289 = qconv_reduce_mod_12289((qconv_inner_int64) (U.mod_12289.value - V.mod_12289.value) * omegainv1N_rev.value);
    }
    return;
}

enum qconv_status qconv_2D_NTT_rc_mod_12289 (size_t size_x,
                                             size_t size_y,
                                             qconv_int32_mod a[static size_x * size_y],
                                             const qconv_inner_int32 psi_rev_x[static const size_x],
                                             const qconv_inner_int32 psi_rev_y[static const size_y]) {

    return status_success;
}

enum qconv_status qconv_2D_INTT_rc_mod_12289 (size_t size_x,
                                              size_t size_y,
                                              qconv_int32_mod a[static size_x * size_y],
                                              const qconv_inner_int32 omegainv_rev_x[static const size_x],
                                              const qconv_inner_int32 omegainv_rev_y[static const size_y],
                                              const qconv_int32 omegainv1N_rev,
                                              const qconv_int32 Ninv) {
    return status_success;
}