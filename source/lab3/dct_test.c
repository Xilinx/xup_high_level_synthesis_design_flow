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
// Module Name: lab3 Discrete Cosine Transformation (DCT)
// Purpose:
//    This is the test bench of the Discrete Cosine Transformation (DCT) example.
// Reference:
//////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "dct.h"

// ********************************************************
int main() {
   short a[N], b[N], b_expected[N];
   int retval = 0, i;
   FILE *fp;

   fp=fopen("in.dat","r");
   for (i=0; i<N; i++){
      int tmp;
      fscanf(fp, "%d", &tmp);
      a[i] = tmp;
   }
   fclose(fp);

   fp=fopen("out.golden.dat","r");
   for (i=0; i<N; i++){
      int tmp;
      fscanf(fp, "%d", &tmp);
      b_expected[i] = tmp;
   }
   fclose(fp);

   dct(a, b);

   for (i = 0; i < N; ++i) {
      if(b[i] != b_expected[i]){
         printf("Incorrect output on sample %d. Expected %d, Received %d \n", i, b_expected[i], b[i]);
         retval = 2;
      }
   }

#if 0 // Optionally write out computed values
   fp=fopen("out.dat","w");
   for (i=0; i<N; i++){
      fprintf(fp, "%d\n", b[i]);
   }
   fclose(fp);
#endif

   if(retval != (2)){
      printf("    *** *** *** *** \n");
      printf("    Results are good \n");
      printf("    *** *** *** *** \n");
   } else {
      printf("    *** *** *** *** \n");
      printf("    BAD!! %d \n", retval);
      printf("    *** *** *** *** \n");
   }
   return retval;
}
