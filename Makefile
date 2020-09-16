#!/bin/bash
# Makefile for the linux SIMD Instructions Benchmark (simd-ibm) project

TARGET          = simd-ibm
VERSION         = 0.3a
PROJECT         = 'SIMD Instructions Benchmark ('$(TARGET)') v'$(VERSION)
BACKUP          = ../$(TARGET)

CXX             = g++
LD              = g++

RM              = /bin/rm -rf
CP              = /bin/cp -f
MV              = /bin/mv -f
ECHO            = /bin/echo

PWD             := $(shell pwd)
MAKE            = make

CXXFLAGS	= -O3 -MMD -march=native -mtune=native -mavx2 -ffast-math -std=c++11 -Wall -faligned-new
LDFLAGS         = $(CXXFLAGS)

LIBS            = -lm -lpthread
LIB_DIRS        = -L.

INCLUDES	= -I.

CXXOPTIONS      = $(LIBS) $(LIB_DIRS) $(INCLUDES)
LDOPTIONS       = $(CXXOPTIONS)

DFILES          = $(foreach bdir,$(BUILD_DIRS), $(wildcard $(bdir)/*.d))

SOURCES         = simd-ibm.c
HEADERS         = simd-ibm.h
OBJECTS         = simd-ibm.o

BLACK           = '\033[30;1m'
RED             = '\033[31;1m'
GREEN           = '\033[32;1m'
YELLOW          = '\033[33;1m'
BLUE            = '\033[34;1m'
PURPLE          = '\033[35;1m'
CYAN            = '\033[36;1m'
WHITE           = '\033[37;1m'
GRAY		= '\033[30;1m'
OFF             = '\033[0m'

.PHONY: $(TARGET) clean git-push-"update_commit" backup

$(TARGET): clean $(OBJECTS)
	@$(ECHO) -en $(GREEN)' LD  '$(TARGET)$(OFF)'\n'
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ $(LDOPTIONS)
	@$(ECHO) -en $(GREEN)$(PROJECT)' successfully built.'$(OFF)'\n'

simd-ibm.o: simd-ibm.c
	@echo -en $(WHITE)' CC  '$<$(OFF)'\n'
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXXOPTIONS)

clean:
	$(RM) $(TARGET) *.o *.d *.~ gmon.out

git-push-%: clean
	@$(ECHO) -en "\n > "
	git add .
	@$(ECHO) -en "\n > "
	git status
	@$(ECHO) -en "\n > "
	git commit -m "v"$(VERSION)-$(DATE)" $*"
	@$(ECHO) -en "\n > "
	git push

backup: clean
	@$(ECHO) '> > > > folder tar archiving ...'
	@tar cfv ./$(TARGET)-$(VERSION)-`date +%d.%m.%y`.tar --exclude=$(TARGET)'-*.tar.gz' $(BACKUP)
	@$(ECHO) '> > > > zip compressing ...'
	@gzip -v9 -f -S .gz ./$(TARGET)-$(VERSION)-`date +%d.%m.%y`.tar

include $(DFILES)
