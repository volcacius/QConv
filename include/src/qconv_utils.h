//
// Created by alessandro on 3/28/17.
//

#pragma once

#include <stddef.h>

#include "qconv.h"

size_t qconv_get_log2_power_of_two(size_t power_of_two);

char* qconv_get_optimize_level_string(enum qconv_optimize_transform optimize_level);