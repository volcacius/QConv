//
// Created by alessandro on 3/11/17.
//
#include "qconv_test_uint16.h"
#include "qconv_test_uint32.h"
#include "qconv_test_uint16_mod_f_3.h"
#include "qconv_test_uint16_mod_m_13.h"
#include "qconv_test_uint32_mod_f_4.h"
#include "qconv_test_crt.h"
#include "qconv_block.h"

int main() {
    //srand(time(NULL));
    //qconv_test_uint16_runall();
    //qconv_test_uint16_mod_f_3_runall();
    //qconv_test_uint32_runall();
    qconv_test_uint32_mod_f_4_runall();
    //qconv_test_mod_crt_f_3_f_4_run_all();

    /*
    qconv_test_zero_pad_uint32_2D_array();
    const size_t input_size = 512;
    const size_t kernel_size = 11;
    qconv_uint32_mod input[input_size];
    qconv_uint32_mod kernel[kernel_size];
    qconv_uint32_mod output[input_size + kernel_size - 1];
    qconv_uint32_mod direct[input_size + kernel_size - 1];

    double direct_tot_time = 0;
    double ntt_tot_time = 0;
    for (int i = 0; i < 1; i++) {

        qconv_test_util_random_uint32_1D_array(input_size, input, 2);
        qconv_test_util_random_uint32_1D_array(input_size, kernel, 2);
        double direct_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_uint32_direct_1D_linear_convolution(input_size, kernel_size, input, kernel, direct);
        double direct_end_time = (double) clock() / CLOCKS_PER_SEC;
        direct_tot_time += (direct_end_time - direct_start_time);

        double ntt_start_time = (double) clock() / CLOCKS_PER_SEC;
        qconv_NTT_1D_block_linear_convolution_uint32_mod_f_4(input_size, kernel_size, input, kernel, output, optimize_precomp_order);
        double ntt_end_time = (double) clock() / CLOCKS_PER_SEC;
        ntt_tot_time += ntt_end_time - ntt_start_time;
        assert(qconv_test_util_compare_uint32_1D_array(input_size + kernel_size - 1, output, direct));
    }
    printf("\n");

    printf("NTT:\n");
    for (int i = 0; i <input_size + kernel_size - 1; i++) {
        printf("%d ", output[i]);
    }
    printf("Direct:\n");
    for (int i = 0; i <input_size + kernel_size - 1; i++) {
        printf("%d ", direct[i]);
    }
    printf("\n");

    printf("Direct: %fs, NTT %fs, Speed ratio over direct: %f\n\n",
           direct_tot_time, ntt_tot_time, direct_tot_time/ntt_tot_time);*/
}