#~!makefile for nbcc
# Name:  makefile Part No.: _______-____r
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

#ident	"$Id: makefile,v 1.4 1995/10/13 23:00:59 jbev Exp $"

# $Log: makefile,v $
# Revision 1.4  1995/10/13 23:00:59  jbev
# Change mode to 775 from 755.
#
# Revision 1.3  1995/03/28  21:29:35  jbev
# Revised name to makefile, instead of make.mpx.
#
# Revision 1.2  1995/03/13  17:49:59  jbev
# Add Id and Log.
#
#

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
CPFLAGS = -M
CC = $(UBIN)/$(PREFIX)cc
CFLAGS = -DMPX
LD = $(UBIN)/$(PREFIX)nbcat
LDFLAGS = -Ynbccmap
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile

# Fill in with correct information

OBJECTS = nbcc.o

HDRS =

SRCS = nbcc.c

MAIN = nbcc

ALL:	all

all:	$(MAIN)
	$(BIN)/echo $(MAIN) is up to date.

$(MAIN):	$(MAKEFILE) $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(MAIN)
	$(BIN)/chmod 775 $(MAIN)
	$(BIN)/chgrp system $(MAIN)
	$(BIN)/chown system $(MAIN)

CLEAN:  clean

clean:
	$(BIN)/rm -f $(OBJECTS)

CLOBBER: clobber

clobber: clean
	$(BIN)/rm -f $(MAIN)

DEPEND: depend

depend: $(SRCS) $(HDRS) $(MAKEFILE)
	$(BIN)/mkdep $(MAKEFILE) >dep.out
	@for i in $(SRCS); do \
	$(BIN)/echo "# Source file '$$i'" >> dep.out; \
	$(CPP) $(CPFLAGS) $$i >> dep.out; \
	done;
	$(BIN)/echo "# End of dependencies" >> dep.out;
	$(BIN)/mv dep.out $(MAKEFILE)

INSTALL: install

install: all
	$(BIN)/cp $(MAIN) $(BIN)/$(MAIN)
	$(BIN)/cp $(MAIN) $(ROOT)/$(MAIN)

# DO NOT DELETE THIS LINE -- the dependencies begin here
# Source file 'nbcc.c'
nbcc.o: nbcc.c
nbcc.o: /system/nbinclude/param.h
nbcc.o: /system/nbinclude/stdio.h
nbcc.o: /system/nbinclude/fcntl.h
nbcc.o: /system/nbinclude/ctype.h
nbcc.o: /system/nbinclude/signal.h
nbcc.o: /system/nbinclude/dirent.h
nbcc.o: /system/nbinclude/limits.h
nbcc.o: /system/nbinclude/string.h
# End of dependencies
