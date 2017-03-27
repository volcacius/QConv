//
// Created by alessandro on 3/27/17.
//

#include "qconv_test_crt.h"

void qconv_test_NTT_1D_convolution_mod_crt_f_3_f_4(size_t size, size_t bit_size, enum qconv_optimize_transform optimize_level) {
    double direct_tot_time = 0;
    double ntt_tot_time = 0;
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        qconv_uint32_mod input[size], kernel[size], conv[size], ntt[size];
        qconv_test_util_random_uint32_1D_array(size, input, bit_size);
        qconv_test_util_random_uint32_1D_array(size, kernel, bit_size);
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint32_direct_1D_circular_convolution(size, input, kernel, conv);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);
        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_1D_circular_convolution_mod_crt_f_3_f_4(size, input, kernel, ntt, optimize_level);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint32_1D_array(size, ntt, conv));
    }
    printf(" Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);

}