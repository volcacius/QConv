//
// Created by alessandro on 3/11/17.
//
#include "qconv_test_uint16.h"
#include "qconv_test_uint32.h"
#include "qconv_test_uint16_mod_f_3.h"
#include "qconv_test_uint16_mod_m_13.h"
#include "qconv_test_uint32_mod_f_4.h"
#include "qconv_test_crt.h"



int main() {
    srand(time(NULL));
    //qconv_test_uint16_runall();
    qconv_test_uint16_mod_f_3_runall();
    //qconv_test_uint32_runall();
    //qconv_test_uint32_mod_f_4_runall();
    //qconv_test_mod_crt_f_3_f_4_run_all();
    /*size_t size = 8;
    size_t log_size = 3;
    qconv_uint16_mod a[size], original[size];
    qconv_test_util_random_uint16_1D_array(size, a, 2);
    qconv_test_util_clone_uint16_1D_array(size, a, original);
    //qconv_DIF_r2_std2rev_precomp_1D_uint16_mod_f_3(size, log_size, a, qconv_const_f_3_DIF_r2_std2rev_size_8_forward);
    //qconv_DIT_r2_rev2std_precomp_1D_uint16_mod_f_3(size, log_size, a, qconv_const_f_3_DIT_r2_rev2std_size_8_inverse);
    qconv_NTT_1D_uint16_mod_f_3(size, a, optimize_precomp_order);
    qconv_INTT_1D_uint16_mod_f_3(size, a, optimize_precomp_order);
    //qconv_INTT_1D_size_norm_uint16_mod_f_3(size, a);
    qconv_test_util_compare_uint16_1D_array(size, a, original);*/
}
