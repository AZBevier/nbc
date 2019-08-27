#~!Makefile for nbasm
# Name:  Makefile Part No.: _______-____r
#
# make depend 		# adds dependencies to makefile
# make clean		# deletes objects
# make clobber		# deletes load module and objects
# make all		# makes everything
# make			# makes everything, defaults to make all
# make library		# updates only library
# make install		# does make all, then copies load module
#			# to system directory

#ident	"@(#)Make:nbasm/Makefile	1.0"

# Make parameters when running on MPX

ROOT = /system/system
TARGET = /system/system
SOURCE = .
PREFIX = nb
INCLUDE = /system/$(PREFIX)include
SINCLUDE = $(INCLUDE)
SBIN = /system/system
BIN = /system/bin
UBIN = /system/bin
LIB = /system/bin
YBIN = /system/bin
CPP = $(LIB)/$(PREFIX)cpp
CPFLAGS = -M -DMYATOF
CC = $(UBIN)/$(PREFIX)cc
CFLAGS = -DMPX -DMYATOF
LD = $(UBIN)/$(PREFIX)nbcat
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile

# loadmap file for nbcat output
LDFLAGS = -Ynbasmmap

HDRS	= defs.h float.h

SRCS 	= main.c macro.c goasm.c parse.c io.c opcode.c pseudo.c symbol.c \
	xref.c float.c myatof.c

OBJECTS	= main.o macro.o goasm.o parse.o io.o opcode.o pseudo.o symbol.o \
	xref.o float.o myatof.o

# loadmodule name
MAIN = nbasm

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
	$(BIN)/rm -f nbasmmap

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
	$(BIN)/cp $(MAIN) $(BIN)/$(MAIN)

xref.o:		xref.c defs.h

float.o:	float.c float.h

myatof.o:	myatof.c float.h

goasm.o:	goasm.c defs.h

io.o:		io.c defs.h

main.o:		main.c defs.h

macro.o:	macro.c defs.h

opcode.o:	opcode.c defs.h

parse.o:	parse.c defs.h float.h

pseudo.o:	pseudo.c defs.h

symbol.o:	symbol.c defs.h

# DO NOT DELETE THIS LINE -- the dependencies begin here
# Source file main.c
main.o: main.c
main.o: defs.h
main.o: /system/nbinclude/stdio.h
main.o: /system/nbinclude/signal.h
main.o: /system/nbinclude/time.h
# Source file macro.c
macro.o: macro.c
macro.o: defs.h
macro.o: /system/nbinclude/stdio.h
macro.o: /system/nbinclude/stdio.h
# Source file goasm.c
goasm.o: goasm.c
goasm.o: defs.h
goasm.o: /system/nbinclude/stdio.h
# Source file parse.c
parse.o: parse.c
parse.o: defs.h
parse.o: /system/nbinclude/stdio.h
parse.o: /system/nbinclude/ctype.h
parse.o: /system/nbinclude/string.h
parse.o: float.h
parse.o: float.h
# Source file io.c
io.o: io.c
io.o: /system/nbinclude/ctype.h
io.o: defs.h
io.o: /system/nbinclude/stdio.h
io.o: /system/nbinclude/string.h
# Source file opcode.c
opcode.o: opcode.c
opcode.o: defs.h
opcode.o: /system/nbinclude/stdio.h
opcode.o: /system/nbinclude/string.h
# Source file pseudo.c
pseudo.o: pseudo.c
pseudo.o: defs.h
pseudo.o: /system/nbinclude/stdio.h
pseudo.o: /system/nbinclude/string.h
# Source file symbol.c
symbol.o: symbol.c
symbol.o: defs.h
symbol.o: /system/nbinclude/stdio.h
symbol.o: /system/nbinclude/ctype.h
# Source file xref.c
xref.o: dummy.c
xref.o: defs.h
xref.o: /system/nbinclude/stdio.h
# Source file float.c
float.o: float.c
float.o: float.h
# Source file myatof.c
myatof.o: myatof.c
myatof.o: /system/nbinclude/ctype.h
myatof.o: float.h
# End of dependencies
