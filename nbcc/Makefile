#
# Makefile for nbcc
#
CC = cc
CFLAGS = -O
BINDIR = /system/bin
INSTALL = cp

all:	nbcc

nbcc:	nbcc.c	
	$(CC) $(CFLAGS) -o nbcc nbcc.c
	/bin/chmod 755 nbcc

clean:
	-rm -f *.o

clobber: clean
	-rm -f nbcc core

install: all
	$(INSTALL) nbcc $(BINDIR)
