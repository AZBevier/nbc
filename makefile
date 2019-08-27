#!/bin/sh
# Top level makefile for nbc environment on MPX1X, MPX3X, and UNIX.

default:
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "To build everything, run \"make install\""
	@echo "To rebuild, run \"make remake\""
	@echo "To remove objects, run \"make clean\""
	@echo "To remove objects and load modules, run \"make clobber\""
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++"

#make everything
all:	install
install:
	@make -f mk.unix install
	@make -f mk.mpx1x install
	@make -f mk.mpx3x install
	@echo "All load modules built"
	@echo "NBC installation complete"

#remake everything
remake:
	@make -f mk.unix remake
	@make -f mk.mpx1x remake
	@make -f mk.mpx3x remake
	@echo "All load modules rebuilt"
	@echo "NBC remake complete"

#remove objects from build directories
clean:
	-make -f mk.unix clean
	-make -f mk.mpx1x clean
	-make -f mk.mpx3x clean
	@echo "All objects deleted"
	@echo "NBC clean complete"

#remove objects and loadmodules
clobber:
	-make -f mk.unix clobber
	-make -f mk.mpx1x clobber
	-make -f mk.mpx3x clobber
	@echo "All objects and load modules deleted"
	@echo "NBC clobber complete"

