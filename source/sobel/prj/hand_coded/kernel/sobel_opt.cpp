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

void sobel(hls::stream<trans_pkt>& src, hls::stream<trans_pkt>& dst, int rows, int cols)
{
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS INTERFACE s_axilite port=rows  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

	trans_pkt data_p;

	PIXEL _sobel;

	PIXEL LineBuffer[3][WIDTH];
#pragma HLS ARRAY_PARTITION variable=LineBuffer complete dim=1

	PIXEL WindowBuffer[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
#pragma HLS ARRAY_PARTITION variable=WindowBuffer complete dim=0

	ap_uint<13> row, col;
	ap_uint<2> lb_r_i;
	ap_uint<2> top, mid, btm;//line buffer row index

	for(col = 0; col < cols; col++)
	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=1280
#pragma HLS pipeline
		LineBuffer[0][col] = 0;
		data_p = src.read();
		LineBuffer[1][col] = (PIXEL) data_p.data;
	}

	lb_r_i = 2;
	for(row = 1; row < rows + 1; row++)
	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=720
		if(lb_r_i == 2)
		{
			top = 0; mid = 1; btm = 2;
		}
		else if(lb_r_i == 0)
		{
			top = 1; mid = 2; btm = 0;
		}
		else if(lb_r_i == 1)
		{
			top = 2; mid = 0; btm = 1;
		}

		WindowBuffer[top][0] = WindowBuffer[top][1] = 0;
		WindowBuffer[mid][0] = WindowBuffer[top][1] = 0;
		WindowBuffer[btm][0] = WindowBuffer[top][1] = 0;

		for(col = 0; col < cols; col++)
		{
#pragma HLS LOOP_TRIPCOUNT min=1 max=1280
#pragma HLS pipeline
			if(row < rows)
			{
				data_p = src.read();
				LineBuffer[btm][col] = (PIXEL) data_p.data;
			}
			else
				LineBuffer[btm][col] = 0;

			WindowBuffer[0][2] = LineBuffer[top][col];
			WindowBuffer[1][2] = LineBuffer[mid][col];
			WindowBuffer[2][2] = LineBuffer[btm][col];
			_sobel = sobel3x3_kernel(WindowBuffer);
			WindowBuffer[0][0] = WindowBuffer[0][1];
			WindowBuffer[1][0] = WindowBuffer[1][1];
			WindowBuffer[2][0] = WindowBuffer[2][1];
			WindowBuffer[0][1] = WindowBuffer[0][2];
			WindowBuffer[1][1] = WindowBuffer[1][2];
			WindowBuffer[2][1] = WindowBuffer[2][2];

			if ((row == rows ) && (col == cols - 1))
				data_p.last = 1;
			else
				data_p.last= 0;
			data_p.data = _sobel;
			data_p.keep = -1;
			dst.write(data_p);
		}
		lb_r_i++;
		if(lb_r_i == 3) lb_r_i = 0;
	}
}
