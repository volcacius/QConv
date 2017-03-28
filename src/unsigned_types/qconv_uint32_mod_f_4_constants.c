//
// Created by alessandro on 3/3/17.
//
#include "qconv_uint32_mod_f_4_constants.h"

//Declare the useful constants as const structs as well
const qconv_uint32_mod qconv_const_f_4 = {.mod_f_4.value = QCONV_F_4};
const qconv_uint32_mod qconv_const_p_root_f_4_size_32 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_32};
const qconv_uint32_mod qconv_const_p_root_f_4_size_65536 = {.mod_f_4.value = QCONV_P_ROOT_F_4_SIZE_65536};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_forward[5] = {[0].value = 256,
        [1].value = 256,
        [2].value = 16,
        [3].value = 256,
        [4].value = 4096};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_8_inverse[5] = {[0].value = 65281,
        [1].value = 65281,
        [2].value = 61441,
        [3].value = 65281,
        [4].value = 65521};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_forward[17] = {[0].value = 256,
        [1].value = 256,
        [2].value = 256,
        [3].value = 256,
        [4].value = 16,
        [5].value = 16,
        [6].value = 256,
        [7].value = 256,
        [8].value = 4096,
        [9].value = 4096,
        [10].value = 4,
        [11].value = 16,
        [12].value = 64,
        [13].value = 256,
        [14].value = 1024,
        [15].value = 4096,
        [16].value = 16384};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_16_inverse[17] = {[0].value = 65281,
        [1].value = 65281,
        [2].value = 65281,
        [3].value = 65281,
        [4].value = 61441,
        [5].value = 61441,
        [6].value = 65281,
        [7].value = 65281,
        [8].value = 65521,
        [9].value = 65521,
        [10].value = 49153,
        [11].value = 61441,
        [12].value = 64513,
        [13].value = 65281,
        [14].value = 65473,
        [15].value = 65521,
        [16].value = 65533};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_forward[49] = {[0].value = 256,
        [1].value = 256,
        [2].value = 256,
        [3].value = 256,
        [4].value = 256,
        [5].value = 256,
        [6].value = 256,
        [7].value = 256,
        [8].value = 16,
        [9].value = 16,
        [10].value = 16,
        [11].value = 16,
        [12].value = 256,
        [13].value = 256,
        [14].value = 256,
        [15].value = 256,
        [16].value = 4096,
        [17].value = 4096,
        [18].value = 4096,
        [19].value = 4096,
        [20].value = 4,
        [21].value = 4,
        [22].value = 16,
        [23].value = 16,
        [24].value = 64,
        [25].value = 64,
        [26].value = 256,
        [27].value = 256,
        [28].value = 1024,
        [29].value = 1024,
        [30].value = 4096,
        [31].value = 4096,
        [32].value = 16384,
        [33].value = 16384,
        [34].value = 2,
        [35].value = 4,
        [36].value = 8,
        [37].value = 16,
        [38].value = 32,
        [39].value = 64,
        [40].value = 128,
        [41].value = 256,
        [42].value = 512,
        [43].value = 1024,
        [44].value = 2048,
        [45].value = 4096,
        [46].value = 8192,
        [47].value = 16384,
        [48].value = 32768};

const qconv_uint16 qconv_const_uint32_mod_f_4_CT_precomp_size_32_inverse[49] = {[0].value = 65281,
        [1].value = 65281,
        [2].value = 65281,
        [3].value = 65281,
        [4].value = 65281,
        [5].value = 65281,
        [6].value = 65281,
        [7].value = 65281,
        [8].value = 61441,
        [9].value = 61441,
        [10].value = 61441,
        [11].value = 61441,
        [12].value = 65281,
        [13].value = 65281,
        [14].value = 65281,
        [15].value = 65281,
        [16].value = 65521,
        [17].value = 65521,
        [18].value = 65521,
        [19].value = 65521,
        [20].value = 49153,
        [21].value = 49153,
        [22].value = 61441,
        [23].value = 61441,
        [24].value = 64513,
        [25].value = 64513,
        [26].value = 65281,
        [27].value = 65281,
        [28].value = 65473,
        [29].value = 65473,
        [30].value = 65521,
        [31].value = 65521,
        [32].value = 65533,
        [33].value = 65533,
        [34].value = 32769,
        [35].value = 49153,
        [36].value = 57345,
        [37].value = 61441,
        [38].value = 63489,
        [39].value = 64513,
        [40].value = 65025,
        [41].value = 65281,
        [42].value = 65409,
        [43].value = 65473,
        [44].value = 65505,
        [45].value = 65521,
        [46].value = 65529,
        [47].value = 65533,
        [48].value = 65535};