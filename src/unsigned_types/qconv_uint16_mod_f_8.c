//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_mod_f_8.h"

extern inline qconv_uint16_mod_f_8 qconv_reduce_uint32_mod_f_8(qconv_uint32 x);

extern inline qconv_uint16_mod_f_8 qconv_mul_uint16_mod_f_8(const qconv_uint16_mod_f_8 x, const qconv_uint16_mod_f_8 y);

extern inline qconv_uint16_mod_f_8 qconv_add_uint16_mod_f_8(qconv_uint16_mod_f_8 x, qconv_uint16_mod_f_8 y);

extern inline qconv_uint16_mod_f_8 qconv_subtract_uint16_mod_f_8(qconv_uint16_mod_f_8 x, qconv_uint16_mod_f_8 y);

extern inline qconv_uint16_mod_f_8 qconv_subtract_uint16_mod_f_8(qconv_uint16_mod_f_8 f_8, qconv_uint16_mod_f_8 f8);

extern inline qconv_uint16_mod_f_8 qconv_add_uint16_mod_f_8(qconv_uint16_mod_f_8 f_8, qconv_uint16_mod_f_8 f8);

extern inline void qconv_pmul_mod_f_8(const size_t size,
                                      const qconv_uint16_mod a[static const size],
                                      const qconv_uint16_mod b[static const size],
                                      qconv_uint16_mod c[static size]);

qconv_uint16_mod_f_8 qconv_power_uint16_mod_f_8(qconv_uint16_mod_f_8 base, unsigned int exp) {
    qconv_uint16_mod_f_8 res = {.value = (qconv_inner_uint16) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_uint16_mod_f_8(res, base);
        }
        base = qconv_mul_uint16_mod_f_8(base, base);
        exp /= 2;
    }
    return res;
}

void qconv_INTT_len_norm_mod_f_8(const size_t size, qconv_uint16_mod a[static size]) {
    qconv_uint16_mod to_invert = {.uint16.value = size};
    qconv_uint16_mod_f_8 inv = qconv_inverse_mod_f_8(to_invert);
    for (size_t j = 0; j < size; j++) {
        a[j].mod_f_8 = qconv_mul_uint16_mod_f_8(a[j].mod_f_8, inv);
    }
}

qconv_uint16_mod_f_8 qconv_inverse_mod_f_8(qconv_uint16_mod a) {
    // If a and module are relatively prime, then modulo inverse is a^(m-2) mode m
    return qconv_power_uint16_mod_f_8(a.mod_f_8, (unsigned int) (qconv_const_f_8.mod_f_8.value - 2));
}

void qconv_CT_mod_f_8(size_t size, qconv_uint16_mod a[static size], qconv_uint16_mod p_root, bool inverse) {
    size_t m, i, j, istep, mmax;
    qconv_uint16_mod w, wt, wr, wtemp;
    qconv_bit_reverse_uint16_array_order(size, a);
    if (inverse) {
        w.mod_f_8 = qconv_power_uint16_mod_f_8(p_root.mod_f_8,
                                              qconv_const_f_8.mod_f_8.value - 1 - ((qconv_const_f_8.mod_f_8.value - 1) / size));
    } else {
        w.mod_f_8 = qconv_power_uint16_mod_f_8(p_root.mod_f_8,
                                              ((qconv_const_f_8.mod_f_8.value - 1) / size));
    }
    mmax = 1;
    while (size > mmax) {
        istep = mmax << 1;
        wt.mod_f_8 = qconv_power_uint16_mod_f_8(w.mod_f_8, (size / istep));
        wr.mod_f_8 = wt.mod_f_8;

        // Optimize first step when wr = 1
        for (i = 0; i < size; i += istep) {
            j = i + mmax;
            wtemp = a[j];
            a[j].mod_f_8 = qconv_subtract_uint16_mod_f_8(a[i].mod_f_8, a[j].mod_f_8);
            a[i].mod_f_8 = qconv_add_uint16_mod_f_8(a[i].mod_f_8, wtemp.mod_f_8);
        }

        for (m = 1; m < mmax; m++) {
            for (i = m; i < size; i += istep) {
                j = i + mmax;
                wtemp.mod_f_8 = qconv_mul_uint16_mod_f_8(wr.mod_f_8, a[j].mod_f_8);
                a[j].mod_f_8 = qconv_subtract_uint16_mod_f_8(a[i].mod_f_8, wtemp.mod_f_8);
                a[i].mod_f_8= qconv_add_uint16_mod_f_8(a[i].mod_f_8, wtemp.mod_f_8);
            }
            wr.mod_f_8 = qconv_mul_uint16_mod_f_8(wr.mod_f_8, wt.mod_f_8);
        }
        mmax = istep;
    }
}

enum qconv_status qconv_NTT_mod_f_8(const size_t size, qconv_uint16_mod a[static size]) {
    switch(size) {
        case QCONV_LEN_8:
            qconv_CT_mod_f_8(QCONV_LEN_8, a, qconv_const_p_root_f_8_len_up_to_16, false);
            return status_success;
        case QCONV_LEN_16:
            qconv_CT_mod_f_8(QCONV_LEN_16, a, qconv_const_p_root_f_8_len_up_to_16, false);
            return status_success;
        case QCONV_LEN_32:
            qconv_CT_mod_f_8(QCONV_LEN_32, a, qconv_const_p_root_f_8_len_up_to_256, false);
            return status_success;
        case QCONV_LEN_64:
            qconv_CT_mod_f_8(QCONV_LEN_64, a, qconv_const_p_root_f_8_len_up_to_256, false);
            return status_success;
        case QCONV_LEN_128:
            qconv_CT_mod_f_8(QCONV_LEN_128, a, qconv_const_p_root_f_8_len_up_to_256, false);
            return status_success;
        case QCONV_LEN_256:
            qconv_CT_mod_f_8(QCONV_LEN_256, a, qconv_const_p_root_f_8_len_up_to_256, false);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_mod_f_8(const size_t size, qconv_uint16_mod a[static size]) {
    switch(size) {
        case QCONV_LEN_8:
            qconv_CT_mod_f_8(QCONV_LEN_8, a, qconv_const_p_root_f_8_len_up_to_16, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_8, a);
            return status_success;
        case QCONV_LEN_16:
            qconv_CT_mod_f_8(QCONV_LEN_16, a, qconv_const_p_root_f_8_len_up_to_16, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_16, a);
            return status_success;
        case QCONV_LEN_32:
            qconv_CT_mod_f_8(QCONV_LEN_32, a, qconv_const_p_root_f_8_len_up_to_256, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_32, a);
            return status_success;
        case QCONV_LEN_64:
            qconv_CT_mod_f_8(QCONV_LEN_64, a, qconv_const_p_root_f_8_len_up_to_256, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_64, a);
            return status_success;
        case QCONV_LEN_128:
            qconv_CT_mod_f_8(QCONV_LEN_128, a, qconv_const_p_root_f_8_len_up_to_256, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_128, a);
            return status_success;
        case QCONV_LEN_256:
            qconv_CT_mod_f_8(QCONV_LEN_256, a, qconv_const_p_root_f_8_len_up_to_256, true);
            qconv_INTT_len_norm_mod_f_8(QCONV_LEN_256, a);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_1D_circular_convolution_uint16_mod_f_8(size_t size,
                                                                   qconv_uint16_mod a[static size],
                                                                   qconv_uint16_mod b[static size],
                                                                   qconv_uint16_mod ntt[size]) {
    enum qconv_status status;
    status = qconv_NTT_mod_f_8(size, a);
    CHECK_STATUS(status);
    status = qconv_NTT_mod_f_8(size, b);
    CHECK_STATUS(status);
    qconv_pmul_mod_f_8(size, a, b, ntt);
    status = qconv_INTT_mod_f_8(size, ntt);
    return status;
}

enum qconv_status qconv_NTT_1D_linear_convolution_uint16_mod_f_8(size_t input_size,
                                                                 size_t kernel_size,
                                                                 qconv_uint16_mod input[static input_size],
                                                                 qconv_uint16_mod kernel[static kernel_size],
                                                                 qconv_uint16_mod ntt[static input_size + kernel_size - 1]) {
    enum qconv_status status;
    size_t size;
    if (input_size >= kernel_size) {
        size = input_size * 2;
    } else {
        size = kernel_size * 2;
    }
    qconv_uint16_mod input_padded[size];
    qconv_uint16_mod kernel_padded[size];
    qconv_uint16_mod ntt_padded[size];
    status = qconv_zero_pad_uint16_1D_array(size, input_size, input, input_padded);
    CHECK_STATUS(status);
    status = qconv_zero_pad_uint16_1D_array(size, kernel_size, kernel, kernel_padded);
    CHECK_STATUS(status);
    status = qconv_NTT_mod_f_8(size, input_padded);
    CHECK_STATUS(status);
    status = qconv_NTT_mod_f_8(size, kernel_padded);
    CHECK_STATUS(status);
    qconv_pmul_mod_f_8(size, input_padded, kernel_padded, ntt_padded);
    status = qconv_INTT_mod_f_8(size, ntt_padded);
    CHECK_STATUS(status);
    status = qconv_slice_uint16_1D_array(size, input_size + kernel_size - 1, 0, ntt_padded, ntt);
    return status;
}



