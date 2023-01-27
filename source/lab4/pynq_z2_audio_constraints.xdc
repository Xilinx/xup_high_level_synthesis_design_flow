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

# Audio Related constraints
set_property PACKAGE_PIN R18 [get_ports BCLK]
set_property IOSTANDARD LVCMOS33 [get_ports BCLK]

set_property PACKAGE_PIN T17 [get_ports LRCLK]
set_property IOSTANDARD LVCMOS33 [get_ports LRCLK]

set_property PACKAGE_PIN F17 [get_ports SDATA_I]
set_property IOSTANDARD LVCMOS33 [get_ports SDATA_I]

set_property PACKAGE_PIN G18 [get_ports SDATA_O]
set_property IOSTANDARD LVCMOS33 [get_ports SDATA_O]

#MCLK
set_property PACKAGE_PIN U5 [get_ports FCLK_CLK1]
set_property IOSTANDARD LVCMOS33 [get_ports FCLK_CLK1]

set_property PACKAGE_PIN U9 [get_ports IIC_1_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_1_scl_io]

set_property PACKAGE_PIN T9 [get_ports IIC_1_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_1_sda_io]

set_property PACKAGE_PIN M17 [get_ports {GPIO_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_tri_io[0]}]

set_property PACKAGE_PIN M18 [get_ports {GPIO_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_tri_io[1]}]

# GPIO2[0] for bypass a sample or send it through the filter
set_property PACKAGE_PIN M20 [get_ports {GPIO2_tri_i[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO2_tri_i[0]}]

set_property PULLUP true [get_ports IIC_1_scl_io];
set_property PULLUP true [get_ports IIC_1_sda_io];

