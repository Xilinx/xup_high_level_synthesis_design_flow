# High-Level-Synthesis-Flow-on-Zynq-using-Vitis-HLS

This course provides users with an understanding of high-level synthesis design methodologies necessary to develop digital systems using Vitis HLS 2021.2 version.

## Required Setup

Create a recommended working directory as **/home/xup/hls**. Clone this repository and then copy the **source** directory as **labs** into a working directory. After copying the directory, all labs will be carried out in their respective folders located at **/home/xup/hls/labs**.

---
#### Instructions for the labs;

**{labs}** refers to **/home/xup/hls/labs** on a Linux machine and **C:\\xup\\hls\\labs** on a Windows machine.

---
**NOTE**

Board support for the PYNQ-Z2 and PYNQ-ZU are not included in Vivado 2021.2 by default. The relevant files need to be extracted and saved to:

<Vivado_2021_2_installation>/data/xhub/boards/XilinxBoardStore/boards/Xilinx/ on Linux, and <Vivado_2021_2_installation>\\data\\xhub\\boards\\XilinxBoardStore\\boards\\Xilinx\\ on Windows machine

These files can be downloaded from  

PYNQ-Z2:[/board_files](https://www.xilinx.com/support/documents/university/vivado/workshops/vivado-adv-embedded-design-zynq/materials/2018x/PYNQZ2/pynq-z2.zip).

PYNQ-ZU:[/board_files](https://github.com/Xilinx/XilinxBoardStore/tree/master/boards/TUL/pynqzu/1.1).

---

## Hardware Setup

Connect the board to the PC using a micro USB cable. Make sure that a jumper is connected to JTAG (between JP1_1 and JP1_2) to use the board in the development mode. Also, make sure that another jumper is placed between J9_2 and J9_3 to select USB as a power source.

---

## Labs Overview

### Lab1:

This lab provides a basic introduction to high-level synthesis using the Vitis HLS tool flow. You will use
Vitis HLS in GUI mode to create a project. You will simulate, synthesize, perform design analysis, and implement the provided model.

### Lab2:

This lab introduces various techniques and directives which can be used in Vitis HLS to improve
design performance. The design under consideration accepts an image in a (custom) RGB format,
converts it to the Y’UV color space, applies a filter to the Y’UV image and converts it back to RGB.

### Lab3:

This lab introduces various techniques and directives which can be used in Vitis HLS to improve
design performance as well as area and resource utilization. The design under consideration performs
discrete cosine transformation (DCT) on an 8x8 block of data.

### Lab4:

This lab introduces a design flow to generate a IP-XACT adapter from a design using Vitis HLS and
using the generated IP-XACT adapter in a processor system using IP Integrator in Vivado.
<p align="center">Copyright&copy; 2022, Advanced Micro Devices, Inc.</p>