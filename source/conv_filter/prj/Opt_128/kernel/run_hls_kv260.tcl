#Copyright (C) 2024, Advanced Micro Devices, Inc. All rights reserved.
#SPDX-License-Identifier: MIT

set project_name "filter2d"
set opt_method "opt"
set pynq_z2 "xc7z020-clg484-1"
set kv260 "xck26-sfvc784-2LV-c"


# Create a project
open_project -reset ${project_name}

# Add design files
add_files ${project_name}.cpp
# Add test bench & files
add_files -tb filter2d_test.cpp
add_files -tb src.txt
add_files -tb dst.txt
add_files filter2d_out.txt

# Set the top-level function
set_top filter2d_accel

# ########################################################
# Create a solution
open_solution -reset ${opt_method} -flow_target vivado

# Define technology and clock rate
set_part  ${kv260}
create_clock -period 5

# Set variable to select which steps to execute
set hls_exec 3


csim_design
# Set any optimization directives
# End of directives

if {$hls_exec >= 1} {
	# Run Synthesis
   csynth_design
}
if {$hls_exec >= 2} {
	# Run Synthesis, RTL Simulation
   cosim_design
}
if {$hls_exec >= 3} { 
	# Run Synthesis, RTL Simulation, RTL implementation
   #export_design -format ip_catalog -version "1.00a" -library "hls" -vendor "xilinx.com" -description "A memory mapped IP created by Vitis HLS" -evaluate verilog
   export_design -format ip_catalog -evaluate verilog
}

exit