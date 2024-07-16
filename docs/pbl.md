# Project-Based Learning Tutorial

## Goal

**[Project-based learning](https://en.wikipedia.org/wiki/Project-based_learning)** is a teaching method that involves a dynamic classroom approach in which it is believed that students acquire a deeper knowledge through active exploration of real-world challenges and problems.

This Project-based learning tutorial offers a straightforward, transparent, and intuitive learning approach with practical applications utilizing the Vitis High-Level Synthesis Tool:

* Adoption of Vitis Library Level 1 HLS Kernels.
* Emphasis on HLS Kernel programming methodology.
* System-level Integration under the PYNQ framework.
* Visual project demonstrations in the Jupyter Lab environment.

## Background

A program written in C/C++ is essentially written for the von Neumann style of architecture where each instruction in the user's program is executed sequentially. In order to achieve high performance, the HLS tool must infer parallelism in the sequential code and exploit it to achieve greater performance.

Now even if the software program can be automatically converted (or synthesized) into hardware, achieving acceptable quality of results (QoR), will require additional work such as rewriting the software to help the HLS tool achieve the desired performance goals.

To help, the designer needs to understand the best practices for writing good software for execution on the FPGA device. This project-based learning material encompasses projects ranging from simple to complex, incorporating applications in computer vision, digital signal processing, and accelerator design for neural networks.

The HLS kernel programming methodology will cover how you can first identify some macro-level architectural optimizations to structure your program and then focus on some fine-grained micro-level architectural optimizations to boost your performance goals.

## Objectives

| Project                                                                                                                  | Difficulty | Implementation       | Key Concept                                               | Interface           | Board         |
| ------------------------------------------------------------------------------------------------------------------------ | ---------- | -------------------- | --------------------------------------------------------- | ------------------- | ------------- |
| [FIR](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/fir/readme.md)                        | Easy       | Hand-written         | Transferring Sequential Loops to Parallel Loops           | Memory              | PYNQ-Z2/KV260 |
| [Sobel](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/sobel/readme.md)                    | Easy       | Vitis Vision Library | Flexible Adoption of Vitis Vision Library Level 1 Kernels | Memory/<br />Stream | PYNQ-Z2/KV260 |
| [Convolution Filter](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/conv_filter/readme.md) | Easy       | Hand-written         | Best Practices for Data-driven Task-level Parallelism     | Stream              | PYNQ-Z2/KV260 |
| [Matmult](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/blob/main/source/matmult/readme.md)                | Easy       | Hand-written         | Mapping the 2D Array to Customizable Memory               | Memory              | PYNQ-Z2/KV260 |

## Lab Structure

All the labs in this PBL tutorial is divided into three parts. The first part shows the whole process of designing an application and verifying it using Python. The second part focus on the kernel programming using the Vitis HLS tool to achieve the highest performance on the programmable logic. The following table  illustrate the process of the PBL experiment, starting from Part 1 where applications are showcased in a Jupyter notebook, progressing to Part 2 where kernel code optimized to achieve high performance using Vitis HLS tool, and finally advancing to Part 3 where the overlay is loaded onto the board and on-board test results are exported and imported back into the Jupyter notebook for performance verification.

| PART |          TOPIC          | SPECIFICATION                                                         | Environment          |
| ---- | :----------------------: | :-------------------------------------------------------------------- | -------------------- |
| 1    | Software Implementation | Demonstrate the software implementation of the application            | Jupyter Notebook     |
|      |                          | Use the powerful python extensible library                           |                      |
| 2    |  HLS Kernel Programming  | Detailed explanation of HLS kernel programming                        | AMD Vitis HLS 2023.2 |
|      |                          | Analyze and optimize hardware acceleration performance                |                      |
| 3    | System-level Integration | Create the overlay by Integrating the IP with Zynq processing system | AMD Vivado 2023.2    |
|      |                          | Load the overlay and run the application on the PYNQ framework        | Jupyter Notebook     |
|      |                          | Visualize the results and analyze the performance                     |                      |

## Steps

The installation process for the experimental environment requires installing AMD Vivado and Vitis HLS tools in the Linux environment, as well as connecting to the PYNQ board to run the corresponding experiments in Jupyter Notebook. The following will use Fir Lab as an example to demonstrate the experimental steps and procedures.

### Part 1: Software Implementation

1. Getting Started with the PYNQ Framework
   You need a PYNQ-supported AMD platform to begin. For the PYNQ-Z2, you need to download an SD card image to boot the board, and for KV260, you can install PYNQ onto your host Operating System. For any installation-related questions, please visit the [PYNQ support forum](https://discuss.pynq.io/) for assistance.

   * [PYNQ-Z2 Setup Guide](https://pynq.readthedocs.io/en/latest/getting_started/pynq_z2_setup.html)
   * [Kria-PYNQ](http://github.com/Xilinx/Kria-PYNQ)
2. Building the Software Application Using Python Libraries in Jupyter Notebook

   * Open and run the part1 notebook located at the following path:

   ```
   $LAB_WORK_DIR/fir/notebook/fir_part1.ipynb
   ```

### Part 2: HLS Kernel Programming

1. Setting up the Vitis HLS and Vivado Lab Environment on a Linux Machine

   ```bash
   git clone https://github.xilinx.com/Xilinx/xup_high-level-synthesis-design-flow.git
   export LAB_WORK_DIR=`<Downloaded Github repository>`/source
   source <Vitis_install_path>/Vitis/2023.2/settings64.sh
   ```
2. Designing the Acceleration Kernel Using the Vitis HLS Tool

   * Open and review the kernel optimization guide in the part2 notebook located at the following path:

   ```bash
   $LAB_WORK_DIR/fir/notebook/fir_part2.ipynb
   ```

   * Perform simulation, synthesis, and IP export in Vitis HLS

   ```bash
   cd $LAB_WORK_DIR/fir/prj/unroll_pipeline/kernel
   vitis_hls -f run_hls.tcl
   ```

### Part 3: System-level Integration

1. Creating the Overlay by Integrating the HLS Exported IP with Zynq Processing System and Generating the Bitstream

   ```bash
   cd $LAB_WORK_DIR/fir/prj/unroll_pipeline/overlay
   vivado -mode batch -source run_vivado.tcl
   ```
2. Loading the Overlay onto the Board
   An overlay typically includes:

   * A bitstream to configure the FPGA fabric
   * A Vivado design hardware handoff (HWH) file to determine the available IP
   * Python API that exposes the IPs as attributes
3. Building and Running the Hardware-accelerated Application in Jupyter Notebook

   * Open and review the part3 notebook located at the following path:

   ```bash
   $LAB_WORK_DIR/fir/notebook/fir_part3.ipynb
   ```

## Report an Issue

[Follow the instructions to report an issue](docs/report_issues.md)

## Contact Details

You can contact us by email [aup@amd.com](mailto:aup@amd.com)

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
