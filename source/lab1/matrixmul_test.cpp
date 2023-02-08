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
// Module Name: lab1 matrix multiplier
// Purpose:
//    This is the C++ test bench for the matrix multiplier example.
// Reference:
//////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "matrixmul.h"

using namespace std;

int main(int argc, char **argv)
{
   mat_a_t in_mat_a[3][3] = {
      {11, 12, 13},
      {14, 15, 16},
      {17, 18 ,19}
   };
   mat_b_t in_mat_b[3][3] = {
      {21, 22, 23},
      {24, 25, 26},
      {27, 28, 29}
   };
   result_t hw_result[3][3], sw_result[3][3];
   int err_cnt = 0;

   // Generate the expected result
   // Iterate over the rows of the A matrix
   for(int i = 0; i < MAT_A_ROWS; i++) {
      for(int j = 0; j < MAT_B_COLS; j++) {
         // Iterate over the columns of the B matrix
         sw_result[i][j] = 0;
         // Do the inner product of a row of A and col of B
         for(int k = 0; k < MAT_B_ROWS; k++) {
            sw_result[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
         }
      }
   }

#ifdef HW_COSIM
   // Run the AutoESL matrix multiply block
   matrixmul(in_mat_a, in_mat_b, hw_result);
#endif

   // Print result matrix
   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_A_ROWS; i++) {
      cout << "{";
      for (int j = 0; j < MAT_B_COLS; j++) {
#ifdef HW_COSIM
         cout << hw_result[i][j];
         // Check HW result against SW
         if (hw_result[i][j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }
#else
         cout << sw_result[i][j];
#endif
         if (j == MAT_B_COLS - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;

#ifdef HW_COSIM
   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed." << endl;
#endif
   return err_cnt;
}

