# Best Practices for Data-Driven Convolution Filter HLS Kernel

Convolution filter plays a very important role in FPGA application nowadays. It's the cornerstone of many popular applications. In the field of image processing, the convolution filter kernel with different parameters gliding through the image can complete different image processing tasks, such as sharpening, blurring or edge detection.

In the field of neural network accelerator, no matter what network architecture or network layer is selected, convolution calculation is also the most important computing unit, but the filtering kernel becomes trained weight data. As a result, designing the convolution filtering kernel is like building the most basic and important block of a Lego toy.

Using abstract model as the basis, two types of task-level parallelism (TLP) models can be used to structure and design your application. TLP can be data-driven or control-driven, or can mix control-driven and data-driven tasks in a single design. The main differences between these two models are:

* If your application is purely data-driven, does not require any interaction with external memory and the functions can execute in parallel with no data dependencies, then the data-driven TLP model is the best fit. You can design a purely data-driven model that is always running, requires no control, and reacts only to data. For additional details refer to [Data-driven Task-level Parallelism](https://docs.amd.com/r/4lwvWeCi9jb~DWzdfWuVQQ/whHLtgBvkVhufkkguaTckA).
* If your application requires some interaction with external memory, and there are data dependencies between the tasks that execute in parallel, then the control-driven TLP model is the best fit. **Vitis HLS** infers the parallelism between tasks and creates the right channels (as defined by you) such that these functions can be overlapped during execution. The control-driven TLP model is also known as the dataflow optimization in **Vitis HLS** as described in [Control-driven Task-level Parallelism](https://docs.amd.com/r/4lwvWeCi9jb~DWzdfWuVQQ/vBrR0VK9YLAzu~BPeFSj3A).

In this section, we will understand the best practices for writing data-driven application on the FPGA device by taking convolution filter as an example.

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
    <td rowspan="2"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/conv_filter/notebook/baseline.md">Software Implementation</a></td>
    <td>Teaching Case: Simple Convolution Filter Without Considering Boundary Conditions</td>
    <td rowspan="2">Jupyter Notebook</td>
  </tr>
  <tr>
    <td>Industrial Case: Extensible Universal Convolution Filter Kernel</td>
  </tr>
  <tr>
    <td rowspan="7">2</td>
    <td rowspan="7">HLS Kernel Programming</td>
    <td>Determine the Design Specifications</td>
    <td rowspan="7">AMD Vitis HLS 2023.2</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/conv_filter/notebook/kernel_tlp.md">TLP: Partition the Code into a Load-Compute-Store Pattern</a></td>
  </tr>
  <tr>
    <td>TLP: Partition the Compute Blocks into Smaller Functions</td>
  </tr>
  <tr>
    <td>TLP: Connect the Load, Compute, and Store Functions</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/conv_filter/notebook/kernel_dlp.md">DLP: Scaling/Unroll - Determine the Unroll factor</a></td>
  </tr>
  <tr>
    <td>DLP: Enable Pipelining with II = 1</td>
  </tr>
  <tr>
    <td>DLP: Maximize Memory efficiency</td>
  </tr>
  <tr>
    <td rowspan="3">3</td>
    <td rowspan="3"><a href="https://github.com/Xilinx/xup_High-Level-Synthesis-Design-Flow/blob/main/source/conv_filter/notebook/filter2d_all.md">System-level Integration</a></td>
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

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
