//
// Created by alessandro on 3/11/17.
//
#include "qconv_test_int32.h"
#include "qconv_test_uint16.h"
#include "qconv_test_uint32.h"
#include "qconv_test_uint16_mod_f_3.h"
#include "qconv_test_uint16_mod_m_13.h"
#include "qconv_test_uint32_mod_f_4.h"
#include "qconv_test_crt.h"



int main() {
    srand(time(NULL));
    //qconv_test_uint16_runall();
    //qconv_test_int32_mod_runall();
    //qconv_test_uint16_mod_f_3_runall();
    //qconv_test_uint32_runall();
    qconv_test_uint32_mod_f_4_runall();
    //qconv_test_NTT_1D_convolution_mod_crt_f_3_f_4(QCONV_SIZE_256, 8, optimize_precomp);
}
