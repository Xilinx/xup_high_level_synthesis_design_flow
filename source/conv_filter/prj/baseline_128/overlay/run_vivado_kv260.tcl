#******************************************************************************
# Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#******************************************************************************
################################################################

################################################################
# This is a generated script based on design: filter2d
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################


set project_name "filter2d"
set opt_method "baseline"
set design_name "design_1"
set kv260 "xck26-sfvc784-2LV-c"


#Clean up
file delete {*}[glob *.log]
file delete {*}[glob *.jou]
file delete -force ./${project_name}
file delete -force .crashReporter
file delete -force .Xil

create_project ${project_name} ./${project_name} -part ${kv260} -force
set_property board_part xilinx.com:kv260_som:part0:1.4 [current_project]

# You should revise the path for your own export
set_property  ip_repo_paths  ../kernel/${project_name}/${opt_method}/impl/ip [current_project]

update_ip_catalog

create_bd_design ${design_name}

create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.5 zynq_ultra_ps_e_0

apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property CONFIG.PSU__USE__S_AXI_GP2 {1} [get_bd_cells zynq_ultra_ps_e_0]

create_bd_cell -type ip -vlnv xilinx.com:hls:fir_wrap:1.0 fir_wrap_0

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/fir_wrap_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins fir_wrap_0/s_axi_CTRL]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/fir_wrap_0/m_axi_gmem} Slave {/zynq_ultra_ps_e_0/S_AXI_HP0_FPD} ddr_seg {Auto} intc_ip {New AXI SmartConnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP0_FPD]

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (99 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (99 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/fir_wrap_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]


validate_bd_design

generate_target all [get_files  ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd]

export_ip_user_files -of_objects [get_files ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd] -no_script -sync -force -quiet

create_ip_run [get_files -of_objects [get_fileset sources_1] ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd]

launch_runs ${design_name}_zynq_ultra_ps_e_0_synth_1 ${design_name}_fir_wrap_0_0_synth_1 ${design_name}_auto_pc_0_synth_1 ${design_name}_rst_ps7_0_50M_0_synth_1 ${design_name}_auto_pc_1_synth_1 ${design_name}_auto_us_0_synth_1 -jobs 8
export_simulation -of_objects [get_files ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd] -directory ./${project_name}/${project_name}.ip_user_files/sim_scripts -ip_user_files_dir ./${project_name}/${project_name}.ip_user_files -ipstatic_source_dir ./${project_name}/${project_name}.ip_user_files/ipstatic -lib_map_path [list {modelsim=./${project_name}/${project_name}.cache/compile_simlib/modelsim} {questa=./${project_name}/${project_name}.cache/compile_simlib/questa} {riviera=./${project_name}/${project_name}.cache/compile_simlib/riviera} {activehdl=./${project_name}/${project_name}.cache/compile_simlib/activehdl}] -use_ip_compiled_libs -force -quiet

make_wrapper -files [get_files ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd] -top
add_files -norecurse ./${project_name}/${project_name}.gen/sources_1/bd/${design_name}/hdl/${design_name}_wrapper.v

launch_runs synth_1 -jobs 8
wait_on_run synth_1

launch_runs impl_1 -jobs 8
wait_on_run impl_1

launch_runs impl_1 -to_step write_bitstream -jobs 8 
wait_on_run impl_1

#move and rename bitstream to final location
file copy -force ./${project_name}/${project_name}.runs/impl_1/${design_name}_wrapper.bit ${project_name}.bit

file copy -force ./${project_name}/${project_name}.gen/sources_1/bd/${design_name}/hw_handoff/${design_name}.hwh ${project_name}.hwh
