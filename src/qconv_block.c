//
// Created by alessandro on 2/20/17.
//

#include "qconv_block.h"

enum qconv_status qconv_NTT_1D_block_cnn_convolution_uint32_mod_f_4(size_t input_size,
                                                                    size_t kernel_size,
                                                                    size_t block_size,
                                                                    qconv_uint32_mod input[input_size],
                                                                    qconv_uint32_mod kernel[kernel_size],
                                                                    qconv_uint32_mod output[input_size + kernel_size - 1],
                                                                    enum qconv_optimize_transform optimize_level) {

    size_t discard_subblock_size = kernel_size - 1;
    size_t valid_subblock_size = block_size - discard_subblock_size;

    //pad and transform kernel
    qconv_uint32_mod padded_kernel[block_size];
    qconv_right_zero_pad_uint32_1D_array(block_size, kernel_size, kernel, padded_kernel);
    qconv_NTT_1D_uint32_mod_f_4(block_size, padded_kernel, optimize_level);

    printf("Input:\n");
    for (size_t i = 0; i < input_size; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    //Compute first block
    qconv_uint32_mod first_block[block_size];
    qconv_uint32_mod first_output_block[block_size];
    for (size_t i = 0; i < discard_subblock_size; i++) {
        first_block[i].mod_f_4.value = 0;
    }
    for (size_t i = 0; i < valid_subblock_size; i++) {
        first_block[discard_subblock_size + i].mod_f_4.value = input[i].mod_f_4.value;
    }
    printf("First input block:\n");
    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", first_block[i]);
    }
    printf("\n");
    qconv_NTT_1D_uint32_mod_f_4(block_size, first_block, optimize_level);
    qconv_pmul_mod_f_4(block_size, first_block, padded_kernel, first_output_block);
    qconv_INTT_1D_uint32_mod_f_4(block_size, first_output_block, optimize_level);

    printf("First block:\n");

    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", first_output_block[i]);
    }
    printf("\n");
    for (size_t i = 0; i < valid_subblock_size; i++) {
        output[i].mod_f_4.value = first_output_block[discard_subblock_size + i].mod_f_4.value;
    }

    //inner blocks that do not require padding
    int input_offset = valid_subblock_size - discard_subblock_size;
    for (input_offset = valid_subblock_size - discard_subblock_size; input_offset < input_size - block_size; input_offset += valid_subblock_size) {

        printf("Offset: %d\n", input_offset);

        //I can't transform in place given that the blocks are overlapped
        qconv_uint32_mod input_block[block_size];
        qconv_uint32_mod output_block[block_size];
        for (size_t i = 0; i < block_size; i++) {
            input_block[i].mod_f_4.value = input[input_offset + i].mod_f_4.value;
        }

        printf("Input:\n");

        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", input_block[i]);
        }

        printf("\n");

        qconv_NTT_1D_uint32_mod_f_4(block_size, input_block, optimize_level);
        qconv_pmul_mod_f_4(block_size, input_block, padded_kernel, output_block);
        qconv_INTT_1D_uint32_mod_f_4(block_size, output_block, optimize_level);

        printf("Block:\n");

        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", output_block[i]);
        }
        printf("\n");
        size_t output_offset = input_offset + discard_subblock_size;
        for (size_t i = 0; i < valid_subblock_size; i++) {
            output[output_offset + i].mod_f_4.value = output_block[discard_subblock_size + i].mod_f_4.value;
        }
    }

    //last blocks that requires padding
    for (input_offset; input_offset < input_size; input_offset += valid_subblock_size) {
        qconv_uint32_mod last_block[block_size];
        qconv_uint32_mod last_output_block[block_size];
        qconv_right_zero_pad_uint32_1D_array(block_size, input_size - input_offset, &input[input_offset],
                                             last_block);
        printf("Last input block:\n");
        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", last_block[i]);
        }
        printf("\n");
        qconv_NTT_1D_uint32_mod_f_4(block_size, last_block, optimize_level);
        qconv_pmul_mod_f_4(block_size, last_block, padded_kernel, last_output_block);
        qconv_INTT_1D_uint32_mod_f_4(block_size, last_output_block, optimize_level);

        printf("Last output block:\n");
        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", last_output_block[i]);
        }
        printf("\n");
        size_t output_offset = input_offset + discard_subblock_size;
        for (size_t i = 0; i < valid_subblock_size; i++) {
            output[output_offset + i].mod_f_4.value = last_output_block[discard_subblock_size + i].mod_f_4.value;
        }
    }

    return status_success;
}

/*

enum qconv_status qconv_NTT_1D_block_cnn_convolution_uint32_mod_f_4(size_t input_size,
                                                                    size_t kernel_size,
                                                                    size_t block_size,
                                                                    qconv_uint32_mod input[input_size],
                                                                    qconv_uint32_mod kernel[kernel_size],
                                                                    qconv_uint32_mod output[input_size + kernel_size - 1],
                                                                    enum qconv_optimize_transform optimize_level) {

    size_t output_size = input_size + kernel_size - 1;
    size_t discard_subblock_size = kernel_size - 1;
    size_t valid_subblock_size = block_size - discard_subblock_size;
    size_t last_valid_subbblock_size = input_size % valid_subblock_size;

    //pad and transform kernel
    qconv_uint32_mod padded_kernel[block_size];
    qconv_right_zero_pad_uint32_1D_array(block_size, kernel_size, kernel, padded_kernel);
    qconv_NTT_1D_uint32_mod_f_4(block_size, padded_kernel, optimize_level);

    printf("Input:\n");
    for (size_t i = 0; i < input_size; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    //Compute first block
    qconv_uint32_mod first_block[block_size];
    qconv_uint32_mod first_output_block[block_size];
    for (size_t i = 0; i < discard_subblock_size; i++) {
        first_block[i].mod_f_4.value = 0;
    }
    for (size_t i = 0; i < valid_subblock_size; i++) {
        first_block[discard_subblock_size + i].mod_f_4.value = input[i].mod_f_4.value;
    }
    printf("First input block:\n");
    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", first_block[i]);
    }
    printf("\n");
    qconv_NTT_1D_uint32_mod_f_4(block_size, first_block, optimize_level);
    qconv_pmul_mod_f_4(block_size, first_block, padded_kernel, first_output_block);
    qconv_INTT_1D_uint32_mod_f_4(block_size, first_output_block, optimize_level);

    printf("First block:\n");

    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", first_output_block[i]);
    }
    printf("\n");
    for (size_t i = 0; i < valid_subblock_size; i++) {
        output[i].mod_f_4.value = first_output_block[discard_subblock_size + i].mod_f_4.value;
    }

    //inner blocks
    size_t input_offset;
    for (input_offset = valid_subblock_size - discard_subblock_size; input_offset < input_size - last_valid_subbblock_size; input_offset += valid_subblock_size) {

        printf("Offset: %d\n", input_offset);

        //I can't transform in place given that the blocks are overlapped
        qconv_uint32_mod input_block[block_size];
        qconv_uint32_mod output_block[block_size];
        for (size_t i = 0; i < block_size; i++) {
            input_block[i].mod_f_4.value = input[input_offset + i].mod_f_4.value;
        }

        printf("Input:\n");

        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", input_block[i]);
        }

        printf("\n");

        qconv_NTT_1D_uint32_mod_f_4(block_size, input_block, optimize_level);
        qconv_pmul_mod_f_4(block_size, input_block, padded_kernel, output_block);
        qconv_INTT_1D_uint32_mod_f_4(block_size, output_block, optimize_level);

        printf("Block:\n");

        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", output_block[i]);
        }
        printf("\n");
        size_t output_offset = input_offset + discard_subblock_size;
        for (size_t i = 0; i < valid_subblock_size; i++) {
            output[output_offset + i].mod_f_4.value = output_block[discard_subblock_size + i].mod_f_4.value;
        }
    }

    //last block
    qconv_uint32_mod last_block[block_size];
    qconv_uint32_mod last_output_block[block_size];
    qconv_right_zero_pad_uint32_1D_array(block_size, input_size - input_offset, &input[input_offset],
                                         last_block);
    printf("Last input block:\n");
    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", last_block[i]);
    }
    printf("\n");
    qconv_NTT_1D_uint32_mod_f_4(block_size, last_block, optimize_level);
    qconv_pmul_mod_f_4(block_size, last_block, padded_kernel, last_output_block);
    qconv_INTT_1D_uint32_mod_f_4(block_size, last_output_block, optimize_level);

    printf("Last output block:\n");
    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", last_output_block[i]);
    }
    printf("\n");

    for (size_t i = 0; i < valid_subblock_size; i++) {
        output[output_size - valid_subblock_size + i].mod_f_4.value = last_output_block[discard_subblock_size + i].mod_f_4.value;
    }
    return status_success;
}

*/

/*
enum qconv_status qconv_NTT_2D_block_cnn_convolution_uint32_mod_f_4(size_t input_size_width,
                                                                    size_t input_size_height,
                                                                    size_t kernel_size_width,
                                                                    size_t kernel_size_height,
                                                                    size_t block_size_width,
                                                                    size_t block_size_height,
                                                                    qconv_uint32_mod input[static input_size_width * input_size_height],
                                                                    qconv_uint32_mod kernel[static kernel_size_width * kernel_size_height],
                                                                    qconv_uint32_mod output[static (input_size_width + kernel_size_width - 1) 
                                                                                                   * (input_size_height + kernel_size_height - 1)],
                                                                    enum qconv_optimize_transform optimize_level) {

    size_t output_size_width = input_size_width + kernel_size_width - 1;
    size_t output_size_height = input_size_height + kernel_size_height - 1;

    size_t discard_subblock_size_width = kernel_size_width - 1;
    size_t discard_subblock_size_height = kernel_size_height - 1;
    size_t valid_subblock_size_width = block_size_width - discard_subblock_size_width;
    size_t valid_subblock_size_height = block_size_height - discard_subblock_size_height;

    ///pad input
    size_t padded_input_size_width = input_size_width + 2 * discard_subblock_size_width;
    size_t padded_input_size_height = input_size_height + 2 * discard_subblock_size_height;
    qconv_uint32_mod padded_input[padded_input_size_width * padded_input_size_height];

    //pad and transform kernel
    qconv_uint32_mod padded_kernel[block_size_width * block_size_height];
    qconv_bottom_right_zero_pad_uint32_2D_array(block_size_width, block_size_height, kernel_size_width, kernel_size_height, kernel, padded_kernel);
    qconv_NTT_2D_uint32_mod_f_4(block_size_width, block_size_height, padded_kernel, optimize_level);

    */
/*printf("Input:\n");
    for (size_t i = 0; i < input_size; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");*//*



    //inner blocks
    for (size_t input_offset = valid_subblock_size - discard_subblock_size; input_offset < input_size + discard_subblock_size - block_size; input_offset += valid_subblock_size) {
*/
/*
        printf("Offset: %d\n", input_offset);
*//*

        //I can't transform in place given that the blocks are overlapped
        qconv_uint32_mod input_block[block_size];
        qconv_uint32_mod output_block[block_size];
        for (size_t i = 0; i < block_size; i++) {
            input_block[i].mod_f_4.value = input[input_offset + i].mod_f_4.value;
        }
*/
/*
        printf("Input:\n");

        for (size_t i = 0; i < block_size; i++) {
            printf("%d ", input_block[i]);
        }

        printf("\n");
*//*

        qconv_NTT_1D_uint32_mod_f_4(block_size, input_block, optimize_level);
        qconv_pmul_mod_f_4(block_size, input_block, padded_kernel, output_block);
        qconv_INTT_1D_uint32_mod_f_4(block_size, output_block, optimize_level);
*/
/*
        printf("Block:\n");
*//*

        */
/*for (size_t i = 0; i < block_size; i++) {
            printf("%d ", output_block[i]);
        }
        printf("\n");*//*

        size_t output_offset = input_offset + discard_subblock_size;
        for (size_t i = 0; i < valid_subblock_size; i++) {
            output[output_offset + i].mod_f_4.value = output_block[discard_subblock_size + i].mod_f_4.value;
        }
    }

    //last block
    qconv_uint32_mod last_block[block_size];
    qconv_uint32_mod last_output_block[block_size];
    qconv_right_zero_pad_uint32_1D_array(block_size, valid_subblock_size, &input[input_size - valid_subblock_size],
                                         last_block);
    */
/*printf("Last input block:\n");
    for (size_t i = 0; i < block_size; i++) {
        printf("%d ", last_block[i]);
    }
    printf("\n");*//*

    qconv_NTT_1D_uint32_mod_f_4(block_size, last_block, optimize_level);
    qconv_pmul_mod_f_4(block_size, last_block, padded_kernel, last_output_block);
    qconv_INTT_1D_uint32_mod_f_4(block_size, last_output_block, optimize_level);
    for (size_t i = 0; i < valid_subblock_size; i++) {
        output[output_size - valid_subblock_size + i].mod_f_4.value = last_output_block[discard_subblock_size + i].mod_f_4.value;
    }

}



*/
