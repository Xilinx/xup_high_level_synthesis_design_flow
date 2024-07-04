// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef MMULT_BASELINE_H
#define MMULT_BASELINE_H

#define DATA_SIZE 128
//Declaring the hardware function
void mmult_hw(int in1[DATA_SIZE*DATA_SIZE] , int in2[DATA_SIZE*DATA_SIZE] , int out[DATA_SIZE*DATA_SIZE] , int dim);

#endif
