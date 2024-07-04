// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
using namespace std;
#include <math.h>
#include "filter2d.h"
#include "hls_stream.h"
#include "hls_print.h"

#define N 128
#define K 3

///*
void ReadFromMem(
        int       width,
        int       height,
        const char        *coeffs,
        hls::stream<char>   &coeff_stream,
        U8 *src,
        hls::stream<U8>     &pixel_stream)
{
    assert(width <= MAX_IMAGE_WIDTH);
    assert(height <= MAX_IMAGE_HEIGHT);

    unsigned num_coefs = 3*3;
//    unsigned num_coefs_padded = (((num_coefs-1)/64)+1)*64; // Make sure number of reads of multiple of 64, enables auto-widening
    read_coefs: for (int i=0; i<num_coefs; i++) {
        unsigned char coef = coeffs[i];
//        if (i<num_coefs)
            coeff_stream.write( coef );
    }

    width = (width/64)*64; // Makes compiler see that width is a multiple of 64, enables auto-widening
//    int num_pixels=  height*width;
    unsigned offset = 0;
    unsigned x = 0;
    read_image: for (int n = 0; n < height*width; n++) {
#pragma HLS LOOP_TRIPCOUNT max=16384
        U8 pix = src[n];
        pixel_stream.write( pix );
     }
}

void WriteToMem(
        int     width,
        int     height,

        hls::stream<U8>     &pixel_stream,
        U8         *dst)
{
    assert(width <= MAX_IMAGE_WIDTH);
    assert(height <= MAX_IMAGE_HEIGHT);
//    int num_pixels=  (height-2)*(width-2);

    unsigned offset = 0;
    unsigned x = 0;

    write_image: for (int n = 0; n < (height-2)*(width-2); n++) {
#pragma HLS LOOP_TRIPCOUNT max= 15876
            U8 pix = pixel_stream.read();
            dst[n] = pix;
            hls::print("n = %d\n",n);
            hls::print("pixout=%d\n",pix);

    }
}


void Window2D(
        int      width,
        int       height,
        hls::stream<U8>      &pixel_stream,
        hls::stream<window>     &window_stream)
{
    // Line buffers - used to store [FILTER_V_SIZE-1] entire lines of pixels
    U8 LineBuffer[FILTER_V_SIZE-1][MAX_IMAGE_WIDTH];
#pragma HLS ARRAY_PARTITION variable=LineBuffer dim=1 complete
#pragma HLS DEPENDENCE variable=LineBuffer inter false
#pragma HLS DEPENDENCE variable=LineBuffer intra false

    // Sliding window of [FILTER_V_SIZE][FILTER_H_SIZE] pixels
    window Window;

    static unsigned col_ptr = 0;
    unsigned win_ptr = 0;
    unsigned ramp_up = width*(FILTER_V_SIZE-1)+(FILTER_H_SIZE-1); //258
    unsigned num_pixels = width*height;
    unsigned num_iterations = num_pixels + ramp_up;

    const unsigned max_iterations = MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT + MAX_IMAGE_WIDTH*((FILTER_V_SIZE-1)/2)+(FILTER_H_SIZE-1)/2; //128*128+129

    // Iterate until all pixels have been processed
    update_window: for (int n=0; n<num_pixels; n++)
    {
#pragma HLS LOOP_TRIPCOUNT max=max_iterations
#pragma HLS PIPELINE II=1

        // Read a new pixel from the input stream
        U8 new_pixel = (n<num_pixels) ? pixel_stream.read() : 0;


        // Shift the window and add a column of new pixels from the line buffer
        for(int i = 0; i < FILTER_V_SIZE; i++) {
            for(int j = 0; j < FILTER_H_SIZE-1; j++) {
                Window.pix[i][j] = Window.pix[i][j+1];
            }
            Window.pix[i][FILTER_H_SIZE-1] = (i<FILTER_V_SIZE-1) ? LineBuffer[i][col_ptr] : new_pixel;
        }

        // Shift pixels in the column of pixels in the line buffer, add the newest pixel
        for(int i = 0; i < FILTER_V_SIZE-1; i++) {
            LineBuffer[i][col_ptr] = LineBuffer[i+1][col_ptr];
        }
        LineBuffer[FILTER_V_SIZE-2][col_ptr] = new_pixel;

        // Write output only when enough pixels have been read the buffers and ramped-up
        if (n >= ramp_up && col_ptr>1) {
            window_stream.write(Window);
//            hls::print("col_ptr=%d\n",col_ptr);
        }

        // Update the line buffer column pointer
        if (col_ptr==(width-1)) {
            col_ptr = 0;
        } else {
            col_ptr++;
        }

    }
}

void Filter2D(
        int      width,
        int      height,

        hls::stream<char>   &coeff_stream,
        hls::stream<window>  &window_stream,
        hls::stream<U8>     &pixel_stream )
{
    assert(width  <= MAX_IMAGE_WIDTH);
    assert(height <= MAX_IMAGE_HEIGHT);

    // Filtering coefficients
    char coeffs[FILTER_V_SIZE][FILTER_H_SIZE];
#pragma HLS ARRAY_PARTITION variable=coeffs complete dim=0
//#pragma HLS PIPELINE II=1

    // Load the coefficients into local storage
    load_coefs: for (char i=0; i<FILTER_V_SIZE; i++) {
        for (char j=0; j<FILTER_H_SIZE; j++) {
#pragma HLS PIPELINE II=1
            coeffs[i][j] = coeff_stream.read();
        }
    }

    // Process the incoming stream of pixel windows
//    apply_filter: for (int y = 0; y < (height-2); y++)
    Loop1: for (int y = 0; y < 126; y++)
//#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT max=126
    {
//        for (int x = 0; x < (width-2); x++)
        Loop2: for (int x = 0; x < 126; x++)
        {
#pragma HLS LOOP_TRIPCOUNT max=126
#pragma HLS PIPELINE II=1
            // Read a 2D window of pixels
            window w = window_stream.read();

            // Apply filter to the 2D window
            short sum = 0;
            Loop3: for(int row=0; row<FILTER_V_SIZE; row++)

//#pragma HLS PIPELINE
 {
                Loop4: for(int col=0; col<FILTER_H_SIZE; col++)

//#pragma HLS PIPELINE
 {
                    U8 pixel;
                    pixel = w.pix[row][col];
                    sum += (short)pixel*(short)coeffs[row][col];
                }
            }
            unsigned char outpix = MIN(MAX(sum,0), 255);
            pixel_stream.write(outpix);
        }
    }
}


extern "C" {


void filter2d_accel(
        const char kernel[9],
        int height,
        int width,

        U8 src[MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT],
        U8 dst[(MAX_IMAGE_WIDTH-2)*(MAX_IMAGE_HEIGHT-2)]
)
{
#pragma HLS INTERFACE mode=m_axi bundle=msrc depth=16384 port=src //bundle=IMG
#pragma HLS INTERFACE mode=m_axi bundle=msrc depth=15876 port=dst //bundle=IMG
#pragma HLS INTERFACE mode=s_axilite port=kernel bundle=CTRL
#pragma HLS INTERFACE mode=s_axilite port=height bundle=CTRL
#pragma HLS INTERFACE mode=s_axilite port=width bundle=CTRL
#pragma HLS INTERFACE mode=s_axilite port=return bundle=CTRL

#pragma HLS DATAFLOW


    // Stream of pixels from kernel input to filter, and from filter to output
    hls::stream<char,3>      coefs_stream;
    hls::stream<U8,2>      pixel_stream;
    hls::stream<window,3>     window_stream; // Set FIFO depth to 0 to minimize resources
    hls::stream<U8,64>     output_stream;

    // Read image data from global memory over AXI4 MM, and stream pixels out
    ReadFromMem(width, height, kernel, coefs_stream, src, pixel_stream);

    // Read incoming pixels and form valid HxV windowsm
    Window2D(width, height, pixel_stream, window_stream);

    // Process incoming stream of pixels, and stream pixels out
    Filter2D(width, height, coefs_stream, window_stream, output_stream);

    // Write incoming stream of pixels and write them to global memory over AXI4 MM
    WriteToMem(width, height, output_stream, dst);

  }

}

