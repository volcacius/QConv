//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4.h"

extern inline qconv_uint32_mod_f_4 qconv_mul_uint32_mod_f_4(const qconv_uint32_mod_f_4 x, const qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_add_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_subtract_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_subtract_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_add_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_reduce_int32_mod_f_4(qconv_inner_int32 x);

extern inline void qconv_pmul_mod_f_4(const size_t size,
                                      const qconv_uint32_mod a[static const size],
                                      const qconv_uint32_mod b[static const size],
                                      qconv_uint32_mod c[static size]);

qconv_uint32_mod_f_4 qconv_power_uint32_mod_f_4(qconv_uint32_mod_f_4 base, unsigned int exp) {
    qconv_uint32_mod_f_4 res = {.value = (qconv_inner_uint32) 1};
    while(exp > 0) {
        if (exp % 2 == 1) {
            res = qconv_mul_uint32_mod_f_4(res, base);
        }
        base = qconv_mul_uint32_mod_f_4(base, base);
        exp /= 2;
    }
    return res;
}

void qconv_INTT_1D_size_norm_uint32_mod_f_4(const size_t size, qconv_uint32_mod a[static size]) {
    qconv_uint32_mod to_invert = {.uint32.value = size};
    qconv_uint32_mod_f_4 inv = qconv_inverse_uint32_mod_f_4(to_invert);

    //#pragma omp parallel for
    for (size_t j = 0; j < size; j++) {
        a[j].mod_f_4 = qconv_mul_uint32_mod_f_4(a[j].mod_f_4, inv);
    }
}

void qconv_INTT_2D_size_norm_uint32_mod_f_4(const size_t size_width,
                                            const size_t size_height,
                                            qconv_uint32_mod a[static size_width * size_height]) {
    qconv_INTT_1D_size_norm_uint32_mod_f_4(size_width * size_height, a);
}

qconv_uint32_mod_f_4 qconv_inverse_uint32_mod_f_4(qconv_uint32_mod a) {
    // If a and module are relatively prime, then modulo inverse is a^(m-2) mode m
    return qconv_power_uint32_mod_f_4(a.mod_f_4, (unsigned int) (qconv_const_f_4.mod_f_4.value - 2));
}

void qconv_DIT_r2_std2std_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size,
                                            const bool inverse) {
    qconv_bit_reverse_uint32_array_order(size, a);
    qconv_DIT_r2_rev2std_1D_uint32_mod_f_4(size, log2_size, a, p_root, p_root_size, inverse);
}

void qconv_DIT_r2_rev2std_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size,
                                            bool inverse) {
    //get N root of unity
    if (inverse) {
        p_root.mod_f_4 = qconv_power_uint32_mod_f_4(p_root.mod_f_4,
                                                    p_root_size - (p_root_size / size));
    } else {
        p_root.mod_f_4 = qconv_power_uint32_mod_f_4(p_root.mod_f_4,
                                                    (p_root_size / size));
    }

    //printf("size %d\n", size);
    //optimize first iteration of outermost loop
    for (size_t first_iter = 0; first_iter < size; first_iter+= 2) {
        const qconv_uint32_mod temp = a[first_iter + 1];
        a[first_iter + 1].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[first_iter].mod_f_4, temp.mod_f_4);
        a[first_iter].mod_f_4 = qconv_add_uint32_mod_f_4(a[first_iter].mod_f_4, temp.mod_f_4);
    }

    for (size_t log2_m = 2; log2_m <= log2_size; log2_m++) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        const qconv_uint32_mod_f_4 dw = qconv_power_uint32_mod_f_4(p_root.mod_f_4, (1 << (log2_size - log2_m)));
        for (size_t r = 0; r < size; r += m) {
            qconv_uint32_mod_f_4 w = {.value = 1};
            for (size_t j = 0; j < mh; j++) {
                //printf("%d, ", w.value);
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint32_mod_f_4 u = a[t1].mod_f_4;
                const qconv_uint32_mod_f_4 v = qconv_mul_uint32_mod_f_4(a[t2].mod_f_4, w);
                a[t1].mod_f_4 = qconv_add_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_subtract_uint32_mod_f_4(u, v);
                w = qconv_mul_uint32_mod_f_4(w, dw);
            }
        }
    }
}

void qconv_DIF_r2_std2rev_1D_uint32_mod_f_4(const size_t size,
                                            const size_t log2_size,
                                            qconv_uint32_mod a[static size],
                                            qconv_uint32_mod p_root,
                                            const size_t p_root_size) {
    //get N root of unity
    p_root.mod_f_4 = qconv_power_uint32_mod_f_4(p_root.mod_f_4,
                                                (p_root_size / size));
    //printf("size %d\n", size);

    for (size_t log2_m = log2_size; log2_m >= 2; log2_m--) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        const qconv_uint32_mod_f_4 dw = qconv_power_uint32_mod_f_4(p_root.mod_f_4, (1 << (log2_size - log2_m)));
        for (size_t r = 0; r < size; r += m) {
            qconv_uint32_mod_f_4 w = {.value = 1};
            for (size_t j = 0; j < mh; j++) {
                //printf("%d, ", w.value);
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint32_mod_f_4 u = a[t1].mod_f_4;
                const qconv_uint32_mod_f_4 v = a[t2].mod_f_4;
                a[t1].mod_f_4 = qconv_add_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_subtract_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_mul_uint32_mod_f_4(a[t2].mod_f_4, w);
                w = qconv_mul_uint32_mod_f_4(w, dw);
            }
        }
    }
    //optimize last iteration of outermost loop
    for (size_t last_iter = 0; last_iter < size; last_iter+= 2) {
        const qconv_uint32_mod temp = a[last_iter + 1];
        a[last_iter + 1].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[last_iter].mod_f_4, temp.mod_f_4);
        a[last_iter].mod_f_4 = qconv_add_uint32_mod_f_4(a[last_iter].mod_f_4, temp.mod_f_4);
    }
}

void qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers) {
    size_t power_index = 0;
    for (size_t log2_m = log2_size; log2_m >= 2; log2_m--) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        for (size_t r = 0; r < size; r += m) {
            for (size_t j = 0; j < mh; j++) {
                qconv_uint32_mod_f_4 w = {.value = powers[power_index]};
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint32_mod_f_4 u = a[t1].mod_f_4;
                const qconv_uint32_mod_f_4 v = a[t2].mod_f_4;
                a[t1].mod_f_4 = qconv_add_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_subtract_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_mul_uint32_mod_f_4(a[t2].mod_f_4, w);
                power_index++;
            }
        }
    }
    //optimize last iteration of outermost loop
    for (size_t last_iter = 0; last_iter < size; last_iter+= 2) {
        const qconv_uint32_mod temp = a[last_iter + 1];
        a[last_iter + 1].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[last_iter].mod_f_4, temp.mod_f_4);
        a[last_iter].mod_f_4 = qconv_add_uint32_mod_f_4(a[last_iter].mod_f_4, temp.mod_f_4);
    }
}

void qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers) {
    qconv_bit_reverse_uint32_array_order(size, a);
    qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(size, log2_size, a, powers);

}

void qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(const size_t size,
                                                    const size_t log2_size,
                                                    qconv_uint32_mod a[static size],
                                                    const qconv_inner_uint16 *powers) {
    //optimize first iteration of outermost loop
    for (size_t first_iter = 0; first_iter < size; first_iter+= 2) {
        const qconv_uint32_mod temp = a[first_iter + 1];
        a[first_iter + 1].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[first_iter].mod_f_4, temp.mod_f_4);
        a[first_iter].mod_f_4 = qconv_add_uint32_mod_f_4(a[first_iter].mod_f_4, temp.mod_f_4);
    }

    size_t power_index = 0;
    for (size_t log2_m = 2; log2_m <= log2_size; log2_m++) {
        const size_t m = (1U << log2_m);
        const size_t mh = (m >> 1);
        for (size_t r = 0; r < size; r += m) {
            for (size_t j = 0; j < mh; j++) {
                const size_t t1 = r + j;
                const size_t t2 = t1 + mh;
                const qconv_uint32_mod_f_4 u = a[t1].mod_f_4;
                const qconv_uint32_mod_f_4 w = {.value = powers[power_index]};
                const qconv_uint32_mod_f_4 v = qconv_mul_uint32_mod_f_4(a[t2].mod_f_4, w);
                a[t1].mod_f_4 = qconv_add_uint32_mod_f_4(u, v);
                a[t2].mod_f_4 = qconv_subtract_uint32_mod_f_4(u, v);
                power_index++;
            }
        }
    }
}

enum qconv_status qconv_NTT_1D_uint32_mod_f_4(const size_t size,
                                              qconv_uint32_mod a[static size],
                                              const enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_4_DIF_r2_std2rev_size_8_forward);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_4_DIT_r2_std2std_size_8_forward);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                           qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, false);
                    return status_success;
            }
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_4_DIF_r2_std2rev_size_16_forward);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_4_DIT_r2_std2std_size_16_forward);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                           qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, false);
                    return status_success;
            }
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
        case QCONV_SIZE_512:
        case QCONV_SIZE_1024:
        case QCONV_SIZE_2048:
            qconv_DIT_r2_std2std_1D_uint32_mod_f_4(size, qconv_get_log2_power_of_two(size), a,
                                                   qconv_const_p_root_f_4_size_65536, QCONV_SIZE_65536, false);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_1D_uint32_mod_f_4(const size_t size, qconv_uint32_mod a[static size], enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_4_DIT_r2_rev2std_size_8_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, a);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                                   qconv_const_f_4_DIT_r2_std2std_size_8_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, a);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint32_mod_f_4(QCONV_SIZE_8, QCONV_LOG_SIZE_8, a,
                                                           qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, true);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, a);
                    return status_success;
            }
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_order:
                    qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_4_DIT_r2_rev2std_size_16_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, a);
                    return status_success;
                case optimize_precomp:
                    qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                                   qconv_const_f_4_DIT_r2_std2std_size_16_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, a);
                    return status_success;
                case optimize_null:
                default:
                    qconv_DIT_r2_std2std_1D_uint32_mod_f_4(QCONV_SIZE_16, QCONV_LOG_SIZE_16, a,
                                                           qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, true);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, a);
                    return status_success;
            }
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
        case QCONV_SIZE_512:
        case QCONV_SIZE_1024:
        case QCONV_SIZE_2048:
            qconv_DIT_r2_std2std_1D_uint32_mod_f_4(size, qconv_get_log2_power_of_two(size), a,
                                                   qconv_const_p_root_f_4_size_65536, QCONV_SIZE_65536, true);
            qconv_INTT_1D_size_norm_uint32_mod_f_4(size, a);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_1D_circular_convolution_uint32_mod_f_4(const size_t size,
                                                                   qconv_uint32_mod input[static size],
                                                                   qconv_uint32_mod kernel[static size],
                                                                   qconv_uint32_mod ntt[size],
                                                                   enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_NTT_1D_uint32_mod_f_4(size, input, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_1D_uint32_mod_f_4(size, kernel, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);
    qconv_pmul_mod_f_4(size, input, kernel, ntt);
    status = qconv_INTT_1D_uint32_mod_f_4(size, ntt, optimize_level);
    return status;
}

enum qconv_status qconv_NTT_1D_linear_convolution_uint32_mod_f_4(const size_t input_size,
                                                                 const size_t kernel_size,
                                                                 qconv_uint32_mod input[static input_size],
                                                                 qconv_uint32_mod kernel[static kernel_size],
                                                                 qconv_uint32_mod ntt[static input_size + kernel_size - 1],
                                                                 const enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;

    size_t size;
    if (input_size >= kernel_size) {
        size = input_size * 2;
    } else {
        size = kernel_size * 2;
    }
    qconv_uint32_mod input_padded[size];
    qconv_uint32_mod kernel_padded[size];
    qconv_uint32_mod ntt_padded[size];

    //Zero pad input and kernel
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_right_zero_pad_uint32_1D_array(size, input_size, input, input_padded);
        }
        #pragma omp section
        {
            status_bis = qconv_right_zero_pad_uint32_1D_array(size, kernel_size, kernel, kernel_padded);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    //Perform transform
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_NTT_1D_uint32_mod_f_4(size, input_padded, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_1D_uint32_mod_f_4(size, kernel_padded, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    qconv_pmul_mod_f_4(size, input_padded, kernel_padded, ntt_padded);

    status = qconv_INTT_1D_uint32_mod_f_4(size, ntt_padded, optimize_level);
    CHECK_STATUS(status);

    status = qconv_slice_uint32_1D_array(size, input_size + kernel_size - 1, 0, ntt_padded, ntt);

    return status;
}

void qconv_DIT_rev2std_2D_uint32_mod_f_4(const size_t size_width,
                                         const size_t size_height,
                                         const size_t log2_size_width,
                                         const size_t log2_size_height,
                                         qconv_uint32_mod a[static size_width * size_height],
                                         qconv_uint32_mod row_p_root,
                                         qconv_uint32_mod column_p_root,
                                         const size_t row_p_root_size,
                                         const size_t column_p_root_size) {
    //row transform
    //#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_rev2std_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_p_root,
                                               row_p_root_size, false);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    //#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_rev2std_1D_uint32_mod_f_4(size_height,
                                               log2_size_height,
                                               &a_transpose[a_transpose_column * size_height],
                                               column_p_root,
                                               column_p_root_size,
                                               false);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_std2std_2D_uint32_mod_f_4(const size_t size_width,
                                         const size_t size_height,
                                         const size_t log2_size_width,
                                         const size_t log2_size_height,
                                         qconv_uint32_mod a[static size_width * size_height],
                                         qconv_uint32_mod row_p_root,
                                         qconv_uint32_mod column_p_root,
                                         const size_t row_p_root_size,
                                         const size_t column_p_root_size,
                                         const bool inverse) {
    //row transform
#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_std2std_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_p_root,
                                               row_p_root_size, inverse);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_std2std_1D_uint32_mod_f_4(size_height,
                                               log2_size_height,
                                               &a_transpose[a_transpose_column * size_height],
                                               column_p_root,
                                               column_p_root_size,
                                               inverse);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIF_std2rev_2D_uint32_mod_f_4(const size_t size_width,
                                         const size_t size_height,
                                         const size_t log2_size_width,
                                         const size_t log2_size_height,
                                         qconv_uint32_mod a[static size_width * size_height],
                                         qconv_uint32_mod row_p_root,
                                         qconv_uint32_mod column_p_root,
                                         const size_t row_p_root_size,
                                         const size_t column_p_root_size) {
    //row transform
    //#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIF_r2_std2rev_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_p_root,
                                               row_p_root_size);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    //#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIF_r2_std2rev_1D_uint32_mod_f_4(size_height,
                                               log2_size_height,
                                               &a_transpose[a_transpose_column * size_height],
                                               column_p_root,
                                               column_p_root_size);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_std2std_2D_precomp_uint32_mod_f_4(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint32_mod a[static size_width * size_height],
                                                 const qconv_inner_uint16 *row_powers,
                                                 const qconv_inner_uint16 *column_powers) {
    //row transform
    //#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    //#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_std2std_precomp_1D_uint32_mod_f_4(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIT_rev2std_2D_precomp_uint32_mod_f_4(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint32_mod a[static size_width * size_height],
                                                 const qconv_inner_uint16 *row_powers,
                                                 const qconv_inner_uint16 *column_powers) {
    //row transform
    //#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    //#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIT_r2_rev2std_precomp_1D_uint32_mod_f_4(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_DIF_std2rev_2D_precomp_uint32_mod_f_4(const size_t size_width,
                                                 const size_t size_height,
                                                 const size_t log2_size_width,
                                                 const size_t log2_size_height,
                                                 qconv_uint32_mod a[static size_width * size_height],
                                                 const qconv_inner_uint16 *row_powers,
                                                 const qconv_inner_uint16 *column_powers) {
    //row transform
    //#pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(size_width, log2_size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    //#pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_DIF_r2_std2rev_precomp_1D_uint32_mod_f_4(size_height, log2_size_height,
                                                       &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

enum qconv_status qconv_NTT_2D_uint32_mod_f_4_inner2x(const size_t size_width,
                                                      const size_t size_height,
                                                      qconv_uint32_mod a[static size_width * size_height],
                                                      enum qconv_optimize_transform optimize_level,
                                                      qconv_uint32_mod row_p_root,
                                                      qconv_uint32_mod column_p_root,
                                                      const size_t row_p_root_size,
                                                      const size_t column_p_root_size) {
    switch(optimize_level) {
        case optimize_precomp_order:
            qconv_DIF_std2rev_2D_precomp_uint32_mod_f_4(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_4_DIF_std2rev_forward(size_width),
                                                        qconv_get_const_f_4_DIF_std2rev_forward(size_height));
            return status_success;
        case optimize_order:
            qconv_DIF_std2rev_2D_uint32_mod_f_4(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                column_p_root,
                                                row_p_root_size,
                                                column_p_root_size);
            return status_success;
        case optimize_precomp:
            qconv_DIT_std2std_2D_precomp_uint32_mod_f_4(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_4_DIT_std2std_forward(size_width),
                                                        qconv_get_const_f_4_DIT_std2std_forward(size_height));
            return status_success;
        case optimize_null:
        default:
            qconv_DIT_std2std_2D_uint32_mod_f_4(size_width,
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

enum qconv_status qconv_NTT_2D_uint32_mod_f_4_inner(const size_t size_width,
                                                    const size_t size_height,
                                                    qconv_uint32_mod a[static size_width * size_height],
                                                    enum qconv_optimize_transform optimize_level,
                                                    qconv_uint32_mod row_p_root,
                                                    const size_t row_p_root_size) {
    switch (size_height) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_NTT_2D_uint32_mod_f_4_inner2x(size_width,
                                                       size_height,
                                                       a,
                                                       optimize_level,
                                                       row_p_root,
                                                       qconv_const_p_root_f_4_size_32,
                                                       row_p_root_size,
                                                       QCONV_SIZE_32);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
        case optimize_order:
            qconv_DIF_std2rev_2D_uint32_mod_f_4(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                qconv_const_p_root_f_4_size_65536,
                                                row_p_root_size,
                                                QCONV_SIZE_65536);
            return status_success;
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_2D_uint32_mod_f_4(const size_t size_width,
                                              const size_t size_height,
                                              qconv_uint32_mod a[static size_width * size_height],
                                              enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_NTT_2D_uint32_mod_f_4_inner(size_width,
                                                     size_height,
                                                     a,
                                                     optimize_level,
                                                     qconv_const_p_root_f_4_size_32,
                                                     QCONV_SIZE_32);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            return qconv_NTT_2D_uint32_mod_f_4_inner(size_width,
                                                     size_height,
                                                     a,
                                                     optimize_level,
                                                     qconv_const_p_root_f_4_size_65536,
                                                     QCONV_SIZE_65536);
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_2D_uint32_mod_f_4_inner2x(const size_t size_width,
                                                       const size_t size_height,
                                                       qconv_uint32_mod a[static size_width * size_height],
                                                       enum qconv_optimize_transform optimize_level,
                                                       qconv_uint32_mod row_p_root,
                                                       qconv_uint32_mod column_p_root,
                                                       const size_t row_p_root_size,
                                                       const size_t column_p_root_size) {
    switch(optimize_level) {
        case optimize_precomp_order:
            qconv_DIT_rev2std_2D_precomp_uint32_mod_f_4(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_4_DIT_rev2std_inverse(size_width),
                                                        qconv_get_const_f_4_DIT_rev2std_inverse(size_height));
            qconv_INTT_2D_size_norm_uint32_mod_f_4(size_width, size_height, a);
            return status_success;
        case optimize_order:
            qconv_DIT_rev2std_2D_uint32_mod_f_4(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                column_p_root,
                                                row_p_root_size,
                                                column_p_root_size);
            qconv_INTT_2D_size_norm_uint32_mod_f_4(size_width, size_height, a);
        case optimize_precomp:
            qconv_DIT_std2std_2D_precomp_uint32_mod_f_4(size_width,
                                                        size_height,
                                                        qconv_get_log2_power_of_two(size_width),
                                                        qconv_get_log2_power_of_two(size_height),
                                                        a,
                                                        qconv_get_const_f_4_DIT_std2std_inverse(size_width),
                                                        qconv_get_const_f_4_DIT_std2std_inverse(size_height));
            qconv_INTT_2D_size_norm_uint32_mod_f_4(size_width, size_height, a);
            return status_success;
        case optimize_null:
        default:
            qconv_DIT_std2std_2D_uint32_mod_f_4(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                column_p_root,
                                                row_p_root_size,
                                                column_p_root_size,
                                                true);
            qconv_INTT_2D_size_norm_uint32_mod_f_4(size_width, size_height, a);
            return status_success;
    }

}

enum qconv_status qconv_INTT_2D_uint32_mod_f_4_inner(const size_t size_width,
                                                     const size_t size_height,
                                                     qconv_uint32_mod a[static size_width * size_height],
                                                     enum qconv_optimize_transform optimize_level,
                                                     qconv_uint32_mod row_p_root,
                                                     const size_t row_p_root_size) {
    switch (size_height) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_INTT_2D_uint32_mod_f_4_inner2x(size_width,
                                                        size_height,
                                                        a,
                                                        optimize_level,
                                                        row_p_root,
                                                        qconv_const_p_root_f_4_size_32,
                                                        row_p_root_size,
                                                        QCONV_SIZE_32);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            qconv_DIT_rev2std_2D_uint32_mod_f_4(size_width,
                                                size_height,
                                                qconv_get_log2_power_of_two(size_width),
                                                qconv_get_log2_power_of_two(size_height),
                                                a,
                                                row_p_root,
                                                qconv_const_p_root_f_4_size_65536,
                                                row_p_root_size,
                                                QCONV_SIZE_65536);
            qconv_INTT_2D_size_norm_uint32_mod_f_4(size_width, size_height, a);
            return status_success;
        default:
            return status_invalid_input_size;

    }
}

enum qconv_status qconv_INTT_2D_uint32_mod_f_4(const size_t size_width,
                                               const size_t size_height,
                                               qconv_uint32_mod a[static size_width * size_height],
                                               enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
        case QCONV_SIZE_16:
            return qconv_INTT_2D_uint32_mod_f_4_inner(size_width,
                                                      size_height,
                                                      a,
                                                      optimize_level,
                                                      qconv_const_p_root_f_4_size_32,
                                                      QCONV_SIZE_32);
        case QCONV_SIZE_32:
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
            return qconv_INTT_2D_uint32_mod_f_4_inner(size_width,
                                                      size_height,
                                                      a,
                                                      optimize_level,
                                                      qconv_const_p_root_f_4_size_65536,
                                                      QCONV_SIZE_65536);
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_NTT_2D_circular_convolution_uint32_mod_f_4(const size_t size_width,
                                                                   const size_t size_height,
                                                                   qconv_uint32_mod a[static size_width * size_height],
                                                                   qconv_uint32_mod b[static size_width * size_height],
                                                                   qconv_uint32_mod ntt[size_width * size_height],
                                                                   enum qconv_optimize_transform optimize_level) {
    enum qconv_status status, status_bis;
    #pragma omp sections
    {
        #pragma omp section
        {
            status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, a, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, b, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);
    qconv_pmul_mod_f_4(size_width * size_height, a, b, ntt);
    status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, ntt, optimize_level);
    return status;
}

enum qconv_status qconv_NTT_2D_linear_convolution_uint32_mod_f_4(const size_t input_size_width,
                                                                 const size_t input_size_height,
                                                                 const size_t kernel_size_width,
                                                                 const size_t kernel_size_height,
                                                                 qconv_uint32_mod input[static input_size_width * input_size_height],
                                                                 qconv_uint32_mod kernel[static kernel_size_width * kernel_size_height],
                                                                 qconv_uint32_mod ntt[(input_size_width + kernel_size_width - 1) * (input_size_height + kernel_size_height - 1)],
                                                                 enum qconv_optimize_transform optimize_level) {
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
    qconv_uint32_mod input_padded[size_width * size_height];
    qconv_uint32_mod kernel_padded[size_width * size_height];
    qconv_uint32_mod ntt_padded[size_width * size_height];

    //Zero pad input and kernel
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_bottom_right_zero_pad_uint32_2D_array(size_width, size_height, input_size_width, input_size_height, input, input_padded);
        }
        #pragma omp section
        {
            status_bis = qconv_bottom_right_zero_pad_uint32_2D_array(size_width, size_height, kernel_size_width, kernel_size_height, kernel, kernel_padded);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    //Perform transform
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            status = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, input_padded, optimize_level);
        }
        #pragma omp section
        {
            status_bis = qconv_NTT_2D_uint32_mod_f_4(size_width, size_height, kernel_padded, optimize_level);
        }
    }
    CHECK_STATUS(status);
    CHECK_STATUS(status_bis);

    qconv_pmul_mod_f_4(size_width * size_height, input_padded, kernel_padded, ntt_padded);

    status = qconv_INTT_2D_uint32_mod_f_4(size_width, size_height, ntt_padded, optimize_level);
    CHECK_STATUS(status);

    status = qconv_slice_uint32_2D_array(size_width,
                                         size_height,
                                         input_size_width + kernel_size_width - 1,
                                         input_size_height + kernel_size_height - 1,
                                         0,
                                         0,
                                         ntt_padded,
                                         ntt);
    return status;
}



