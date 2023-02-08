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
// Module Name: lab2 yuv filter
// Purpose:
//    This is the C++ test bench for the yuv filter example.
// Reference:
//////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "yuv_filter.h"

int main () {
   // Dynamically allocate image buffers as they are rather large
   // and stack overflow may occur if statically allocated
   image_t *img_rgb = (image_t *)malloc(sizeof(image_t));
   image_t *img_restore = (image_t *)malloc(sizeof(image_t));

   // Read input image
   image_read(img_rgb);

   // Create output image
   // Scale should be <=128 (128 corresponds to a scale of 1.0)
   yuv_filter(img_rgb, img_restore, 128, 128, 128);

   // Save output image
   image_write(img_restore);

   // Compare results
   int ret = system("diff --brief -w test_data/output.dat test_data/output.golden.dat");

   if (ret != 0) {
      printf("Test failed!!!\n", ret);
      return 1;
   } else {
      printf("Test passed!\n", ret);
      return 0;
   }
}

