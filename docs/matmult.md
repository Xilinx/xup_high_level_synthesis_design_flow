# Matrix Multiplication

### Overview

Matrix multiplication is one of the most fundamental operations in scientific computing. It represents the composition of linear mappings, symbolizing spatial transformations and rotations. This operation finds extensive applications in various fields, such as encryption and decryption in cryptography, simulation of input-output models in mathematical modeling, and serving as an essential computational tool for advanced algorithms. Therefore, accelerating the computation of matrix multiplication is a crucial problem.

In the FIR lab, we focused on explaining the design philosophy of hardware optimization, providing a preliminary understanding of the emphasis in hardware design. In this chapter, we take it a step further, demonstrating how to design an efficient matrix multiplication accelerator by improving computational structures, optimizing data access, and enhancing parallelism. 

* Matrix blocking enables better utilization of on-chip memory resources on FPGAs by partitioning large matrices into smaller blocks. Blocked algorithms on FPGAs can be pipelined and parallelized to exploit fine-grained parallelism inherent in FPGA architectures. This results in improved throughput and reduced latency for matrix operations

The goal is to enhance the computation speed for matrices of size 128*128 or even larger. We will compare the speed with the matrix multiplication operation in the Python Numpy library, visibly boosting the speed from 0.0571 seconds in software to 0.0021 seconds (block matrix architecture) , achieving nearly 20 times faster, respectively.

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
    <td rowspan="2"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/matmult/notebook/matmul_part1.ipynb">Software Implementation</a></td>
    <td>Run a matrix multiplication in Numpy</td>
    <td rowspan="2">Jupyter Notebook</td>
  </tr>
  <tr>
    <td>Test the computation speed on Prosessing System</td>
  </tr>
  <tr>
    <td rowspan="4">2</td>
    <td rowspan="4"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/matmult/notebook/matmul_part2.ipynb">HLS Kernel Programming</a></td>
    <td>Optimize Data Access with Array Partitioning</td>
    <td rowspan="4">AMD Vitis HLS 2023.2</td>
  </tr>
  <tr>
    <td>Optimize On-Chip Memory Utilization and Latency with Matrix Blocking</td>
  </tr>
  <tr>
    <td>Optimize Area Efficiency with Arbitrary Precision</td>
  </tr>
  <tr>
    <td>Optimize Latency with Loop Unrolling and Pipelining</td>
  </tr>
  <tr>
    <td rowspan="3">3</td>
    <td rowspan="3"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/matmult/notebook/matmul_part3.ipynb">System-level Integration</a></td>
    <td>Create the overlay by Integrating the IP with Zynq processing system</td>
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

---
<p align="center">Copyright© 2024 Advanced Micro Devices</p>
