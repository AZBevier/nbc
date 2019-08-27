# /* makefile */
# 			Makefile for NBCAS/GASM
# 	    (c) Copyright 1990 J B Systems, Morrison, CO
# 			All Rights Reserved
#
DESTDIR		=
INSTDIR		= $(DESTDIR)/system/bin
CC		= /usr/bin/cc
DCC		= /bin/cc.sco
LINT		= /usr/bin/lint
CFLAGS		= $(OPT)
#OPT		= -O -g -DMYATOF -pg
OPT		= -O -DMYATOF
DOPTS		= -O -dos -DDOS
LIBS		=
INSTALL		= /bin/cp
CHMOD		= /bin/chmod
PROGRAM		= nbcas
DPROGRAM	= gasm.exe

HDRS	= defs.h

SRCS 	= main.c macro.c goasm.c parse.c io.c opcode.c pseudo.c symbol.c \
	xref.c float.c myatof.c

CSRCS 	= main.c macro.c goasm.c parse.c io.c opcode.c pseudo.c symbol.c xref.c

OBJS 	= main.o macro.o goasm.o parse.o io.o opcode.o pseudo.o symbol.o \
	xref.o float.o myatof.o

DOBJS 	= main.obj macro.obj goasm.obj parse.obj io.obj opcode.obj pseudo.obj symbol.obj xref.obj

all:	$(PROGRAM)

lint:	$(SRCS)
	rm -f lint.out
	$(LINT) $(SRCS) >lint.out

dos:	$(DPROGRAM)

$(DPROGRAM):    $(DOBJS)
	$(DCC) $(DOPTS) $(LDFLAGS) $(LIBS) -o $@ $(DOBJS)

$(PROGRAM):     $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $(OBJS)

xref.o:	xref.c defs.h

xref.obj:	xref.c defs.h
	$(DCC) $(DOPTS) -c xref.c
	mv xref.o xref.obj

float.o:	float.c float.h

myatof.o:	myatof.c float.h

goasm.o:	goasm.c defs.h

goasm.obj:	goasm.c defs.h
	$(DCC) $(DOPTS) -c goasm.c
	mv goasm.o goasm.obj

io.o:	io.c defs.h

io.obj:	io.c defs.h
	$(DCC) $(DOPTS) -c io.c
	mv io.o io.obj

main.o:		main.c defs.h

main.obj:	main.c defs.h
	$(DCC) $(DOPTS) -c main.c
	mv main.o main.obj

macro.o:	macro.c defs.h

macro.obj:	macro.c defs.h
	$(DCC) $(DOPTS) -c macro.c
	mv macro.o macro.obj

opcode.o:	opcode.c defs.h

opcode.obj:	opcode.c defs.h
	$(DCC) $(DOPTS) -c opcode.c
	mv opcode.o opcode.obj

parse.o:	parse.c defs.h float.h

parse.obj:	parse.c defs.h
	$(DCC) $(DOPTS) -c parse.c
	mv parse.o parse.obj

pseudo.o:	pseudo.c defs.h

pseudo.obj:	pseudo.c defs.h
	$(DCC) $(DOPTS) -c pseudo.c
	mv pseudo.o pseudo.obj

symbol.o:	symbol.c defs.h

symbol.obj:	symbol.c defs.h
	$(DCC) $(DOPTS) -c symbol.c
	mv symbol.o symbol.obj

clean:
	rm -f $(DOBJS) 
	rm -f $(OBJS) a.out core 

clobber:	clean
	rm -f $(PROGRAM)
	rm -f $(DPROGRAM)

install:	all
	$(CHMOD) 755 $(PROGRAM)
	$(INSTALL) $(PROGRAM) $(INSTDIR)

print:;		@$(PRINT) $(HDRS) $(SRCS) Makefile
