#~!Makefile for nbyacc
# Name:  Makefile Part No.: _______-____r
#
# Copyright 1994 - J B Systems, Morrison, CO
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

#ident	"@(#)Make:nbyacc/Makefile	1.0"

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
CFLAGS = -N -DMPX #Do not output reg-reg floats
LD = $(UBIN)/$(PREFIX)nbcat
LDFLAGS = -Ynbyaccmap
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile

# Fill in with correct information

OBJECTS = y1.o y2.o y3.o y4.o

HDRS =

SRCS = y1.c y2.c y3.c y4.c

MAIN = nbyacc

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

# DO NOT DELETE THIS LINE -- the dependencies begin here
