//
// Created by alessandro on 3/11/17.
//
#include "qconv_test_uint16.h"
#include "qconv_test_uint16_mod_f_8.h"
#include "qconv_test_uint16_mod_m_13.h"

int main() {
    srand(time(NULL));
    //qconv_test_uint16_runall();
    //qconv_test_int32_mod_runall();
    qconv_test_uint16_mod_f_8_runall();
}
