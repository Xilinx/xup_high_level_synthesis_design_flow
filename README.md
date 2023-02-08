# High-Level-Synthesis Design Flow on ZYNQ
This workshop provides participants the necessary skills to create high-level-synthesis IPs using the Vitis HLS tool flow targeting PYNQ-Z2 and PYNQ-ZU board. Various techniques and directives which can be used in Vitis HLS to improve design performance and the essential steps to create a subsystem with the Arm® processor using the Vivado® IP integrator are introduced in detail.

The labs have been developed on **CentOS Linux 7.9 machine** and using **Vitis HLS 2021.2** version tools. A PC running Microsoft Windows 10 professional edition is also able to run the labs. Linux machine to run the Vitis HLS tool is more recommended.


## Change Log
---
2022 : Upgrade the tool version to Vitis HLS 2021.2, adding support for Boolean board. At this time, tutorial sources and docs for PYNQ-Z2 and PYNQ-ZU has finished initial release.

## Source Files Setup
---
All the source files are located in the path of **{this_repo}/sources**

For Windows machine, the absolute path for the source code should only contain ascii characters. Deep path should also be avoided since the maximum supporting length of path for Windows is 260 characters.

- **{SOURCES}** refers to {this_repository}/sources, and {this_repository} is the directory on your computer where you have copied the files.

- **{LABS}** refers to the working folder you will use for the lab projects you will create.

- **{BOARD}** refers to the target board; PYNQ-Z2 and PYNQ-ZU

**NOTE**

Board support for the and PYNQ-Z2 and PYNQ-ZU are not included in Vitis 2021.2 by default.

<Vivado_2021_2_installation>/data/xhub/boards/XilinxBoardStore/boards/Xilinx/ on Linux, and <Vivado_2021_2_installation>\\data\\xhub\\boards\\XilinxBoardStore\\boards\\Xilinx\\ on Windows machine

These files can be downloaded from  

PYNQ-Z2:[/board_files](https://www.xilinx.com/support/documents/university/vivado/workshops/vivado-adv-embedded-design-zynq/materials/2018x/PYNQZ2/pynq-z2.zip).

PYNQ-ZU:[/board_files](https://github.com/Xilinx/XilinxBoardStore/tree/master/boards/TUL/pynqzu/1.1).

**For Pynq-z2:**

When creating Vitis and Vivado projects, targeting to the parts to specify the device, The Pynq-z2 uses a **xc7z020clg400-1** Zynq-7 device with the following attributes:

| **Part Number**       | xc7z020clg400-1 |

**For Pynq-ZU:**

When creating Vitis and Vivado projects, targeting to the parts to specify the device, The Pynq-ZU uses a **xczu5eg-sfvc784-1-e** Zynq Ultrascale+ device with the following attributes:

| **Part Number**       | xczu5eg-sfvc784-1-e |

## Hardware Setup
---
**PYNQ-Z2**: Connect the board to the PC using a micro USB cable. Make sure that a jumper is connected to JTAG (between JP1_1 and JP1_2) to use the board in the development mode. Also, make sure that another jumper is placed between J9_2 and J9_3 to select USB as a power source. The PYNQ-Z2 needs to be connected to a full power USB port to operate correctly.

**PYNQ-ZU**：

Please refer to the following link to get started on PYNQ-ZU:
https://github.com/Xilinx/PYNQ-ZU/blob/master/docs/getting_started.md

## Labs Overview:
---
### Lab 1 ：Vitis HLS Design Flow 
This lab provides a basic introduction to high-level synthesis using the Vitis HLS tool flow targeting PYNQ-Z2. You will use Vitis HLS in GUI mode to create a project. You will simulate, synthesize, and implement the provided design.


### Lab 2 ：Improving Performance
This lab introduces various techniques and directives which can be used in Vitis HLS to improve design performance. The design under consideration accepts an image in a (custom) RGB format, converts it to the Y’UV color space, applies a filter to the Y’UV image and converts it back to RGB.

### Lab 3 ：Improving Area and Resource Utilization
This lab introduces various techniques and directives which can be used in Vitis HLS to improve design performance as well as area and resource utilization. The design under consideration performs Discrete Cosine Transformation (DCT) on an 8x8 block of data.

### Lab 4 ：HLS Design Flow – System Integration
This lab illustrates the HLS design flow for generating IP from the Vitis™ HLS tool. The generated IP is then used to create a subsystem with the Arm® processor from a Zynq® UltraScale+™ MPSoC using the Vivado® IP integrator. The hardware from the Vivado Design Suite is imported into the Vitis environment, and the FIR application is then run on the PYNQ-ZU development board.



<p align="center">Copyright&copy; 2022, Advanced Micro Devices, Inc.</p>