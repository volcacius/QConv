//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_m_13.h"

extern inline qconv_uint16_mod_m_13 qconv_reduce_uint32_mod_m_13(qconv_uint32 x);

extern inline qconv_uint16_mod_m_13 qconv_mul_uint16_mod_m_13(const qconv_uint16_mod_m_13 x, const qconv_uint16_mod_m_13 y);

//Declare the useful constants as const structs as well
const qconv_uint16_mod qconv_const_m_13 = {.mod_m_13.value = QCONV_M_13};

qconv_uint16_mod_m_13 qconv_power_uint16_mod_m_13(qconv_uint16_mod_m_13 base, unsigned int exp) {
    qconv_uint16_mod_m_13 res = {.value = (qconv_inner_uint16) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_uint16_mod_m_13(res, base);
        }
        base = qconv_mul_uint16_mod_m_13(base, base);
        exp /= 2;
    }
    return res;
}

/*

 void qconv_NTT_CT_std2rev_mod_m_13 (const size_t size,
                                    qconv_int32_mod a[static size]) {
    size_t m, i, j, istep, mmax;
    qconv_int32_mod w, wt, wr, wtemp;

    w.mod_m_13 = qconv_power_mod_m_13(qconv_const_p_root_m_13.mod_m_13,
                                      (int) ((qconv_const_m_13.mod_m_13.value - 1) / size));
    mmax = 1;
    while (size > mmax) {
        istep = mmax << 1;
        wt.mod_m_13 = qconv_power_mod_m_13(w.mod_m_13, (int) (size / istep));
        wr.mod_m_13 = wt.mod_m_13;

        // Optimize first step when wr = 1
        for (i = 0; i < size; i += istep) {
            j = i + mmax;
            wtemp = a[j];
            a[j].mod_m_13.value = a[i].mod_m_13.value - wtemp.mod_m_13.value;
            a[j].mod_m_13 = qconv_reduce_mod_m_13(a[j].mod_m_13);
            a[i].mod_m_13.value = a[i].mod_m_13.value + wtemp.mod_m_13.value;
            a[i].mod_m_13 = qconv_reduce_mod_m_13(a[i].mod_m_13);
        }

        for (m = 1; m < mmax; m++) {
            for (i = m; i < size; i += istep)
            {
                j = i + mmax;
                wtemp.mod_m_13 = qconv_mul_mod_m_13(wr.mod_m_13, a[j].mod_m_13);
                a[j].mod_m_13.value = a[i].mod_m_13.value - wtemp.mod_m_13.value;
                a[j].mod_m_13 = qconv_reduce_mod_m_13(a[j].mod_m_13);
                a[i].mod_m_13.value = a[i].mod_m_13.value + wtemp.mod_m_13.value;
                a[i].mod_m_13 = qconv_reduce_mod_m_13(a[i].mod_m_13);
            }
            wr.mod_m_13 = qconv_mul_mod_m_13(wr.mod_m_13, wt.mod_m_13);
        }
        mmax = istep;
    }
}

void qconv_INTT_GS_rev2std_mod_m_13 (const size_t size,
                                     qconv_int32_mod a[static size]) {
    size_t m, h, i, j, j1, j2, k = 1;
    qconv_int32_mod S, U, V;
    qconv_inner_int64 temp;

    for (m = size; m > 2; m /= 2) {
        j1 = 0;
        h = m / 2;
        for (i = 0; i < h; i++) {
            j2 = j1 + k - 1;
            S.mod_12289.value = omegainv_rev[h + i];
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

  */