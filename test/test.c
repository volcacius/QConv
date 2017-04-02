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


void naive_convolution_output_no_padding(
        const size_t input_size_width,
        const size_t input_size_height,
        const size_t kernel_size_width,
        const size_t kernel_size_height,
        const int input[static const input_size_width][input_size_height],
        const int kernel[static const kernel_size_width][kernel_size_height],
        int output[static input_size_width - kernel_size_width + 1][input_size_height - kernel_size_height + 1]
){
    //define offset of the current portion of input that overlaps with the kernel,
    //defined as positive index starting at 0,0 on upper left corner
    size_t i_row_offset = 0;
    size_t i_column_offset = 0;

    //iterate over output rows
    for(size_t o_row = 0; o_row < input_size_height - kernel_size_height + 1; o_row++){

        //iterate over output columns
        for(size_t o_column = 0; o_column < input_size_width - kernel_size_width + 1; o_column++) {

            //set the starting value of a single point of output to 0.
            //a single point of output is the sum of the dot product between the
            //shifted kernel and the overlapped region of input
            //the current overlapped region of input is retrived from i_row_offset, i_column_offset
            output[o_row][o_column] = 0;

            //iterate over kernel rows
            for(size_t k_row = 0; k_row < kernel_size_height; k_row++) {

                //iterate over kernel columns
                for(size_t k_column = 0 ; k_column < kernel_size_width; k_column++){
                    size_t i_row = i_row_offset + k_row;
                    size_t i_column = i_column_offset + k_column;
                    output[o_row][o_column] += input[i_row][i_column] * kernel[k_row][k_column];
                }
            }
            //at the end of the computation of a single output point, compute the new offset for the next point.
            //we shift first the kernel to the right, and when it reaches the end of the input we start again on the left by going down one row
            if (i_column_offset + kernel_size_width == input_size_width) {
                i_column_offset = 0;
                i_row_offset += 1;
            } else {
                i_column_offset += 1;
            }
        }
    }
}