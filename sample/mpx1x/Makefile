#~!Makefile for SAMPLE
# Name:  Makefile Part No.: _______-____r
#
# make setup		# creates make directory & copies files
# make depend 		# adds dependencies to makefile
# make clean		# deletes objects
# make clobber		# deletes load module and objects
# make delete		# removes make directory & files
# make all		# makes everything
# make			# makes everything, defaults to make all
# make install		# does make all, then copies load module
#			# to system directory
# do a make 'DEBUG=' to not do debugging
# do a make 'LIST=' to not do listings
# do a make 'LIST=' 'DEBUG=' to not get either

#ident	"@(#)Make:SAMPLE/Makefile	1.0"

# Make parameters when running on MPX

ROOT = /system/system
TARGET = /system/system
VOL = /system
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
DEBUG = -G -QC
LIST = -L
CFLAGS = -V $(LIST) $(DEBUG) -DMPX
LD = $(UBIN)/$(PREFIX)nbcat
YACC = $(YBIN)/$(PREFIX)yacc
YFLAGS =
MAKEFILE = makefile
MAKEDIR = sample

# define all sources for depend
SRCS = dcat.c ucat.c fixer.c obd.c caid.c summer.c

# define all headers depend
HDRS = caid.h

# loadmodule names
MAINS = dcat ucat fixer obd caid summer

ALL:	all

# build everything
all:	$(MAINS)
	$(BIN)/echo $(MAINS) are up to date.

SETUP:	setup

setup:	doall all
	$(BIN)/echo Setup processing complete.

doall:
	$(BIN)/echo Do dependencies.
	$(BIN)/dodep $(CPFLAGS) $(MAKEFILE) $(SRCS) >dep.out
	$(BIN)/mv dep.out $(MAKEFILE)
	$(BIN)/echo Now do make clobber.
	$(BIN)/make clobber
	$(BIN)/echo Now do make all.

#build dcat
dcat:	dcat.o
	$(CC) $(LDFLAGS) -o dcat dcat.o #-ydcatmap
	$(BIN)/chmod 775 dcat
#	$(BIN)/chgrp system dcat
#	$(BIN)/chown system dcat

#build ucat
ucat:	ucat.o
	$(CC) $(LDFLAGS) -o ucat ucat.o #-yucatmap
	$(BIN)/chmod 775 ucat
#	$(BIN)/chgrp system ucat
#	$(BIN)/chown system ucat

#build fixer
fixer:	fixer.o
	$(CC) $(LDFLAGS) -o fixer fixer.o #-yfixermap
	$(BIN)/chmod 775 fixer
#	$(BIN)/chgrp system fixer
#	$(BIN)/chown system fixer

#build obd
obd:	obd.o
	$(CC) $(LDFLAGS) -o obd obd.o #-yobdmap
	$(BIN)/chmod 775 obd
#	$(BIN)/chgrp system obd
#	$(BIN)/chown system obd

#build caid
caid:	caid.o
	$(CC) $(LDFLAGS) -o caid $(BIN)/c.srte.o caid.o #-ycaidmap
	$(BIN)/chmod 775 caid
#	$(BIN)/chgrp system caid
#	$(BIN)/chown system caid

#build summer
summer:	summer.o
	$(CC) $(LDFLAGS) -o summer summer.o #-ysummermap
	$(BIN)/chmod 775 summer
#	$(BIN)/chgrp system summer
#	$(BIN)/chown system summer

CLEAN:  clean

clean:				# delete object files
#	following line(s) must start with a TAB character
	$(BIN)/rm -f \
	dcat.o ucat.o fixer.o obd.o caid.o summer.o \
	dcat.l ucat.l fixer.l obd.l caid.l summer.l

CLOBBER: clobber

clobber: clean			# delete main from current directory
#	following line(s) must start with a TAB character
	$(BIN)/rm -f $(MAINS) \
	dcatmap ucatmap fixermap obdmap caidmap summermap

REMOVE: remove

remove:
	$(BIN)/rm -f $(VOL)/$(MAKEDIR)/*
	$(BIN)/rmdir $(VOL)/$(MAKEDIR)

DEPEND: depend

depend: $(SRCS) $(HDRS) $(MAKEFILE)	# generate dependencies
#	following line(s) must start with a TAB character
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
#	following line(s) must start with a TAB character
	$(BIN)/cp $(MAIN) $(BIN)
#	$(BIN)/cp $(MAIN) $(SBIN)

# DO NOT DELETE THIS LINE -- the dependencies begin here
