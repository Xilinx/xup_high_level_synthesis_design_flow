// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include "mmult_baseline.h"

void mmult_hw(int in1[DATA_SIZE * DATA_SIZE], int in2[DATA_SIZE * DATA_SIZE], int out[DATA_SIZE * DATA_SIZE], int dim)
{
#pragma HLS INTERFACE m_axi depth=16384 port=in1
#pragma HLS INTERFACE m_axi depth=16384 port=in2
#pragma HLS INTERFACE m_axi depth=16384 port=out
#pragma HLS INTERFACE s_axilite port=dim  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

	loop1:for (int i = 0; i < dim; i++){
#pragma HLS loop_tripcount min=128 max=128 avg=128
	    loop2:for (int j = 0; j < dim; j++){
#pragma HLS loop_tripcount min=128 max=128 avg=128
	        loop3:for (int k = 0; k < dim; k++){
#pragma HLS loop_tripcount min=128 max=128 avg=128
	            out[i * dim + j] += in1[i * dim + k] * in2[k * dim  + j];
	        }
	    }
	}
}
