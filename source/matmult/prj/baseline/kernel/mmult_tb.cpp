// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "mmult_baseline.h"

#ifdef __SDSCC__
#include "sds_lib.h"
#else
#define sds_alloc malloc
#define sds_free free
#endif

#ifndef NUM_TIMES
#define NUM_TIMES 2
#endif


void mmult_sw( int *in1,   // Input matrix 1
               int *in2,   // Input matrix 2
               int *out,   // Output matrix (out = A x B)
               int dim     // Matrix size of one dimension
             )
{
    //Performs matrix multiplication out = in1 x in2
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                out[i * dim + j] += in1[i * dim + k] * in2[k * dim  + j];
            }
        }
    }
}


int main(int argc, char** argv)
{
    int dim =  DATA_SIZE;
    size_t matrix_size_bytes = sizeof(int) * DATA_SIZE * DATA_SIZE;
    //Allocate memory
    //malloc() doesn't guarantee contiguous physical memory allocation, but for
    //the hardware to implement the function using simple DMA, it requires
    //allocation of contiguous physical memory which can be done using sds_alloc().
    int *in1 = (int *) sds_alloc(matrix_size_bytes);
    int *in2 = (int *) sds_alloc(matrix_size_bytes);
    int *hw_result = (int *) sds_alloc(matrix_size_bytes);
    int *sw_result = (int *) malloc(matrix_size_bytes);

    if( (in1 == NULL) || (in2 == NULL) || (sw_result == NULL) || (hw_result == NULL) )
        {
            std::cout << "TEST FAILED : Failed to allocate memory" << std::endl;
            return -1;
        }

    bool match = true;

    for (int i = 0; i < NUM_TIMES; i++)
    {
        //Create test data
        for (int i = 0; i < dim * dim; i++) {
            in1[i] = rand() % dim;
            in2[i] = rand() % dim;
            sw_result[i] = 0;
            hw_result[i] = 0;
        }

        //Launch the software solution
        mmult_sw( in1, in2, sw_result, dim);

        //Launch the Hardware solution
        mmult_hw( in1, in2, hw_result, dim);

        //Compare the results of hardware to the software
        for(int i=0; i< dim * dim; i++)
        {
            if( sw_result[i] != hw_result[i] )
            {
                std::cout << "Results Mismatch on " << "Row:" << i/dim << "Col:" << i - (i/dim)*dim << std::endl;
                std::cout << "CPU output:" << sw_result[i] <<"\t Hardware output:" << hw_result[i] << std::endl;
                match = false;
                break;
            }
        }
    }

    //Release Memory
    sds_free(in1);
    sds_free(in2);
    sds_free(hw_result);
    free(sw_result);

    std::cout << " TEST " << (match? "PASSED": "FAILED") << std::endl;
    return(match? EXIT_SUCCESS: EXIT_FAILURE);
}




