#include "nnom.h"

/* Weights, bias and Q format */
#define TENSOR_CONV1D_KERNEL_0 {51, -16, -71, 31, 31, -61, 49, -42, -22, 40, 52, -6, 29, 57, -61, 38, 51, 40, 11, -64, -52, -55, -54, -13, -42, -48, -45, 10, 58, 54, 40, 70, -3, 33, 66, 57, 47, 24, 64, 39, 21, 59, 37, -11, 50, 38, 26, 5, 62, 61, 20, 32, 70, 30, -77, -55, 40, -77, -20, 31, -42, 22, -5, -7, 16, 50, -6, -14, 71, -41, 41, -7, 52, -14, -75, 7, 22, -53, 48, -26, -38, -74, 50, 29, -37, 57, 57, -33, 63, 41, -22, -69, -52, -8, -57, -60, -39, -33, -43, 12, -14, -73, 27, 9, -68, 9, -56, -50, -10, 33, -26, -40, -15, -72, 7, 23, -58, 39, 19, 44, 46, 65, 21, 52, 48, -36, -45, 35, 28, 0, 27, 70, -4, 43, 3, -10, 43, -8, 49, 62, -39, 49, 13, -71, 15, 39, 58, 47, 53, 41, 43, 17, 63, -67, -72, 21, -19, -77, 34, -69, -60, 49, 3, 58, 30, -30, 12, 34, -18, 57, 29, -30, -34, 0, -57, -52, 8, -1, 0, 72, -63, 49, -27, -36, 57, 21, -76, 10, 3, -60, 42, 21, -11, 30, 66, -17, 8, 67, 55, -65, -22, 29, -41, -29, 21, -54, -66, 12, -16, 13, -38, 24, 69, -1, -21, 53, 60, 34, 8, 35, 52, -30, 33, 49, -53, 55, 61, 7, 23, 63, -62, 37, 55, -47, 45, -19, 35, 28, -75, 45, 61, -71, 13, -49, 57, 17, -56, 52, 38, -20, 58, 33, 7, 25, -62, 29, -13, -63, 6, -11, -33, 52, 54, 63, 39, 7, 47, 32, 54, 12}

#define TENSOR_CONV1D_KERNEL_0_DEC_BITS {7}

#define TENSOR_CONV1D_BIAS_0 {85, 81, 11, 13, 70, 11, 70, 67, 42, 30, 49, 6, 0, 15, 68, 8, 57, 12, 7, 78, 40, 27, 73, 1, 26, 74, 85, 65, 41, 12}

#define TENSOR_CONV1D_BIAS_0_DEC_BITS {9}

#define CONV1D_BIAS_LSHIFT {6}

#define CONV1D_OUTPUT_RSHIFT {9}

#define TENSOR_CONV1D_1_KERNEL_0 {-5, 26, 1, 35, -16, 19, 35, -10, -26, 52, 2, -20, -11, -15, 29, -13, 15, -3, 24, 46, 23, 3, -23, -21, -26, 0, -55, 28, -47, -19, -6, 19, -12, -32, -20, 11, 14, 44, 30, 5, 4, 2, 33, 0, 43, 18, -4, -31, 16, -10, 29, -23, -13, 4, 29, 0, -40, 13, -4, 21, 2, 37, -26, 43, -33, -24, -5, -49, 27, 28, -36, 34, 21, -17, -26, 29, -2, -29, 14, 19, 24, 23, -2, 27, 31, 40, -32, 50, 25, -23, 52, 19, 32, -2, -14, 4, -42, -33, 44, -8, 37, 64, 27, 18, -18, 56, -19, 3, 9, -48, 14, -41, 15, 17, 40, 12, 0, -18, 54, -5, 56, 34, 6, 23, -7, 38, -7, -35, 53, -47, 33, 50, 23, 10, 2, 63, -28, -25, -6, -20, 1, -16, 46, 17, 12, 35, -19, -43, 34, -14, 14, 16, 37, -6, 11, 20, -48, 0, 51, -21, 25, 23, 40, 11, -21, 60, 3, -25, 31, -32, -6, -7, 21, 58, 48, 7, -11, 2, 17, 24, 52, 62, -65, 28, 42, 37, -27, -16, 12, -17, -43, 7, -33, 39, 51, -1, 57, -27, -22, -14, -11, 22, 13, 16, 38, 42, 35, 37, -7, 18, 17, 8, -36, -13, 17, 21, -33, 11, -1, -42, -22, -33, -45, 61, 28, -13, 13, -62, -16, 13, -14, -20, 22, -47, 57, 58, 20, -19, 20, 27, 24, 58, -65, 19, 46, 12, -18, -19, 35, 5, -22, -23, 11, -8, 8, -10, 29, -56, 1, 41, -20, 8, -5, 14, 3, 43, 37, 25, 27, 6, -28, -23, 30, -11, -28, 17, 35, -22, 9, 7, 41, -24, 14, -13, 1, 14, -43, 46, 32, 41, 3, 8, -15, -17, -10, 5, -25, 11, -18, -27, -7, -21, 34, 24, -15, 1, 15, -6, -19, 33, 2, -39, 1, 46, 23, 18, -44, 39, 22, -31, 52, -6, -11, -25, 0, 21, -26, 43, -47, 4, -26, 16, 22, 49, -18, 25, 40, 2, -24, 45, -7, -10, 42, 38, 26, 51, 42, 42, 15, 0, 55, 35, -12, 58, 54, 11, -10, 45, -21, 15, 24, 3, 15, 13, -21, 38, -28, 10, 14, 26, 18, 45, 8, 40, -25, 50, -7, -12, 11, -29, -9, 21, 35, 45, 33, 6, -28, -33, 51, -7, 14, -23, 42, -7, -41, -25, -29, -30, 48, -7, 31, 51, 40, -15, -27, 25, -33, 4, 10, -32, 21, 13, 41, -11, 37, 22, -30, 7, 46, 3, 58, 8, 51, 11, -29, -33, -13, -46, 52, -13, 18, 37, 54, 8, -14, 27, -26, -42, 25, -28, -8, 11, 9, 13, 11, 44, -18, -15, 41, -11, -61, 3, -29, 40, 40, 26, 20, 45, -42, 25, -35, -29, -43, 11, 49, 23, 28, 25, 19, 8, 58, 62, -55, 38, 34, 35, -8, 55, -27, 18, -50, -50, 24, 4, 10, -19, 59, 50, -3, 7, 19, -13, 41, -34, 11, 7, -16, 50, 27, 23, 55, 7, 4, 21, -8, -21, -8, 49, 0, 21, -6, -1, 6, -42, -11, 0, 11, 7, 27, 50, -28, -7, 19, -4, 42, 40, 0, 18, -10, 14, 51, 11, 6, 35, 9, 11, 10, 0, -2, -28, -10, 32, -60, 39, 2, 25, -25, 35, -14, 60, -17, -29, -15, 25, 24, 35, 28, 12, 27, 2, 26, 5, -10, -6, 33, 7, -12, 14, -40, 43, -10, 41, -14, 49, 9, 25, -7, 0, -53, 57, -32, -9, -10, 26, 46, 33, 39, 15, 50, -8, 37, 25, -49, 40, 27, 37, -27, 30, -28, -9, -33, 5, -16, 13, 7, 21, 4, 6, -26, 63, -13, -30, -8, 8, 34, -45, 9, 25, 20, 5, 34, 58, -67, 13, -19, -16, -28, 58, -14, 34, 29, 58, 12, -17, -15, -19, 53, -9, -37, 2, 27, -54, 15, -44, -9, -36, 15, 13, -2, 45, 42, -20, 34, -4, 17, 1, -4, 33, 29, -53, 25, 46, 40, 0, -15, -50, 32, 38, -11, -1, 22, -34, -12, -7, 48, -2, 9, -10, -6, 7, 16, 8, 28, -22, 11, 25, -28, 24, 7, 6, -4, 4, -50, 12, 25, -52, 37, 39, 0, 55, -26, -36, -10, -22, 35, -44, -4, 17, -21, 17, 11, 21, -17, 1, -23, -4, 0, 26, -4, -44, -6, 47, -32, 57, -4, 67, -26, -7, -1, 42, -46, 18, 22, 59, -8, 47, 37, -32, 36, -40, 6, -10, -27, 32, 58, 62, -13, 6, 14, 50, -14, 9, -5, 25, -8, 44, 4, -6, 22, 9, -29, 11, 19, 37, 8, 48, 20, 0, 25, -9, -38, 20, 0, -20, 13, 49, 5, 26, 36, 36, 23, -22, 46, 37, -12, 51, -20, -20, 36, 11, -1, 12, 40, -4, -24, 26, -3, 32, -9, -15, 2, -12, 6, 28, 39, 4, -15, -20, 39, 6, -25, 5, 41, 50, 50, 25, 0, 5, -20, -19, -7, 34, 17, -8, 10, 6, 21, 47, 18, 29, -50, 33, -16, 34, -9, -37, 13, -39, -22, 17, 23, -31, 17, 19, 43, 5, -40, 5, 42, 33, -21, 51, 12, 0, -13, 10, 51, 49, 4, 2, -20, 31, 1, 47, 8, -20, 54, 6, -9, 53, -18, -41, 37, 12, 22, 20, -2, 2, 11, -13, 37, 25, -3, 30, 15, -6, 12, 49, 26, -22, -25, 27, 42, 18, -1, -31, 27, -31, 0, 43, 44, 24, 21, 2, -7, 21, -6, 11, 18, -26, 27, 42, 8, 7, -26, 46, 17, 47, 24, 33, -40, -26, 58, -23, 46, 24, 54, -47, 12, 40, -3, -2, 57, -14, -40, 29, 8, 1, 5, -39, 54, 7, 43, 14, -6, 20, -28, 4, -43, 26, -37, -39, 46, 25, 14, 15, 26, -6, 30, 20, 45, -2, 12, -23, -22, 0, -8, -11, 11, -35, 39, 11, 54, -14, -45, 53, -19, 44, -36, 29, -32, -19, 54, -27, 6, 39, 44, -54, 55, -28, 24, 47, -47, 13, 37, 62, -27, 36, 35, 3, -13, 22, -10, 44, 17, 56, 51, -42, 19, -34, -27, 30, -7, -28, 67, 46, -29, 11, 21, 63, 22, 14, 17, 30, 17, 24, -30, 15, -16, 45, -34, 19, 2, 48, 14, 41, 1, -23, 45, -45, 6, 16, -19, -32, 44, 35, -12, 16, -2, 37, 17, 53, -54, 44, 14, 52, -33, -19, 32, 33, -55, 42, 37, 48, 15, 30, 25, -65, 47, -13, -1, -12, -44, -12, 47, 58, 6, 29, 19, 22, 28, 4, 35, -2, -21, -10, 9, 13, 36, 16, 51, 61, 38, -25, -18, 38, 15, 41, 25, -11, 20, 1, 12, 29, 5, 34, -2, 0, 51, 35, 32, -28, 63, -13, -18, -12, -8, -44, 55, -20, 57, 18, 34, 5, -39, 58, -43, 54, -5, 0, 9, 5, 14, -12, 37, 10, 12, -41, 28, 9, 44, -14, 33, 2, 18, -7, 37, -23, 3, -38, 26, 63, 53, 5, -5, 18, 3, 18, 25, -16, 3, -18, 48, 42, 14, -6, 12, -40, 25, 33, -55, -7, -13, 20, 49, 14, 13, 13, -58, 26, -57, -44, 17, 23, 29, -5, 49, 51, -5, -15, -11, 51, -18, 25, 13, -5, 36, 11, -33, 32, -30, -18, 1, 33, 10, 17, 14, 16, -45, 7, -29, 8, -21, 7, 34, 21, 32, 18, 13, 18, -26, 31, -27, 20, 17, -19, 34, -5, -42, 39, -16, -8, -4, 40, 18, 15, 13, 9, -22, 5, -11, -13, -17, -13, 10, -20, 29, 19, 20, 45, -49, 34, 14, 26, -31, -21, 44, -21, -61, 41, -48, -24, -19, 6, -28, -9, 52, 44, -55, 42, -1, -10, -10, -41, 26, -8, -3, 14, 25, -7, 51, 49, -23, 3, -4, 5, -20, 20, 14, 2, -37, -47, -18, -34, 12, -5, 10, 34, -51, 55, -22, -24, -8, -1, 56, -21, -10, 49, 40, 30, 10, 53, -43, 50, -2, -41, 17, 30, 6, -7, -5, -7, -6, 39, 24, -5, 28, 24, -20, 59, -10, -33, 17, -8, 11, -55, 12, 0, 13, 25, 33, 53, -58, 58, -5, -14, -34, 39, -30, 9}

#define TENSOR_CONV1D_1_KERNEL_0_DEC_BITS {7}

#define TENSOR_CONV1D_1_BIAS_0 {16, 2, 60, -16, -8, 19, -16, 80, -41, -34, 40, -22, 4, -10, 19}

#define TENSOR_CONV1D_1_BIAS_0_DEC_BITS {9}

#define CONV1D_1_BIAS_LSHIFT {4}

#define CONV1D_1_OUTPUT_RSHIFT {8}

#define TENSOR_DENSE_KERNEL_0 {-24, -49, 15, -36, 16, -37, -8, -27, -28, -8, -3, 59, 45, 49, -53, -43, -28, -49, 10, -17, 48, 32, -59, -4, 13, -41, 11, -5, -51, -1, -9, 5, 40, -11, -35, -16, 28, -23, 59, 44, -36, -10, 16, 1, 12, 33, -32, -64, 2, -3, -1, 7, 18, 12, -33, 22, -16, 26, -20, -30, -36, 26, -15, -12, 40, -11, -33, 23, 19, 3, 38, -25, -34, 27, 59, 5, -7, 11, -30, -13, -24, 63, -32, 25, -1, 18, -11, -39, -33, 24, -23, 66, 8, -18, -5, 3, -12, 7, 29, 61, 14, 10, -25, -54, 38, -34, 40, -28, -22, 17, -4, -26, -48, 34, -22, 16, 29, 20, 23, -4, -12, -26, 38, -1, 17, 31, -13, -17, -52, -1, 40, -23, -59, -41, 9, -34, -61, 22, -28, -28, -6, -3, 40, -9, -12, 28, -10, 14, 26, -50, -1, -32, -46, -33, 56, -24, 12, 13, -16, 30, 26, 3, 39, -57, 29, -4, 11, 0, -36, 9, 36, -5, -14, -75, 4, 1, 5, -14, 18, -50, 13, -4, -14, 51, -14, -6, 26, -5, -11, 20, -50, 8, -51, -16, -34, -5, 14, 52, -62, 34, 14, 0, 0, 18, 5, 18, 0, -7, 16, -28, 3, 7, -45, -33, -11, -23, 13, 4, -28, -27, -33, 34, 42, -46, -17, 30, 38, -31, -70, -11, 0, -26, 6, -30, 20, 28, -1, -9, -21, 50, -37, 21, 13, -28, -25, 43, -45, 47, 28, 50, -40, -9, -8, 7, 10, 19, 13, 6, -16, 18, -4, 23, 3, -2, -31, 0, -2, -19, 33, -18, 6, 5, 44, 64, -15, -3, 12, 0, 32, -5, -8, 39, 33, 3, 53, -11, -37, 32, 7, 1, 26, -25, -11, -11, 32, -7, 2, -5, 12, 0, -11, 39, -31, -9, 40, -38, -32, 15, -5, -26, -4, -11, -68, 8, 51, -49, -24, -14, 14, -38, -19, 8, 26, -46, 27, -34, 29, -9, 42, -24, 3, -11, -34, -9, -46, -64, -19, -26, -15, -7, 51, -29, 0, -35, -38, -9, 13, -11, -36, 7, 6, -2, -71, 49, 58, -22, 4, 17, 21, -32, -8, -30, 50, 14, -21, -28, 24, 27, -17, -3, 34, -15, -58, -38, 27, -15, 8, 20, 33, -17, -18, -41, -51, 11, 39, -16, 28, 38, -28, 5, -21, 21, -18, -59, -26, -61, 6, -42, 19, -1, -64, -38, -38, -57, -7, -4, 3, -29, -13, 26, -48, 40, -19, 18, 46, 44, 7, -66, 3, 22, -39, 7, 18, 31, 70, -49, 39, -21, 46, 46, -3, 50, 3, 30, 7, -23, 62, -38, 3, -16, -9, 11, -45, -10, -2, 32, 61, -1, -49, 22, -63, -70, -25, -33, 1, 17, -50, 7, -73, -54, -7, 24, -42, 39, 24, -75, -23, -67, 33, 64, -23, 35, -64, -12, -45, 4, -13, -13, -40, 38, 37, 33, 25, -47, -47, -7, -12, -16, -33, 20, 45, -3, 53, -58, 8, 1, -52, 10, -38, 37, -39, 57, 19, -43, 22, -54, 6, 58, 21, -41, -9, -14, -18, 68, -7, -54, -12, 42, 48, 35, -41, 2, -18, 3, 20, -7, 22, 2, -2, 4, -4, -18, -5, 49, 4, -43, 21, -22, -26, 2, 41, -60, -68, -53, -30, 24, 17, 23, -42, 12, 14, -56, -2, -57, -18, 2, -28, 1, -11, -35, -18, -14, 31, -2, -22, -26, 5, -4, 23, 8, -1, 36, -60, -18, -60, 3, -12, -65, -51, -45, -75, 26, -24, -38, -11, -23, -10, 5, -23, 16, -53, -33, -60, -16, 28, 38, 33, -58, 9, 61, -29, -2, 38, -65, 5, 5, -38, 49, -29, -46, 33, -36, 35, 0, -53, 23, 13, 47, -43, -52, -4, -15, 24, 3, 34, -29, 1, -16, 47, -52, 3, 0, -4, -67, -14, -11, -14, 55, -8, -54, 2, -27, -22, -57, -25, -26, 2, 57, -56, -9, 3, -16, 3, -38, -41, 42, 9, -33, -43, -59, 7, -8, 47, -38, -10, -5, -84, 39, -61, -21, 14, -38, -33, -58, -32, 19, -56, 42, -5, 10, -2, 21, -46, 29, 49, 10, 42, -57, 8, -12, -4, 2, 2, -45, -15, -8, 44, -18, 26, -39, -4, -37, -17, -32, 12, -7, 15, -5, -9, -3, 9, 18, 7, -23, -2, -8, -5, -1, -28, 42, 8, -62, 13, -8, -31, 34, 3, 41, -61, -24, -11, 12, -40, -4, 27, 20, -39, 16, -34, -62, 7, -33, -9, -31, -24, -39, 20, -30, -10, 28}

#define TENSOR_DENSE_KERNEL_0_DEC_BITS {7}

#define TENSOR_DENSE_BIAS_0 {-38, -20, 58, -24, -61, -69, 44, 106, 104, -44}

#define TENSOR_DENSE_BIAS_0_DEC_BITS {10}

#define DENSE_BIAS_LSHIFT {2}

#define DENSE_OUTPUT_RSHIFT {9}


/* output q format for each layer */
#define INPUT_1_OUTPUT_DEC 8
#define INPUT_1_OUTPUT_OFFSET 0
#define CONV1D_OUTPUT_DEC 6
#define CONV1D_OUTPUT_OFFSET 0
#define RE_LU_OUTPUT_DEC 6
#define RE_LU_OUTPUT_OFFSET 0
#define CONV1D_1_OUTPUT_DEC 5
#define CONV1D_1_OUTPUT_OFFSET 0
#define RE_LU_1_OUTPUT_DEC 5
#define RE_LU_1_OUTPUT_OFFSET 0
#define MAX_POOLING1D_OUTPUT_DEC 5
#define MAX_POOLING1D_OUTPUT_OFFSET 0
#define FLATTEN_OUTPUT_DEC 5
#define FLATTEN_OUTPUT_OFFSET 0
#define DENSE_OUTPUT_DEC 3
#define DENSE_OUTPUT_OFFSET 0
#define DROPOUT_OUTPUT_DEC 3
#define DROPOUT_OUTPUT_OFFSET 0
#define SOFTMAX_OUTPUT_DEC 7
#define SOFTMAX_OUTPUT_OFFSET 0

/* bias shift and output shift for none-weighted layer */

/* tensors and configurations for each layer */
static int8_t nnom_input_data[450] = {0};

const nnom_shape_data_t tensor_input_1_dim[] = {150, 3};
const nnom_qformat_param_t tensor_input_1_dec[] = {8};
const nnom_qformat_param_t tensor_input_1_offset[] = {0};
const nnom_tensor_t tensor_input_1 = {
    .p_data = (void*)nnom_input_data,
    .dim = (nnom_shape_data_t*)tensor_input_1_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_input_1_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_input_1_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};

const nnom_io_config_t input_1_config = {
    .super = {.name = "input_1"},
    .tensor = (nnom_tensor_t*)&tensor_input_1
};
const int8_t tensor_conv1d_kernel_0_data[] = TENSOR_CONV1D_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_kernel_0_dim[] = {3, 3, 30};
const nnom_qformat_param_t tensor_conv1d_kernel_0_dec[] = TENSOR_CONV1D_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_kernel_0 = {
    .p_data = (void*)tensor_conv1d_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_bias_0_data[] = TENSOR_CONV1D_BIAS_0;

const nnom_shape_data_t tensor_conv1d_bias_0_dim[] = {30};
const nnom_qformat_param_t tensor_conv1d_bias_0_dec[] = TENSOR_CONV1D_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_bias_0 = {
    .p_data = (void*)tensor_conv1d_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_output_shift[] = CONV1D_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_bias_shift[] = CONV1D_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_config = {
    .super = {.name = "conv1d"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_bias_shift, 
    .filter_size = 30,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_VALID
};
const int8_t tensor_conv1d_1_kernel_0_data[] = TENSOR_CONV1D_1_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_1_kernel_0_dim[] = {3, 30, 15};
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_dec[] = TENSOR_CONV1D_1_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_kernel_0 = {
    .p_data = (void*)tensor_conv1d_1_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_1_bias_0_data[] = TENSOR_CONV1D_1_BIAS_0;

const nnom_shape_data_t tensor_conv1d_1_bias_0_dim[] = {15};
const nnom_qformat_param_t tensor_conv1d_1_bias_0_dec[] = TENSOR_CONV1D_1_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_bias_0 = {
    .p_data = (void*)tensor_conv1d_1_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_1_output_shift[] = CONV1D_1_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_1_bias_shift[] = CONV1D_1_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_1_config = {
    .super = {.name = "conv1d_1"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_1_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_1_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_1_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_1_bias_shift, 
    .filter_size = 15,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_VALID
};

const nnom_pool_config_t max_pooling1d_config = {
    .super = {.name = "max_pooling1d"},
    .padding_type = PADDING_VALID,
    .output_shift = 0,
    .kernel_size = {3},
    .stride_size = {3},
    .num_dim = 1
};

const nnom_flatten_config_t flatten_config = {
    .super = {.name = "flatten"}
};
const int8_t tensor_dense_kernel_0_data[] = TENSOR_DENSE_KERNEL_0;

const nnom_shape_data_t tensor_dense_kernel_0_dim[] = {75, 10};
const nnom_qformat_param_t tensor_dense_kernel_0_dec[] = TENSOR_DENSE_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_dense_kernel_0 = {
    .p_data = (void*)tensor_dense_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};
const int8_t tensor_dense_bias_0_data[] = TENSOR_DENSE_BIAS_0;

const nnom_shape_data_t tensor_dense_bias_0_dim[] = {10};
const nnom_qformat_param_t tensor_dense_bias_0_dec[] = TENSOR_DENSE_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_bias_0_offset[] = {0};
const nnom_tensor_t tensor_dense_bias_0 = {
    .p_data = (void*)tensor_dense_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t dense_output_shift[] = DENSE_OUTPUT_RSHIFT;
const nnom_qformat_param_t dense_bias_shift[] = DENSE_BIAS_LSHIFT;
const nnom_dense_config_t dense_config = {
    .super = {.name = "dense"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_dense_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_dense_bias_0,
    .output_shift = (nnom_qformat_param_t *)&dense_output_shift,
    .bias_shift = (nnom_qformat_param_t *)&dense_bias_shift
};

const nnom_softmax_config_t softmax_config = {
    .super = {.name = "softmax"}
};
static int8_t nnom_output_data[10] = {0};

const nnom_shape_data_t tensor_output0_dim[] = {10};
const nnom_qformat_param_t tensor_output0_dec[] = {SOFTMAX_OUTPUT_DEC};
const nnom_qformat_param_t tensor_output0_offset[] = {0};
const nnom_tensor_t tensor_output0 = {
    .p_data = (void*)nnom_output_data,
    .dim = (nnom_shape_data_t*)tensor_output0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_output0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_output0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_io_config_t output0_config = {
    .super = {.name = "output0"},
    .tensor = (nnom_tensor_t*)&tensor_output0
};
/* model version */
#define NNOM_MODEL_VERSION (10000*0 + 100*4 + 3)

/* nnom model */
static nnom_model_t* nnom_model_create(void)
{
	static nnom_model_t model;
	nnom_layer_t* layer[10];

	check_model_version(NNOM_MODEL_VERSION);
	new_model(&model);

	layer[0] = input_s(&input_1_config);
	layer[1] = model.hook(conv2d_s(&conv1d_config), layer[0]);
	layer[2] = model.active(act_relu(), layer[1]);
	layer[3] = model.hook(conv2d_s(&conv1d_1_config), layer[2]);
	layer[4] = model.active(act_relu(), layer[3]);
	layer[5] = model.hook(maxpool_s(&max_pooling1d_config), layer[4]);
	layer[6] = model.hook(flatten_s(&flatten_config), layer[5]);
	layer[7] = model.hook(dense_s(&dense_config), layer[6]);
	layer[8] = model.hook(softmax_s(&softmax_config), layer[7]);
	layer[9] = model.hook(output_s(&output0_config), layer[8]);
	model_compile(&model, layer[0], layer[9]);
	return &model;
}
