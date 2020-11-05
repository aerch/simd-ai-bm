#!/bin/bash
# Makefile for the Linux (test) project

TARGET          = test
VERSION         = 0.1a
DATE            = $(shell date +%d.%m.%y)
PROJECT         = 'Test Project ('$(TARGET)') v'$(VERSION)
BACKUP          = ../$(TARGET)
NPROC           = $(shell nproc)

CXX             = g++
LD              = g++

RM              = /bin/rm -rf
CP              = /bin/cp -f
MV              = /bin/mv -f
ECHO            = /bin/echo

PWD             := $(shell pwd)
MAKE            = make

CPUFLAGS        = -mmmx -msse -msse2 -msse3 -mssse3 -msse4 #-mavx -mavx2 -mfma
DFLAGS          = -D VERSION='"$(VERSION)"' -D CYCLESCOUNT=1000000000 -D THREADSCOUNT=$(NPROC) -D NO_CPU_TIME_MEASURE #-D PTHREAD_STACK_SIZE=20000000 #-D PTHREAD_SCHED_FIFO # $(NPROC)

CXXFLAGS        = -g3 -MMD -march=native -mtune=native -ffast-math -std=c++11 $(CPUFLAGS) $(DFLAGS) -Wall -faligned-new
LDFLAGS         = $(CXXFLAGS)

LIBS            = -lm -lpthread
LIB_DIRS        = -L.

INCLUDES        = -I.

CXXOPTIONS      = $(LIBS) $(LIB_DIRS) $(INCLUDES)
LDOPTIONS       = $(CXXOPTIONS)

DFILES          = $(foreach bdir,$(BUILD_DIRS), $(wildcard $(bdir)/*.d))

SOURCES         = test.c
HEADERS         = test.h
OBJECTS         = test.o

BLACK           = '\033[30;1m'
RED             = '\033[31;1m'
GREEN           = '\033[32;1m'
YELLOW          = '\033[33;1m'
BLUE            = '\033[34;1m'
PURPLE          = '\033[35;1m'
CYAN            = '\033[36;1m'
WHITE           = '\033[37;1m'
GRAY            = '\033[30;1m'
OFF             = '\033[0m'

.PHONY: $(TARGET) clean

$(TARGET): clean $(OBJECTS)
	@$(ECHO) -en $(GREEN)' ld  '$(TARGET)$(OFF)'\n'
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@ $(LDOPTIONS)
	@$(ECHO) -en $(GREEN)$(PROJECT)' successfully built.'$(OFF)'\n'

test.o: test.c
	@echo -en $(WHITE)' cc  '$<$(OFF)'\n'
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXXOPTIONS)

clean:
	@echo -en $(WHITE)' cleaning project folder ...'$<$(OFF)'\n'
	@$(RM) $(TARGET) *.o *.d *.~ gmon.out
