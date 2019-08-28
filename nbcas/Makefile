#~!Makefile for nbcas
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

#ident	"$Id: Makefile,v 1.3 2019/02/24 23:41:20 jbev Exp $"

# $Log: Makefile,v $
# Revision 1.3  2019/02/24 23:41:20  jbev
# Change suffix to .s from .S
#
# Revision 1.2  1995/03/28 22:10:35  jbev
# Need -C option for assembler.
#
# Revision 1.1  1995/03/28  21:52:58  jbev
# Initial revision
#
#

# Make parameters when running on UNIX

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
CFLAGS =
LD = $(UBIN)/$(PREFIX)nbcat
LDFLAGS = -Ynbcasmap
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = Makefile

# Fill in with correct information

OBJECTS = nbcas.o

HDRS =

PRE = mpxpre

SRCS = nbcas.s

MAIN = nbcas

ALL:	all

all:	$(PRE) $(MAIN)
	$(BIN)/echo $(MAIN) is up to date.

$(MAIN):	$(MAKEFILE) $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(MAIN)
	$(BIN)/chmod 755 $(MAIN)
#	$(BIN)/chgrp system $(MAIN)
#	$(BIN)/chown system $(MAIN)

CLEAN:  clean

clean:
	$(BIN)/rm -f $(OBJECTS)

CLOBBER: clobber

clobber: clean
	$(BIN)/rm -f $(MAIN)

DEPEND: depend

depend: $(SRCS) $(PRE) $(MAKEFILE)
	$(BIN)/mkdep $(MAKEFILE) >dep.out;
	echo "nbcas.o: nbcas.s $(PRE)" >> dep.out;
	echo "	$(CC) $(CFLAGS) -C -P$(PRE) nbcas.s" >> dep.out;
	$(BIN)/echo "# End of dependencies" >> dep.out;
	$(BIN)/mv dep.out $(MAKEFILE)

INSTALL: install

install: all
	$(BIN)/cp $(MAIN) $(BIN)/$(MAIN)

#nbcas.o: nbcas.s $(PRE)
#	$(CC) $(CFLAGS) -P$(PRE) nbcas.s

# DO NOT DELETE THIS LINE -- the dependencies begin here
nbcas.o: nbcas.s mpxpre
	/system/bin/nbcc -C -Pmpxpre nbcas.s
# End of dependencies
