//
// Created by alessandro on 2/20/17.
//

#pragma once

#include <stddef.h>
#include <event.h>
#include <stdlib.h>

/*
 * @brief Status code for QConv function calls.
 */
enum qconv_status {
    status_success,
    status_invalid_input_size
};

/*
 * Size of images and kernels.
 */
struct qconv_size {
    size_t width;
    size_t height;
};

/*
 * @brief Padding of images in QConv.
 */
struct qconv_padding {
    size_t top;
    size_t right;
    size_t bottom;
    size_t left;
};

/*
 * @brief Profiling information about time spent in the computation
 */
struct qconv_profile {
    double input_transform;
    double kernel_transform;
    double point_to_point_multiplication;
    double output_transform;
};

/*
 * @param input_channels The number of channels in the input image.
 * @param output_channels The number of channels in the output image.
 * @param input_size Size of input image, excluding padding.
 * @param input_padding Padding of input image.
 * @param kernel_size Kernel size.
 * @param stride Convolution stride.
 * @param[in]  input  A 3D tensor input[input_channels][input_size.height][input_size.width].
 * @param[in]  kernel A 4D tensor kernel[output_channels][input_channels][kernel_size.height][kernel_size.width].
 * @param[in]  bias   A 1D array bias[output_channels].
 * @param[out] output A 3D tensor output[output_channels][output_size.height][output_size.width] where
        * output_size.height = (input_padding.top + input_size.height + input_padding.bottom) - (kernel_size.height - 1)
        * output_size.width  = (input_padding.left + input_size.width + input_padding.right) - (kernel_size.width - 1)
 * @param[out] profile An optional pointer to profiling structure.
 *         If provided, the structure would record time spent in different phases of the computation.
 */
enum qconv_status qconv_convolution(
        size_t input_channels,
        size_t output_channels,
        struct qconv_size input_size,
        struct qconv_padding input_padding,
        struct qconv_size kernel_size,
        struct qconv_size stride,
        const uint32_t input[],
        const uint32_t kernel[],
        const uint32_t bias[],
        uint32_t output[],
        struct qconv_profile* profile);