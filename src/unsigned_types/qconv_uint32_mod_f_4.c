//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4.h"

extern inline qconv_uint32_mod_f_4 qconv_mul_uint32_mod_f_4(const qconv_uint32_mod_f_4 x, const qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_add_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_subtract_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_subtract_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_add_uint32_mod_f_4(qconv_uint32_mod_f_4 x, qconv_uint32_mod_f_4 y);

extern inline qconv_uint32_mod_f_4 qconv_reduce_int64_mod_f_4(qconv_inner_int64 x);

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

    #pragma omp parallel for
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

void qconv_CT_1D_uint32_mod_f_4(const size_t size,
                                qconv_uint32_mod a[static size],
                                const qconv_uint32_mod p_root,
                                const size_t p_root_size,
                                const bool inverse) {
    size_t m, i, j, istep, mmax;
    qconv_uint32_mod w, wt, wr, wtemp;
    qconv_bit_reverse_uint32_array_order(size, a);
    if (inverse) {
        w.mod_f_4 = qconv_power_uint32_mod_f_4(p_root.mod_f_4,
                                              p_root_size - ((p_root_size) / size));
    } else {
        w.mod_f_4 = qconv_power_uint32_mod_f_4(p_root.mod_f_4,
                                              (p_root_size) / size);
    }
    mmax = 1;
    size_t powers_index = 0;
    //printf("Size %d\n", size);
    while (size > mmax) {
        istep = mmax << 1;
        wt.mod_f_4 = qconv_power_uint32_mod_f_4(w.mod_f_4, (size / istep));
        wr.mod_f_4 = wt.mod_f_4;
        for (i = 0; i < size; i += istep) {
            j = i + mmax;
            wtemp = a[j];
            a[j].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[i].mod_f_4, a[j].mod_f_4);
            a[i].mod_f_4 = qconv_add_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
        }
        for (m = 1; m < mmax; m++) {
            for (i = m; i < size; i += istep) {
                j = i + mmax;
                //printf("[%d].value = %d,\n", powers_index, wr.mod_f_4.value);
                wtemp.mod_f_4 = qconv_mul_uint32_mod_f_4(wr.mod_f_4, a[j].mod_f_4);
                a[j].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
                a[i].mod_f_4= qconv_add_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
                powers_index++;
            }
            wr.mod_f_4 = qconv_mul_uint32_mod_f_4(wr.mod_f_4, wt.mod_f_4);
        }
        mmax = istep;
    }
}

void qconv_CT_1D_precomp_uint32_mod_f_4(const size_t size,
                                        qconv_uint32_mod a[static size],
                                        const qconv_uint16 *powers) {
    size_t m, i, j, istep, mmax;
    qconv_uint32_mod wtemp;
    qconv_bit_reverse_uint32_array_order(size, a);
    mmax = 1;
    size_t powers_index = 0;
    while (size > mmax) {
        istep = mmax << 1;

        for (i = 0; i < size; i += istep) {
            j = i + mmax;
            wtemp = a[j];
            a[j].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[i].mod_f_4, a[j].mod_f_4);
            a[i].mod_f_4 = qconv_add_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
        }

        for (m = 1; m < mmax; m++) {
            for (i = m; i < size; i += istep) {
                j = i + mmax;
                qconv_uint32_mod power = {.mod_f_4.value = (qconv_inner_uint32) powers[powers_index].value};
                wtemp.mod_f_4 = qconv_mul_uint32_mod_f_4(power.mod_f_4, a[j].mod_f_4);
                a[j].mod_f_4 = qconv_subtract_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
                a[i].mod_f_4= qconv_add_uint32_mod_f_4(a[i].mod_f_4, wtemp.mod_f_4);
                powers_index++;
            }
        }
        mmax = istep;
    }
}

enum qconv_status qconv_NTT_1D_uint32_mod_f_4(const size_t size,
                                              qconv_uint32_mod a[static size],
                                              const enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:    
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_8, a, qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_8, a, qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, false);
                    break;
            }
            return status_success;
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_16, a, qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_16, a, qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, false);
                    break;
            }
            return status_success;
        case QCONV_SIZE_32:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_32, a, qconv_const_uint32_mod_f_4_CT_precomp_size_32_forward);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_32, a, qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, false);
                    break;
            }
            return status_success;
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
        case QCONV_SIZE_512:
        case QCONV_SIZE_1024:
        case QCONV_SIZE_2048:
            qconv_CT_1D_uint32_mod_f_4(size, a, qconv_const_p_root_f_4_size_65536, QCONV_SIZE_65536, false);
            return status_success;

        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_1D_uint32_mod_f_4(const size_t size, qconv_uint32_mod a[static size], enum qconv_optimize_transform optimize_level) {
    switch(size) {
        case QCONV_SIZE_8:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_8, a, qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, a);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_8, a, qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, true);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, a);
                    break;
            }
            return status_success;
        case QCONV_SIZE_16:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_16, a, qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, a);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_16, a, qconv_const_p_root_f_4_size_32,QCONV_SIZE_32, true);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, a);
                    break;
            }
            return status_success;
        case QCONV_SIZE_32:
            switch (optimize_level) {
                case optimize_precomp_fuse_order:
                case optimize_precomp_fuse:
                case optimize_precomp_order:
                case optimize_precomp:
                    qconv_CT_1D_precomp_uint32_mod_f_4(QCONV_SIZE_32, a, qconv_const_uint32_mod_f_4_CT_precomp_size_32_inverse);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_32, a);
                    break;
                case optimize_null:
                default:
                    qconv_CT_1D_uint32_mod_f_4(QCONV_SIZE_32, a, qconv_const_p_root_f_4_size_32, QCONV_SIZE_32, true);
                    qconv_INTT_1D_size_norm_uint32_mod_f_4(QCONV_SIZE_32, a);
                    break;
            }
            return status_success;
        case QCONV_SIZE_64:
        case QCONV_SIZE_128:
        case QCONV_SIZE_256:
        case QCONV_SIZE_512:
        case QCONV_SIZE_1024:
        case QCONV_SIZE_2048:
            qconv_CT_1D_uint32_mod_f_4(size, a, qconv_const_p_root_f_4_size_65536, QCONV_SIZE_65536, true);
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
            status = qconv_zero_pad_uint32_1D_array(size, input_size, input, input_padded);
        }
        #pragma omp section
        {
            status_bis = qconv_zero_pad_uint32_1D_array(size, kernel_size, kernel, kernel_padded);
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

void qconv_CT_2D_uint32_mod_f_4(const size_t size_width,
                                const size_t size_height,
                                qconv_uint32_mod a[size_width * size_height],
                                qconv_uint32_mod row_p_root,
                                qconv_uint32_mod column_p_root,
                                const size_t row_p_root_size,
                                const size_t column_p_root_size,
                                const bool inverse) {
    //row transform
    #pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_CT_1D_uint32_mod_f_4(size_width, &a[a_row * size_width], row_p_root, row_p_root_size, inverse);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    #pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_CT_1D_uint32_mod_f_4(size_height,
                                   &a_transpose[a_transpose_column * size_height],
                                   column_p_root,
                                   column_p_root_size,
                                   inverse);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

void qconv_CT_2D_precomp_uint32_mod_f_4(const size_t size_width,
                                        const size_t size_height,
                                        qconv_uint32_mod a[size_width * size_height],
                                        const qconv_uint16 *row_powers,
                                        const qconv_uint16 *column_powers) {
    //row transform
    #pragma omp parallel for
    for (size_t a_row = 0; a_row < size_height; a_row++) {
        qconv_CT_1D_precomp_uint32_mod_f_4(size_width, &a[a_row * size_width], row_powers);
    }

    //transpose
    qconv_uint32_mod a_transpose[size_height * size_width];
    qconv_transpose_uint32_2D(size_width, size_height, a, a_transpose);

    //column transform
    #pragma omp parallel for
    for (size_t a_transpose_column = 0; a_transpose_column < size_width; a_transpose_column++) {
        qconv_CT_1D_precomp_uint32_mod_f_4(size_height, &a_transpose[a_transpose_column * size_height], column_powers);
    }

    //transpose back
    qconv_transpose_uint32_2D(size_height, size_width, a_transpose, a);
}

enum qconv_status qconv_NTT_2D_uint32_mod_f_4(const size_t size_width,
                                              const size_t size_height,
                                              qconv_uint32_mod a[static size_width * size_height],
                                              const enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
            switch(size_height) {
                case QCONV_SIZE_8:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_8,
                                                               QCONV_SIZE_8,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_8,
                                                       QCONV_SIZE_8,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       false);
                            break;
                    }
                    return status_success;
                case QCONV_SIZE_16:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_8,
                                                               QCONV_SIZE_16,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_8,
                                                       QCONV_SIZE_16,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       false);
                            break;
                    }
                    return status_success;
                default:
                    return status_invalid_input_size;

            }
        case QCONV_SIZE_16:
            switch(size_height) {
                case QCONV_SIZE_8:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_16,
                                                               QCONV_SIZE_8,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_16,
                                                       QCONV_SIZE_8,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       false);
                            break;
                    }
                    return status_success;
                case QCONV_SIZE_16:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_16,
                                                               QCONV_SIZE_16,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_16,
                                                       QCONV_SIZE_16,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       false);
                            break;
                    }
                    return status_success;
                default:
                    return status_invalid_input_size;

            }
        default:
            return status_invalid_input_size;
    }
}

enum qconv_status qconv_INTT_2D_uint32_mod_f_4(const size_t size_width,
                                               const size_t size_height,
                                               qconv_uint32_mod a[static size_width * size_height],
                                               const enum qconv_optimize_transform optimize_level) {
    switch(size_width) {
        case QCONV_SIZE_8:
            switch(size_height) {
                case QCONV_SIZE_8:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_8,
                                                               QCONV_SIZE_8,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, a);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_8,
                                                       QCONV_SIZE_8,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       true);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_8, a);
                            break;
                    }
                    return status_success;
                case QCONV_SIZE_16:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_8,
                                                               QCONV_SIZE_16,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_16, a);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_8,
                                                       QCONV_SIZE_16,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       true);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_8, QCONV_SIZE_16, a);
                            break;
                    }
                    return status_success;
                default:
                    return status_invalid_input_size;

            }
        case QCONV_SIZE_16:
            switch(size_height) {
                case QCONV_SIZE_8:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_16,
                                                               QCONV_SIZE_8,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_8, a);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_16,
                                                       QCONV_SIZE_8,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       true);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_8, a);
                            break;
                    }
                    return status_success;
                case QCONV_SIZE_16:
                    switch(optimize_level) {
                        case optimize_precomp_fuse_order:
                        case optimize_precomp_fuse:
                        case optimize_precomp_order:
                        case optimize_precomp:
                            qconv_CT_2D_precomp_uint32_mod_f_4(QCONV_SIZE_16,
                                                               QCONV_SIZE_16,
                                                               a,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse,
                                                               qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, a);
                            break;
                        case optimize_null:
                        default:
                            qconv_CT_2D_uint32_mod_f_4(QCONV_SIZE_16,
                                                       QCONV_SIZE_16,
                                                       a,
                                                       qconv_const_p_root_f_4_size_32,
                                                       qconv_const_p_root_f_4_size_32,
                                                       QCONV_SIZE_32,
                                                       QCONV_SIZE_32,
                                                       true);
                            qconv_INTT_2D_size_norm_uint32_mod_f_4(QCONV_SIZE_16, QCONV_SIZE_16, a);
                            break;
                    }
                    return status_success;
                default:
                    return status_invalid_input_size;

            }
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
    #pragma omp parallel sections
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
            status = qconv_zero_pad_uint32_2D_array(size_width, size_height, input_size_width, input_size_height, input, input_padded);
        }
        #pragma omp section
        {
            status_bis = qconv_zero_pad_uint32_2D_array(size_width, size_height, kernel_size_width, kernel_size_height, kernel, kernel_padded);
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



