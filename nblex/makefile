#~!Makefile for NBLEX
# Name:  Makefile Part No.: _______-____r
#
# Prototype makefile for MAKE4MPX - J B Systems, Morrison, CO
#
# Change all occurances of nblex to be the lower case name of
# your load module.  Use UNIX style pathnames and insure all
# file names are lower case.  Use the TAB character to start
# lines where indicated.  This makefile generates several
# macros for your use:
#
# make depend 		# adds dependencies to makefile
# make clean		# deletes objects
# make clobber		# deletes load module and objects
# make all		# makes everything
# make			# makes everything, defaults to make all
# make library		# updates only library
# make install		# does make all, then copies load module
#			# to system directory

#ident	"@(#)Make:nblex/Makefile	1.0"

# Make parameters when running on MPX

ROOT = /system/system
TARGET = /system/bin
SOURCE = .
PREFIX = nb
INCLUDE = /system/$(PREFIX)include
SINCLUDE = $(INCLUDE)
SBIN = /system/bin
BIN = /system/bin
UBIN = /system/bin
LIB = /system/bin
YBIN = /system/bin
CPP = $(LIB)/$(PREFIX)cpp
CPFLAGS = -M
CC = $(UBIN)/$(PREFIX)cc
CFLAGS = -DMPX
LD = $(UBIN)/$(PREFIX)cat
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile

# Fill in with correct information
# Notice! All file names MUST be in lower case.
# if definition is not to be used, assign to null as follows

# loadmap file for nbcat output
LDFLAGS = -Ynblexmap

# non library objects
OBJECTS = lmain.o sub1.o sub2.o header.o parser.o

# define all sources for depend
SRCS = lmain.c sub1.c sub2.c header.c parser.y

# loadmodule name
MAIN = nblex

ALL:	all

all:	$(MAIN)			# build everything
	$(BIN)/echo $(MAIN) is up to date.

$(MAIN):	$(MAKEFILE) $(OBJECTS)  # build main
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(MAIN)
	$(BIN)/chmod 775 $(MAIN)
	$(BIN)/chgrp system $(MAIN)
	$(BIN)/chown system $(MAIN)

CLEAN:  clean

clean:				# delete object files
	$(BIN)/rm -f $(OBJECTS)

CLOBBER: clobber

clobber: clean			# delete main from current directory
	$(BIN)/rm -f $(MAIN)

DEPEND: depend

depend: $(SRCS) $(HDRS) $(MAKEFILE)	# generate dependencies
	$(BIN)/dodep $(CPFLAGS) $(MAKEFILE) $(SRCS) >dep.out
	$(BIN)/mv dep.out $(MAKEFILE)

#	$(BIN)/mkdep $(MAKEFILE) >dep.out
#	@for i in $(SRCS); do \
#	$(BIN)/echo "# Source file '$$i'" >> dep.out; \
#	$(CPP) $(CPFLAGS) $$i >> dep.out; \
#	done;
#	$(BIN)/echo "# End of dependencies" >> dep.out;
#	$(BIN)/mv dep.out $(MAKEFILE)

INSTALL: install

install: all	# build if necessary, and then copy main to system directory
	$(BIN)/cp $(MAIN) $(SBIN)/$(MAIN)

# DO NOT DELETE THIS LINE -- the dependencies begin here
