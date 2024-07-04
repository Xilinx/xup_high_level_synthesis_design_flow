# Part 2.2 Using Sobel in Vitis Vision Library to Extract Image Edges

## 1. Brief Introduction on Vitis Vision Library

* The AMD Vitis™ vision library has been designed to work in the Vitis development environment and provides a software interface for computer vision functions accelerated on an FPGA device. Vitis vision library functions are mostly similar in functionality to their OpenCV equivalent. Any deviations, if present, are documented.

### 1.1 Basic Features for All Vitis Vision Library Functions

All Vitis vision library functions follow a common format. The following properties are true for all functions:

* All the functions are designed as templates and all arguments that are images, must be provided as `xf::cv::Mat`.
* All functions are defined in the `xf::cv` namespace.
* Some of the major template arguments are:
  * Maximum size of the image to be processed
  * Datatype defining the properties of each pixel
  * Number of pixels to be processed per clock cycle
  * Depth of the hls::stream defined in `xf::cv::Mat`
  * Other compile-time arguments relevent to the functionality.

The Vitis vision library contains enumerated datatypes which enables you to configure `xf::cv::Mat`. For more details on `xf::cv::Mat`, see the [xf::cv::Mat Image Container Class](https://docs.amd.com/r/MB7YwCDoUdYtdARUnAYaJA/YlQqjjXiyAeT02v87sduFA).

### 1.2 Vitis Vision Warppers around HLS Kernel

All Vitis Vision kernels are provided with C++ function templates (located at `<Github repo>`/include) with image containers as objects of xf::cv::Mat class. In addition, these kernels will work either in stream based (where complete image is read continuously) or memory mapped (where image data access is in blocks).

Vitis flow (OpenCL) requires kernel interfaces to be memory pointers with width in power(s) of 2. So glue logic is required for converting memory pointers to xf::cv::Mat class data type and vice-versa when interacting with Vitis Vision kernel(s). Wrapper(s) are build over the kernel(s) with this glue logic. The following examples provide a methodology to handle different kernel (Vitis Vision kernels located at `<Github repo>`/include) types (stream and memory mapped), you can find it in [Wrappers around HLS Kernel(s) • Vitis Libraries](https://docs.amd.com/r/en-US/Vitis_Libraries/vision/overview.html_1_1_1)

For this tutorial, we will introduce **xf::CV::Mat** , **xf::cv::Array2xfMat** and **xf::cv::xfMat2Array** since they are used in the sobel code.

### 1.2.1 Image Pixel Data Types

[Data types](https://docs.amd.com/r/en-US/Vitis_Libraries/vision/api-reference.html_0_3) will differ depending on the combination of the depth of pixels and the number of channels in the image. The generic nomenclature of the parameter is listed below.

```
XF_<Number of bits per pixel><signed (S) or unsigned (U) or float (F)>C<number of channels>
```

For example, for an 8-bit pixel - unsigned -1 channel the data type is `XF_8UC1.`

### 1.2.2 Image Container Class - xf::CV::Mat

- `xf::cv::Mat` is a template class that serves as a container for storing image data and its attributes.
- The `xf::cv::Mat` image container class is similar to the `cv::Mat` class of the OpenCV library.
- For example, in the sobel Vitis Vision Library code, `xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN>in_mat(rows, cols);`
  - For template parameter descriptions
    - | Parameter | Description                                                                                                                      |
      | --------- | -------------------------------------------------------------------------------------------------------------------------------- |
      | TYPE      | Type of the pixel data, XF_8UC1 for 8-bit grayscale image.                                                                       |
      | HEIGHT    | Maximum height of an image.                                                                                                      |
      | WIDTH     | Maximum width of an image.                                                                                                       |
      | NPC       | The number of pixels to be packed per word. For instance, XF_NPPC1 for 1 pixel per word; and XF_NPPC8 for eight pixels per word. |
      | XFCVDEPTH | Depth of the hls::stream in the xf::cv::Mat, which is 2 in this case                                                             |
  - For the constructor
    - This constructor initializes the `xf::cv::Mat` object using arguments `rows` and `cols`.
  - More details can be found at this link: [Class Definition • Vitis Libraries • Reader • AMD Technical Information Portal](https://docs.amd.com/r/en-US/Vitis_Libraries/vision/api-reference.html_0_1)

### 1.2.3 Array2xfMat

* This function converts the input array to `xf::cv::Mat`. The Vitis Vision kernel would require the input to be of type, `xf::cv::Mat`. This function would read from the array pointer and write into `xf::cv::Mat` based on the particular configuration (bit-depth, channels, pixel-parallelism) the xf::cv::Mat was created. `Array2xfMat` supports line stride. Line stride is the number of pixels which needs to be added to the address in the first pixel of a row in order to access the first pixel of the next row.
* ```cpp
  //Without Line stride support
  template <int PTR_WIDTH, int MAT_T, int ROWS, int COLS, int NPC>
  void Array2xfMat(ap_uint< PTR_WIDTH > *srcPtr, xf::cv::Mat<MAT_T,ROWS,COLS,NPC,XFCVDEPTH>& dstMat)

  //With Line stride support
  template <int PTR_WIDTH, int MAT_T, int ROWS, int COLS, int NPC>
  void Array2xfMat(ap_uint< PTR_WIDTH > *srcPtr, xf::cv::Mat<MAT_T,ROWS,COLS,NPC,XFCVDEPTH>& dstMat, int stride)
  ```
* | Parameter | Description                                                                         |
  | --------- | ----------------------------------------------------------------------------------- |
  | COLS      | Maximum width of image                                                              |
  | dstMat    | Output image of type xf::cv::Mat                                                    |
  | MAT_T     | Input Mat type. Example XF_8UC1, XF_16UC1, XF_8UC3 and XF_8UC4                      |
  | NPC       | Number of pixels computed in parallel. Example XF_NPPC1, XF_NPPC8                   |
  | PTR_WIDTH | Data width of the input pointer. The value must be power 2, starting from 8 to 512. |
  | ROWS      | Maximum height of image                                                             |
  | srcPtr    | Input pointer. Type of the pointer based on the PTR_WIDTH.                          |
  | stride    | Line stride. Default value is dstMat.cols                                           |
  | XFCVDEPTH | Depth of the Output image.                                                          |

## 2 Sobel Filter in Vitis Vision Library `xf_sobel_accel.cpp`

- The **Sobel** function Computes the gradients of input image in both x and y direction by convolving the kernel with input image being processed.
- This design aims to implement a **$3\times 3$ Sobel Filter** to find edges of an **8-bit grayscale $128 \times 128$ image**.

### 2.1 Sobel Filter API - `xf::cv::Sobel`

- In this code, it firstly read image data from `m_axi` as an array, then use `xf::cv::array2xfmat` to convert it to an `xf::cv::Mat`, the using the `xf::cv::Sobel` function to apply Sobel filter to the image, then the result is converted to array using `xf::cv::xfMat2array`, and sent back to memory through `m_axi`.
- For data depth of `m_axi`, it is the number of pixels of the input image or output image, like `static constexprint__XF_DEPTH= (HEIGHT*WIDTH* (XF_PIXELWIDTH(IN_TYPE, NPPCX)) /8) / (INPUT_PTR_WIDTH/8);`, in which

  * `XF_PIXELWIDTH(IN_TYPE, NPPCX)` is replaced during compilation with a template class `DataType<flags, npc>::pixelwidth`.
    * `IN_TYPE` specifies the image pixel type. In the Sobel filter, the input image type must be 8-bit, unsigned, supporting 1 and 3 channels (XF_8UC1 and XF_8UC3).
    * `NPPCX` refers to the number of pixels to be processed per cycle, with possible options being `XF_NPPC1` for 1 pixel and `XF_NPPC8` for 8 pixels.
    * `pixelwidth` represents the total bit-width of all color channels for a single pixel. When `IN_TYPE=XF_8UC1` (8-bit grayscale) and `NPPCX=XF_NPPC1`, `datawidth` is 8. When `IN_TYPE=XF_8UC3` (8-bit RGB color) and `NPPCX=XF_NPPC1`, `datawidth` is 24.
    * Therefore, dividing `datawidth` by the bit depth per channel (8 bits) yields the corresponding number of channels.
  * `INPUT_PTR_WIDTH` is the bit-width per pixel for the image. For 8-bit grayscale or RGB images, this value is 8, hence `INPUT_PTR_WIDTH/8` signifies a single pixel.
  * Consequently, `depth` corresponds to the total number of pixels to be processed in the input stage, similarly for the output.
- The Sobel Parameter Description of `xf::cv:Sobel()` is listed in [Table 726 Table . Sobel Parameter Description](https://docs.amd.com/r/en-US/Vitis_Libraries/vision/api-reference.html_5_3), and the relavent configration of Sobel is noted in `<Your Vitis Vision Library Path>/vision/L1/examples/sobelfilter/config/xf_config_params.h`, the detailted configration will be shown in the next section.

### 2.2 Configration of Sobel Filter

- Configration of Sobel Filter is listed in `<Your Vitis Vision Library Path>/vision/L1/examples/sobelfilter/config/xf_config_params.h`, **DO NOT FORGET to change the relavent settings if you want to use Sobel Filter for other cases**.
- We want to process an $128 \times 128$ image, so the `WIDTH` and `HEIGHT` will be 128.
- We apply a $3 \times 3$ sobel filter to the image, so  `FILTER_SIZE_3` will be 1, while  `FILTER_SIZE_5` and `FILTER_SIZE_7` will be 0.
- Also, we expect 1 pixel is processed per cycle, so `NPPCX` will be `XF_NPPC1`.
- Moreover, since we a processing an 8-bit grayscale image, `IN_TYPE`, `OUT_TYPE`, `CV_IN_TYPE`, `CV_OUT_TYPE`, will be `XF_8UC1`, you can change it to `XF_8UC3`if you want to process an 8-bit RGB image.
- Lastly, `INPUT_PTR_WIDTH` and `OUTPUT_PTR_WIDTH` are set to 8, since every pixel in every channel is 8-bit.

  - | Parameter       | Description                                                                            | Configration in this tutorial |
    | --------------- | -------------------------------------------------------------------------------------- | ----------------------------- |
    | FILTER_TYPE     | Filter size. Filter size of 3, 5 , and 7 are supported.                                | XF_FILTER_3X3                 |
    | BORDER_TYPE     | Border Type supported is XF_BORDER_CONSTANT.                                           | \                             |
    | SRC_T           | Input pixel type. Only 8-bit, unsigned, 1 and 3 channels are supported.                | XF_8UC1                       |
    | DST_T           | Output pixel type. Only 8-bit unsigned, 16-bit signed, 1 and 3 channels are supported. | XF_8UC1                       |
    | ROWS            | Maximum height of input and output image.                                              | 128                           |
    | COLS            | Maximum width of input and output image. Must be multiple of 8, for 8-pixel operation. | 128                           |
    | NPC             | Number of pixels to be processed per cycle;                                            | XF_NPPC1                      |
    | USE_URAM        | Enable to map storage structures to UltraRAM.                                          | Disable                       |
    | XFCVDEPTH_IN    | Depth  of the input image.                                                            | 2                             |
    | XFCVDEPTH_OUT_X | Depth of the output image.                                                             | 2                             |
    | XFCVDEPTH_OUT_Y | Depth of the output image.                                                             | 2                             |
    | _src_mat        | Input image.                                                                           | \                             |
    | _dst_matx       | X gradient output image.                                                               | \                             |
    | _dst_maty       | Y gradient output image.                                                               | \                             |
    |                 | **Note:** Sobel 7x7 NPC = 8-pixel is not supported.                              |                               |

---

### 3 Synthesis Report

| Operation Mode | Filter Size | Operating Frequency (MHz) | BRAM | DSP | FF   | LUT   | URAM |
| -------------- | ----------- | ------------------------- | ---- | --- | ---- | ----- | ---- |
| 1 pixel        | 3x3         | 200                       | 9    | 8   | 8128 | 11063 | 0    |

## Reference

- https://docs.amd.com/r/en-US/Vitis_Libraries/vision/overview.html_0_0
- https://docs.amd.com/r/en-US/Vitis_Libraries/vision/overview.html_1_1_1
- https://docs.amd.com/r/en-US/Vitis_Libraries/vision/api-reference.html_0_0
- https://docs.amd.com/r/en-US/Vitis_Libraries/vision/api-reference.html_5_3

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
