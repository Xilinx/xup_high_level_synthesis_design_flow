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
// Module Name: lab4 FIR
// Purpose:
//    This is the test bench of the Finite Impulse Response (FIR) example.
// Reference:
//////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h> 
#include "fir.h"
void fir (
  data_t *y,
  data_t x
  );

int main () {
  FILE   *fp;

  data_t signal, output;

  fp=fopen("fir_impulse.dat","w");
  int i;
  for (i=0;i<SAMPLES;i++) {
	  if(i==0)
		  signal = 0x8000;
	  else
		  signal = 0;
	  fir(&output,signal);
   	  printf("%i %d %d\n",i,(int)signal,(int)output);
//   	  fprintf(fp,"%i %d %d\n",i,signal,output);
  }
  fclose(fp);
  return 0;
}
