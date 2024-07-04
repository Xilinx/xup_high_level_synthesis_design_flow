// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef MMULT_BLOCK_H
#define MMULT_BLOCK_H
#include "ap_int.h"



//Array size to access
#define DATA_SIZE 128

#ifdef __SYNTHESIS__
typedef ap_uint<8> buf_t;
#else
typedef int buf_t;
#endif

//Declaring the hardware function
void mmult_hw(int* in1 , int* in2 , int* out , int dim);

#endif
