#~!Makefile for nbccom
# Name:  Makefile Part No.: _______-____r
#
# Copyright 1995 - J B Systems, Morrison, CO
#
# The recipient of this product specifically agrees not to distribute,
# disclose, or disseminate in any way, to any one, nor use for its own
# benefit, or the benefit of others, any information contained  herein
# without the expressed written consent of J B Systems.
#
#                     RESTRICTED RIGHTS LEGEND
#
# Use, duplication, or disclosure by the Government is  subject  to
# restriction  as  set forth in paragraph (b) (3) (B) of the Rights
# in Technical Data and Computer Software  Clause  in  DAR  7-104.9
# (a).
#
 
#ident	"$Id: make.mpx,v 1.9 1995/03/03 16:25:00 jbev Exp jbev $"
 
# Make parameters when running on MPX
 
ROOT = /system/system
TARGET = /system/bin
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
CPFLAGS = -M
CC = $(UBIN)/$(PREFIX)cc
##CFLAGS = -DMPX -DNOBUG -DMYATOF
CFLAGS = -DMPX -DNOBUG -DNEWATOF
#CFLAGS = -DMPX -DNOBUG
#CFLAGS = -DMPX -DNOBUG -DMYATOF
#CFLAGS = -DMPX -DNOBUG -DTWOPASS -DMYATOF
LD = $(UBIN)/$(PREFIX)nbcat
LDFLAGS = -Ynbcommap
LD1FLAGS = -Ynbcp1map
LD2FLAGS = -Ynbcp2map
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile
#MAKEFILE = makefile2
 
# Fill in with correct information
 
OBJS = getenv.o version.o fixcall.o stab.o code.o \
	comm1.o cgram.o local.o optim.o pftn.o scan.o trees.o xdefs.o \
	allo.o local2.o match.o order.o reader.o switch.o table.o
 
P1OBJS = getenv.o version.o fixcall.o stab.o code.o \
	comm1.o cgram.o local.o optim.o pftn.o scan.o trees.o xdefs.o
 
P2OBJS = allo.o comm2.o local2.o match.o order.o reader.o switch.o table.o
 
HDRS = caloff.h common.h mac2defs.h macdefs.h manifest.h mfile1.h \
	mfile2.h opdesc.h print.h stab.h treemgr.h treewalk.h error.h
 
FHDRS = float.h
 
#FSRCS = float.c myatof.c #atofn.c #atof.c
FSRCS = float.c atofn.c #myatof.c #atof.c
 
#FOBJS = float.o myatof.o #atofn.o #atof.o
FOBJS = float.o atofn.o #myatof.o #atof.o
 
SRCS = getenv.c version.c fixcall.c stab.c code.c \
	comm1.c cgram.c local.c optim.c pftn.c scan.c trees.c xdefs.c \
	allo.c local2.c match.c order.c reader.c switch.c table.c
 
P1SRCS = getenv.c version.c fixcall.c stab.c code.c \
	comm1.c cgram.y local.c optim.c pftn.c scan.c trees.c xdefs.c
 
P2SRCS = allo.c comm2.c local2.c match.c order.c reader.c switch.c table.c
 
ALLHDR = $(FHDRS) $(HDRS)
 
ALLSRC = $(FSRCS) $(SRCS)
 
ALLOBJ = $(FOBJS) $(OBJS)
 
MAIN = nbccom
#MAIN = nbcp1 nbcp2
 
ALL:	all
 
all:	$(MAIN)
	$(BIN)/echo $(MAIN) is up to date.
 
nbccom:	$(MAKEFILE) $(ALLOBJ)
	$(CC) $(LDFLAGS) $(ALLOBJ) -o nbccom
	$(BIN)/chmod 755 nbccom
	$(BIN)/chgrp system nbccom
	$(BIN)/chown system nbccom
 
nbcp1:	$(MAKEFILE) $(P1OBJS)
	$(CC) $(LD1FLAGS) $(P1OBJS) -o nbcp1
	$(BIN)/chmod 755 nbcp1
	$(BIN)/chgrp system nbcp1
	$(BIN)/chown system nbcp1
 
nbcp2:	$(MAKEFILE) $(P2OBJS)
	$(CC) $(LD2FLAGS) $(P2OBJS) -o nbcp2
	$(BIN)/chmod 755 nbcp2
	$(BIN)/chgrp system nbcp2
	$(BIN)/chown system nbcp2
 
CLEAN:  clean
 
clean:
	$(BIN)/rm -f $(ALLOBJ)
#	$(BIN)/rm -f $(P1OBJS) $(P2OBJS)
 
CLOBBER: clobber
 
clobber: clean
	$(BIN)/rm -f $(MAIN) cgram.c
	$(BIN)/rm -f nbcommap nbcp1map nbcp2map
 
DEPEND: depend
 
#depend: $(P1SRCS) $(P2SRCS) $(HDRS) $(MAKEFILE)
#	$(BIN)/dodep $(CFLAGS) $(MAKEFILE) $(P1SRCS) $(P2SRCS) >dep.out
#	$(BIN)/mv dep.out $(MAKEFILE)
 
depend: $(ALLSRC) $(ALLHDR) $(MAKEFILE)
	$(BIN)/mkdep $(MAKEFILE) >dep.out
	@for i in $(ALLSRC); do \
	$(BIN)/echo "# Source file '$$i'" >> dep.out; \
	$(CPP) $(CPFLAGS) $(CFLAGS) $$i >> dep.out; \
	done;
	$(BIN)/echo "# End of dependencies" >> dep.out;
	$(BIN)/mv dep.out $(MAKEFILE)
 
INSTALL: install
 
install: all
	$(BIN)/cp $(MAIN) $(BIN)
 
# DO NOT DELETE THIS LINE -- the dependencies begin here
# Source file 'float.c'
float.o: float.c
float.o: float.h
# Source file 'atofn.c'
atofn.o: atofn.c
atofn.o: /system/nbinclude/stdio.h
atofn.o: float.h
# Source file 'getenv.c'
getenv.o: getenv.c
getenv.o: /system/nbinclude/timeb.h
# Source file 'version.c'
version.o: version.c
# Source file 'fixcall.c'
fixcall.o: fixcall.c
fixcall.o: mfile1.h
fixcall.o: macdefs.h
fixcall.o: manifest.h
fixcall.o: /system/nbinclude/stdio.h
# Source file 'stab.c'
stab.o: stab.c
stab.o: mfile1.h
stab.o: macdefs.h
stab.o: manifest.h
stab.o: /system/nbinclude/stdio.h
stab.o: /system/nbinclude/types.h
stab.o: /system/nbinclude/a.out.h
# Source file 'code.c'
code.o: code.c
code.o: mfile1.h
code.o: macdefs.h
code.o: manifest.h
code.o: /system/nbinclude/stdio.h
code.o: /system/nbinclude/types.h
code.o: /system/nbinclude/a.out.h
code.o: stab.h
# Source file 'comm1.c'
comm1.o: comm1.c
comm1.o: mfile1.h
comm1.o: macdefs.h
comm1.o: manifest.h
comm1.o: /system/nbinclude/stdio.h
comm1.o: common.h
comm1.o: error.h
comm1.o: treewalk.h
comm1.o: opdesc.h
comm1.o: caloff.h
comm1.o: treemgr.h
# Source file 'cgram.c'
cgram.o: cgram.c
cgram.o: mfile1.h
cgram.o: macdefs.h
cgram.o: manifest.h
cgram.o: /system/nbinclude/stdio.h
# Source file 'local.c'
local.o: local.c
local.o: mfile1.h
local.o: macdefs.h
local.o: manifest.h
local.o: /system/nbinclude/stdio.h
# Source file 'optim.c'
optim.o: optim.c
optim.o: mfile1.h
optim.o: macdefs.h
optim.o: manifest.h
optim.o: /system/nbinclude/stdio.h
# Source file 'pftn.c'
pftn.o: pftn.c
pftn.o: mfile1.h
pftn.o: macdefs.h
pftn.o: manifest.h
pftn.o: /system/nbinclude/stdio.h
# Source file 'scan.c'
scan.o: scan.c
scan.o: mfile1.h
scan.o: macdefs.h
scan.o: manifest.h
scan.o: /system/nbinclude/stdio.h
scan.o: /system/nbinclude/a.out.h
scan.o: /system/nbinclude/ctype.h
# Source file 'trees.c'
trees.o: trees.c
trees.o: mfile1.h
trees.o: macdefs.h
trees.o: manifest.h
trees.o: /system/nbinclude/stdio.h
# Source file 'xdefs.c'
xdefs.o: xdefs.c
xdefs.o: mfile1.h
xdefs.o: macdefs.h
xdefs.o: manifest.h
xdefs.o: /system/nbinclude/stdio.h
# Source file 'allo.c'
allo.o: allo.c
allo.o: mfile2.h
allo.o: macdefs.h
allo.o: mac2defs.h
allo.o: manifest.h
allo.o: /system/nbinclude/stdio.h
# Source file 'local2.c'
local2.o: local2.c
local2.o: mfile2.h
local2.o: macdefs.h
local2.o: mac2defs.h
local2.o: manifest.h
local2.o: /system/nbinclude/stdio.h
local2.o: /system/nbinclude/ctype.h
local2.o: /system/nbinclude/a.out.h
# Source file 'match.c'
match.o: match.c
match.o: mfile2.h
match.o: macdefs.h
match.o: mac2defs.h
match.o: manifest.h
match.o: /system/nbinclude/stdio.h
# Source file 'order.c'
order.o: order.c
order.o: mfile2.h
order.o: macdefs.h
order.o: mac2defs.h
order.o: manifest.h
order.o: /system/nbinclude/stdio.h
# Source file 'reader.c'
reader.o: reader.c
reader.o: mfile2.h
reader.o: macdefs.h
reader.o: mac2defs.h
reader.o: manifest.h
reader.o: /system/nbinclude/stdio.h
reader.o: print.h
# Source file 'switch.c'
switch.o: switch.c
switch.o: /system/nbinclude/stdio.h
switch.o: mfile2.h
switch.o: macdefs.h
switch.o: mac2defs.h
switch.o: manifest.h
switch.o: /system/nbinclude/stdio.h
# Source file 'table.c'
table.o: table.c
table.o: mfile2.h
table.o: macdefs.h
table.o: mac2defs.h
table.o: manifest.h
table.o: /system/nbinclude/stdio.h
# End of dependencies
