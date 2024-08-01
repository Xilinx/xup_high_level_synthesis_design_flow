# High-Level-Synthesis Design Flow on ZYNQ

This workshop provides participants the necessary skills to create high-level-synthesis IPs using the Vitis HLS tool flow targeting PYNQ-Z2 and PYNQ-ZU board. Various techniques and directives which can be used in Vitis HLS to improve design performance and the essential steps to create a subsystem with the Arm® processor using the Vivado® IP integrator are introduced in detail.

The original labs have been developed to demonstarte the basic design flow on Vitis HLS. A PC running Microsoft Windows 10 professional edition is also able to run the labs. Linux machine to run the Vitis HLS tool is more recommended.

The [project-based learning labs](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/docs/pbl.md) offer a straightforward, transparent, and intuitive approach to learning, with practical applications within the PYNQ framework. This includes the HLS kernel design methodology and the utilization of the Vitis Accelerated Library.

## Change Log

2024 : Add the new Project-based Learning Section, upgrade the tool version to **2023.2**, adding support for KV260 Board, Jupyter Notebooks and tutorial sources for PYNQ-Z2 and KV260 under PYNQ framework has finished initial release

2022 : Upgrade the basic labs to Vitis HLS **2021.2**, adding support for Boolean board. At this time, tutorial sources and docs for PYNQ-Z2 and PYNQ-ZU has finished initial release.

## Board Setup

|         | Board File                                                                                                                                       | Part Number         | Hardware Bring Up                                                              |
| ------- | ------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------- | ------------------------------------------------------------------------------ |
| PYNQ-Z2 | [Download](https://www.xilinx.com/support/documents/university/vivado/workshops/vivado-adv-embedded-design-zynq/materials/2018x/PYNQZ2/pynq-z2.zip) | xc7z020clg400-1     | [Guide](https://pynq.readthedocs.io/en/latest/getting_started/pynq_z2_setup.html) |
| PYNQ-ZU | [Download](https://github.com/Xilinx/XilinxBoardStore/tree/master/boards/TUL/pynqzu/1.1)                                                            | xczu5eg-sfvc784-1-e | [Guide](https://github.com/Xilinx/PYNQ-ZU/blob/master/docs/getting_started.md)    |
| KV260   | /                                                                                                                                                | xck26-sfvc784-2LV-c | [Guide](https://docs.amd.com/r/en-US/ug1089-kv260-starter-kit/Initial-Setup)      |

All the source files are located in the path of **{this_repo}/sources**

For Windows machine, deep path should also be avoided since the maximum supporting length of path for Windows is 260 characters.

**NOTE**

Board support for the and PYNQ-Z2 and PYNQ-ZU are not included in Vitis by default.

<Vivado_installation>/data/xhub/boards/XilinxBoardStore/boards/Xilinx/ on Linux, and <Vivado_installation>\\data\\xhub\\boards\\XilinxBoardStore\\boards\\Xilinx\\ on Windows machine

## Projected-based Learning Labs Overview：

| Project                                                                                                                  | Difficulty | Implementation                          | Key Concept                                               | Interface           | Board         |
| ------------------------------------------------------------------------------------------------------------------------ | ---------- | --------------------------------------- | --------------------------------------------------------- | ------------------- | ------------- |
| [FIR](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/fir/readme.md)                        | Easy       | Hand-written                            | Transferring Sequential Loops to Parallel Loops           | Memory              | PYNQ-Z2/KV260 |
| [Sobel](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/sobel/readme.md)                    | Easy       | Hand-written/<br />Vitis Vision Library | Flexible Adoption of Vitis Vision Library Level 1 Kernels | Memory/<br />Stream | PYNQ-Z2/KV260 |
| [Convolution Filter](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/conv_filter/readme.md) | Easy       | Hand-written                            | Best Practices for Data-driven Task-level Parallelism     | Stream              | PYNQ-Z2/KV260 |
| [Matmult](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/matmult/readme.md)                | Easy       | Hand-written                            | Mapping the 2D Array to Customizable Memory               | Memory              | PYNQ-Z2/KV260 |

---

## Basic Labs Overview:

### Lab 1 ：Vitis HLS Design Flow

This lab provides a basic introduction to high-level synthesis using the Vitis HLS tool flow targeting PYNQ-Z2. You will use Vitis HLS in GUI mode to create a project. You will simulate, synthesize, and implement the provided design.

### Lab 2 ：Improving Performance

This lab introduces various techniques and directives which can be used in Vitis HLS to improve design performance. The design under consideration accepts an image in a (custom) RGB format, converts it to the Y’UV color space, applies a filter to the Y’UV image and converts it back to RGB.

### Lab 3 ：Improving Area and Resource Utilization

This lab introduces various techniques and directives which can be used in Vitis HLS to improve design performance as well as area and resource utilization. The design under consideration performs Discrete Cosine Transformation (DCT) on an 8x8 block of data.

### Lab 4 ：HLS Design Flow – System Integration

This lab illustrates the HLS design flow for generating IP from the Vitis™ HLS tool. The generated IP is then used to create a subsystem with the Arm® processor from a Zynq® UltraScale+™ MPSoC using the Vivado® IP integrator. The hardware from the Vivado Design Suite is imported into the Vitis environment, and the FIR application is then run on the PYNQ-ZU development board.

---

<p align="center">Copyright© 2024, Advanced Micro Devices, Inc.</p>
