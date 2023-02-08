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
#include <stdio.h>
#include "image_aux.h"


void image_read (
      image_t *in_image
      ) {
   image_dim_t width, height;
   int x, y;
   FILE        *fp;

   fp=fopen("test_data/input.dat","r");
   int tmp;
   fscanf(fp, "%d", &tmp);
   width = tmp;
   fscanf(fp, "%d", &tmp);
   height = tmp;

   in_image->width  = width;
   in_image->height = height;
   for (x=0;x<width;x++) {
      for (y=0;y<height;y++) {
         fscanf(fp, "%d", &tmp);
         in_image->channels.ch1[x][y] = tmp;
         fscanf(fp, "%d", &tmp);
         in_image->channels.ch2[x][y] = tmp;
         fscanf(fp, "%d", &tmp);
         in_image->channels.ch3[x][y] = tmp;
      }
   }
   fclose(fp);

}


void image_write (
      image_t *out_image
      ) {
   FILE *fp;
   int x, y;
   image_dim_t width, height;
   image_pix_t tmp;

   fp=fopen("test_data/output.dat","w");

   width = out_image->width;
   fprintf(fp, "%d \n", width);

   height = out_image->height;
   fprintf(fp, "%d \n", height);

   for (y=0;y<height;y++) {
      /* Scan-line: */
      for (x=0;x<width;x++) {
         tmp = out_image->channels.ch1[x][y];
         fprintf(fp, "%d\n", tmp);
         tmp = out_image->channels.ch2[x][y];
         fprintf(fp, "%d\n", tmp);
         tmp = out_image->channels.ch3[x][y];
         fprintf(fp, "%d\n", tmp);
      }
   }
   fclose(fp);
}
