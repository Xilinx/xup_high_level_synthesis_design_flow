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
#ifndef IMAGE_AUX_H_
#define IMAGE_AUX_H_

#ifdef BIT_ACCURATE
#include "autopilot_tech.h"

typedef uint8  image_pix_t;
typedef uint11 image_dim_t;

#else // Use native C types

typedef unsigned char  image_pix_t;
typedef unsigned short image_dim_t;

#endif // ifdef BIT_ACCURATE

#define WIDTH 1920
#define HEIGHT 1280

typedef struct {
   image_pix_t ch1[WIDTH][HEIGHT];
   image_pix_t ch2[WIDTH][HEIGHT];
   image_pix_t ch3[WIDTH][HEIGHT];
} channel_t;

typedef struct {
   channel_t channels;
   image_dim_t width;
   image_dim_t height;
} image_t;

void image_read(image_t *in_image);

void image_write(image_t *out_image);

#endif
