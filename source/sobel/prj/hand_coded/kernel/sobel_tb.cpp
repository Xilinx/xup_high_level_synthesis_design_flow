// Copyright (C) 2024 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <complex>
#include <complex.h>

#include "sobel.hpp"

using namespace std;

int main () {

  PIXEL src[HEIGHT*WIDTH];
  PIXEL dst[(HEIGHT-2)*(WIDTH-2)];

  ifstream file("../data/data.txt");
  string line;
  short int s1;
  int i = 0;

read_file:
  while(getline(file,line) && (i < (HEIGHT*WIDTH)))
  {
    istringstream sin(line);
    sin >> s1;
    src[i] = (PIXEL)s1;
    //cout << src[i] << endl;
    i = i + 1;
  }

	hls::stream<trans_pkt> _src;
	hls::stream<trans_pkt> _dst;
	trans_pkt data_p;
	int row, col;

mm2s:
	for(row = 0; row < HEIGHT; row++)
	{
		for(col = 0; col < WIDTH; col++)
		{
			data_p.data = *(src + row*WIDTH + col);
			_src.write(data_p);
		}
	}

  sobel(_src, _dst, HEIGHT, WIDTH);

s2mm:
	for(row = 0; row < HEIGHT; row++)
	{
		for(col = 0; col < WIDTH; col++)
		{
			data_p = _dst.read();
			*(dst + row*WIDTH + col) = data_p.data;
		}
	}

  int tf = 0;

//verify the result
  ifstream fileo("../data/dst_1280x720.txt");
  string lineo;
  short int s2;
  int j = 0;
  int err_cnt = 0;

  while(getline(fileo,lineo) && (j < (HEIGHT)*(WIDTH)))
  {
    istringstream sino(lineo);
    sino >> s2;
    if ((short int)dst[j] != s2)
    {
      tf = 1;
      err_cnt++;
    }
    j = j + 1;
  }


//  write the result to txt
    ofstream fout;
    fout.open("../data/imgo.txt");
    int m = 0;
    string pixelo;
    short int pixel;
	for(m = 0; m < ((HEIGHT)*(WIDTH)); m++)
	{
	   pixel = dst[m];
	   fout << pixel << endl;
	}

  if (tf == 1)
  {
    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
    fprintf(stdout, "*******************************************\n");
    return 1;
  }
  else
  {
    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "PASS: The output matches the golden output!\n");
    fprintf(stdout, "*******************************************\n");
    return 0;
  }

}
