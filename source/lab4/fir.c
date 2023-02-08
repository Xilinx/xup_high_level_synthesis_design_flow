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
//    This is a C++ version of a Finite Impulse Response (FIR) example using the 
// generated IP-XACT adapter in a processor system using IP Integrator in Vivado.
// Reference:
//////////////////////////////////////////////////////////////////////////////////
#include "fir.h" 

void fir (
  data_t *y,
  data_t x
  ) {
  const coef_t c[N+1]={
 #include "fir_coef.dat"
    };
  

  static data_t shift_reg[N];
  acc_t acc;
  int i;
  
  acc=(acc_t)shift_reg[N-1]*(acc_t)c[N];
  loop: for (i=N-1;i!=0;i--) {
    acc+=(acc_t)shift_reg[i-1]*(acc_t)c[i];
    shift_reg[i]=shift_reg[i-1];
  }
  acc+=(acc_t)x*(acc_t)c[0];
  shift_reg[0]=x;
  *y = acc>>15;
}
