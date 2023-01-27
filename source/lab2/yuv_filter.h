// MIT License
// Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// SOFTWARE.

//////////////////////////////////////////////////////////////////////////////////
// Module Name: lab1 matrix multiplier
// Purpose:
//    This is the header for the yuv_filter.cpp design.
// Reference:
//////////////////////////////////////////////////////////////////////////////////
#ifndef RGB2YUV_H_
#define RGB2YUV_H_

#ifdef BIT_ACCURATE
#include "autopilot_tech.h"

typedef int9  rgb2yuv_coef_t;
typedef int11 yuv2rgb_coef_t;
typedef int9  yuv_intrnl_t;
typedef uint8 yuv_scale_t;

#else // Use native C types

typedef signed short  rgb2yuv_coef_t ;
typedef signed short  yuv2rgb_coef_t;
typedef signed short  yuv_intrnl_t;
typedef unsigned char yuv_scale_t;

#endif

#include "image_aux.h"

#define CLIP(x) (((x)>255) ? 255 : (((x)<0) ? 0 : (x)))

void rgb2yuv (image_t*, image_t*);
void yuv2rgb (image_t*, image_t*);

void yuv_scale (
  image_t *in,
  image_t *out,
  yuv_scale_t Y_scale,
  yuv_scale_t U_scale,
  yuv_scale_t V_scale
  );

void yuv_filter (
  image_t *in,
  image_t *out,
  yuv_scale_t Y_scale,
  yuv_scale_t U_scale,
  yuv_scale_t V_scale
  );

#endif
