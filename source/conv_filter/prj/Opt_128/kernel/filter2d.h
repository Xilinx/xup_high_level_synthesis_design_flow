// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

typedef unsigned char U8;

#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_IMAGE_WIDTH     128
#define MAX_IMAGE_HEIGHT    128

#define FILTER_V_SIZE		3
#define FILTER_H_SIZE		3

#ifndef MIN
#define MIN(a,b) ((a<b)?a:b)
#endif
#ifndef MAX
#define MAX(a,b) ((a<b)?b:a)
#endif

struct window {
	U8 pix[FILTER_V_SIZE][FILTER_H_SIZE];
};

extern "C" {

void filter2d_accel(
		const char kernel[9],
		int height,
		int width,

		U8 src[MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT],
		U8 dst[(MAX_IMAGE_WIDTH-2)*(MAX_IMAGE_HEIGHT-2)]
);


}

