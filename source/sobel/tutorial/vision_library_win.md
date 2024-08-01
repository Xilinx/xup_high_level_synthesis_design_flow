# Tutorial: Create and Run a Vitis Vision Library Example on Windows

This blog will run through creating an HLS component that utilizes the Vitis Vision Library. This uses the Vitis Unified IDE. Most steps are the same if you are using Vitis Classic.

**Note: **Our tools have extremely limited testing on Windows, and therefore are limited to specific documentation and support. It is recommended to use Linux if the option is available.

This was tested on:

OS: Windows 10/11 (22H2)
Version: Vitis 2023.2

## Environment Setup

### 1. OpenCV 4.4.0 Installation

 Follow the instruction to build the  [Install/Setup OpenCV on Windows 10](https://support.xilinx.com/s/article/000035890)

### 2. Set up the environment variable to reference the OpenCV installation

1. OpenCV inclulde directory : `{Path-to-OpenCV}/OpenCV/build_win64/install/include`
2. OpenCV library directory : `{Path to OpenCV}/OpenCV/build_win64/install/x64/mingw/lib`
3. Vitis Vision Directory : `{Path to Vitis Library}/Vitis_Libraries/Vitis_Libraries-master/vision/`

## Running a Vitis Vision Library Example with Vitis HLS

There are two methods to create and execute the Sobel kernel project: the TCL flow and the GUI flow. Please choose the one you prefer.

### 1. Using Tcl Flow for Execution

This Tutorial describes the process to create a HLS Tcl script with runs the sobel filter example in the L1 Vision directory in Windows.

To utilize the examples designs, or reference the OpenCV libraries in a user testbench, the following steps must be taken:

1. Install the OpenCV tools version 4.4.0
2. Set up the environment variable to reference the OpenCV installation

```
   1. OpenCV inclulde directory : {Path to OpenCV}/OpenCV/build_win64/install/include
   2. OpenCV library directory : {Path to OpenCV}/OpenCV/build_win64/install/x64/mingw/lib
   3. Vitis Vision Directory : {Path to Vitis_Lib}/Vitis_Libraries/Vitis_Libraries-master/vision/
```

To run the Vitis HLS script, perform the following actions:

1) Place the  [run_tcl_win.tcl](https://github.com/Xilinx/xup_high_level_synthesis_design_flow/tree/main/source/sobel/prj/vision_lib/kernel/run_tcl_win.tcl) script in the `<Path to Vitis library>/vision/L1/example/sobelfilter` directory.
2) Open the Vitis HLS command line shell and navigate to the `<Path to Vitis library>/vision/L1/example/sobelfilter` directory
3) Run the following command:

```
vitis_hls -f run_tcl_win.tcl

```

---

### 1. Using GUI Flow for Execution

1. If you have not already done so, download the Vitis Libraries from the link below and extract them to any location.
   1. [https://github.com/Xilinx/Vitis_Libraries](https://github.com/Xilinx/Vitis_Libraries)
2. Use the following steps to build the "remap" example design from the Vitis Vision Library in the GUI.
   1. Launch the Vitis Unified IDE
   2. Select "Open Workspace" and Browse to *Vitis_Libraries/vision/L1/examples/remap*
      1. Note that the workspace is called "remap" in the upper left hand corner:
         ![image.png](https://support.xilinx.com/servlet/rtaImage?eid=ka04U000000soC9&feoid=00N2E00000Ji4Tx&refid=0EM4U0000058gmi)
   3. Select "Create Component" under HLS Development
   4. Specify the component name. We will use "hls_component"
   5. Click Browse and go to *Vitis_Libraries/vision/L1/examples/remap*
   6. Click Next
   7. Select "Empty File" and keep the default configuration file name
   8. Click Next
   9. Under the Design Files section, select the *xf_remap_accel.cpp* file which can be found in the remap folder
   10. Click Browse underneath to find the Top Level function
   11. Under the Test Bench section, browse to remap to add *xf_remap_tb.cpp*
       ![image.png](https://support.xilinx.com/servlet/rtaImage?eid=ka04U000000soC9&feoid=00N2E00000Ji4Tx&refid=0EM4U0000058gnM)
   12. Click Next
   13. Select as the part - xc7z020-clg484-1
   14. Click Next.
   15. Make sure your flow_target is set to "Vivado IP Flow Target" and the package.output.format is set to "Vivado IP and zip archive"
   16. Click Next to view the Summary and then click Finish.
   17. You've now created an HLS Component. Running Simulation or Synthesis will fail because we need to add the necessary includes paths for the design to use.
3. Edit the settings of the design to utilize the compiled OpenCV libraries the project needs.
   1. Select Settings > hls_config.cfg from the left-hand side
   2. Select " **C Synthesis sources** "
      1. In the CFLAGS and CSIMFLAGS boxes, enter the following:
         ```
         -I <path to vitis libraries>/vision/L1/examples/remap/config -I<path to vitis libraries>/vision/L1/include -I ./ -D__SDSVHLS__ -std=c++14
         ```
      2. ![image.png](https://support.xilinx.com/servlet/rtaImage?eid=ka04U000000soC9&feoid=00N2E00000Ji4Tx&refid=0EM4U0000058hb7)
   3. Select " **Testbench sources** "
      1. In the CFLAGS box, enter the following:

         ```
         -I <path to vitis libraries>/vision/L1/examples/remap/config -I<path to opencv install>/include -I<path to vitis libraries>/vision/L1/include -I ./ -D__SDSVHLS__ -std=c++14
         ```

         ![image.png](https://support.xilinx.com/servlet/rtaImage?eid=ka04U000000soC9&feoid=00N2E00000Ji4Tx&refid=0EM4U0000058hNt)
      2. Scroll down to " **argv** " and add:

         ```
         <path to vitis libraries>/vision/data/128x128.png 
         ```
      3. Scroll down to " **ldflags** " and add:

         ```
         -L <path to opencv install>/x64/mingw/lib -lopencv_imgcodecs440 -lopencv_imgproc440 -lopencv_calib3d440 -lopencv_core440 -lopencv_highgui440 -lopencv_flann440 -lopencv_features2d440
         ```

         1. **Note:** The version number is appended to each library name. If you used a different version of OpenCV outside of 4.4.0, you will have to append the corresponding number to the end of the library names.
   4. Select the "**C/RTL Cosimulation"**
      1. In **"argv"** add:
         ```
         <path to vitis libraries>/vision/data/128x128.png 
         ```
      2. Scroll down to **"ldflags"** and add:
         ```
         -L <path to opencv install>/x64/mingw/lib -lopencv_imgcodecs440 -lopencv_imgproc440 -lopencv_calib3d440 -lopencv_core440 -lopencv_highgui440 -lopencv_flann440 -lopencv_features2d440
         ```
   5. Run C-Simulation
   6. Run C-synthesis.
   7. Run C/RTL Co-Simulation

You should now have a working HLS design running on Windows 10.

You have now completed the steps for creating an HLS design that uses the Vitis Vision Library on Windows 10.

![image.png](https://support.xilinx.com/servlet/rtaImage?eid=ka04U000000soC9&feoid=00N2E00000Ji4Tx&refid=0EM4U0000058i2d)

**Troubleshooting:**  Missing header file errors - check the CFLAG/CSIMFLAG includes paths in settings

* Missing library errors - check the ldflag paths to the Library linkers
* Use forward slashes for all paths set in the settings (libraries, input argument)
* Double check that you set the correct environment variable for the system environment variable PATH from the OpenCV setup blog
