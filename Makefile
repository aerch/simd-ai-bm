#!/bin/bash
# Makefile for the Linux SIMD Arithmetic Instructions Benchmark (simd-ai-bm) project

TARGET          = simd-ai-bm
VERSION         = 0.9.24a
DATE            = $(shell date +%d.%m.%y)
PROJECT         = 'SIMD Arithmetic Instructions Benchmark ('$(TARGET)') v'$(VERSION)
BACKUP          = ../$(TARGET)
NPROC           = $(shell nproc)

CXX             = g++
LD              = g++

RM              = /bin/rm -rf
CP              = /bin/cp -f
MV              = /bin/mv -f
ECHO            = /bin/echo
STRIP           = /usr/bin/strip

PWD             := $(shell pwd)
MAKE            = make

# CPUFLAGS        = -mmmx -msse -msse2 -msse3 -mssse3 -msse4 -mavx -mavx2 -mfma

DFLAGS          = -D VERSION='"$(VERSION)"' -D CYCLESCOUNT=1000000000 -D THREADSCOUNT=$(NPROC) -D NO_CPU_TIME_MEASURE #-D PTHREAD_STACK_SIZE=20000000 #-D PTHREAD_SCHED_FIFO # $(NPROC)

CXXFLAGS        = -O3 -MMD -march=native -mtune=native -std=c++11 -ffast-math -faligned-new -ffunction-sections -fdata-sections -Wl,--gc-sections $(CPUFLAGS) $(DFLAGS) -Wall
LDFLAGS         = $(CXXFLAGS)

LIBS            = -lm -lpthread
LIB_DIRS        = -L.

INCLUDES        = -I.

CXXOPTIONS      = $(LIBS) $(LIB_DIRS) $(INCLUDES)
LDOPTIONS       = $(CXXOPTIONS)

DFILES          = $(foreach bdir,$(BUILD_DIRS), $(wildcard $(bdir)/*.d))

SOURCES         = simd-ai-bm.c
HEADERS         = simd-ai-bm.h
OBJECTS         = simd-ai-bm.o

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

.PHONY: $(TARGET) git-push-"update" backup help docs html pdf clean

$(TARGET): clean $(OBJECTS)
	@$(ECHO) -en $(GREEN)' ld  '$(TARGET)$(OFF)'\n'
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@ $(LDOPTIONS)
	@echo -en $(WHITE)' strip executable'$(OFF)'\n'
	@$(STRIP) $(TARGET)
	@$(ECHO) -en $(GREEN)$(PROJECT)' successfully built.'$(OFF)'\n'
# 	@file $(TARGET)

simd-ai-bm.o: simd-ai-bm.c
	@echo -en $(WHITE)' cc  '$<$(OFF)'\n'
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXXOPTIONS)

clean: clean-docs
	@echo -en $(WHITE)' cleaning project folder ...'$(OFF)
	@$(RM) $(TARGET) *.o *.d gmon.out *.log *~
	@echo -en $(WHITE)' done.'$(OFF)'\n'

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

# Makefile part for Sphinx documentation
# You can set these variables from the command line, and also from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = docs/source
BUILDDIR      = docs/build
DOXYFILE      = docs/doxygen/doxyfile

help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

doxygen:
	mkdir -p $(BUILDDIR)
	doxygen $(DOXYFILE)

docs: doxygen
# 	cd docs/build/doxylatex && make
# 	/bin/ln -sf $(BUILDDIR)/doxylatex/refman.pdf simd-ai-bm-api.pdf
	/bin/ln -sf $(BUILDDIR)/doxyhtml/index.html simd-ai-bm-api.html
	$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	/bin/ln -sf $(BUILDDIR)/html/index.html simd-ai-bm.html
	$(SPHINXBUILD) -M latexpdf "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	/bin/ln -sf $(BUILDDIR)/latex/simd-ai-bm.pdf simd-ai-bm.pdf

html-local: doxygen
	/bin/ln -sf $(BUILDDIR)/doxyhtml/index.html simd-ai-bm-api.html
	$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	/bin/ln -sf $(BUILDDIR)/html/index.html simd-ai-bm.html

pdf-local: doxygen
# 	cd docs/build/doxylatex && make
# 	/bin/ln -sf $(BUILDDIR)/doxylatex/refman.pdf simd-ai-bm-api.pdf
	$(SPHINXBUILD) -M latexpdf "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	/bin/ln -sf $(BUILDDIR)/latex/simd-ai-bm.pdf simd-ai-bm.pdf

clean-docs:
	@rm -rf $(BUILDDIR) simd-ai-bm-api.html simd-ai-bm.html simd-ai-bm-api.pdf simd-ai-bm.pdf

clean-local: clean-docs

include $(DFILES)
