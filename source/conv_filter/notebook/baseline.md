In this section, we will learn how to use OpenCV filter2D method to apply filters on images such as sharpening, bluring and finding edges in the images. Applying filters to images is basically a 2D convolution process. With that in mind we are going to introduce the best practise to implement custom image processing in hardware using the Vitis HLS tool. So lets get started!!!

While dealing with images in Image Processing, filter2D function is used to change the pixel intensity value of an image based on the surrounding pixel intensity values. This method can enhance or remove certain features of an image to create a new image.

## What is a kernel?

Also known as convolution matrix or mask, kernel is a small 2-dimensional matrix containing values that represent how much part of surrounding pixel values it should take to calculate intensity value of the current pixel. Usually, kernels are square matrices of odd length like 3×3, 5×5, 7×7 matrices.

Thus, the kernel act as a weighted matrix and is used for the blurring of images, sharpening of images, detection of edges in the images, etc. in image processing. This is done by convolution between image and kernel.

## What is Convolution?

In Image Processing, Convolution is simply an element wise multiplication of kernel and some part of source image to produce a new single data point representing a pixel, doing it on every possible part of image to create a new image.

In Convolution, we take a sub-matrix from source image of same size as that of kernel, multiply each element of source image with corresponding element of kernel, perform addition on the previous computation and normalize the data so as to represent the data as pixel value.

## Baseline Application of Convolution Filter

A matrix of coefficients defines a convolution filter. The convolution operation is essentially a sum of products performed on a pixel set (a frame/image sub-matrix centered around a given pixel) and a coefficients matrix. The figure below illustrates how convolution is calculated for a pixel; it is highlighted in green. Here the filter has a coefficient matrix that is 3x3 in size. The figure also displays how the whole output image is generated during the filtering process. The index of the output pixel being generated is the index of the input pixel highlighted in green that is being filtered. In algorithmic terms, the process of filtering consists of:

1. Selecting an input pixel as highlighted in the figure below
2. Extracting a sub-matrix whose size is the same as filter coefficients
3. Calculating element-wise sum-of-product of extracted sub-matrix and coefficients matrix
4. Placing the sum-of-product as output pixel in output image/frame on the same index as the input pixel

Consider an example as shown in the image below:
![filter2d](./image/filter2d.avif)

## Boundary condition

In most cases, the processing window contains a region of the input image. However, near the boundary of the input image, the filter may extend beyond the boundary of the input image. Depending on the requirements of different applications, there are many different ways of accounting for the behavior of the filter near the boundary. Perhaps the simplest way to account for the boundary condition is to compute a smaller output image that avoids requiring the values of input pixels outside of the input image. However, in applications where the output image size is fixed, such as Digital Television, this approach is generally unacceptable. In addition, if a sequence of filters is required, dealing with a large number images with slightly different sizes can be somewhat cumbersome. Alternatively, the missing values can be synthesized, typically in one of several ways.

• Missing input values can be filled with a constant

• Missing input values can be filled from the boundary pixel of the input image.

• Missing input values can be reconstructed by reflecting pixels from the interior of the input image.

### Teaching Case: Simple Convolution Filter Without Considering Boundary Conditions

Below is the baseline code of a functionally correct, but highly unoptimized, implementation of filter2D. Boundary conditions where it is not possible to center sub-matrix around a given pixel require special processing. This teaching case assumes that no padding operations are done to the input and output pixels. As a result, if the size of the input image is N squared, the size of the output image would be $N-2 \times (k/2)$ squared. In this way, we can focus on the optimization of the convolution filtering itself in the following study.

Run the teaching baseline application using Vitis HLS to measure performance as follows:

```bash
cd /BEST_PRACTICE_REPO_PATH/src/baseline_128
vitis_hls -f script.tcl

```

The following is the core codes of the teaching case.

```c++
#define N 128 //input image size
#define K 3 //filter kernel size

void filter2d_accel(DTYPE* img_in, DTYPE* kernel, DTYPE* img_out, int rows, int cols)
{


    for (int r = k/2; r < rows-k/2; r++)
    {
        for (int c = k/2; c < cols-k/2; c++)
        {
        	DTYPE img_temp=0;
    		for(int i=0; i<K; i++){
    			for(int j=0; j<K; j++){
    				 img_temp += img_in[(r+i-k/2)*128+ c+j-k/2] * kernel[i*K+j];
    			}
    		}
    		img_out[ (r-k/2) * (N-2(k/2)) + c - k/2] = img_temp;
        }
    }
}

```

### Industrial Case: Extensible Universal Convolution Filter Kernel

This industrial baseline application has higher extensibility and versatility by adding the features of dealing with boundary conditions, setting the stride parameter and normalizing the output pixels. In this case, the missing image boundaries are filled with 0 to keep the output image size fixed.

Run the industrial baseline application using Vitis HLS to measure performance as follows:

```bash
cd /VITIS_TUTORIAL_REPO_PATH/Hardware_Acceleration/Design_Tutorials/01-convolution-tutorial/hls_build/
vitis_hls -f build.tcl
```

```C++
void Filter2D(
		const char           coeffs[FILTER_V_SIZE][FILTER_H_SIZE],
		float		         factor,
		short                bias,
		unsigned short       width,
		unsigned short       height,
		unsigned short       stride,
		const unsigned char *src,
		unsigned char       *dst)
{
    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
        	// Apply 2D filter to the pixel window
			int sum = 0;
			for(int row=0; row<FILTER_V_SIZE; row++)
			{
				for(int col=0; col<FILTER_H_SIZE; col++)
				{
					unsigned char pixel;
					int xoffset = (x+col-(FILTER_H_SIZE/2));
					int yoffset = (y+row-(FILTER_V_SIZE/2));
					// Deal with boundary conditions : clamp pixels to 0 when outside of image 
					if ( (xoffset<0) || (xoffset>=width) || (yoffset<0) || (yoffset>=height) ) {
						pixel = 0;
					} else {
						pixel = src[yoffset*stride+xoffset];
					}
					sum += pixel*coeffs[row][col];
				}
			}

        	// Normalize and saturate result
			unsigned char outpix = MIN(MAX((int(factor * sum)+bias), 0), 255);

			// Write output
           	dst[y*stride+x] = outpix;
        }
    }
}
```

In the following chapters, a complete design flow with the best practices to create a image processing kernel using the Vitis HLS tool on Alveo U200 device will be introduced.

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
