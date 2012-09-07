# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#
# GNU Make based build file.  For details on GNU Make see:
#   http://www.gnu.org/software/make/manual/make.html
#

#
# Get pepper directory for toolchain and includes.
#
# If NACL_SDK_ROOT is not set, then assume it can be found a two directories up,
# from the default example directory location.
#
THIS_MAKEFILE:=$(abspath $(lastword $(MAKEFILE_LIST)))
NACL_SDK_ROOT?=$(abspath $(dir $(THIS_MAKEFILE))../..)
CHROME_PATH?=Undefined

#
# Defaults
#
NACL_WARNINGS:=-Wno-long-long -Wall -Wswitch-enum -pedantic
NACL_CCFLAGS:=-O0 -g -pthread -DPIXELBOOST_PLATFORM_NACL $(NACL_WARNINGS)
NACL_CXXFLAGS:= -O0 -g -pthread -std=gnu++98 -DPIXELBOOST_PLATFORM_NACL $(NACL_WARNINGS)
NACL_LDFLAGS:=-g -pthread -lppapi_cpp -lppapi

#
# Project Settings
#
VALID_TOOLCHAINS:=newlib
TOOLCHAIN?=newlib

PIXELBOOST_NACL_CC  := pixelboost.cc matrix.cc

PIXELBOOST_LIB_CPP := $(shell find ../pixelboost/engine/src/common -type f -name "*.cpp")
PIXELBOOST_LIB_CPP += $(shell find ../pixelboost/engine/src/external -type f -name "*.cpp")
PIXELBOOST_LIB_CPP += $(shell find ../pixelboost/engine/src/platform/nacl -type f -name "*.cpp")

PIXELBOOST_LIB_C := $(shell find ../pixelboost/engine/src/common -type f -name "*.c")
PIXELBOOST_LIB_C += $(shell find ../pixelboost/engine/src/external -type f -name "*.c")
PIXELBOOST_LIB_C += $(shell find ../pixelboost/engine/src/platform/nacl -type f -name "*.c")

PIXELBOOST_APP_CPP += $(shell find ../source -type f -name "*.cpp")

PIXELBOOST_CXXFLAGS:=$(NACL_CXXFLAGS) -I../src
PIXELBOOST_CXXFLAGS += -I../../src/ppapi/lib/gl
PIXELBOOST_CXXFLAGS += -I../pixelboost/engine/src/common/
PIXELBOOST_CXXFLAGS += -I../pixelboost/engine/src/external/
PIXELBOOST_CXXFLAGS += -I../pixelboost/engine/src/platform/nacl/
PIXELBOOST_CXXFLAGS += -I../libs/fmod/nacl/inc/
PIXELBOOST_CXXFLAGS += -I../source/
PIXELBOOST_LDFLAGS := -g -pthread -lppapi_cpp -lppapi -lppapi_gles2 -lnosys

FMOD_LIB_32 = ../libs/fmod/nacl/lib/pepper_21/win_x86_newlib/x86-32/libfmodex.a
FMOD_LIB_64 = ../libs/fmod/nacl/lib/pepper_21/win_x86_newlib/x86-64/libfmodex.a

#
# Default target
#
all: newlib/pixelboost.nmf

#
# Alias for standard commands
#
CP:=python $(NACL_SDK_ROOT)/tools/oshelpers.py cp
MKDIR:=python $(NACL_SDK_ROOT)/tools/oshelpers.py mkdir
MV:=python $(NACL_SDK_ROOT)/tools/oshelpers.py mv

#
# Verify we selected a valid toolchain for this example
#
ifeq (,$(findstring $(TOOLCHAIN),$(VALID_TOOLCHAINS)))
$(warning Availbile choices are: $(VALID_TOOLCHAINS))
$(error Can not use TOOLCHAIN=$(TOOLCHAIN) on this example.)
endif

#
# Compute path to requested NaCl Toolchain
#
OSNAME:=$(shell python $(NACL_SDK_ROOT)/tools/getos.py)
TC_PATH:=$(abspath $(NACL_SDK_ROOT)/toolchain)

#
# Verify we have a valid NACL_SDK_ROOT by looking for the toolchain directory
#
ifeq (,$(wildcard $(TC_PATH)))
$(warning No valid NACL_SDK_ROOT at $(NACL_SDK_ROOT))
ifeq ($(origin NACL_SDK_ROOT), 'file')
$(error Override the default value via enviornment variable, or command-line.)
else
$(error Fix the NACL_SDK_ROOT specified in the environment or command-line.)
endif
endif

#
# Disable DOS PATH warning when using Cygwin based NaCl tools on Windows
#
CYGWIN ?= nodosfilewarning
export CYGWIN

#
# Defaults for TOOLS
#

NEWLIB_CC?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-gcc -c
NEWLIB_CXX?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-g++ -c
NEWLIB_LD?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-ld
NEWLIB_LINK?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-g++ -Wl,-as-needed
NEWLIB_DUMP?=$(TC_PATH)/$(OSNAME)_x86_newlib/x86_64-nacl/bin/objdump

#
# NMF Manifiest generation
#
# Use the python script create_nmf to scan the binaries for dependencies using
# objdump.  Pass in the (-L) paths to the default library toolchains so that we
# can find those libraries and have it automatically copy the files (-s) to
# the target directory for us.
NMF:=python $(NACL_SDK_ROOT)/tools/create_nmf.py

#
# Verify we can find the Chrome executable if we need to launch it.
#
.PHONY: CHECK_FOR_CHROME
CHECK_FOR_CHROME:
ifeq (,$(wildcard $(CHROME_PATH)))
	$(warning No valid Chrome found at CHROME_PATH=$(CHROME_PATH))
	$(error Set CHROME_PATH via an environment variable, or command-line.)
else
	$(warning Using chrome at: $(CHROME_PATH))
endif

#
# Rules for newlib toolchain
#
newlib:
	$(MKDIR) newlib

PB_x86_32_NACL_CC_O := $(patsubst %.cc, newlib/nacl/%_x86_32.o,$(PIXELBOOST_NACL_CC))
$(PB_x86_32_NACL_CC_O) : newlib/nacl/%_x86_32.o : %.cc $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m32 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_32_LIB_CPP_O := $(patsubst %.cpp, newlib/pixelboost/dummy/%_x86_32.o,$(PIXELBOOST_LIB_CPP))
$(PB_x86_32_LIB_CPP_O) : newlib/pixelboost/dummy/%_x86_32.o : %.cpp $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m32 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_32_LIB_C_O := $(patsubst %.c, newlib/pixelboost/dummy/%_x86_32.o,$(PIXELBOOST_LIB_C))
$(PB_x86_32_LIB_C_O) : newlib/pixelboost/dummy/%_x86_32.o : %.c $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CC) -o $@ $< -m32 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_32_APP_CPP_O := $(patsubst %.cpp, newlib/app/dummy/%_x86_32.o,$(PIXELBOOST_APP_CPP))
$(PB_x86_32_APP_CPP_O) : newlib/app/dummy/%_x86_32.o : %.cpp $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m32 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

newlib/pixelboost_x86_32.o : $(PB_x86_32_LIB_CPP_O) $(PB_x86_32_LIB_C_O)
	$(NEWLIB_LD) -r -o $@ $^

newlib/app_x86_32.o : $(PB_x86_32_APP_CPP_O)
	$(NEWLIB_LD) -r -o $@ $^

newlib/nacl_x86_32.o : $(PB_x86_32_NACL_CC_O)
	$(NEWLIB_LD) -r -o $@ $^

newlib/pixelboost_x86_32.nexe : newlib/pixelboost_x86_32.o newlib/app_x86_32.o newlib/nacl_x86_32.o $(FMOD_LIB_32)
	$(NEWLIB_LINK) -o $@ $^ -L../libs/fmod/nacl/lib/pepper_21/win_x86_newlib/x86-32/ -m32 $(PIXELBOOST_LDFLAGS)
NEWLIB_NMF += newlib/pixelboost_x86_32.nexe

PB_x86_64_NACL_CC_O := $(patsubst %.cc, newlib/nacl/%_x86_64.o,$(PIXELBOOST_NACL_CC))
$(PB_x86_64_NACL_CC_O) : newlib/nacl/%_x86_64.o : %.cc $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m64 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_64_LIB_CPP_O := $(patsubst %.cpp, newlib/pixelboost/dummy/%_x86_64.o,$(PIXELBOOST_LIB_CPP))
$(PB_x86_64_LIB_CPP_O) : newlib/pixelboost/dummy/%_x86_64.o : %.cpp $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m64 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_64_LIB_C_O := $(patsubst %.c, newlib/pixelboost/dummy/%_x86_64.o,$(PIXELBOOST_LIB_C))
$(PB_x86_64_LIB_C_O) : newlib/pixelboost/dummy/%_x86_64.o : %.c $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CC) -o $@ $< -m64 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

PB_x86_64_APP_CPP_O := $(patsubst %.cpp, newlib/app/dummy/%_x86_64.o,$(PIXELBOOST_APP_CPP))
$(PB_x86_64_APP_CPP_O) : newlib/app/dummy/%_x86_64.o : %.cpp $(THIS_MAKE) | newlib
	mkdir -p $(shell echo $@ | sed "s/\(.*\)\/.*.o/\1/g")
	$(NEWLIB_CXX) -o $@ $< -m64 $(PIXELBOOST_CXXFLAGS) -DTCNAME=newlib

newlib/pixelboost_x86_64.o : $(PB_x86_64_LIB_CPP_O) $(PB_x86_64_LIB_C_O)
	$(NEWLIB_LD) -r -m elf64_nacl -o $@ $^

newlib/app_x86_64.o : $(PB_x86_64_APP_CPP_O)
	$(NEWLIB_LD) -r -m elf64_nacl -o $@ $^

newlib/nacl_x86_64.o : $(PB_x86_64_NACL_CC_O)
	$(NEWLIB_LD) -r -m elf64_nacl -o $@ $^

newlib/pixelboost_x86_64.nexe : newlib/pixelboost_x86_64.o newlib/app_x86_64.o newlib/nacl_x86_64.o $(FMOD_LIB_64)
	$(NEWLIB_LINK) -o $@ $^ -L../libs/fmod/nacl/lib/pepper_21/win_x86_newlib/x86-64/ -m64 $(PIXELBOOST_LDFLAGS)
NEWLIB_NMF += newlib/pixelboost_x86_64.nexe

newlib/pixelboost.nmf : $(NEWLIB_NMF)
	$(NMF) -D $(NEWLIB_DUMP) -o $@ $^ -t newlib -s newlib

RUN: all
	python ../httpd.py

LAUNCH_NEXE: CHECK_FOR_CHROME all
	$(CHROME_PATH) $(NEXE_ARGS) "localhost:5103/$(PROJECT).html?tool=$(TOOLCHAIN)"


