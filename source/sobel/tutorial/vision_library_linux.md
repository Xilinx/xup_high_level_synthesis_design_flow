# Tutorial: Creating a Vitis Vision Library HLS Project Via Tcl Command

This Tutorial will guide you through the installation of OpenCV, the Vitis Vision Library, and the corresponding compilation environment in a Linux setting. It will also provide you with a streamlined process using Tcl scripts to compile a standalone Vitis HLS project that calls the Sobel operator from the Vitis Vision Library. During this process, it is crucial to strictly adhere to details regarding the versions of the compilation tools, the setting of environment variables, and the dependencies on library paths.

## Step0: Prerequisites

1. **OpenCV** 4.4.0
2. **Vitis HLS** 2023.2
3. **Vitis Vision Library** 2023.2
4. **CMake** 3.5+ (3.29.0-rc1 was tested)
5. **gcc 6.2.0** bundled with **Vitis HLS**, for compiling OpenCV

---

## Step1: Installing CMake

Before installing OpenCV 4.4.0, ensure that your CMake version is greater than 3.5 and that it is added to your environment variables. You can check the CMake version included in your Linux by running `cmake --version`.

Here we will install the precompiled version of CMake:

1. Download the **CMake** 3.5+ Linux x86_64 version from the Cmake website.
2. Extract CMake to your desired directory:
   ```bash
   tar -zxvf <your cmake file name>.tar.gz
   ```
3. Add CMake to your environment variables in `.bashrc`:
   ```bash
   export PATH=<your extract dir>/<your cmake file name>/bin:$PATH
   ```
4. Update the environment:
   ```bash
   source .bashrc
   ```

---

## Step2: Compiling and Installing OpenCV

### Compilation and Installation Steps

1. Create a directory named "source" and clone OpenCV 4.4.0 into it:

   ```bash
   git clone https://github.com/opencv/opencv --branch 4.4.0 source
   ```
2. Create a directory named "source_contrib" and clone OpenCV 4.4.0 contrib modules into it:

   ```bash
   git clone https://github.com/opencv/opencv_contrib --branch 4.4.0 source_contrib
   ```
3. cd to 'source', create a 'build' directory, and cd into it:

   ```bash
   cd source
   mkdir build
   cd build
   ```
4. Set the library path:

   ```bash
   export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/:$LIBRARY_PATH
   ```
5. Set up the Vitis HLS tools via the `settings64.sh` script in the installation directory(replace directory paths with the appropriate locations):

   ```bash
   source < path-to-Vitis-installation-directory >/settings64.sh
   ```
6. Run the following command (replace directory paths with the appropriate locations):

   ```bash
   cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=<any output install directory>/install -D WITH_V4L=ON -D OPENCV_EXTRA_MODULES_PATH=<path to opencv directory>/source_contrib/modules -DBUILD_TESTS=OFF -DBUILD_ZLIB=ON -DBUILD_JPEG=ON -DWITH_JPEG=ON -DWITH_PNG=ON -DBUILD_EXAMPLES=OFF -DINSTALL_C_EXAMPLES=OFF -DINSTALL_PYTHON_EXAMPLES=OFF -DWITH_OPENEXR=OFF -DBUILD_OPENEXR=OFF -D CMAKE_CXX_COMPILER=$XILINX_HLS/tps/lnx64/gcc-6.2.0/bin/g++ ..
   ```
7. Compile all:

   ```bash
   make all -j8
   ```
8. Install:

   ```bash
   make install
   ```
9. Set the following for your project/example design runs, or add them to `.bashrc`:

   ```bash
   export OPENCV_INCLUDE=<output path to installed opencv>/include/opencv4
   export OPENCV_LIB=<output path to installed opencv>/lib
   export LD_LIBRARY_PATH=<output path to installed opencv>/lib:$LD_LIBRARY_PATH
   ```

## Step3: Installing Vitis Vision Library

1. Create a directory and clone Vitis Vision Library into it:

   ```bash
   git clone https://github.com/Xilinx/Vitis_Libraries.git 
   ```
2. Set the environment variable to the Vitis Vision Library

   ```bash
   set XF_PROJ_ROOT "<Your Vision Vision Library Path>/vision" 
   ```

### Potential Issues and Solutions

On Ubuntu 20.04, using the default **gcc 9.4.0** can result in the following error:

```
/opencv_compiled/lib/libopencv_imgcodecs.so: undefined reference to `std::__cxx11::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >::basic_stringstream()@GLIBCXX_3.4.26'
```

Therefore, we need to use **gcc 6.2.0** provided by **Vitis HLS** for compiling OpenCV. This can be found in the directory like:  `/tools/Xilinx/Vitis_HLS/2023.2/tps/lnx64/gcc-6.2.0`.

### References

For more information, refer to [Compiling and Installing OpenCV libraries for use with Vision library](https://support.xilinx.com/s/article/Vitis-Libraries-Compiling-and-Installing-OpenCV?language=en_US).

---

## Step4: Creating a Standalone Vitis HLS Project - Example with Sobel Filter

### Project Setup Steps

1. In this section, we want to run the **L1 sobel filter example** design outside of the acceleration platform makefile. Follow the steps from [Using Vitis Vision Libraries with OpenCV in Vitis HLS](https://support.xilinx.com/s/article/75727?language=en_US), and update the C++ version from `-std=c++0x` (C++11) to `-std=c++14`.
2. Modify the Tcl script to update **XF_PROJ_ROOT**, **OPENCV_INCLUDE**, **OPENCV_LIB** to your corresponding directories:

   ```bash
   set XF_PROJ_ROOT "<Your Vision Vision Library Path>/vision" #Vitis Vision Libary include directory
   set OPENCV_INCLUDE "<Your OpenCV 4.4.0 Path>/include/opencv4" #OpenCV header file directory
   set OPENCV_LIB "<Your OpenCV 4.4.0 Path>/lib" #OpenCV compiled library directory
   ```
3. Modify the Tcl script to update **PROJ_DIR** **SOURCE_DIR** to your corresponding directories, in this tutorial, it is `<Your Vitis Vision Library Path>/L1/examples/sobelfilter`

   ```bash
   set PROJ_DIR "$XF_PROJ_ROOT/L1/examples/sobelfilter" # Project root directory
   set SOURCE_DIR "$PROJ_DIR/"
   set PROJ_NAME "hls_example" # Project name in Vitis HLS
   set PROJ_TOP "sobel_accel" # Top level function name
   set SOLUTION_NAME "sol1" # Solution name in Vitis HLS
   set SOLUTION_PART "xck26-sfvc784-2LV-c" # Solution part in Vitis HLS, you can modify it if you want to use other boards. For example, use "xc7z020-clg484-1" for PYNQ-Z2 or use "xck26-sfvc784-2LV-c" for KV260E
   set SOLUTION_CLKP 5 # Clock period setting in Vitis HLS
   ```
4. Modify the OpenCV C-Simulation / CoSimulation Library References

   ```bash
   set VISION_INC_FLAGS "-I$XF_PROJ_ROOT/L1/include -I$PROJ_DIR/config/ -std=c++14" # Vitis Vision Include path, and C++ 14 settings
   set OPENCV_INC_FLAGS "-I$OPENCV_INCLUDE" # OpenCV include directory references
   set OPENCV_LIB_FLAGS "-L $OPENCV_LIB" # OpenCV libary reference
   ```
5. Modify the OpenCV library reference, use the appropriate style for your operating system.

   - Windows OpenCV Include Style:

     - In Windows, the library references must include the version number. This example uses a OpenCV 3.4.11 installation.

     ```bash
     set OPENCV_LIB_REF   "-lopencv_imgcodecs3411 -lopencv_imgproc3411 -lopencv_core3411 -lopencv_highgui3411 -lopencv_flann3411 -lopencv_features2d3411"
     ```
   - Linux OpenCV Include Style:

     ```bash
     set OPENCV_LIB_REF   "-lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_features2d"
     ```
6. Create project.

   ```bash
   open_project -reset $PROJ_NAME
   ```
7. Add C++ source and Testbench files with Vision and OpenCV includes

   ```bash
   add_files "${PROJ_DIR}/xf_sobel_accel.cpp" -cflags "${VISION_INC_FLAGS} -I${PROJ_DIR}/build" -csimflags "${VISION_INC_FLAGS} -I${PROJ_DIR}/build" #add the accelerator code and include directories for C-synthesis and C-simulation
   add_files -tb "${PROJ_DIR}/xf_sobel_tb.cpp" -cflags "${OPENCV_INC_FLAGS} ${VISION_INC_FLAGS} -I${PROJ_DIR}/build" -csimflags "${OPENCV_INC_FLAGS} ${VISION_INC_FLAGS} -I${PROJ_DIR}/build" # add the accelerator code and include directories for C-synthesis and C-simulation
   ```
8. Create Project and Solution

   ```bash
   set_top $PROJ_TOP
   open_solution -reset $SOLUTION_NAME
   set_part $SOLUTION_PART
   create_clock -period $SOLUTION_CLKP
   ```
9. Run Vitis HLS Stages. Note that CSim and CoSim require datafiles to be included.

   ```bash
   csim_design -ldflags "-L ${OPENCV_LIB} ${OPENCV_LIB_REF}" -argv "${XF_PROJ_ROOT}/data/128x128.png" # run C-Simulation, link the libraries, specifies input image file for the simulation
   csynth_design # run c-synthesis
   cosim_design -ldflags "-L ${OPENCV_LIB} ${OPENCV_LIB_REF}" -argv "${XF_PROJ_ROOT}/data/128x128.png"  # run Co-Simulation, link the libraries, specifies input image file for the simulation
   export_design -flow syn -rtl verilog # export the synthesized design, RTL output will be in Verilog
   #  export_design -flow impl -rtl verilog
   exit # exit Vitis HLS
   ```

### Build the HLS Kernel Project

```
   cd $LAB_WORK_DIR/sobel/prj/vision_lib/kernel
   vitis_hls -f run_hls_linux.tcl
```

---

### The Overall Tcl File

```tcl
# ------------------------------------------------------------------------------
# Vitis Vision and OpenCV Library Path Information
# ------------------------------------------------------------------------------
set XF_PROJ_ROOT "<Your Vision Vision Library Path>/vision" #Vitis Vision Libary include directory
set OPENCV_INCLUDE "<Your OpenCV 4.4.0 Path>/include/opencv4" #OpenCV header file directory
set OPENCV_LIB "<Your OpenCV 4.4.0 Path>/lib" #OpenCV compiled library directory

# ------------------------------------------------------------------------------
# Vitis HLS Project Information
# ------------------------------------------------------------------------------
set PROJ_DIR "$XF_PROJ_ROOT/L1/examples/sobelfilter"
set SOURCE_DIR "$PROJ_DIR/"
set PROJ_NAME "hls_example"
set PROJ_TOP "sobel_accel"
set SOLUTION_NAME "sol1"
set SOLUTION_PART "xck26-sfvc784-2LV-c"
set SOLUTION_CLKP 5 

# ------------------------------------------------------------------------------
# OpenCV C Simulation / CoSimulation Library References
# ------------------------------------------------------------------------------
set VISION_INC_FLAGS "-I$XF_PROJ_ROOT/L1/include -I$PROJ_DIR/config -std=c++14"
set OPENCV_INC_FLAGS "-I$OPENCV_INCLUDE"
set OPENCV_LIB_FLAGS "-L $OPENCV_LIB"

# Windows OpenCV Include Style:
# set OPENCV_LIB_REF   "-lopencv_imgcodecs3411 -lopencv_imgproc3411 -lopencv_core3411 -lopencv_highgui3411 -lopencv_flann3411 -lopencv_features2d3411"

# Linux OpenCV Include Style:
set OPENCV_LIB_REF   "-lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_flann -lopencv_features2d"

# ------------------------------------------------------------------------------
# Create Project
# ------------------------------------------------------------------------------
open_project -reset $PROJ_NAME

# ------------------------------------------------------------------------------
# Add C++ source and Testbench files with Vision and OpenCV includes
# ------------------------------------------------------------------------------
add_files "${PROJ_DIR}/xf_sobel_accel.cpp" -cflags "${VISION_INC_FLAGS} -I${PROJ_DIR}/build" -csimflags "${VISION_INC_FLAGS} -I${PROJ_DIR}/build"
add_files -tb "${PROJ_DIR}/xf_sobel_tb.cpp" -cflags "${OPENCV_INC_FLAGS} ${VISION_INC_FLAGS} -I${PROJ_DIR}/build" -csimflags "${OPENCV_INC_FLAGS} ${VISION_INC_FLAGS} -I${PROJ_DIR}/build"

# ------------------------------------------------------------------------------
# Create Project and Solution
# ------------------------------------------------------------------------------
set_top $PROJ_TOP
open_solution -reset $SOLUTION_NAME
set_part $SOLUTION_PART
create_clock -period $SOLUTION_CLKP

# ------------------------------------------------------------------------------
# Run Vitis HLS Stages
# Note: CSim and CoSim require datafiles to be included 
# ------------------------------------------------------------------------------
csim_design -ldflags "-L ${OPENCV_LIB} ${OPENCV_LIB_REF}" -argv "${XF_PROJ_ROOT}/data/128x128.png"
csynth_design
cosim_design -ldflags "-L ${OPENCV_LIB} ${OPENCV_LIB_REF}" -argv "${XF_PROJ_ROOT}/data/128x128.png"
export_design -flow syn -rtl verilog
#  export_design -flow impl -rtl verilog
exit
```

## References

For detailed steps, visit the [Using Vitis Vision Libraries with OpenCV in Vitis HLS](https://support.xilinx.com/s/article/75727?language=en_US).

---
