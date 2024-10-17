# Vitis Design Flow Lab

## Introduction

This lab provides a basic introduction to high-level synthesis using the Vitis flow. You will use Vitis to create a project. You will simulate, synthesize, and implement the provided design.

## Objectives

After completing this lab, you will be able to:

* Create a new project using Vitis
* Simulate a C design by using a self-checking test bench
* Synthesize the design
* Perform design analysis using the Analysis Perspective view
* Perform co-simulation on a generated RTL design by using a provided C test bench
* Implement a design

## Steps

### Create a New Project

#### Create a new project in Vitis HLS targeting PYNQ-Z2 board
1. Launch Vitis: Select **Create Component... > Create Empty HLS Component**
    <p align="center">
    <img src ="./images/lab1_vitis/Figure1.jpg">
    </p>
    <p align = "center">
    <i>Getting Started view of Vitis</i>
    </p>
2. Click the *Browse…* button of the Location field and browse to **{labs}\\lab1** on a Windows machine or **{labs}/lab1** on a Linux machine creating sub-folders as necessary, and then click **OK**.
   
   Note: From this point onward reference will be made to Linux name.

3. For Project Name, type **matrixmul**.
    <p align="center">
    <img src ="./images/lab1_vitis/Figure2.jpg">
    </p>
    <p align = "center">
    <i>New Vitis HLS Project wizard</i>
    </p>

4. Click **Next**.
5. In the *Configuration File* window, select the *Empty File* option and click **Next**.
6. In the *Source Files* window, type **matrixmul** as the *Top Function* name (the provided source file contains the function, called matrixmul, to be synthesized).
7. Click the *Add Files…* button (which in the line of DESIGN FILES), select **matrixmul.cpp** file from the **{labs}/lab1** folder, and then click **Open**.
8. Then we add the test file, in the next block click *Add Files…* button (which in the line of TEST BENCH FILES), select **matrixmul_test.cpp** file from the **/home/xup/hls/labs/lab1** folder and click **Open**.
9.  Select the **matrixmul_test.cpp** in the files list window and click the *Edit CFLAG…* button, type</P> **-DHW_COSIM** (there has  a "-" in here, don't forget it), and click **OK**. (This defines a compiler flag that will be used later.)
10. Click **Next**.
    <p align="center">
    <img src ="./images/lab1_vitis/Figure3.jpg">
    </p>
    <p align = "center">
    <i>Source Files setting</i>
    </p>

11. In the *Hardware* page, select **Part** field, enter  **xc7z020clg400-1** in the *Search* field and click **next**.</p>
<sub>here you should select the device that you are using, In my class Zedboard using xc7z020clg484-1</sub>
    <p align="center">
    <img src ="./images/lab1_vitis/Figure4.jpg">
    </p>
    <p align = "center">
    <i>Using Search to selcet the chip</i>
    </p>

12. In the *Settings* page, tpye 10ns in the clock.Click **next**. 
13. Click **Finish**.
    You will see the created project in the *VITIS COMPOMENTS* view. Expand various sub-folders to see the entries under each sub-folder.
    <p align="center">
    <img src ="./images/lab1_vitis/Figure5.jpg">
    </p>
    <p align = "center">
    <i>Explorer Window</i>
    </p>
14. Double-click on the **matrixmul.cpp** under the source folder to open its content in the information pane.
    <p align="center">
    <img src ="./images/lab1_vitis/Figure6.jpg">
    </p>
    <p align = "center">
    <i>The Design under consideration</i>
    </p>
    It can be seen that the design is a matrix multiplication implementation, consisting of three nested loops. The Product loop is the inner most loop performing the actual Matrix elements product and sum. The Col loop is the outer-loop which feeds the next column element data with the passed row element data to the Product loop. Finally, Row is the outer-most loop. The res[i][j]=0 (line 41) resets the result every time a new row element is passed and new column element is used.

### Run C Simulation

1. Select **FLOW > C Simulation > Run**.</p>
   <sub>it may be have a windows ask if Enable Code Analyzer, click **Yes, enable Code Analyzer**</sub></p>
    The files will be compiled and you will see the output in the Console window.
    <p align="center">
    <img src ="./images/lab1_vitis/Figure7.jpg">
    </p>
    <p align = "center">
    <i>Program output</i>
    </p>
2. Double-click on **matrixmul_test.cpp** under **testbench** folder in the Explorer to see the content.

    You should see two input matrices initialized with some values and then the code that executes the algorithm. If HW_COSIM is defined (as was done during the project set-up) then the **matrixmul** function is called and compares the output of the computed result with the one returned from the called function, and prints **Test passed** if the results match.
    If **HW_COSIM** had not been defined then it will simply output the computed result and not call the **matrixmul** function.

