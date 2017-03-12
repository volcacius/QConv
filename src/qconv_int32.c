//
// Created by alessandro on 3/3/17.
//
#include "qconv_int32.h"

extern inline void qconv_int32_smul(const size_t size, qconv_int32_mod a[static size], const qconv_int32 scalar);

extern inline qconv_mod_f_8 qconv_reduce_mod_f_8(qconv_mod_f_8 x);

extern inline qconv_mod_m_13 qconv_reduce_mod_m_13(qconv_mod_m_13 x);

extern inline qconv_mod_f_8 qconv_mul_mod_f_8(const qconv_mod_f_8 x, const qconv_mod_f_8 y);

extern inline qconv_mod_m_13 qconv_mul_mod_m_13(const qconv_mod_m_13 x, const qconv_mod_m_13 y);

extern inline qconv_mod_12289 qconv_reduce_mod_12289(qconv_inner_int64 a);

extern inline qconv_mod_12289 qconv_two_merged_reduce_mod_12289(qconv_inner_int64 a);

extern inline void qconv_two_reduce_mod_12289(const size_t size, qconv_int32_mod a[static size]);

extern inline void qconv_pmul_mod_12289(const size_t size,
                                        const qconv_int32_mod a[static const size],
                                        const qconv_int32_mod b[static const size],
                                        qconv_int32_mod c[static size]);

extern inline void qconv_pmuladd_mod_12289(const size_t size,
                                           const qconv_mod_12289 a[static const size],
                                           const qconv_mod_12289 b[static const size],
                                           const qconv_mod_12289 c[static const size],
                                           qconv_mod_12289 d[static size]);

extern inline void qconv_correction_mod_12289(const size_t size, qconv_int32_mod a[static size]);

//Declare the useful constants as const structs as well
const qconv_int32_mod qconv_const_f_8 = {.mod_f_8.value = QCONV_F_8};
const qconv_int32_mod qconv_const_m_13 = {.mod_m_13.value = QCONV_M_13};
const qconv_int32_mod qconv_const_12289 = {.mod_12289.value = QCONV_12289};

const int32_t mask12 = ((int64_t) 1 << 12) - 1;

qconv_mod_f_8 qconv_power_mod_f_8(qconv_mod_f_8 base, int exp) {
    qconv_mod_f_8 res = {.value = (qconv_inner_int32) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_mod_f_8(res, base);
        }
        base = qconv_mul_mod_f_8(base, base);
        exp /= 2;
    }
    return res;
}

qconv_mod_m_13 qconv_power_mod_m_13(qconv_mod_m_13 base, int exp) {
    qconv_mod_m_13 res = {.value = (qconv_inner_int32) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_mod_m_13(res, base);
        }
        base = qconv_mul_mod_m_13(base, base);
        exp /= 2;
    }
    return res;
}

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
                V.mod_12289 = qconv_reduce_mod_12289((int64_t) a[j + k].mod_12289.value * S.mod_12289.value);
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
            U.mod_12289 = qconv_reduce_mod_12289((int64_t) a[j].mod_12289.value);
            V.mod_12289 = qconv_two_merged_reduce_mod_12289((int64_t) a[j + 4].mod_12289.value * S.mod_12289.value);
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
                V.mod_12289 = qconv_reduce_mod_12289((int64_t) a[j + k].mod_12289.value * S.mod_12289.value);
                a[j].mod_12289.value = U.mod_12289.value + V.mod_12289.value;
                a[j+k].mod_12289.value = U.mod_12289.value - V.mod_12289.value;
            }
        }
    }
    return;
}

void qconv_INTT_GS_rev2std_mod_12289(const size_t size,
                                     qconv_int32_mod a[static size],
                                     const qconv_inner_int32 omegainv_rev[static const size],
                                     const qconv_int32 omegainv1N_rev,
                                     const qconv_int32 Ninv) {
    size_t m, h, i, j, j1, j2, k = 1;
    qconv_int32_mod S, U, V;
    int64_t temp;

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
                temp = (int64_t)(U.mod_12289.value - V.mod_12289.value) * S.mod_12289.value;
                if (m == 32) {
                    a[j].mod_12289 = qconv_reduce_mod_12289((int64_t) a[j].mod_12289.value);
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
        a[j].mod_12289 = qconv_reduce_mod_12289((int64_t) (U.mod_12289.value + V.mod_12289.value) * Ninv.value);
        a[j+k].mod_12289 = qconv_reduce_mod_12289((int64_t) (U.mod_12289.value - V.mod_12289.value) * omegainv1N_rev.value);
    }
    return;
}

enum qconv_status qconv_int32_direct_1D_linear_convolution (
        const size_t input_size,
        const size_t kernel_size,
        const qconv_int32_mod input[static input_size],
        const qconv_int32_mod kernel[static kernel_size],
        qconv_int32_mod output[input_size + kernel_size - 1]) {
    size_t output_size = input_size + kernel_size - 1;
    for (size_t o = 0; o < output_size; o++) {
        output[o].int32.value = 0;
        for (size_t i = 0; i < input_size; i++) {
            int k = (int) (o - i);
            if (k >= 0 && k < kernel_size) {
                output[o].int32.value += input[i].int32.value * kernel[k].int32.value;
            }
        }
    }
    return status_success;
}

enum qconv_status qconv_int32_direct_1D_circular_convolution (
        const size_t size,
        const qconv_int32_mod input[static const size],
        const qconv_int32_mod kernel[static const size],
        qconv_int32_mod output[static size]) {
    for (size_t o = 0; o < size; o++) {
        output[o].int32.value = 0;
        for (size_t i = 0; i < size; i++) {
            int k = (int) (o - i);
            while (k < 0 || k >= size) {
                k += size;
            }
            output[o].int32.value += input[i].int32.value * kernel[k].int32.value;
        }
    }
    return status_success;
}

enum qconv_status qconv_int32_direct_2D_circular_convolution (
        size_t size_x,
        size_t size_y,
        const qconv_int32_mod input[static const size_x][size_y],
        const qconv_int32_mod kernel[static const size_x][size_y],
        qconv_int32_mod output[static size_x][size_y]) {

    for (size_t o_x = 0; o_x < size_x; o_x++) {
        for (size_t o_y = 0; o_y < size_y; o_y++) {
            output[o_x][o_y].int32.value = 0;
            for (int i_x = 0; i_x < size_x; i_x++) {
                for (size_t i_y = 0; i_y < size_y; i_y++) {
                    int k_x = (int) (o_x - i_x);
                    int k_y = (int) (o_y - i_y);
                    while (k_x < 0 || k_x >= size_x) {
                        k_x += size_x;
                    }
                    while (k_y < 0 || k_y >= size_y) {
                        k_y += size_y;
                    }
                    if (k_x >= 0 && k_y >= 0 && k_x < size_x && k_y < size_y) {
                        output[o_x][o_y].int32.value += input[i_x][i_y].int32.value * kernel[i_x][i_y].int32.value;
                    }
                }
            }
        }
    }

    return status_success;
}

enum qconv_status qconv_int32_direct_2D_linear_convolution (
        size_t input_size_x,
        size_t input_size_y,
        size_t kernel_size_x,
        size_t kernel_size_y,
        const qconv_int32_mod input[static const input_size_x][input_size_y],
        const qconv_int32_mod kernel[static const kernel_size_x][kernel_size_y],
        qconv_int32_mod output[static input_size_x + kernel_size_x - 1][input_size_y + kernel_size_y - 1]) {

    size_t output_size_x = input_size_x + kernel_size_x - 1;
    size_t output_size_y = input_size_y + kernel_size_y - 1;

    for (size_t o_x = 0; o_x < output_size_x; o_x++) {
        for (size_t o_y = 0; o_y < output_size_y; o_y++) {
            output[o_x][o_y].int32.value = 0;
            for (int i_x = 0; i_x < input_size_x; i_x++) {
                for (size_t i_y = 0; i_y < input_size_y; i_y++) {
                    int k_x = (int) (o_x - i_x);
                    int k_y = (int) (o_y - i_y);
                    if (k_x >= 0 && k_y >= 0 && k_x < kernel_size_x && k_y < kernel_size_y) {
                        output[o_x][o_y].int32.value += input[i_x][i_y].int32.value * kernel[i_x][i_y].int32.value;
                    }
                }
            }
        }
    }
    return status_success;
}

