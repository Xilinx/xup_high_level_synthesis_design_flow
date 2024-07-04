# Birdsong Separation Using FIR Filters

## Introduction

In this project-based lab, we are given a piece of audio with two bird sounds mixed in. Through the human ear, we can simply distinguish the two sounds. Then you can think about how, through technical means, you can turn this piece of audio mixed with two bird sounds into two pieces of audio with separate bird sounds? After running this lab, you will have the answer.

The purpose of this lab is to separate the two bird sounds in the audio and get separate bird sounds. To achieve this, we will use C++ language to write FIR filter for separation at HLS (high level synthesis) level, and use parallel and pipelined hardware design ideas and AXI4 data transfer protocol to perform hardware acceleration on PYNQ board. We also use python for software code writing to show the advantages of hardware acceleration after comparing the two.

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
    <td rowspan="2">1</td>
    <td rowspan="2"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/fir/notebook/fir_part1.ipynb">Software Implementation</a></td>
    <td>Read in an audio clip and visualize the audio in the frequency domain</td>
    <td rowspan="2">Jupyter Notebook</td>
  </tr>
  <tr>
    <td>Designing a high-pass filter to remove low-frequency birdsong</td>
  </tr>
  <tr>
    <td rowspan="6">2</td>
    <td rowspan="6"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/fir/notebook/fir_part2.ipynb">HLS Kernel Programming</a></td>
    <td>Determine the Design Specifications</td>
    <td rowspan="6">AMD Vitis HLS 2023.2</td>
  </tr>
  <tr>
    <td>Code hoisting to remove unnecessary conditional operations</td>
  </tr>
  <tr>
    <td>Array partitioning to enable loop parallelism</td>
  </tr>
  <tr>
    <td>Loop split for tailored optimizations</td>
  </tr>
  <tr>
    <td>Loop Unrolling and Pipelining</td>
  </tr>
    <tr>
    <td>Putting it All Together -- Kernel Code Analysis</td>
  </tr>
  <tr>
    <td rowspan="4">3</td>
    <td rowspan="4"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/fir/notebook/fir_part3.ipynb">System-level Integration</a></td>
    <td>Create the kernel Graph and the test bench</td>
    <td rowspan="4">Jupyter Notebook</td>
  </tr>
  <tr>
    <td>Analyze AXI4 Data Transfer Protocol</td>
  </tr>
    <tr>
    <td>Load the overlay and run the application on the PYNQ framework</td>
  </tr>
  <tr>
    <td>Visualize the results and analyze the performance</td>
  </tr>
</tbody>
</table>

- Note: A basic understanding of FIR filters, C language, and the Vitis™ tools is assumed.


---
<p align="center">Copyright© 2024 Advanced Micro Devices</p>
