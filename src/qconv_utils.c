//
// Created by alessandro on 3/28/17.
//

#include "qconv_utils.h"

size_t qconv_get_log2_power_of_two(size_t power_of_two) {
    size_t log2 = 0;
    while (power_of_two > 1) {
        power_of_two >>= 1;
        log2++;
    }
    return log2;
}

char* qconv_get_optimize_level_string(enum qconv_optimize_transform optimize_level) {
    switch(optimize_level) {
        case optimize_null:
            return "Optimize null";
        case optimize_precomp:
            return "Optimize precompute";
        case optimize_precomp_order:
            return "Optimize precompute order";
        default:
            return "Undefined optimization";
    }
}