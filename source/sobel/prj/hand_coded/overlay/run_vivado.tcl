#  Copyright (C) 2024 Advanced Micro Devices, Inc
# 
#  SPDX-License-Identifier: MIT

set project_name "sobel_opt"
set opt_method "opt"
set design_name "design_1"

#Clean up
file delete {*}[glob *.log]
file delete {*}[glob *.jou]
file delete -force ./${project_name}
file delete -force .crashReporter
file delete -force .Xil

create_project ${project_name} ./${project_name} -part xc7z020clg484-1 -force

# You should revise the path for your own export
set_property  ip_repo_paths  ../kernel/${project_name}/${opt_method}/impl/ip [current_project]

update_ip_catalog

# create_bd_design ${design_name}

# create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0

# create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma:7.1 axi_dma_0

# create_bd_cell -type ip -vlnv xilinx.com:hls:sobel:1.0 sobel_0

# apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]

# set_property -dict [list CONFIG.PCW_USE_S_AXI_HP0 {1}] [get_bd_cells processing_system7_0]

# set_property -dict [list \
#   CONFIG.c_include_sg {0} \
#   CONFIG.c_sg_length_width {23} \
# ] [get_bd_cells axi_dma_0]

# connect_bd_intf_net [get_bd_intf_pins sobel_0/dst] [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM]
# connect_bd_intf_net [get_bd_intf_pins axi_dma_0/M_AXIS_MM2S] [get_bd_intf_pins sobel_0/src]

# apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]

# apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/processing_system7_0/M_AXI_GP0} Slave {/axi_dma_0/S_AXI_LITE} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_dma_0/S_AXI_LITE]

# apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_dma_0/M_AXI_MM2S} Slave {/processing_system7_0/S_AXI_HP0} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins processing_system7_0/S_AXI_HP0]

# apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/processing_system7_0/M_AXI_GP0} Slave {/sobel_0/s_axi_CTRL} ddr_seg {Auto} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins sobel_0/s_axi_CTRL]

# apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/processing_system7_0/FCLK_CLK0 (50 MHz)} Clk_xbar {/processing_system7_0/FCLK_CLK0 (50 MHz)} Master {/axi_dma_0/M_AXI_S2MM}}

source ./block_design.tcl

validate_bd_design

generate_target all [get_files  ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd]
catch { config_ip_cache -export [get_ips -all ${design_name}_processing_system7_0_0] }
catch { config_ip_cache -export [get_ips -all ${design_name}_sobel_0_0] }
catch { config_ip_cache -export [get_ips -all ${design_name}_auto_pc_0] }
catch { config_ip_cache -export [get_ips -all ${design_name}_rst_ps7_0_50M_0] }
catch { config_ip_cache -export [get_ips -all ${design_name}_auto_pc_1] }
catch { config_ip_cache -export [get_ips -all ${design_name}_auto_us_0] }
export_ip_user_files -of_objects [get_files ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd] -no_script -sync -force -quiet
create_ip_run [get_files -of_objects [get_fileset sources_1] ./${project_name}/${project_name}.srcs/sources_1/bd/${design_name}/${design_name}.bd]
launch_runs ${design_name}_processing_system7_0_0_synth_1 ${design_name}_sobel_0_0_synth_1 ${design_name}_auto_pc_0_synth_1 ${design_name}_rst_ps7_0_50M_0_synth_1 ${design_name}_auto_pc_1_synth_1 ${design_name}_auto_us_0_synth_1 -jobs 8
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
