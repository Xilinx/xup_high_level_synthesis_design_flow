# Explore Different Implementations of the Sobel Filter: Hand-Written vs. Vitis Vision Library

In this section, we will focus on implementing an optimized hand-written version of the Sobel operator in HLS and comparing its performance with the Sobel operator from the Vitis Vision Library. The first challenge we will encounter is the installation and configuration of the Vitis Vision Library, with all installation details provided in this document. Next, we will deploy the different versions of the Sobel HLS kernel onto the board and test the hardware acceleration performance within the PYNQ framework. A comparison of different implementations of the Sobel operator shows that using the Vitis Vision Library is more than three times faster than the hand-written Sobel acceleration kernel when run on the same device and interface. Therefore, we need to master not only the design process and optimization techniques for HLS kernels but also learn to implement suitable operators using the existing Vitis Acceleration library.

## Comparison

The advantages and disadvantages of the two methods are as follows:

| Method                         | Advantages                                               | Disadvantages                                              |
| ------------------------------ | -------------------------------------------------------- | ---------------------------------------------------------- |
| **Hand-Written Sobel**   | - Highly customizable                                    | - Time-consuming to develop and optimize                   |
|                                | - Potential for tailored optimization for specific needs | - Requires deep knowledge of HLS and algorithm intricacies |
| **Vitis Vision Library** | - Faster development time                                | - Less flexibility in customization                        |
|                                | - Pre-optimized for performance                          | - Dependent on library updates                             |
|                                | - Easier to implement                                    |                                                            |

## Content

<table border="2">
<thead>
  <tr>
    <th>Part</th>
    <th>Topic</th>
    <th>Description</th>
    <th>Environment</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td rowspan="1">1</td>
    <td rowspan="1"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/notebook/sobel_part1.ipynb">Software Implementation</a></td>
    <td>Software Implementation with OpenCV-Python Library</td>
    <td rowspan="1">Jupyter Notebook</td>
  </tr>
  <tr>
    <td rowspan="2">2</td>
    <td rowspan="2">HLS Kernel Programming</td>
    <td><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/notebook/sobel_part2_handcoded.md">Hand-Coded Sobel HLS Kernel to Extract Image edges</a></td>
    <td rowspan="2">AMD Vitis HLS 2023.2</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/notebook/sobel_part2_visionLib.md">Using Sobel in Vitis Vision Library to Extract Image Edges</a></td>
  </tr>
  <tr>
    <td rowspan="3">3</td>
    <td rowspan="3"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/notebook/sobel_part3.ipynb">System-level Integration</a></td>
    <td>Create the kernel Graph and the test bench</td>
    <td rowspan="3">Jupyter Notebook</td>
  </tr>
  <tr>
    <td>Load the overlay and run the application on the PYNQ framework</td>
  </tr>
  <tr>
    <td>Visualize the results and analyze the performance</td>
  </tr>
</tbody>
</table>

## Installation and Deployment of Vitis Vision Library

1. **Installation Steps** :

   * Detailed instructions for installing the Vitis Vision Library are provided in the accompanying [documentation](https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/tutorial/vision_library_guide.md).
   * Ensure all dependencies and environment settings are configured correctly.
   * Follow the configuration steps to set up the library within your development environment.
   * Verify the installation by running [run_standalone.tcl](https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/tutorial/run_standalone.tcl) file.

2. **Deployment Steps** :

   * Follow the Sobel GUI flow [tutorial](https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/sobel/tutorial/sobel_gui_flow.md) or the tcl file to generate the PYNQ overlay.
   * Deploy both the hand-written HLS Sobel kernel and the Vitis Vision Library Sobel kernel onto the board.
   * Ensure that the PYNQ framework is correctly set up to support hardware acceleration.
   * Test the performance of both implementations within the PYNQ framework.
   * Measure metrics such as execution time, resource utilization, and power consumption.

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
