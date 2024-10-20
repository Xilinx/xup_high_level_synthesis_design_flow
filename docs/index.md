# High-Level-Synthesis Design Flow on ZYNQ

This workshop provides participants the necessary skills to create high-level-synthesis IPs using the Vitis HLS tool flow targeting PYNQ-Z2 and PYNQ-ZU board. Various techniques and directives which can be used in Vitis HLS to improve design performance and the essential steps to create a subsystem with the Arm® processor using the Vivado® IP integrator are introduced in detail.

The original labs have been developed to demonstarte the basic design flow on Vitis HLS. A PC running Microsoft Windows 10 professional edition is also able to run the labs. Linux machine to run the Vitis HLS tool is more recommended.

The [project-based learning labs](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/docs/pbl.md) offer a straightforward, transparent, and intuitive approach to learning, with practical applications within the PYNQ framework. This includes the HLS kernel design methodology and the utilization of the Vitis Accelerated Library.

## Change Log

2024 : Add the new Project-based Learning Section, upgrade the tool version to **2023.2**, adding support for KV260 Board, Jupyter Notebooks and tutorial sources for PYNQ-Z2 and KV260 under PYNQ framework has finished initial release

2022 : Upgrade the basic labs to Vitis HLS **2021.2**, adding support for Boolean board. At this time, tutorial sources and docs for PYNQ-Z2 and PYNQ-ZU has finished initial release.

## Board Setup

<table>
<thead>
    <tr>
        <th></th>
        <th>Board File</th>
        <th>Part Number</th>
        <th>Hardware Bring Up</th>
    </tr>
</thead>
<tbody>
    <tr>
        <th>PYNQ-Z2</th>
    	<td><a href="https://www.xilinx.com/support/documents/university/vivado/workshops/vivado-adv-embedded-design-zynq/materials/2018x/PYNQZ2/pynq-z2.zip">Download</a></td>
        <td>xc7z020clg400-1</td>
        <td><a 	href="https://pynq.readthedocs.io/en/latest/getting_started/pynq_z2_setup.html">Guide</a>
        </td>
    </tr>
    <tr>
        <th>PYNQ-ZU</th>
    	<td><a href="https://github.com/Xilinx/XilinxBoardStore/tree/master/boards/TUL/pynqzu/1.1">Download</a></td>
        <td>xczu5eg-sfvc784-1-e</td>
        <td><a 	href="https://github.com/Xilinx/PYNQ-ZU/blob/master/docs/getting_started.md">Guide</a>
        </td>
    </tr>
    <tr>
        <th>KV260</th>
    	<td>Pre-installed</td>
        <td>xck26-sfvc784-2LV-c</td>
        <td><a 	href="https://docs.amd.com/r/en-US/ug1089-kv260-starter-kit/Initial-Setup">Guide</a>
        </td>
    </tr>
</tbody>
</table>

All the source files are located in the path of **{this_repo}/sources**

For Windows machine, deep path should also be avoided since the maximum supporting length of path for Windows is 260 characters.

---

## Projected-based Learning Labs Overview

<table>
<thead>
    <tr>
        <th>Project</th>
        <th>Difficulty</th>
        <th>Implementation</th>
        <th>Key Concept</th>
        <th>Interface</th>
        <th>Board</th>
    </tr>
</thead>
<tbody>
    <tr>
    	<td><a href="https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/fir/readme.md">FIR</a></td>
        <td>Easy</td>
        <td>Hand-written</td>
        <td>Transferring Sequential Loops to Parallel Loops</td>
        <td>Memory</td>
        <td>PYNQ-Z2/KV260</td>
    </tr>
    <tr>
    	<td><a href="https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/sobel/readme.md">Sobel</a></td>
        <td>Easy</td>
        <td>Hand-written/<br />Vitis Vision Library</td>
        <td>Flexible Adoption of Vitis Vision Library Level 1 Kernels</td>
        <td>Memory/<br />Stream</td>
        <td>PYNQ-Z2/KV260</td>
    </tr>
    <tr>
    	<td><a href="https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/conv_filter/readme.md">Convolution Filter</a></td>
        <td>Easy</td>
        <td>Hand-written</td>
        <td>Best Practices for Data-driven Task-level Parallelism</td>
        <td>Stream</td>
        <td>PYNQ-Z2/KV260</td>
    </tr>
    <tr>
    	<td><a href="https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/matmult/readme.md">Matmult</a></td>
        <td>Easy</td>
        <td>Hand-written</td>
        <td>Mapping the 2D Array to Customizable Memory</td>
        <td>Memory</td>
        <td>PYNQ-Z2/KV260</td>
    </tr>
</tbody>
</table>

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
