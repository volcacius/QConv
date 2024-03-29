//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint16_mod_f_3.h"

extern inline qconv_uint16_mod_f_3 qconv_mul_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_add_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_subtract_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_subtract_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_add_uint16_mod_f_3(qconv_uint16_mod_f_3 x, qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_reduce_uint32_mod_f_3(qconv_inner_uint32 x);

extern inline qconv_uint16_mod_f_3 qconv_forward_shift_uint16_mod_f_3(const qconv_uint16_mod_f_3 x,
                                                                      const qconv_uint16_mod_f_3 y);

extern inline qconv_uint16_mod_f_3 qconv_inverse_shift_uint16_mod_f_3(const qconv_uint16_mod_f_3 x,
                                                                      const qconv_uint16_mod_f_3 y);

extern inline void qconv_pmul_mod_f_3(const size_t size,
                                      const qconv_uint16_mod a[static const size],
                                      const qconv_uint16_mod b[static const size],
                                      qconv_uint16_mod c[static size]);

qconv_uint16_mod_f_3 qconv_power_uint16_mod_f_3(qconv_uint16_mod_f_3 base, unsigned int exp) {
    qconv_uint16_mod_f_3 res = {.value = (qconv_inner_uint16) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_uint16_mod_f_3(res, base);
        }
        base = qconv_mul_uint16_mod_f_3(base, base);
        exp /= 2;
    }
    return res;
}

void qconv_INTT_1D_size_norm_uint16_mod_f_3(const size_t size, qconv_uint16_mod a[static size]) {
    qconv_uint16_mod to_invert = {.uint16.value = size};
    qconv_uint16_mod_f_3 inv = qconv_inverse_uint16_mod_f_3(to_invert);

    for (size_t j = 0; j < size; j++) {
        a[j].mod_f_3 = qconv_mul_uint16_mod_f_3(a[j].mod_f_3, inv);
    }
}

void qconv_INTT_2D_size_norm_precomp_uint16_mod_f_3(const size_t size_width,
                                                    const size_t size_height,
                                                    qconv_uint16_mod_f_3 norm_const,
                                                    qconv_uint16_mod a[static size_width * size_height]) {
    size_t size = size_width * size_height;
    for (size_t j = 0; j < size; j++) {
        a[j].mod_f_3 = qconv_mul_uint16_mod_f_3(a[j].mod_f_3, norm_const);
    }
}

void qconv_INTT_2D_size_norm_uint16_mod_f_3(const size_t size_width,
                                            const size_t size_height,
                                            qconv_uint16_mod a[static size_width * size_height]) {
    qconv_INTT_1D_size_norm_uint16_mod_f_3(size_width * size_height, a);
}

qconv_uint16_mod_f_3 qconv_inverse_uint16_mod_f_3(qconv_uint16_mod a) {
    // If a and module are relatively prime, then modulo inverse is a^(m-2) mode m
    return qconv_power_uint16_mod_f_3(a.mod_f_3, (unsigned int) (qconv_const_f_3.mod_f_3.value - 2));
}

void qconv_DIT_r2_std2std_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size,
                                            const bool inverse) {
    qconv_bit_reverse_uint16_array_order(size, a);
    qconv_DIT_r2_rev2std_1D_uint16_mod_f_3(size, log2_size, a, p_root, p_root_size, inverse);
}

void qconv_DIT_r2_rev2std_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size,
                                            bool inverse) {
    //get N root of unity
    if (inverse) {
        p_root.mod_f_3 = qconv_power_uint16_mod_f_3(p_root.mod_f_3,
                                                    p_root_size - (p_root_size / size));
    } else {
        p_root.mod_f_3 = qconv_power_uint16_mod_f_3(p_root.mod_f_3,
                                                    (p_root_size / size));
    }

    //printf("size %d\n", size);
    //optimize first iteration of outermost loop
    for (size_t first_iter = 0; first_iter < size; first_iter+= 2) {
        const qconv_uint16_mod temp = a[first_iter + 1];
        a[first_iter + 1].mod_f_3 = qconv_subtract_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
        a[first_iter].mod_f_3 = qconv_add_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
    }

    for (size_t log2_m = 2; log2_m <= log2_size; log2_m++) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        const qconv_uint16_mod_f_3 dw = qconv_power_uint16_mod_f_3(p_root.mod_f_3, (1 << (log2_size - log2_m)));
        for (size_t r = 0; r < size; r += m) {
            qconv_uint16_mod_f_3 w = {.value = 1};
            for (size_t j = 0; j < mh; j++) {
                //printf("%d, ", w.value);
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint16_mod_f_3 u = a[t1].mod_f_3;
                const qconv_uint16_mod_f_3 v = qconv_mul_uint16_mod_f_3(a[t2].mod_f_3, w);
                a[t1].mod_f_3 = qconv_add_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_subtract_uint16_mod_f_3(u, v);
                w = qconv_mul_uint16_mod_f_3(w, dw);
            }
        }
    }
}

void qconv_DIF_r2_std2rev_1D_uint16_mod_f_3(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint16_mod a[static size],
                                            qconv_uint16_mod p_root,
                                            const size_t p_root_size) {
    //get N root of unity
    p_root.mod_f_3 = qconv_power_uint16_mod_f_3(p_root.mod_f_3,
                                                (p_root_size / size));
    //printf("size %d\n", size);

    for (size_t log2_m = log2_size; log2_m >= 2; log2_m--) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        const qconv_uint16_mod_f_3 dw = qconv_power_uint16_mod_f_3(p_root.mod_f_3, (1 << (log2_size - log2_m)));
        for (size_t r = 0; r < size; r += m) {
            qconv_uint16_mod_f_3 w = {.value = 1};
            for (size_t j = 0; j < mh; j++) {
                //printf("%d, ", w.value);
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint16_mod_f_3 u = a[t1].mod_f_3;
                const qconv_uint16_mod_f_3 v = a[t2].mod_f_3;
                a[t1].mod_f_3 = qconv_add_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_subtract_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_mul_uint16_mod_f_3(a[t2].mod_f_3, w);
                w = qconv_mul_uint16_mod_f_3(w, dw);
            }
        }
    }
    //optimize last iteration of outermost loop
    for (size_t last_iter = 0; last_iter < size; last_iter+= 2) {
        const qconv_uint16_mod temp = a[last_iter + 1];
        a[last_iter + 1].mod_f_3 = qconv_subtract_uint16_mod_f_3(a[last_iter].mod_f_3, temp.mod_f_3);
        a[last_iter].mod_f_3 = qconv_add_uint16_mod_f_3(a[last_iter].mod_f_3, temp.mod_f_3);
    }
}

void qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers) {
    size_t power_index = 0;
    for (size_t log2_m = log2_size; log2_m >= 2; log2_m--) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        for (size_t r = 0; r < size; r += m) {
            for (size_t j = 0; j < mh; j++) {
                qconv_uint16_mod_f_3 w = {.value = powers[power_index]};
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint16_mod_f_3 u = a[t1].mod_f_3;
                const qconv_uint16_mod_f_3 v = a[t2].mod_f_3;
                a[t1].mod_f_3 = qconv_add_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_subtract_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_forward_shift_uint16_mod_f_3(a[t2].mod_f_3, w);
                power_index++;
            }
        }
    }
    //optimize last iteration of outermost loop
    for (size_t last_iter = 0; last_iter < size; last_iter+= 2) {
        const qconv_uint16_mod temp = a[last_iter + 1];
        a[last_iter + 1].mod_f_3 = qconv_subtract_uint16_mod_f_3(a[last_iter].mod_f_3, temp.mod_f_3);
        a[last_iter].mod_f_3 = qconv_add_uint16_mod_f_3(a[last_iter].mod_f_3, temp.mod_f_3);
    }
}

void qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers) {
    qconv_bit_reverse_uint16_array_order(size, a);
    //optimize first iteration of outermost loop
    for (size_t first_iter = 0; first_iter < size; first_iter+= 2) {
        const qconv_uint16_mod temp = a[first_iter + 1];
        a[first_iter + 1].mod_f_3 = qconv_subtract_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
        a[first_iter].mod_f_3 = qconv_add_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
    }

    size_t power_index = 0;
    for (size_t log2_m = 2; log2_m <= log2_size; log2_m++) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        for (size_t r = 0; r < size; r += m) {
            for (size_t j = 0; j < mh; j++) {
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint16_mod_f_3 u = a[t1].mod_f_3;
                const qconv_uint16_mod_f_3 w = {.value = powers[power_index]};
                const qconv_uint16_mod_f_3 v = qconv_forward_shift_uint16_mod_f_3(a[t2].mod_f_3, w);
                a[t1].mod_f_3 = qconv_add_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_subtract_uint16_mod_f_3(u, v);
                power_index++;
            }
        }
    }
}

void qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers) {
    qconv_bit_reverse_uint16_array_order(size, a);
    qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(size, log2_size, a, powers);

}

void qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint16_mod a[static size],
                                                    const qconv_inner_uint8 *powers) {
    //optimize first iteration of outermost loop
    for (size_t first_iter = 0; first_iter < size; first_iter+= 2) {
        const qconv_uint16_mod temp = a[first_iter + 1];
        a[first_iter + 1].mod_f_3 = qconv_subtract_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
        a[first_iter].mod_f_3 = qconv_add_uint16_mod_f_3(a[first_iter].mod_f_3, temp.mod_f_3);
    }

    size_t power_index = 0;
    for (size_t log2_m = 2; log2_m <= log2_size; log2_m++) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        for (size_t r = 0; r < size; r += m) {
            for (size_t j = 0; j < mh; j++) {
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint16_mod_f_3 u = a[t1].mod_f_3;
                const qconv_uint16_mod_f_3 w = {.value = powers[power_index]};
                const qconv_uint16_mod_f_3 v = qconv_inverse_shift_uint16_mod_f_3(a[t2].mod_f_3, w);
                a[t1].mod_f_3 = qconv_add_uint16_mod_f_3(u, v);
                a[t2].mod_f_3 = qconv_subtract_uint16_mod_f_3(u, v);
                power_index++;
            }
        }
    }
}

enum qconv_status qconv_NTT_1D_uint16_mod_f_3(const size_t size,
                                              qconv_uint16_mod a[static size],
                                              const enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_3_DIF_r2_std2rev_size_8_forward);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_3_DIT_r2_std2std_size_8_forward);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                           qconv_const_p_root_f_3_size_16, QCONV_SIZE_16, false);
                    return status_success;
            }
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_3_DIF_r2_std2rev_size_16_forward);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_3_DIT_r2_std2std_size_16_forward);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                           qconv_const_p_root_f_3_size_16, QCONV_SIZE_16, false);
                    return status_success;
            }
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            qconv_DIT_r2_std2std_1D_uint16_mod_f_3(size, qconv_get_log2_power_of_two(size), a,
                                                   qconv_const_p_root_f_3_size_256, QCONV_SIZE_256, false);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_1D_uint16_mod_f_3(const size_t size, qconv_uint16_mod a[static size],
                                               const enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_3_DIT_r2_rev2std_size_8_inverse);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_8, a);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_3_DIT_r2_std2std_size_8_inverse);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_8, a);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint16_mod_f_3(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                           qconv_const_p_root_f_3_size_16, QCONV_SIZE_16, true);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_8, a);
                    return status_success;
            }
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_3_DIT_r2_rev2std_size_16_inverse);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_16, a);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_3_DIT_r2_std2std_size_16_inverse);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_16, a);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint16_mod_f_3(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                           qconv_const_p_root_f_3_size_16, QCONV_SIZE_16, true);
                    qconv_INTT_1D_size_norm_uint16_mod_f_3(QCONV_SIZE_16, a);
                    return status_success;
            }
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            qconv_DIT_r2_std2std_1D_uint16_mod_f_3(size, qconv_get_log2_power_of_two(size), a,
                                                   qconv_const_p_root_f_3_size_256, QCONV_SIZE_256, true);
            qconv_INTT_1D_size_norm_uint16_mod_f_3(size, a);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_1D_circular_convolution_uint16_mod_f_3(const size_t size,
                                                                   qconv_uint16_mod a[static size],
                                                                   qconv_uint16_mod b[static size],
                                                                   qconv_uint16_mod ntt[size],
                                                                   const enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    status = qconv_NTT_1D_uint16_mod_f_3(size, a, optimize_level);
    status_bis = qconv_NTT_1D_uint16_mod_f_3(size, b, optimize_level);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);
    qconv_pmul_mod_f_3(size, a, b, ntt);
    status = qconv_INTT_1D_uint16_mod_f_3(size, ntt, optimize_level);
    return status;
}

enum qconv_status qconv_NTT_1D_linear_convolution_uint16_mod_f_3(const size_t input_size,
                                                                 const size_t kernel_size,
                                                                 qconv_uint16_mod input[static input_size],
                                                                 qconv_uint16_mod kernel[static kernel_size],
                                                                 qconv_uint16_mod ntt[static input_size + kernel_size - 1],
                                                                 const enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    size_t size;
    if (input_size >= kernel_size) {
        size = input_size * 2;
    } else {
        size = kernel_size * 2;
    }
    qconv_uint16_mod input_padded[size];
    qconv_uint16_mod kernel_padded[size];
    qconv_uint16_mod ntt_padded[size];

    //Pad the input and kernel
    status = qconv_right_zero_pad_uint16_1D_array(size, input_size, input, input_padded);
    status_bis = qconv_right_zero_pad_uint16_1D_array(size, kernel_size, kernel, kernel_padded);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    //Perform NTT transform
    status = qconv_NTT_1D_uint16_mod_f_3(size, input_padded, optimize_level);
    status_bis = qconv_NTT_1D_uint16_mod_f_3(size, kernel_padded, optimize_level);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    qconv_pmul_mod_f_3(size, input_padded, kernel_padded, ntt_padded);

    status = qconv_INTT_1D_uint16_mod_f_3(size, ntt_padded, optimize_level);
    CHECK_STATUS(status);

    status = qconv_slice_uint16_1D_array(size, input_size + kernel_size - 1, 0, ntt_padded, ntt);

    return status;
}

void qconv_DIT_std2std_2D_uint16_mod_f_3(const size_t size_width,
                                         const size_t size_height,
                                         const size_t log2_size_width,
                                         const size_t log2_size_height,
                                         qconv_uint16_mod a[static size_width * size_height],
                                         qconv_uint16_mod row_p_root,
                                         qconv_uint16_mod column_p_root,
                                         const size_t row_p_root_size,
                                         const size_t column_p_root_size,
                                         const bool inverse) {
    //row transform
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_std2std_1D_uint16_mod_f_3(size_width, log2_size_width, &a[a_row * size_width], row_p_root,
                                               row_p_root_size, inverse);
    }

    //transpose
    qconv_uint16_mod a_transpose[size_height * size_width];
    qconv_transpose_uint16_2D(size_width, size_height, a, a_transpose);

    //column transform
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_std2std_1D_uint16_mod_f_3(size_height,
                                               log2_size_height,
                                               &a_transpose[a_transpose_column * size_height],
                                               column_p_root,
                                               column_p_root_size,
                                               inverse);
    }

    //transpose back
    qconv_transpose_uint16_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_std2std_forward_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers) {
    //row transform
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint16_mod a_transpose[size_height * size_width];
    qconv_transpose_uint16_2D(size_width, size_height, a, a_transpose);

    //column transform
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_std2std_forward_precomp_1D_uint16_mod_f_3(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint16_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_std2std_inverse_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers) {
    //row transform
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint16_mod a_transpose[size_height * size_width];
    qconv_transpose_uint16_2D(size_width, size_height, a, a_transpose);

    //column transform
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_std2std_inverse_precomp_1D_uint16_mod_f_3(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint16_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_rev2std_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers) {
    //row transform
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint16_mod a_transpose[size_height * size_width];
    qconv_transpose_uint16_2D(size_width, size_height, a, a_transpose);

    //column transform
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint16_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIF_std2rev_2D_precomp_uint16_mod_f_3(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint16_mod a[static size_width * size_height],
                                                 const qconv_inner_uint8 *row_powers,
                                                 const qconv_inner_uint8 *column_powers) {
    //row transform
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint16_mod a_transpose[size_height * size_width];
    qconv_transpose_uint16_2D(size_width, size_height, a, a_transpose);

    //column transform
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint16_2D(size_height, size_width, a_transpose, a);
}

enum qconv_status qconv_NTT_2D_uint16_mod_f_3_inner2x(const size_t size_width,
                                                      const size_t size_height,
                                                      qconv_uint16_mod a[static size_width * size_height],
                                                      enum qconv_optimize_transform optimize_level,
                                                      qconv_uint16_mod row_p_root,
                                                      qconv_uint16_mod column_p_root,
                                                      const size_t row_p_root_size,
                                                      const size_t column_p_root_size) {
    switch(optimize_level) {
        case optimize_precomp_order_nonorm:
        case optimize_precomp_order:
            qconv_DIF_std2rev_2D_precomp_uint16_mod_f_3(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_3_DIF_std2rev_forward(size_width),
                                                        qconv_get_const_f_3_DIF_std2rev_forward(size_height));
            return status_success;
        case optimize_precomp:
            qconv_DIT_std2std_forward_2D_precomp_uint16_mod_f_3(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_3_DIT_std2std_forward(size_width),
                                                        qconv_get_const_f_3_DIT_std2std_forward(size_height));
            return status_success;
        case optimize_null:
        default:
            qconv_DIT_std2std_2D_uint16_mod_f_3(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                column_p_root,
                                                row_p_root_size,
                                                column_p_root_size,
                                                false);
            return status_success;
    }

}

enum qconv_status qconv_NTT_2D_uint16_mod_f_3_inner(const size_t size_width,
                                                    const size_t size_height,
                                                    qconv_uint16_mod a[static size_width * size_height],
                                                    enum qconv_optimize_transform optimize_level,
                                                    qconv_uint16_mod row_p_root,
                                                    const size_t row_p_root_size) {
    switch (size_height) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_NTT_2D_uint16_mod_f_3_inner2x(size_width,
                                                       size_height,
                                                       a,
                                                       optimize_level,
                                                       row_p_root,
                                                       qconv_const_p_root_f_3_size_16,
                                                       row_p_root_size,
                                                       QCONV_SIZE_16);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            qconv_DIT_std2std_2D_uint16_mod_f_3(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                qconv_const_p_root_f_3_size_256,
                                                row_p_root_size,
                                                QCONV_SIZE_256,
                                                false);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_2D_uint16_mod_f_3(const size_t size_width,
                                              const size_t size_height,
                                              qconv_uint16_mod a[static size_width * size_height],
                                              enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_NTT_2D_uint16_mod_f_3_inner(size_width,
                                                     size_height,
                                                     a,
                                                     optimize_level,
                                                     qconv_const_p_root_f_3_size_16,
                                                     QCONV_SIZE_16);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            return qconv_NTT_2D_uint16_mod_f_3_inner(size_width,
                                                     size_height,
                                                     a,
                                                     optimize_level,
                                                     qconv_const_p_root_f_3_size_256,
                                                     QCONV_SIZE_256);
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_2D_uint16_mod_f_3_inner2x(const size_t size_width,
                                                       const size_t size_height,
                                                       qconv_uint16_mod a[static size_width * size_height],
                                                       enum qconv_optimize_transform optimize_level,
                                                       qconv_uint16_mod row_p_root,
                                                       qconv_uint16_mod column_p_root,
                                                       const size_t row_p_root_size,
                                                       const size_t column_p_root_size) {
    switch(optimize_level) {
        case optimize_precomp_order_nonorm:
            qconv_DIT_rev2std_2D_precomp_uint16_mod_f_3(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_3_DIT_rev2std_inverse(size_width),
                                                        qconv_get_const_f_3_DIT_rev2std_inverse(size_height));
        case optimize_precomp_order:
            qconv_DIT_rev2std_2D_precomp_uint16_mod_f_3(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_3_DIT_rev2std_inverse(size_width),
                                                        qconv_get_const_f_3_DIT_rev2std_inverse(size_height));
            qconv_INTT_2D_size_norm_uint16_mod_f_3(size_width, size_height, a);
            return status_success;
        case optimize_precomp:
            qconv_DIT_std2std_inverse_2D_precomp_uint16_mod_f_3(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_3_DIT_std2std_inverse(size_width),
                                                        qconv_get_const_f_3_DIT_std2std_inverse(size_height));
            qconv_INTT_2D_size_norm_uint16_mod_f_3(size_width, size_height, a);
            return status_success;
        case optimize_null:
        default:
            qconv_DIT_std2std_2D_uint16_mod_f_3(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                column_p_root,
                                                row_p_root_size,
                                                column_p_root_size,
                                                true);
            qconv_INTT_2D_size_norm_uint16_mod_f_3(size_width, size_height, a);
            return status_success;
    }

}

enum qconv_status qconv_INTT_2D_uint16_mod_f_3_inner(const size_t size_width,
                                                     const size_t size_height,
                                                     qconv_uint16_mod a[static size_width * size_height],
                                                     enum qconv_optimize_transform optimize_level,
                                                     qconv_uint16_mod row_p_root,
                                                     const size_t row_p_root_size) {
    switch (size_height) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_INTT_2D_uint16_mod_f_3_inner2x(size_width,
                                                        size_height,
                                                        a,
                                                        optimize_level,
                                                        row_p_root,
                                                        qconv_const_p_root_f_3_size_16,
                                                        row_p_root_size,
                                                        QCONV_SIZE_16);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            qconv_DIT_std2std_2D_uint16_mod_f_3(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                qconv_const_p_root_f_3_size_256,
                                                row_p_root_size,
                                                QCONV_SIZE_256,
                                                true);
            qconv_INTT_2D_size_norm_uint16_mod_f_3(size_width, size_height, a);
            return status_success;
        default:
            return status_invalid_input_size;

    }
}

enum qconv_status qconv_INTT_2D_uint16_mod_f_3(const size_t size_width,
                                               const size_t size_height,
                                               qconv_uint16_mod a[static size_width * size_height],
                                               enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_INTT_2D_uint16_mod_f_3_inner(size_width,
                                                      size_height,
                                                      a,
                                                      optimize_level,
                                                      qconv_const_p_root_f_3_size_16,
                                                      QCONV_SIZE_16);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            return qconv_INTT_2D_uint16_mod_f_3_inner(size_width,
                                                      size_height,
                                                      a,
                                                      optimize_level,
                                                      qconv_const_p_root_f_3_size_256,
                                                      QCONV_SIZE_256);
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_2D_circular_convolution_uint16_mod_f_3(const size_t size_width,
                                                                   const size_t size_height,
                                                                   qconv_uint16_mod a[static size_width * size_height],
                                                                   qconv_uint16_mod b[static size_width * size_height],
                                                                   qconv_uint16_mod ntt[size_width * size_height],
                                                                   const enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    status = qconv_NTT_2D_uint16_mod_f_3(size_width, size_height, a, optimize_level);
    status_bis = qconv_NTT_2D_uint16_mod_f_3(size_width, size_height, b, optimize_level);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    qconv_pmul_mod_f_3(size_width * size_height, a, b, ntt);

    status = qconv_INTT_2D_uint16_mod_f_3(size_width, size_height, ntt, optimize_level);

    return status;
}

enum qconv_status qconv_NTT_2D_linear_convolution_uint16_mod_f_3(const size_t input_size_width,
                                                                 const size_t input_size_height,
                                                                 const size_t kernel_size_width,
                                                                 const size_t kernel_size_height,
                                                                 qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                 qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                 qconv_uint16_mod ntt[(input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)],
                                                                 const enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    size_t size_width, size_height;
    if (input_size_width >= kernel_size_width) {
        size_width = input_size_width * 2;
    } else {
        size_width = kernel_size_width * 2;
    }
    if (input_size_height >= kernel_size_height) {
        size_height = input_size_height * 2;
    } else {
        size_height = kernel_size_height * 2;
    }
    qconv_uint16_mod input_padded[size_width * size_height];
    qconv_uint16_mod kernel_padded[size_width * size_height];
    qconv_uint16_mod ntt_padded[size_width * size_height];

    //Pad the input and kernel
    status = qconv_bottom_right_zero_pad_uint16_2D_array(size_width, size_height, input_size_width, input_size_height, input, input_padded);
    status_bis = qconv_bottom_right_zero_pad_uint16_2D_array(size_width, size_height, kernel_size_width, kernel_size_height, kernel, kernel_padded);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    //Perform the transform
    status = qconv_NTT_2D_uint16_mod_f_3(size_width, size_height, input_padded, optimize_level);
    status_bis = qconv_NTT_2D_uint16_mod_f_3(size_width, size_height, kernel_padded, optimize_level);
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    qconv_pmul_mod_f_3(size_width * size_height, input_padded, kernel_padded, ntt_padded);

    status = qconv_INTT_2D_uint16_mod_f_3(size_width, size_height, ntt_padded, optimize_level);
    CHECK_STATUS(status);

    status = qconv_slice_uint16_2D_array(size_width,
                                         size_height,
                                         input_size_width + kernel_size_width - 1,
                                         input_size_height + kernel_size_height - 1,
                                         0,
                                         0,
                                         ntt_padded,
                                         ntt);
    return status;
}


enum qconv_status qconv_NTT_2D_block_linear_convolution_uint16_mod_f_3(int input_size_width,
                                                                       int input_size_height,
                                                                       int kernel_size_width,
                                                                       int kernel_size_height,
                                                                       int block_size_width,
                                                                       int block_size_height,
                                                                       qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                       qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                       qconv_uint16_mod output[static (input_size_width + kernel_size_width - 1)
                                                                                                      * (input_size_height + kernel_size_height - 1)]) {
    enum qconv_optimize_transform optimize_level = optimize_precomp_order_nonorm;

    int log2_block_size_width = qconv_get_log2_power_of_two(block_size_width);
    int log2_block_size_height = qconv_get_log2_power_of_two(block_size_height);

    int output_size_width = input_size_width + kernel_size_width - 1;
    int output_size_height = input_size_height + kernel_size_height - 1;

    int discard_subblock_size_width = kernel_size_width - 1;
    int discard_subblock_size_height = kernel_size_height - 1;
    int valid_subblock_size_width = block_size_width - discard_subblock_size_width;
    int valid_subblock_size_height = block_size_height - discard_subblock_size_height;

    int block_size = block_size_width * block_size_height;

    int input_offset_width = 0;
    int input_offset_height = 0;

    int output_offset_width = 0;
    int output_offset_height = 0;

    qconv_uint16_mod to_inv = {.mod_f_3.value = block_size};
    qconv_uint16_mod_f_3 norm_const = qconv_inverse_uint16_mod_f_3(to_inv);

    qconv_inner_uint8 *forward_row_powers = qconv_get_const_f_3_DIF_std2rev_forward(block_size_width);
    qconv_inner_uint8 *forward_column_powers = qconv_get_const_f_3_DIF_std2rev_forward(block_size_height);

    qconv_inner_uint8 *inverse_row_powers = qconv_get_const_f_3_DIT_rev2std_inverse(block_size_width);
    qconv_inner_uint8 *inverse_column_powers = qconv_get_const_f_3_DIT_rev2std_inverse(block_size_height);

    //pad and transform kernel
    qconv_uint16_mod kernel_block[block_size];
    qconv_bottom_right_zero_pad_uint16_2D_array(block_size_width, block_size_height, kernel_size_width,
                                                kernel_size_height, kernel, kernel_block);

    qconv_NTT_2D_uint16_mod_f_3(block_size_width, block_size_height, kernel_block, optimize_level);

    /*
     * STEP 1: TOP ROW OF BLOCKS
     */

    /*
     * STEP 1.1: TOP LEFT BLOCK THAT REQUIRES TOP LEFT PADDING
     */
    if (block_size_width <= input_size_width && block_size_height <= input_size_height) {
        qconv_block_convolution_uint16_mod_f_3_top_left_pad(input_size_width, input_size_height,
                                                            block_size_width, block_size_height,
                                                            block_size,
                                                            log2_block_size_width, log2_block_size_height,
                                                            output_size_width, output_size_height,
                                                            input_offset_width, input_offset_height,
                                                            output_offset_width, output_offset_height,
                                                            discard_subblock_size_width, discard_subblock_size_height,
                                                            valid_subblock_size_width, valid_subblock_size_height,
                                                            norm_const,
                                                            forward_row_powers, forward_column_powers,
                                                            inverse_row_powers, inverse_column_powers,
                                                            input, kernel_block, output,
                                                            optimize_level);
    }

    /*
     * STEP 1.2: INNER TOP ROW OF BLOCKS THAT REQUIRE TOP PADDING
     */

    input_offset_width = valid_subblock_size_width - discard_subblock_size_width;
    output_offset_width = valid_subblock_size_width;

    while (input_offset_width <= input_size_width - block_size_width) {

        qconv_block_convolution_uint16_mod_f_3_top_pad(input_size_width, input_size_height,
                                                       block_size_width, block_size_height, block_size,
                                                       log2_block_size_width, log2_block_size_height,
                                                       output_size_width, output_size_height,
                                                       discard_subblock_size_width, discard_subblock_size_height,
                                                       valid_subblock_size_width, valid_subblock_size_height,
                                                       input_offset_width, input_offset_height,
                                                       output_offset_width, output_offset_height,
                                                       norm_const,
                                                       forward_row_powers, forward_column_powers,
                                                       inverse_row_powers, inverse_column_powers,
                                                       input, kernel_block, output,
                                                       optimize_level);

        input_offset_width += valid_subblock_size_width;
        output_offset_width += valid_subblock_size_width;
    }

    /*
     * STEP 1.3: TOP RIGHT BLOCKS THAT REQUIRE TOP RIGHT PADDING
     */

    while (input_offset_width < input_size_width) {

        int valid_output_subblock_size_width = output_size_width - output_offset_width;
        valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

        qconv_block_convolution_uint16_mod_f_3_top_right_pad(input_size_width, input_size_height,
                                                             block_size_width, block_size_height, block_size,
                                                             log2_block_size_width, log2_block_size_height,
                                                             output_size_width, output_size_height,
                                                             input_offset_width, input_offset_height,
                                                             output_offset_width, output_offset_height,
                                                             discard_subblock_size_width, discard_subblock_size_height,
                                                             valid_subblock_size_width, valid_subblock_size_height,
                                                             norm_const,
                                                             forward_row_powers, forward_column_powers,
                                                             inverse_row_powers, inverse_column_powers,
                                                             input, kernel_block, output,
                                                             optimize_level);
        input_offset_width += valid_subblock_size_width;
        output_offset_width += valid_output_subblock_size_width;
    }

    //Compute new height offset
    input_offset_height = valid_subblock_size_height - discard_subblock_size_height;
    output_offset_height += valid_subblock_size_height;

    /*
     * STEP 2: INNER ROWS OF BLOCKS
     */
    while (input_offset_height <= input_size_height - block_size_height) {

        input_offset_width = 0;
        output_offset_width = 0;

        /*
         * STEP 2.1: LEFT BLOCK THAT REQUIRES LEFT PADDING
         */

        qconv_block_convolution_uint16_mod_f_3_left_pad(input_size_width, input_size_height,
                                                        block_size_width, block_size_height,
                                                        block_size,
                                                        log2_block_size_width, log2_block_size_height,
                                                        output_size_width, output_size_height,
                                                        input_offset_width, input_offset_height,
                                                        output_offset_width, output_offset_height,
                                                        discard_subblock_size_width, discard_subblock_size_height,
                                                        valid_subblock_size_width, valid_subblock_size_height,
                                                        norm_const,
                                                        forward_row_powers, forward_column_powers,
                                                        inverse_row_powers, inverse_column_powers,
                                                        input, kernel_block, output,
                                                        optimize_level);

        /*
         * STEP 2.2: INNER ROW OF BLOCKS THAT DOESN'T REQUIRE PADDING
         */

        input_offset_width = valid_subblock_size_width - discard_subblock_size_width;
        output_offset_width = valid_subblock_size_width;

        while (input_offset_width <= input_size_width - block_size_width) {

            qconv_block_convolution_uint16_mod_f_3_no_pad(input_size_width, input_size_height,
                                                          block_size_width, block_size_height,
                                                          block_size,
                                                          log2_block_size_width, log2_block_size_height,
                                                          output_size_width, output_size_height,
                                                          input_offset_width, input_offset_height,
                                                          output_offset_width, output_offset_height,
                                                          discard_subblock_size_width, discard_subblock_size_height,
                                                          valid_subblock_size_width, valid_subblock_size_height,
                                                          norm_const,
                                                          forward_row_powers, forward_column_powers,
                                                          inverse_row_powers, inverse_column_powers,
                                                          input, kernel_block, output,
                                                          optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_subblock_size_width;
        }

        /*
         * STEP 2.3: RIGHT BLOCKS THAT REQUIRE RIGHT PADDING
         */

        while (input_offset_width < input_size_width) {

            int valid_output_subblock_size_width = output_size_width - output_offset_width;
            valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

            qconv_block_convolution_uint16_mod_f_3_right_pad(input_size_width, input_size_height,
                                                             block_size_width, block_size_height,
                                                             block_size,
                                                             log2_block_size_width, log2_block_size_height,
                                                             output_size_width, output_size_height,
                                                             input_offset_width, input_offset_height,
                                                             output_offset_width, output_offset_height,
                                                             discard_subblock_size_width, discard_subblock_size_height,
                                                             valid_subblock_size_width, valid_subblock_size_height,
                                                             norm_const,
                                                             forward_row_powers, forward_column_powers,
                                                             inverse_row_powers, inverse_column_powers,
                                                             input, kernel_block, output,
                                                             optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_output_subblock_size_width;
        }

        input_offset_height += valid_subblock_size_height;
        output_offset_height += valid_subblock_size_height;

    }

    /*
     * STEP 3: BOTTOM ROWS OF BLOCKS
     */

    while (input_offset_height < input_size_height) {

        input_offset_width = 0;
        output_offset_width = 0;

        int valid_input_subblock_size_height = input_size_height - input_offset_height;

        int valid_output_subblock_size_height = output_size_height - output_offset_height;
        valid_output_subblock_size_height = valid_output_subblock_size_height < valid_subblock_size_height ? valid_output_subblock_size_height : valid_subblock_size_height;

        /*
         * STEP 3.1: BOTTOM LEFT BLOCK
         */

        if (input_size_width <= block_size) {
            qconv_block_convolution_uint16_mod_f_3_bottom_left_pad(input_size_width, input_size_height,
                                                                   block_size_width, block_size_height,
                                                                   block_size,
                                                                   log2_block_size_width, log2_block_size_height,
                                                                   output_size_width, output_size_height,
                                                                   input_offset_width, input_offset_height,
                                                                   output_offset_width, output_offset_height,
                                                                   discard_subblock_size_width, discard_subblock_size_height,
                                                                   valid_subblock_size_width, valid_subblock_size_height,
                                                                   valid_input_subblock_size_height, valid_output_subblock_size_height,
                                                                   norm_const,
                                                                   forward_row_powers, forward_column_powers,
                                                                   inverse_row_powers, inverse_column_powers,
                                                                   input, kernel_block, output,
                                                                   optimize_level);
        }

        /*
         * STEP 3.2: INNER BOTTOM ROW OF BLOCKS THAT REQUIRES BOTTOM PADDING
         */

        input_offset_width = valid_subblock_size_width - discard_subblock_size_width;
        output_offset_width = valid_subblock_size_width;

        while (input_offset_width <= input_size_width - block_size_width) {

            qconv_block_convolution_uint16_mod_f_3_bottom_pad(input_size_width, input_size_height,
                                                              block_size_width, block_size_height,
                                                              block_size,
                                                              log2_block_size_width, log2_block_size_height,
                                                              output_size_width, output_size_height,
                                                              input_offset_width, input_offset_height,
                                                              output_offset_width, output_offset_height,
                                                              discard_subblock_size_width, discard_subblock_size_height,
                                                              valid_subblock_size_width, valid_subblock_size_height,
                                                              valid_input_subblock_size_height, valid_output_subblock_size_height,
                                                              norm_const,
                                                              forward_row_powers, forward_column_powers,
                                                              inverse_row_powers, inverse_column_powers,
                                                              input, kernel_block, output,
                                                              optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_subblock_size_width;
        }

        /*
         * STEP 3.3: BOTTOM RIGHT BLOCKS THAT REQUIRES BOTTOM RIGHT PADDING
         */

        while (input_offset_width < input_size_width) {

            int valid_output_subblock_size_width = output_size_width - output_offset_width;
            valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

            qconv_block_convolution_uint16_mod_f_3_bottom_right_pad(input_size_width, input_size_height,
                                                                    block_size_width, block_size_height,
                                                                    block_size,
                                                                    log2_block_size_width, log2_block_size_height,
                                                                    output_size_width, output_size_height,
                                                                    input_offset_width, input_offset_height,
                                                                    output_offset_width, output_offset_height,
                                                                    discard_subblock_size_width, discard_subblock_size_height,
                                                                    valid_subblock_size_width, valid_subblock_size_height,
                                                                    valid_input_subblock_size_height, valid_output_subblock_size_height,
                                                                    norm_const,
                                                                    forward_row_powers, forward_column_powers,
                                                                    inverse_row_powers, inverse_column_powers,
                                                                    input, kernel_block, output,
                                                                    optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_output_subblock_size_width;
        }
        input_offset_height += valid_subblock_size_height;
        output_offset_height += valid_output_subblock_size_height;
    }
    return status_success;
}

void qconv_block_convolution_uint16_mod_f_3_no_pad(int input_size_width, int input_size_height,
                                                   int block_size_width, int block_size_height, int block_size,
                                                   int log2_block_size_width, int log2_block_size_height,
                                                   int output_size_width, int output_size_height,
                                                   int input_offset_width, int input_offset_height,
                                                   int output_offset_width, int output_offset_height,
                                                   int discard_subblock_size_width, int discard_subblock_size_height,
                                                   int valid_subblock_size_width, int valid_subblock_size_height,
                                                   qconv_uint16_mod_f_3 norm_const,
                                                   qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                   qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                   const qconv_uint16_mod *input,
                                                   const qconv_uint16_mod *kernel_block,
                                                   qconv_uint16_mod *output,
                                                   enum qconv_optimize_transform optimize_level) {

    qconv_uint16_mod block[block_size];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                block_size_width,
                                block_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}

void qconv_block_convolution_uint16_mod_f_3_bottom_pad(int input_size_width, int input_size_height,
                                                       int block_size_width, int block_size_height, int block_size,
                                                       int log2_block_size_width, int log2_block_size_height,
                                                       int output_size_width, int output_size_height,
                                                       int input_offset_width, int input_offset_height,
                                                       int output_offset_width, int output_offset_height,
                                                       int discard_subblock_size_width, int discard_subblock_size_height,
                                                       int valid_subblock_size_width, int valid_subblock_size_height,
                                                       int valid_input_subblock_size_height, int valid_output_subblock_size_height,
                                                       qconv_uint16_mod_f_3 norm_const,
                                                       qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                       qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                       const qconv_uint16_mod *input,
                                                       const qconv_uint16_mod *kernel_block,
                                                       qconv_uint16_mod *output,
                                                       enum qconv_optimize_transform optimize_level) {
    //Extract valid input
    qconv_uint16_mod valid_input_subblock[block_size_width * valid_input_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                block_size_width,
                                valid_input_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    //Top zero pad extracted input
    qconv_uint16_mod block[block_size];
    qconv_bottom_zero_pad_uint16_2D_array(block_size_width,
                                          block_size_height,
                                          valid_input_subblock_size_height,
                                          valid_input_subblock,
                                          block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_output_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}

void qconv_block_convolution_uint16_mod_f_3_bottom_right_pad(int input_size_width, int input_size_height,
                                                             int block_size_width, int block_size_height, int block_size,
                                                             int log2_block_size_width, int log2_block_size_height,
                                                             int output_size_width, int output_size_height,
                                                             int input_offset_width, int input_offset_height,
                                                             int output_offset_width, int output_offset_height,
                                                             int discard_subblock_size_width, int discard_subblock_size_height,
                                                             int valid_subblock_size_width, int valid_subblock_size_height,
                                                             int valid_input_subblock_size_height, int valid_output_subblock_size_height,
                                                             qconv_uint16_mod_f_3 norm_const,
                                                             qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                             qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                             const qconv_uint16_mod *input,
                                                             const qconv_uint16_mod *kernel_block,
                                                             qconv_uint16_mod *output,
                                                             enum qconv_optimize_transform optimize_level) {

    int valid_input_subblock_size_width = input_size_width - input_offset_width;

    //Extract valid input
    qconv_uint16_mod valid_input[valid_input_subblock_size_width * valid_input_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_input_subblock_size_width,
                                valid_input_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input);

    //Top right zero pad extracted input
    qconv_uint16_mod block[block_size];
    qconv_bottom_right_zero_pad_uint16_2D_array(block_size_width,
                                                block_size_height,
                                                valid_input_subblock_size_width,
                                                valid_input_subblock_size_height,
                                                valid_input, block);

    int valid_output_subblock_size_width = output_size_width - output_offset_width;
    valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_output_subblock_size_width,
                                                           valid_output_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}



void qconv_block_convolution_uint16_mod_f_3_top_left_pad(int input_size_width, int input_size_height,
                                                         int block_size_width, int block_size_height, int block_size,
                                                         int log2_block_size_width, int log2_block_size_height,
                                                         int output_size_width, int output_size_height,
                                                         int input_offset_width, int input_offset_height,
                                                         int output_offset_width, int output_offset_height,
                                                         int discard_subblock_size_width, int discard_subblock_size_height,
                                                         int valid_subblock_size_width, int valid_subblock_size_height,
                                                         qconv_uint16_mod_f_3 norm_const,
                                                         qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                         qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                         const qconv_uint16_mod *input,
                                                         const qconv_uint16_mod *kernel_block,
                                                         qconv_uint16_mod *output,
                                                         enum qconv_optimize_transform optimize_level) {

    qconv_uint16_mod valid_input_subblock[valid_subblock_size_width * valid_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_subblock_size_width,
                                valid_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    //Compute first block
    qconv_uint16_mod block[block_size];
    qconv_top_left_zero_pad_uint16_2D_array(block_size_width,
                                            block_size_height,
                                            valid_subblock_size_width,
                                            valid_subblock_size_height,
                                            valid_input_subblock,
                                            block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}

void qconv_block_convolution_uint16_mod_f_3_left_pad(int input_size_width, int input_size_height,
                                                     int block_size_width, int block_size_height, int block_size,
                                                     int log2_block_size_width, int log2_block_size_height,
                                                     int output_size_width, int output_size_height,
                                                     int input_offset_width, int input_offset_height,
                                                     int output_offset_width, int output_offset_height,
                                                     int discard_subblock_size_width, int discard_subblock_size_height,
                                                     int valid_subblock_size_width, int valid_subblock_size_height,
                                                     qconv_uint16_mod_f_3 norm_const,
                                                     qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                     qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                     const qconv_uint16_mod *input,
                                                     const qconv_uint16_mod *kernel_block,
                                                     qconv_uint16_mod *output,
                                                     enum qconv_optimize_transform optimize_level) {

    //Extract valid input
    qconv_uint16_mod valid_input_subblock[valid_subblock_size_width * block_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_subblock_size_width,
                                block_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    //Compute left block
    qconv_uint16_mod block[block_size];
    qconv_left_zero_pad_uint16_2D_array(block_size_width,
                                        block_size_height,
                                        valid_subblock_size_width,
                                        valid_input_subblock,
                                        block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}

void qconv_block_convolution_uint16_mod_f_3_right_pad(int input_size_width, int input_size_height,
                                                      int block_size_width, int block_size_height, int block_size,
                                                      int log2_block_size_width, int log2_block_size_height,
                                                      int output_size_width, int output_size_height,
                                                      int input_offset_width, int input_offset_height,
                                                      int output_offset_width, int output_offset_height,
                                                      int discard_subblock_size_width, int discard_subblock_size_height,
                                                      int valid_subblock_size_width, int valid_subblock_size_height,
                                                      qconv_uint16_mod_f_3 norm_const,
                                                      qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                      qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                      const qconv_uint16_mod *input,
                                                      const qconv_uint16_mod *kernel_block,
                                                      qconv_uint16_mod *output,
                                                      enum qconv_optimize_transform optimize_level) {

    int valid_input_subblock_size_width = input_size_width - input_offset_width;

    qconv_uint16_mod valid_input_subblock[valid_input_subblock_size_width * block_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_input_subblock_size_width,
                                block_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    qconv_uint16_mod block[block_size];
    qconv_right_zero_pad_uint16_2D_array(block_size_width,
                                         block_size_height,
                                         valid_input_subblock_size_width,
                                         valid_input_subblock, block);

    int valid_output_subblock_size_width = output_size_width - output_offset_width;
    valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_output_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);
}

void qconv_block_convolution_uint16_mod_f_3_bottom_left_pad(int input_size_width, int input_size_height,
                                                            int block_size_width, int block_size_height, int block_size,
                                                            int log2_block_size_width, int log2_block_size_height,
                                                            int output_size_width, int output_size_height,
                                                            int input_offset_width, int input_offset_height,
                                                            int output_offset_width, int output_offset_height,
                                                            int discard_subblock_size_width, int discard_subblock_size_height,
                                                            int valid_subblock_size_width, int valid_subblock_size_height,
                                                            int valid_input_subblock_size_height, int valid_output_subblock_size_height,
                                                            qconv_uint16_mod_f_3 norm_const,
                                                            qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                            qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                            const qconv_uint16_mod *input,
                                                            const qconv_uint16_mod *kernel_block,
                                                            qconv_uint16_mod *output,
                                                            enum qconv_optimize_transform optimize_level) {

    qconv_uint16_mod valid_input_block[valid_subblock_size_width * valid_input_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_subblock_size_width,
                                valid_input_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_block);

    qconv_uint16_mod block[block_size];
    qconv_bottom_left_zero_pad_uint16_2D_array(block_size_width,
                                               block_size_height,
                                               valid_subblock_size_width,
                                               valid_input_subblock_size_height,
                                               valid_input_block,
                                               block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_output_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);

}

void qconv_block_convolution_uint16_mod_f_3_top_right_pad(int input_size_width, int input_size_height,
                                                          int block_size_width, int block_size_height, int block_size,
                                                          int log2_block_size_width, int log2_block_size_height,
                                                          int output_size_width, int output_size_height,
                                                          int input_offset_width, int input_offset_height,
                                                          int output_offset_width, int output_offset_height,
                                                          int discard_subblock_size_width, int discard_subblock_size_height,
                                                          int valid_subblock_size_width, int valid_subblock_size_height,
                                                          qconv_uint16_mod_f_3 norm_const,
                                                          qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                          qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                          const qconv_uint16_mod *input,
                                                          const qconv_uint16_mod *kernel_block,
                                                          qconv_uint16_mod *output,
                                                          enum qconv_optimize_transform optimize_level) {

    int valid_input_subblock_size_width = input_size_width - input_offset_width;

    qconv_uint16_mod valid_input_subblock[valid_input_subblock_size_width * valid_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                valid_input_subblock_size_width,
                                valid_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    qconv_uint16_mod block[block_size];
    qconv_top_right_zero_pad_uint16_2D_array(block_size_width,
                                             block_size_height,
                                             valid_input_subblock_size_width,
                                             valid_subblock_size_height,
                                             valid_input_subblock, block);

    int valid_output_subblock_size_width = output_size_width - output_offset_width;
    valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_output_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);


}

void qconv_block_convolution_uint16_mod_f_3_top_pad(int input_size_width, int input_size_height,
                                                    int block_size_width, int block_size_height, int block_size,
                                                    int log2_block_size_width, int log2_block_size_height,
                                                    int output_size_width, int output_size_height,
                                                    int discard_subblock_size_width, int discard_subblock_size_height,
                                                    int valid_subblock_size_width, int valid_subblock_size_height,
                                                    int input_offset_width, int input_offset_height,
                                                    int output_offset_width, int output_offset_height,
                                                    qconv_uint16_mod_f_3 norm_const,
                                                    qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                    qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                    const qconv_uint16_mod *input,
                                                    const qconv_uint16_mod *kernel_block,
                                                    qconv_uint16_mod *output,
                                                    enum qconv_optimize_transform optimize_level) {
    qconv_uint16_mod valid_input_subblock[block_size_width * valid_subblock_size_height];
    qconv_slice_uint16_2D_array(input_size_width,
                                input_size_height,
                                block_size_width,
                                valid_subblock_size_height,
                                input_offset_width,
                                input_offset_height,
                                input, valid_input_subblock);

    qconv_uint16_mod block[block_size];
    qconv_top_zero_pad_uint16_2D_array(block_size_width, block_size_height, valid_subblock_size_height, valid_input_subblock, block);

    qconv_block_convolution_uint16_mod_f_3_output_subblock(block_size_width, block_size_height, block_size,
                                                           log2_block_size_width, log2_block_size_height,
                                                           output_size_width, output_size_height, output_offset_width,
                                                           output_offset_height, discard_subblock_size_width,
                                                           discard_subblock_size_height, valid_subblock_size_width,
                                                           valid_subblock_size_height,
                                                           norm_const,
                                                           forward_row_powers, forward_column_powers,
                                                           inverse_row_powers, inverse_column_powers,
                                                           block, kernel_block, output,
                                                           optimize_level);

}

void qconv_block_convolution_uint16_mod_f_3_output_subblock(int block_size_width, int block_size_height, int block_size,
                                                            int log2_block_size_width, int log2_block_size_height,
                                                            int output_size_width, int output_size_height,
                                                            int output_offset_width, int output_offset_height,
                                                            int discard_subblock_size_width, int discard_subblock_size_height,
                                                            int valid_output_subblock_size_width, int valid_output_subblock_size_height,
                                                            qconv_uint16_mod_f_3 norm_const,
                                                            qconv_inner_uint8 *forward_row_powers, qconv_inner_uint8 *forward_column_powers,
                                                            qconv_inner_uint8 *inverse_row_powers, qconv_inner_uint8 *inverse_column_powers,
                                                            qconv_uint16_mod *block,
                                                            const qconv_uint16_mod *kernel_block,
                                                            qconv_uint16_mod *output,
                                                            enum qconv_optimize_transform optimize_level) {

    qconv_DIF_std2rev_2D_precomp_uint16_mod_f_3(block_size_width,
                                                block_size_height,
                                                log2_block_size_width,
                                                log2_block_size_height,
                                                block,
                                                forward_row_powers,
                                                forward_column_powers);

    qconv_pmul_mod_f_3(block_size, block, kernel_block, block);

    qconv_DIT_rev2std_2D_precomp_uint16_mod_f_3(block_size_width,
                                                block_size_height,
                                                log2_block_size_width,
                                                log2_block_size_height,
                                                block,
                                                inverse_row_powers,
                                                inverse_column_powers);

    //Slice output block back into valid size
    qconv_uint16_mod valid_output_subblock[valid_output_subblock_size_width * valid_output_subblock_size_height];
    qconv_slice_uint16_2D_array(block_size_width,
                                block_size_height,
                                valid_output_subblock_size_width,
                                valid_output_subblock_size_height,
                                discard_subblock_size_width,
                                discard_subblock_size_height,
                                block, valid_output_subblock);

    //Normalize output subblock
    qconv_INTT_2D_size_norm_precomp_uint16_mod_f_3(valid_output_subblock_size_width, valid_output_subblock_size_height, norm_const, valid_output_subblock);

    //Insert valid output block into output
    qconv_insert_uint16_2D_array(output_size_width,
                                 output_size_height,
                                 valid_output_subblock_size_width,
                                 valid_output_subblock_size_height,
                                 output_offset_width,
                                 output_offset_height,
                                 valid_output_subblock, output);
}

enum qconv_status qconv_NTT_2D_block_CNN_convolution_uint16_mod_f_3(int input_size_width,
                                                                    int input_size_height,
                                                                    int kernel_size_width,
                                                                    int kernel_size_height,
                                                                    int block_size_width,
                                                                    int block_size_height,
                                                                    qconv_uint16_mod input[static input_size_width * input_size_height],
                                                                    qconv_uint16_mod kernel[static kernel_size_width * kernel_size_height],
                                                                    qconv_uint16_mod output[static (input_size_width - kernel_size_width + 1)
                                                                                                   * (input_size_height - kernel_size_height + 1)]) {
    enum qconv_optimize_transform optimize_level = optimize_precomp_order_nonorm;

    int output_size_width = input_size_width - kernel_size_width + 1;
    int output_size_height = input_size_height - kernel_size_height + 1;

    int log2_block_size_width = qconv_get_log2_power_of_two(block_size_width);
    int log2_block_size_height = qconv_get_log2_power_of_two(block_size_height);

    int discard_subblock_size_width = kernel_size_width - 1;
    int discard_subblock_size_height = kernel_size_height - 1;
    int valid_subblock_size_width = block_size_width - discard_subblock_size_width;
    int valid_subblock_size_height = block_size_height - discard_subblock_size_height;

    int block_size = block_size_width * block_size_height;

    int input_offset_width = 0;
    int input_offset_height = 0;

    int output_offset_width = 0;
    int output_offset_height = 0;

    qconv_uint16_mod to_inv = {.mod_f_3.value = block_size};
    qconv_uint16_mod_f_3 norm_const = qconv_inverse_uint16_mod_f_3(to_inv);

    qconv_inner_uint8 *forward_row_powers = qconv_get_const_f_3_DIF_std2rev_forward(block_size_width);
    qconv_inner_uint8 *forward_column_powers = qconv_get_const_f_3_DIF_std2rev_forward(block_size_height);

    qconv_inner_uint8 *inverse_row_powers = qconv_get_const_f_3_DIT_rev2std_inverse(block_size_width);
    qconv_inner_uint8 *inverse_column_powers = qconv_get_const_f_3_DIT_rev2std_inverse(block_size_height);

    //pad and transform kernel
    qconv_uint16_mod kernel_block[block_size];
    qconv_bottom_right_zero_pad_uint16_2D_array(block_size_width, block_size_height, kernel_size_width,
                                                kernel_size_height, kernel, kernel_block);

    qconv_NTT_2D_uint16_mod_f_3(block_size_width, block_size_height, kernel_block, optimize_level);

    /*
     * INNER ROWS OF BLOCKS
     */

    while (input_offset_height <= input_size_height - block_size_height) {

        input_offset_width = 0;
        output_offset_width = 0;

        /*
         * LEFT INNER BLOCKS
         */

        while (input_offset_width <= input_size_width - block_size_width) {

            qconv_block_convolution_uint16_mod_f_3_no_pad(input_size_width, input_size_height,
                                                          block_size_width, block_size_height,
                                                          block_size,
                                                          log2_block_size_width, log2_block_size_height,
                                                          output_size_width, output_size_height,
                                                          input_offset_width, input_offset_height,
                                                          output_offset_width, output_offset_height,
                                                          discard_subblock_size_width, discard_subblock_size_height,
                                                          valid_subblock_size_width, valid_subblock_size_height,
                                                          norm_const,
                                                          forward_row_powers, forward_column_powers,
                                                          inverse_row_powers, inverse_column_powers,
                                                          input, kernel_block, output,
                                                          optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_subblock_size_width;

        }

        /*
         * STEP 2.3: RIGHT BLOCKS THAT REQUIRE RIGHT PADDING
         */

        while (input_offset_width < input_size_width) {

            int valid_output_subblock_size_width = output_size_width - output_offset_width;
            valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

            qconv_block_convolution_uint16_mod_f_3_right_pad(input_size_width, input_size_height,
                                                             block_size_width, block_size_height,
                                                             block_size,
                                                             log2_block_size_width, log2_block_size_height,
                                                             output_size_width, output_size_height,
                                                             input_offset_width, input_offset_height,
                                                             output_offset_width, output_offset_height,
                                                             discard_subblock_size_width, discard_subblock_size_height,
                                                             valid_subblock_size_width, valid_subblock_size_height,
                                                             norm_const,
                                                             forward_row_powers, forward_column_powers,
                                                             inverse_row_powers, inverse_column_powers,
                                                             input, kernel_block, output,
                                                             optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_output_subblock_size_width;
        }

        input_offset_height += valid_subblock_size_height;
        output_offset_height += valid_subblock_size_height;
    }

    /*
     * BOTTOM ROW OF BLOCKS
     */

    while (input_offset_height < input_size_height) {

        input_offset_width = 0;
        output_offset_width = 0;

        int valid_input_subblock_size_height = input_size_height - input_offset_height;

        int valid_output_subblock_size_height = output_size_height - output_offset_height;
        valid_output_subblock_size_height = valid_output_subblock_size_height < valid_subblock_size_height ? valid_output_subblock_size_height : valid_subblock_size_height;

        /*
         * LEFT BOTTOM ROW OF BLOCKS THAT REQUIRES BOTTOM PADDING
         */

        while (input_offset_width <= input_size_width - block_size_width) {

            qconv_block_convolution_uint16_mod_f_3_bottom_pad(input_size_width, input_size_height,
                                                              block_size_width, block_size_height,
                                                              block_size,
                                                              log2_block_size_width, log2_block_size_height,
                                                              output_size_width, output_size_height,
                                                              input_offset_width, input_offset_height,
                                                              output_offset_width, output_offset_height,
                                                              discard_subblock_size_width, discard_subblock_size_height,
                                                              valid_subblock_size_width, valid_subblock_size_height,
                                                              valid_input_subblock_size_height, valid_output_subblock_size_height,
                                                              norm_const,
                                                              forward_row_powers, forward_column_powers,
                                                              inverse_row_powers, inverse_column_powers,
                                                              input, kernel_block, output,
                                                              optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_subblock_size_width;
        }

        /*
         * BOTTOM RIGHT BLOCKS THAT REQUIRES BOTTOM RIGHT PADDING
         */

        while (input_offset_width < input_size_width) {

            int valid_output_subblock_size_width = output_size_width - output_offset_width;
            valid_output_subblock_size_width = valid_output_subblock_size_width < valid_subblock_size_width ? valid_output_subblock_size_width : valid_subblock_size_width;

            qconv_block_convolution_uint16_mod_f_3_bottom_right_pad(input_size_width, input_size_height,
                                                                    block_size_width, block_size_height,
                                                                    block_size,
                                                                    log2_block_size_width, log2_block_size_height,
                                                                    output_size_width, output_size_height,
                                                                    input_offset_width, input_offset_height,
                                                                    output_offset_width, output_offset_height,
                                                                    discard_subblock_size_width, discard_subblock_size_height,
                                                                    valid_subblock_size_width, valid_subblock_size_height,
                                                                    valid_input_subblock_size_height, valid_output_subblock_size_height,
                                                                    norm_const,
                                                                    forward_row_powers, forward_column_powers,
                                                                    inverse_row_powers, inverse_column_powers,
                                                                    input, kernel_block, output,
                                                                    optimize_level);

            input_offset_width += valid_subblock_size_width;
            output_offset_width += valid_output_subblock_size_width;
        }
        input_offset_height += valid_subblock_size_height;
        output_offset_height += valid_output_subblock_size_height;
    }
    return status_success;
}


