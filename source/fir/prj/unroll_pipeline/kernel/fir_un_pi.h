// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#define N 99
typedef int coef_t;
typedef int data_t;
typedef int acc_t;

void fir(data_t *y, data_t x);

void fir_wrap(data_t *y, data_t *x, int len, coef_t *coef);

