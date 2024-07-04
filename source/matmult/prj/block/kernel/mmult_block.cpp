// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include "mmult_block.h"

#define BLK_ROW 16
#define A_BLK_NUM DATA_SIZE/BLK_ROW
#define B_BLK_NUM DATA_SIZE/BLK_ROW

void mmult_hw(int* in1, int* in2, int* out, int dim)
{
    buf_t Abuf[BLK_ROW][DATA_SIZE];
    buf_t Bbuf[DATA_SIZE][BLK_ROW];
    int Cbuf[BLK_ROW][BLK_ROW];

#pragma HLS INTERFACE m_axi depth=16384 port=in1
#pragma HLS INTERFACE m_axi depth=16384 port=in2
#pragma HLS INTERFACE m_axi depth=16384 port=out
#pragma HLS INTERFACE s_axilite port=dim  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

#pragma HLS array_partition variable=Abuf cyclic factor=64 dim=2
#pragma HLS array_partition variable=Bbuf cyclic factor=64 dim=1

     SWEEP_B_BLK:
     for ( int i = 0; i < B_BLK_NUM; i++){
          // ---------------------------
          // --- read b block
          // ---------------------------
          READ_B_BLOCK:
          for ( int b_i = 0; b_i < DATA_SIZE; b_i++){
               for ( int b_j = 0; b_j < BLK_ROW; b_j++){
                    #pragma HLS PIPELINE
                    Bbuf[b_i][b_j] = in2[b_i * DATA_SIZE + b_j + i * BLK_ROW];
               }
          }
          SWEEP_A_BLK:
          for (int j = 0; j < A_BLK_NUM; j++){
               // ---------------------------
               // --- sweep a block
               // ---------------------------
               READ_A_BLK:
               for ( int a_i = 0; a_i < BLK_ROW; a_i++){
                    for ( int a_j = 0; a_j < DATA_SIZE; a_j++){
                         #pragma HLS PIPELINE
                         Abuf[a_i][a_j] = in1[(a_i + j * BLK_ROW) * DATA_SIZE + a_j];
                    }
               }
               // ---------------------------
               // --- compute c result
               // ---------------------------
               COMPUTE_C_ROW:
               for (int c_i = 0; c_i < BLK_ROW; c_i++){
                    COMPUTE_C_COL:
                    for (int c_j = 0; c_j < BLK_ROW; c_j++){
                         int c_tmp = 0;
                         #pragma HLS PIPELINE
                         COMPUTE_C_ELE:
                         for (int c_k = 0; c_k < DATA_SIZE; c_k++){
                              #pragma HLS UNROLL
                              c_tmp += Abuf[c_i][c_k] * Bbuf[c_k][c_j];
                         }
                         Cbuf[c_i][c_j] = c_tmp;
                    }
               }
               // ---------------------------
               // --- write result
               // ---------------------------
               WRITE_C:
               for (int w_i = 0; w_i < BLK_ROW; w_i++){
                    for (int w_j = 0; w_j < BLK_ROW; w_j++){
                         #pragma HLS PIPELINE
                         int new_row = j * BLK_ROW + w_i;
                         int new_col = i * BLK_ROW + w_j;
                         out[new_row * DATA_SIZE + new_col] = Cbuf[w_i][w_j];
                    }
               }

          }
     }

}
