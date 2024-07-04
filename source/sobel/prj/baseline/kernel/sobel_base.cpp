// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT
#include "sobel.hpp"
#include <iostream>
using namespace std;

static PIXEL Gradient_X(PIXEL WB[3][3])
{
	short int M00 = ((short int)WB[1][0] << 1);
	short int M01 = ((short int)WB[1][2] << 1);
	short int A00 = (WB[0][2] + WB[2][2]);
	short int S00 = (WB[0][0] + WB[2][0]);
	short int out_pix;
	out_pix = M01 - M00;
	out_pix = out_pix + A00;
	out_pix = out_pix - S00;

	if(out_pix < 0)
	{
		out_pix = 0;
	}
	else if(out_pix>255)
	{
		out_pix = 255;
	}
	return (PIXEL) out_pix;
}

static PIXEL Gradient_Y(PIXEL WB[3][3])
{
	short int M00 = ((short int)WB[0][1] << 1);
	short int M01 = ((short int)WB[2][1] << 1);
	short int A00 = (WB[2][0] + WB[2][2]);
	short int S00 = (WB[0][0] + WB[0][2]);
	short int out_pix;
	out_pix = M01 - M00;
	out_pix = out_pix + A00;
	out_pix = out_pix - S00;

	if(out_pix < 0)
	{
		out_pix = 0;
	}
	else if(out_pix > 255)
	{
		out_pix = 255;
	}
	return (PIXEL) out_pix;
}

static PIXEL sobel3x3_kernel(PIXEL WB[3][3])
{
	PIXEL g_x, g_y, sobel;
	short temp;
	g_x = Gradient_X(WB);
	g_y = Gradient_Y(WB);
	temp = g_x + g_y;
	if(temp > 255) sobel = 255;
	else sobel = temp;

	return sobel;
}

//void sobel(hls::stream<trans_pkt>& src, hls::stream<trans_pkt>& dst, int rows, int cols)
void sobel(PIXEL* src, PIXEL* dst, int rows, int cols)
{
#pragma HLS INTERFACE m_axi port=src depth=921600
#pragma HLS INTERFACE m_axi port=dst depth=917604
#pragma HLS INTERFACE s_axilite port=rows  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

	 int row, col;
	 PIXEL sobel_kernel[3][3];

	 for(row = 1; row < rows-1; row++)
	 {
#pragma HLS LOOP_TRIPCOUNT min=1 max=720
		for(col = 1; col < cols-1; col++)
		{
#pragma HLS LOOP_TRIPCOUNT min=1 max=1280
			PIXEL _sobel;


		    for(int i=0; i<3; i++)
		    {
		        for(int j=0; j<3; j++)
		        {

		             sobel_kernel[i][j] = src[(row+i)*cols+(col+j)];
		        }
            }
		    _sobel = sobel3x3_kernel(sobel_kernel);

	        dst[(row-1)*cols+(col-1)] = _sobel;

		}

	}

}
