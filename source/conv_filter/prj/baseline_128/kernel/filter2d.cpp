// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
using namespace std;
#include <math.h>
#include "filter2d.h"

#define MAX_IMAGE_WIDTH     128
#define MAX_IMAGE_HEIGHT    128
#define N 128
#define K 3


void filter2d_accel(
		DTYPE img_in[MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT],
		DTYPE kernel[9],
		DTYPE img_out[(MAX_IMAGE_WIDTH-2)*(MAX_IMAGE_HEIGHT-2)],
		int rows,
		int cols
)

{
#pragma HLS INTERFACE mode=m_axi port=kernel depth=9 //bundle=KRNL
#pragma HLS INTERFACE mode=m_axi port=img_in depth=16384 //bundle=IMG
#pragma HLS INTERFACE mode=m_axi port=img_out depth=15876 //bundle=IMG
#pragma HLS INTERFACE mode=s_axilite port=rows bundle=CTRL
#pragma HLS INTERFACE mode=s_axilite port=cols bundle=CTRL
#pragma HLS INTERFACE mode=s_axilite port=return bundle=CTRL

    for (int r = 1; r < rows-1; r++)
    {
#pragma HLS LOOP_TRIPCOUNT max=126
        for (int c = 1; c < cols-1; c++)
        {
#pragma HLS LOOP_TRIPCOUNT max=126
        	DTYPE img_temp=0;
    		for(int i=0; i<K; i++){
    			for(int j=0; j<K; j++){
    				 img_temp += img_in[(r+i-1)*128+ c+j-1] * kernel[i*K+j];
    			}
    		}
    		img_out[(r-1)*(N-2)+c-1] = img_temp;
        }
    }
}
