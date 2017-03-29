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
    qconv_uint16_mod a[size], original[size];
    qconv_test_util_random_uint16_1D_array(size, a, 2);
    qconv_test_util_clone_uint16_1D_array(size, a, original);
    qconv_CT_1D_uint16_mod_f_3(size, a, qconv_const_p_root_f_3_size_16, 16, false);
    qconv_DIT_r2_std2std_1D_uint16_mod_f_3(size, a, qconv_const_p_root_f_3_size_16, 16, true);
    qconv_INTT_1D_size_norm_uint16_mod_f_3(size, a);
    qconv_test_util_compare_uint16_1D_array(size, a, original);*/
}
