# ------------------------------------------------------------------------------
# Vitis Vision and OpenCV Library Path Information
# ------------------------------------------------------------------------------
set XF_PROJ_ROOT "<Your Vision Vision Library Path>/vision" 
#Vitis Vision Libary include directory
set OPENCV_INCLUDE "<Your OpenCV 4.4.0 Path>/include/opencv4" 
#OpenCV header file directory
set OPENCV_LIB "<Your OpenCV 4.4.0 Path>/lib" 
#OpenCV compiled library directory

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