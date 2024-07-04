# GUI Flow Tutorial: Implementing FIR Filter to PYNQ Framework

## Objective

Upon completion of this lab, you should have learned:

- How to build a project using Vitis HLS
- Simulation, synthesis and IP export in Vitis HLS
- Integrating HLS exported IP using Vivado
- Build a simple application using PYNQ

In short, you will learn the basic flow of accelerated core design and deployment to PYNQ using HLS. Due to space limitation, this experiment only introduces the basic tool operation process.

## Environmental equirements

- PYNQ-Z2 remote lab service or physical board
- Vitis HLS
- Vivado

## Experimental steps

### 1. Design FIR IP in Vitis_HLS

#### 1.1 Create a new project

1. Open the **Vitis HLS** software and click on **Create Project** to create a new project
2. Enter the project name **fir_hls_prj** in **Project name**, click **Browse** to select an appropriate directory location, and click **Next**.

   ![1.1.2.PNG](./img/1.1.2.PNG)
3. Click **Add Files... **, add **fir.h** and **fir.cpp** from **src** directory to the project
4. Click on the **Browse** button in the **Top Function** column, select **fir_wrap**, which is the top-level function when we do the synthesis, and click on **Next**

   ![1.1.2.PNG](./img/1.1.2.PNG)
5. Click **Add Files... **, add **fir_tb.cpp** in **src** directory to the project, click **Next**

   ![1.1.3.PNG](./img/1.1.3.PNG)
6. Next, go to the **Solution Configuration** interface, keep the other options unchanged, click **.... **on the far right of the **Part Selection** column Click on the button with the word ** and enter **xc7z020clg484-1** in the search box of the **Search** column, which is the model number of the device used in the **PYNQ-Z2** board

   ![1.1.4.PNG](./img/1.1.4.PNG)
7. Click **Finish** to complete the creation of the project

#### 1.2 C-Simulation

1. After completing the project creation, **Vitis HLS** jumps to a new interface, which consists of four main parts:

   1. The **Explorer** at the top left, which contains the various files in the project
   2. The **Flow Navigator** at the bottom left, which shows the various parts of the HLS design
   3. The **editor area** at the top right, where developers modify the code of the design
   4. The **Console** at the bottom right contains the console, error messages, version control, etc.

      <img src="./img/1.2.1.PNG" title="" alt="1.2.1.PNG" width="648">
2. Next, we perform C simulation on the design. Click **Run C Simulation** in the **Flow Navigator** at the bottom left, and in the **C Simulation Dialog** window that pops up, make no changes and click **OK** for C simulation

   <img title="" src="./img/1.2.2.png" alt="1.2.2.png" width="514">
3. Wait a few seconds, after the simulation is complete **Vitis HLS** automatically opens a log file and you can see that the design has passed the C simulation

   ![1.2.3.png](./img/1.2.3.png)

#### 1.3 C-Synthesis

1. Next, we perform C synthesis on the design. Click on **Run C Synthesis** in the **Flow Navigator** at the bottom left, and in the **C Synthesis - Active Solution** window that pops up, leave the options unchanged and click on **OK** to start synthesis.

   ![1.3.1.png](./img/1.3.1.png)
2. Wait a few seconds and **Vitis HLS** will print the information of its combined steps in **Console**
3. After the synthesis is completed, the **Systhesis Summary(solution1)** window will pop up, where we can see the clock frequency information, the number of clock cycles and resource consumption given by **Vitis HLS** (in different versions of Vitis HLS, the synthesis results may vary and the resource usage estimates are more conservative, the final resource usage should be based on the implementation results)

   ![1.3.2.png](./img/1.3.2.png)

#### 1.4 C/RTL Co-simulation

1. In the following, we perform a C-RTL co-simulation of the design. Click **RUN C/RTL COSIMULATION** in the **Flow Navigator** at the bottom left, keep the options unchanged in the **Co-simulation Dialog** window that pops up, and click **OK** to start the synthesis

   ![1.4.1.png](./img/1.4.1.png)
2. Waiting for about 1 minute, the synthesis time of C/RTL co-simulation is usually longer, after the end of the simulation will pop up **Co-simulation Report(solution1)** window, containing information such as whether to pass the simulation, performance estimation, etc.

   ![1.4.2.png](./img/1.4.2.png)

#### 1.5 Export RTL

1. Next, we perform an RTL export of the design. Click **Export RTL** in the **Flow Navigator** at the bottom left, keep the options unchanged in the pop-up window of **Export RTL**, and click **OK** to start the RTL export

   ![1.5.1.png](./img/1.5.1.png)
2. Wait about half a minute, **Console** prints **Finished Export RTL/Implementation.** indicating that the RTL design has been exported, you can find the exported file in **\fir_hls_prj\solution1\impl\export.zip**
3. For subsequent use, please extract the **\fir_hls_prj\solution1\impl\export.zip** file to its directory to get a **\fir_hls_prj\solution1\impl\export** folder
4. At this point, we have completed the design and export of the FIR acceleration core

### 2. IP Integration in Vivado

#### 2.1 Create a new Vivado project

1. Open the **Vivado** software, click **Create Project**, create a new project, and click **Next**.
2. Enter the project name **fir_vivado_prj** in **Project name** and click **... on the right side. ** button to select a suitable directory location and click **Next**.![2.1.1.PNG](./img/2.1.1.PNG)
3. Enter the **Project Type** interface, check the box **Do not specify sources at this time**, then click **Next**.![2.1.2.PNG](./img/2.1.2.PNG)
4. Enter the **Default Part** interface, search for **xc7z020clg484-1** in the **Search** field, select it, and click **Next**.

   ![2.1.3.PNG](./img/2.1.3.PNG)
5. Click **Finish** to complete the project creation

#### 2.2 Import IP

1. We need to first import the IP exported from **Vitis HLS** into **Vivado** by clicking on the **Settings** option in the left window **Flow Navigator** to bring up the **Settings** window
2. Expand the **IP** column in the **Project Settings** on the left, select the **Repository** item, click the **+** button in the right panel, select the IP you just extracted in the pop-up window, i.e. **\fir_hls_prj\solution1\impl\export**, and then click **Select**.

   ![2.2.1.png](./img/2.2.1.png)
3. You can see that the corresponding IP has been successfully added to the project, click **OK** in both windows in turn to close these windows

   ![2.2.2.PNG](./img/2.2.2.PNG)

#### 2.3 Create a Block Design

1. Here we create a **Block Design** to build the complete system using the IP integration feature of **Vivado**. Click **IP INTEGRATOR > Create Block Design** in the **Flow Navigator** on the left, leave the options unchanged in the **Create Block Design** pop-up window, use the default **design_1** for the design name, and click **OK** to create the **Block Design**

   ![2.3.1.png](./img/2.3.1.png)
2. Click the **+** button at the top of the **Diagram** window that appears, a search box will pop up, type **zynq** in the input field and double click on the **ZYNQ7 Processing System** that appears in the backup options to add the IP to the design

   ![2.3.2.png](./img/2.3.2.png)
3. At the top of the window will appear a blue underline prompt **Run Block Automation**, click on the area to pop up the corresponding window, we keep the default settings unchanged, directly click **OK**

   ![2.3.3.png](./img/2.3.3.png)
4. Next, we need to configure the above **Processing System** by adding an HP port

   - Double-click the **processing_system7_0** module in the **Diagram** to bring up the **Re-customize IP** window
   - Select the **PS-PL Configuration** page in the **Page Navigator** on the left, expand the **HP Slave AXI Interface** in the options on the right, and check the **S AXI HP0 interface** option
   - Click **OK**.

   ![2.3.4.PNG](./img/2.3.4.PNG)
5. Click on the **+** button at the top of the Diagam window and search for **fir**, you can see that the IP we just imported is already available, double click on **Fir_wrap** to add it to the design

   <img title="" src="./img/2.3.6.png" alt="2.3.6.png" width="208">
6. Here we perform the automatic connection of the design. Click on the blue underlined prompt **Run Connection Automation** at the top of the window to bring up the corresponding window, check the **All Automation** option on the left, and then click **OK**

   ![2.3.5.png](./img/2.3.5.png)
7. The system will automatically connect according to the corresponding interface, we can get the following design

   ![2.3.7.png](./img/2.3.7.png)
8. Click on the tick icon **Validate Design** in the toolbar on the top side of **Diagram** to validate the design

   ![2.3.10.png](./img/2.3.10.png)
9. Right click on the **Source > Design Sources > design_1** option on the left and select **Generate Output Products**.

   <img title="" src="./img/2.3.8.png" alt="2.3.8.png" width="340">
10. In the pop-up window leave the configurations unchanged and click **Generate**, this process will take about 1 minute

    <img title="" src="./img/2.3.9.PNG" alt="2.4.2.PNG" width="232">
11. Right click on the **Source > Design Sources > design_1** option on the left side, select **Create HDL Wrapper**, leave the options unchanged in the pop-up window and click **OK**. When finished, you can see a layer of **design_1_wrapper.v** nested on top of **design_1.bd**.

    <img src="./img/2.3.11.png" title="" alt="2.3.11.png" width="383">

#### 2.4 Synthesis and generation of bitstreams

1. Select **Run Synthesis** in the **Flow Navigator** on the left, leave the selection unchanged in the pop-up window and select **OK**

   ![2.4.1.png](./img/2.4.1.png)
2. When the synthesis is complete, the **Synthesis Completed** window will pop up. Keep the default **Run Implementation** option in the **Next** column and click **OK**. If a new pop-up window appears, again keep the default option and click **OK**.

   <img title="" src="./img/2.4.2.png" alt="2.4.2.png" width="432">
3. When the **Implementation** is finished, the **Implementation Completed** window will pop up, select the **Generate Bitstream** option in the **Next** field and click on **OK**. If a new pop-up window appears, keep the default option and click **OK**.

   <img title="" src="./img/2.4.4.PNG" alt="2.4.4.PNG" width="248">
4. After the bitstream is generated, the **Bitstream Genreation Completed** window will pop up, we can directly click on **Cancel**.

   <img title="" src="./img/2.4.3.PNG" alt="2.4.3.PNG" width="253">
5. At this point, we have completed the design and export of the hardware part

### 3. Build PYNQ design

#### 3.1 Extract bit and hwh files

1. Visit the **\fir_vivado_prj\fir_vivado_prj.runs\impl_1** directory in the file manager, the **design_1_wrapper.bit** file in that directory is the generated bitstream file, copy it to your own folder to save it and rename it to **fir.bit**

   <img src="./img/3.2.2.png" title="" alt="3.2.2.png" width="413">
2. In the file manager, access the **\fir_vivado_prj\fir_vivado_prj.gen\sources_1\bd\design_1\hw_handoff** directory, where **design_1.hwh** is the **hardware handoff** file we need Copy it to your own folder and rename it to **fir.hwh**.

   <img src="./img/3.2.3.png" title="" alt="3.2.3.png" width="434">

#### 3.2 Visit Jupyter

1. Please complete the PYNQ Remote Lab account registration and **Jupyter** access first
2. Login to the **Jupyter** interface, click the **upload** button at the top right of the interface, and upload the following files to the development board

   - **/fir.ipynb,** **chaffinch.jpg,** **curlew.jpg,** **birds.wav** in the **/jupyter** directory
   - The **fir.bit** and **fir.hwh** files obtained in the previous step

     - If you failed to export in the previous operation, you can also use the **fir.bit** and **fir.hwh** files in the **/overlay** directory to upload first to complete the rest of the experiment

   <img title="" src="./img/3.2.1.png" alt="3.2.1.png" width="741" data-align="inline">

#### 3.3 Deploy and run Overlay

1. Go to the **fir.ipynb** page in **Jupyter** and **Kernel** is automatically loaded with the word **Python3**
2. Click the **Run** button on the top side of the window, **Jupyter Notebook** will execute the current **Cell** and automatically switch to the next **Cell** at the same time

   <img src="./img/3.3.1.png" title="" alt="3.3.1.png" width="435">
3. Just click **Run** in order to finish, the meaning of each code block has been marked in **Jupyter Notebook**, please read the information in **Jupyter Notebook** to continue to complete the experiment.

---

<p align="center">Copyright© 2024 Advanced Micro Devices</p>
