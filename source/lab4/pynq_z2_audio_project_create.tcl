# MIT License
# Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# SOFTWARE.

start_gui
create_project audio ./audio -part xc7z020clg400-1
set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]
set_property simulator_language Verilog [current_project]
create_bd_design "system"
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]
regenerate_bd_layout
startgroup
set_property -dict [list CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {12.288} CONFIG.PCW_EN_CLK1_PORT {1} CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {0} CONFIG.PCW_SD0_PERIPHERAL_ENABLE {0} CONFIG.PCW_USB0_PERIPHERAL_ENABLE {0} CONFIG.PCW_I2C1_PERIPHERAL_ENABLE {1} CONFIG.PCW_GPIO_MIO_GPIO_ENABLE {0}] [get_bd_cells processing_system7_0]
endgroup
regenerate_bd_layout
startgroup
set_property -dict [list CONFIG.PCW_TTC0_PERIPHERAL_ENABLE {0}] [get_bd_cells processing_system7_0]
endgroup
regenerate_bd_layout
set_property ip_repo_paths  C:/xup/hls/labs/lab4/ip_repo [current_project]
update_ip_catalog
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0
endgroup
startgroup
set_property -dict [list CONFIG.C_GPIO_WIDTH {2} CONFIG.C_GPIO2_WIDTH {1} CONFIG.C_IS_DUAL {1} CONFIG.C_ALL_INPUTS_2 {1} ] [get_bd_cells axi_gpio_0]
endgroup
startgroup
create_bd_cell -type ip -vlnv xilinx.com:user:zed_audio_ctrl:1.0 zed_audio_ctrl_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config {Master "/processing_system7_0/M_AXI_GP0" Clk "Auto" }  [get_bd_intf_pins axi_gpio_0/S_AXI]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config {Master "/processing_system7_0/M_AXI_GP0" Clk "Auto" }  [get_bd_intf_pins zed_audio_ctrl_0/S_AXI]
startgroup
create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 GPIO
connect_bd_intf_net [get_bd_intf_pins axi_gpio_0/GPIO] [get_bd_intf_ports GPIO]
endgroup
startgroup
create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 GPIO2
connect_bd_intf_net [get_bd_intf_pins axi_gpio_0/GPIO2] [get_bd_intf_ports GPIO2]
endgroup
startgroup
create_bd_port -dir O BCLK
connect_bd_net [get_bd_pins /zed_audio_ctrl_0/BCLK] [get_bd_ports BCLK]
endgroup
startgroup
create_bd_port -dir O LRCLK
connect_bd_net [get_bd_pins /zed_audio_ctrl_0/LRCLK] [get_bd_ports LRCLK]
endgroup
startgroup
create_bd_port -dir O SDATA_O
connect_bd_net [get_bd_pins /zed_audio_ctrl_0/SDATA_O] [get_bd_ports SDATA_O]
endgroup
startgroup
create_bd_port -dir I SDATA_I
connect_bd_net [get_bd_pins /zed_audio_ctrl_0/SDATA_I] [get_bd_ports SDATA_I]
endgroup
startgroup
create_bd_intf_port -mode Master -vlnv xilinx.com:interface:iic_rtl:1.0 IIC_1
connect_bd_intf_net [get_bd_intf_pins processing_system7_0/IIC_1] [get_bd_intf_ports IIC_1]
endgroup
startgroup
create_bd_port -dir O -type clk FCLK_CLK1
connect_bd_net [get_bd_pins /processing_system7_0/FCLK_CLK1] [get_bd_ports FCLK_CLK1]
endgroup
regenerate_bd_layout
