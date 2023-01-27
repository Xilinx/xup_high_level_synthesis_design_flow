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
# makefile-generator v1.0.3

# ######################################################
# Define design information
# - assumes the design files are .c (update to .cpp for C++ and SystemC)
# - assumes test bench is <design>_test.c

DESIGN		 := yuv_filter
SOURCES		 := $(DESIGN).c $(DESIGN)_test.c image_aux.c
OBJECTS		 := $(SOURCES:.c=.o)
INCLUDES		 := $(DESIGN).h image_aux.h
CLEAN_FILES  := $(OBJECTS) $(DESIGN) $(DESIGN).exe
CLEAN_FILES  += test_data/output.dat
VIVADO_HLS_CLEANUP := $(DESIGN)_prj $(DESIGN).log vivado_hls.log 
# Change to true if using ap[u]int in ISO-C project
USE_ARBITRARY_PRECISION = false
# Change to true if using SystemC types or SC_MODULE, etc.
USE_SYSTEMC 				= false

# ######################################################
# Automatically setup the software paths
SHELL           := sh
KERNEL          := $(shell if [[ $$(uname -s) == Linux ]];then echo Linux; else echo Win; fi)
ARCH            := $(shell if [[ $$(uname -m) =~ 64$$ ]];then echo x86_64; else echo x86; fi)
OS              := $(KERNEL)_$(ARCH)
ifeq ($(KERNEL), Win)
VIVADO_HLS_EXE_FILENAME := vivado_hls.bat
APCC= $(VIVADO_HLS_ROOT)/$(OS)/bin/apcc_bin.exe
else
VIVADO_HLS_EXE_FILENAME := vivado_hls
APCC:= apcc
endif
VIVADO_HLS_EXE   := $(shell which $(VIVADO_HLS_EXE_FILENAME))
VIVADO_HLS_ROOT  := $(VIVADO_HLS_EXE:/bin/$(VIVADO_HLS_EXE_FILENAME)=)
VIVADO_HLS_INC_PATH := $(VIVADO_HLS_ROOT)/include
SYSTEMC_INC_PATH := $(VIVADO_HLS_ROOT)/$(OS)/tools/systemc/include
SYSTEMC_LIB_PATH := $(VIVADO_HLS_ROOT)/$(OS)/tools/systemc/lib

# ######################################################
# Setup C compiler and options
#
# Use APCC for ISO-C projects that use ap[u]int types; gcc otherwise
ifeq ($(USE_ARBITRARY_PRECISION),true)
CC				:= $(APCC)
CFLAGS		+= -DBIT_ACCURATE
else
CC				:= gcc
endif
CXX			:= g++
# C compiler flags
CFLAGS		+= -ggdb
CFLAGS		+= -w
CFLAGS		+= -I$(VIVADO_HLS_INC_PATH)
# C++ compiler flags
CXXFLAGS		+= -ggdb
CXXFLAGS		+= -I$(VIVADO_HLS_INC_PATH)
# Linker flags
LDFLAGS		+= -lm 
# # SystemC additional flags
ifeq ($(USE_SYSTEMC), true)
CXXFLAGS		+= -I$(SYSTEMC_INC_PATH)
LDFLAGS		+= -L$(SYSTEMC_LIB_PATH)
LDLIBS		+= -lsystemc
endif

# ######################################################
# Rules

all: sim

clean:
	rm -rf $(CLEAN_FILES) $(VIVADO_HLS_CLEANUP)

VIVADO_HLS: $(DESIGN).tcl
	VIVADO_HLS $<

sim: $(DESIGN)
	./$(DESIGN)

$(DESIGN): $(OBJECTS)
# Uses implicit recipes, i.e.:
# $([CC|CXX]) $(CPPFLAGS) $([CFLAGS|CXXFLAGS]) -c # For each SOURCE
# $(CC) $(LDFLAGS) $(OBJECTS) $(LOADLIBES) $(LDLIBS) # To link OBJECTS

# TODO: add rule to rebuild OBJECT when its .h file changes
